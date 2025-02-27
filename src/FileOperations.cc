/*
Jakub Ciarcinski, Eryk Jakubowski
Functions for operations on files.
*/

#include "../include/FileOperations.h"

void saveCarDataToJson( const std::vector<CarData> &cars_data, const std::string& filename ){
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    rapidjson::Value cars( rapidjson::kArrayType );
    for ( const auto& car_data : cars_data ){
        rapidjson::Value car( rapidjson::kObjectType );

        rapidjson::Value points( rapidjson::kArrayType );
        for ( const auto& point : car_data.points ){
            rapidjson::Value point_value( rapidjson::kObjectType );
            point_value.AddMember( "x", point.x, allocator );
            point_value.AddMember( "y", point.y, allocator );
            points.PushBack( point_value, allocator );
        }
        car.AddMember( "points", points, allocator );

        rapidjson::Value pos( rapidjson::kObjectType );
        pos.AddMember( "x", car_data.pos.x, allocator );
        pos.AddMember( "y", car_data.pos.y, allocator );
        car.AddMember( "pos", pos, allocator );

        car.AddMember( "car_density", car_data.car_density, allocator );
        car.AddMember( "car_friction", car_data.car_friction, allocator );

        rapidjson::Value wheels_indexes( rapidjson::kArrayType );
        for ( const auto& index : car_data.wheels_indexes ){
            wheels_indexes.PushBack( index, allocator );
        }
        car.AddMember( "wheels_indexes", wheels_indexes, allocator );

        rapidjson::Value wheels_radiuses( rapidjson::kArrayType );
        for ( const auto& radius : car_data.wheels_radiuses ){
            wheels_radiuses.PushBack( radius, allocator );
        }
        car.AddMember( "wheels_radiuses", wheels_radiuses, allocator );

        car.AddMember( "wheels_density", car_data.wheels_density, allocator );
        car.AddMember( "wheels_friction", car_data.wheels_friction, allocator );
        car.AddMember( "max_speed", car_data.max_speed, allocator );
        car.AddMember( "motor_power", car_data.motor_power, allocator );

        cars.PushBack( car, allocator );
    }
    doc.AddMember( "cars", cars, allocator );

    std::ofstream ofs( filename );
    rapidjson::OStreamWrapper osw( ofs );
    rapidjson::Writer<rapidjson::OStreamWrapper> writer( osw );
    doc.Accept( writer );
}


void loadCarDataFromJson( std::vector<CarData> &cars_data, const std::string& filename ){
    std::ifstream ifs( filename );
    if ( !ifs.is_open() ){
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        return;
    }

    // Read the entire file into a string.
    std::string json_str( ( std::istreambuf_iterator<char>( ifs ) ), std::istreambuf_iterator<char>() );

    rapidjson::Document doc;
    doc.Parse( json_str.c_str() );

    if ( doc.HasParseError() ){
        std::cerr << "Error: JSON parse error." << std::endl;
        return;
    }

    const rapidjson::Value& cars = doc["cars"];
    if ( !cars.IsArray() ){
        std::cerr << "Error: 'cars' is not an array." << std::endl;
        return;
    }

    for ( rapidjson::SizeType i = 0; i < cars.Size(); i++ ){
        const rapidjson::Value& car = cars[i];
        CarData car_data;

        // Parsing car data.
        if ( car.HasMember( "points" ) && car["points"].IsArray() ){
            const rapidjson::Value& points = car["points"];
            for ( rapidjson::SizeType j = 0; j < points.Size(); j++ ){
                const rapidjson::Value& point_value = points[j];
                b2Vec2 point;
                if ( point_value.HasMember( "x" ) && point_value.HasMember( "y" ) ){
                    point.x = point_value["x"].GetFloat();
                    point.y = point_value["y"].GetFloat();
                    car_data.points.push_back( point );
                }
            }
        }

        if ( car.HasMember( "pos" ) && car["pos"].IsObject() ){
            const rapidjson::Value& pos = car["pos"];
            if ( pos.HasMember( "x" ) && pos.HasMember( "y" ) ){
                car_data.pos.x = pos["x"].GetFloat();
                car_data.pos.y = pos["y"].GetFloat();
            }
        }

        if ( car.HasMember( "car_density" ) && car.HasMember( "car_friction" ) &&
            car.HasMember( "wheels_indexes" ) && car.HasMember( "wheels_radiuses" ) &&
            car.HasMember( "wheels_density" ) && car.HasMember( "wheels_friction" ) &&
            car.HasMember( "max_speed" ) && car.HasMember( "motor_power" ) ){
            car_data.car_density = car["car_density"].GetFloat();
            car_data.car_friction = car["car_friction"].GetFloat();
            const rapidjson::Value& wheels_indexes = car["wheels_indexes"];
            const rapidjson::Value& wheels_radiuses = car["wheels_radiuses"];
            for ( rapidjson::SizeType j = 0; j < wheels_indexes.Size(); j++ ){
                car_data.wheels_indexes.push_back( wheels_indexes[j].GetInt() );
                car_data.wheels_radiuses.push_back( wheels_radiuses[j].GetFloat() );
            }
            car_data.wheels_density = car["wheels_density"].GetFloat();
            car_data.wheels_friction = car["wheels_friction"].GetFloat();
            car_data.max_speed = car["max_speed"].GetFloat();
            car_data.motor_power = car["motor_power"].GetFloat();
        }

        cars_data.push_back( car_data );
    }
}

std::vector<std::string> getFilesInDirectory( const std::string& directory ){
    std::vector<std::string> files;
    for ( const auto& entry : std::filesystem::directory_iterator( directory ) ){
        files.push_back( entry.path().filename().string() );
    }
    return files;
}