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
    std::cout<<"origin: " << parser << std::endl;
    parser.append_section("fancy").insert("fancy_age", "15").insert("fancy_weight", "88.8").
    insert("fancy_name", "kevin");

    std::cout << "after insert: " << parser << std::endl;

    std::cout << "lr: " << parser["train"].to_int("lr") << std::endl;
    std::cout << "int: " << parser["test"].to_int("int") << std::endl;
    std::cout<< "fancy name: " << parser["fancy"].to_string("fancy_name") << std::endl;

    parser.save("new.ini");

    return 0;
}