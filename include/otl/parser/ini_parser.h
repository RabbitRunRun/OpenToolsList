//
// Created by kevin on 2022/9/23.
//

#ifndef OTL_INIPARSER_H
#define OTL_INIPARSER_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <regex>

#include "otl/utils/except.h"
#include "otl/utils/log.h"

namespace otl {
    class IniSection {
    public:
        using self = IniSection;

        IniSection() = default;
        ~IniSection() = default;

        self& insert(const std::string& key, const std::string& value);

        self& remove(const std::string& key);

        bool has_key(const std::string& key) const;

        bool to_bool(const std::string& key, bool default_val = false);

        std::string to_string(const std::string& key, std::string default_val = "");

        float to_float(const std::string& key, float default_val = 0);

        int to_int(const std::string& key, int default_val = 0);

        std::string& operator[](const std::string& key);

        std::vector<std::string> keys() const;

        friend  class IniParser;

    private:
        std::unordered_map<std::string, std::string>::iterator begin();

        std::unordered_map<std::string, std::string>::iterator  end();

    private:
        std::unordered_map<std::string, std::string> m_map_section;
    };

    class IniParser {
    public:
        IniParser() = default;

        ~IniParser() = default;

        explicit IniParser(const std::string ini_path);

        void load(const std::string& ini_path);

        IniSection& append_section(const std::string& sec_name);

        void remove_section(const std::string& sec_name);

        bool has_section(const std::string& key);

        IniSection& get(const std::string& key);

        IniSection& operator[](const std::string& key);

        std::vector<std::string> keys() const;

        static std::string trim(const std::string& line);

        bool save(const std::string& ini_path);

    private:
        std::unordered_map<std::string, IniSection> m_map_sections;
    };
}
 static inline std::ostream& operator<<(std::ostream& out,  otl::IniSection& section){
    std::vector<std::string> keys = section.keys();

    for (int i = 0; i < keys.size(); ++i) {
        out << keys[i] << " = " << section.to_string(keys[i]) << std::endl;
    }
    return out;
}

static inline std::ostream& operator<<(std::ostream& out, otl::IniParser& parser) {
    std::vector<std::string> keys = parser.keys();
    for (int i = 0; i < keys.size(); ++i) {
        out << "[" << keys[i] << "]" <<std::endl;
        out << parser[keys[i]];
    }

    return out;
}
#endif //OTL_INIPARSER_H
