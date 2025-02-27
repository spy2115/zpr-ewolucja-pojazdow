/*
Eryk Jakubowski
Various helper functions used in project.
*/

#include "../include/Utils.h"

bool isInteger( const std::string& str ){
    std::istringstream iss( str );
    int value;
    iss >> std::noskipws >> value;
    return iss.eof() && !iss.fail();
}

bool isFloat( const std::string& str ){
    std::istringstream iss( str );
    float value;
    iss >> std::noskipws >> value;
    return iss.eof() && !iss.fail();
}

float randomFloatGenerator( float min, float max ){
    static std::mt19937 gen( SEED );
    std::uniform_real_distribution<float> dis( min, max );
	return dis( gen );
}

float randomNormalFloatGenerator( float mean, float stddev ){
    static std::mt19937 gen( SEED );
    std::normal_distribution<float> dis( mean, stddev );
    return dis( gen );
}