/*
Jakub Ciarcinski, Eryk Jakubowski
Functions for operations on files.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/ostreamwrapper.h"
#include "./Car.h"

void saveCarDataToJson( const std::vector<CarData> &car_data, const std::string& filename );

void loadCarDataFromJson( std::vector<CarData> &cars_data, const std::string& filename );

std::vector<std::string> getFilesInDirectory( const std::string& directory );