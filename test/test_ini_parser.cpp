//
// Created by kevin on 2022/9/23.
//

#include <string>
#include <iostream>
#include <sstream>
#include <regex>

#include "otl/parser/ini_parser.h"

int main() {
    otl::IniParser parser("./config.ini");
    std::cout<<parser<<std::endl;
    return 0;
}