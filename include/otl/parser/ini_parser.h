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

        self& insert(const std::string& key, const std::string& value) {
            m_map_section[key] = value;
            return *this;
        }

        self& remove(const std::string& key) {
            auto it = m_map_section.find(key);
            if (it != m_map_section.end()) {
                m_map_section.erase(it);
            }
            return *this;
        }

        bool has_key(const std::string& key) const {
            auto iter = m_map_section.find(key);
            return iter != m_map_section.end();
        }

        bool to_bool(const std::string& key, bool default_val = false)  {
            if (!has_key(key)) return default_val;
            std::string val = m_map_section[key];
            for (auto& ch : val) ch = std::tolower(ch);
            if (val == "true") return true;
            return false;
        }

        std::string to_string(const std::string& key, std::string default_val = "")  {
            if (!has_key(key)) return default_val;
            std::string val = m_map_section[key];
            return val;
        }

        float to_float(const std::string& key, float default_val = 0)  {
            if (!has_key(key)) return default_val;
            std::string val = m_map_section[key];
            float result = (float)std::atof(val.c_str());
            return result;
        }

        int to_int(const std::string& key, int default_val = 0)  {
            return int(to_float(key, default_val));
        }

        std::string& operator[](const std::string& key) {
            return m_map_section[key];
        }

        std::vector<std::string> keys() const {
            std::vector<std::string> keys;

            auto iter = m_map_section.begin();
            for (; iter != m_map_section.end(); ++iter) {
                keys.emplace_back(iter->first);
            }
            return keys;
        }

        friend  class IniParser;

    private:
        std::unordered_map<std::string, std::string>::iterator begin()  {
            return m_map_section.begin();
        }

        std::unordered_map<std::string, std::string>::iterator  end()  {
            return m_map_section.end();
        }


        std::unordered_map<std::string, std::string> m_map_section;
    };

    class IniParser {
    public:
        IniParser() = default;

        ~IniParser() = default;

        explicit IniParser(const std::string ini_path) {
            this->load(ini_path);
        }

        void load(const std::string& ini_path) {
            std::ifstream in(ini_path);
            if (!in.is_open()) {
                OTL_LOG(otl::LOG_ERROR) << "Open file " << ini_path <<" failed." << eject;
            }
#define FORMAT_ERROR_LOG OTL_LOG(LOG_ERROR) << "Format is wrong in file " << ini_path \
                    << " line at: " << line_count << eject;

            std::string line;
            int line_count = 0;
            std::string temp_key;
            while(std::getline(in, line)) {
                ++line_count;

                line = trim(line);
                if (line.size() <= 0) continue;//empty line
                size_t size = line.size();

                if ((line[0] == '#') || (line[0] == ';')) continue; // annotation

                if ((line[0] == '[') && (line[size - 1] != ']')) {
                    FORMAT_ERROR_LOG;
                }

                if ((line[0] == '[') && (line[size - 1] == ']')) {
                    //Section part [name]
                    size_t begin = line.find_first_not_of('[');
                    size_t end = line.find_last_not_of(']');
                    if(begin >= end) {
                        FORMAT_ERROR_LOG;
                    }
                    temp_key = line.substr(begin, end - begin + 1);

                    if(!has_section(temp_key)){
                        IniSection section;
                        m_map_sections[temp_key] = section;
                    }

                } else {
                    // section content
                    auto splits = otl::Split(line, "=");
                    if (splits.size() <= 1){
                        FORMAT_ERROR_LOG;
                    }
                    m_map_sections[temp_key].insert(splits[0], splits[1]);
                }
            }
#undef FORMAT_ERROR_LOG
        }

        IniSection& append_section(const std::string& sec_name) {
            auto it = m_map_sections.find(sec_name);
            if (it == m_map_sections.end()) {
                IniSection section;
                m_map_sections[sec_name] = section;
            }
            return m_map_sections[sec_name];
        }

        void remove_section(const std::string& sec_name) {
            auto it = m_map_sections.find(sec_name);
            if (it != m_map_sections.end()) {
                m_map_sections.erase(it);
            }
        }

        bool has_section(const std::string& key) {
            auto iter = m_map_sections.find(key);
            return iter != m_map_sections.end();
        }

        IniSection& get(const std::string& key) {
            return this->operator[](key);
        }

        IniSection& operator[](const std::string& key) {
            return m_map_sections[key];
        }

        std::vector<std::string> keys() const {
            std::vector<std::string> keys;

            auto iter = m_map_sections.begin();
            for (; iter != m_map_sections.end(); ++iter) {
                keys.emplace_back(iter->first);
            }
            return keys;
        }

        static std::string trim(const std::string& line) {
            if(line.size() <= 0) return line;

            size_t begin = line.find_first_not_of(' ');
            size_t end = line.find_last_not_of(' ');

            return line.substr(begin, end - begin + 1);
        }

        bool save(const std::string& ini_path)  {
            std::ofstream out(ini_path);
            if (!out.is_open()) {
                OTL_LOG(LOG_ERROR) <<  "Create file " << ini_path << " failed." << eject;
                return false;
            }
            for (auto& pair : m_map_sections) {
                 const std::string& name = pair.first;
                 out << "[" << name << "]" << std::endl;
                 IniSection& section = pair.second;
                for (const auto& pair_in_sec : section) {
                    out << pair_in_sec.first << " = " << pair_in_sec.second << std::endl;
                }
            }
            return true;
        }

    private:
        std::unordered_map<std::string, IniSection> m_map_sections;
    };
}
 std::ostream& operator<<(std::ostream& out,  otl::IniSection& section){
    std::vector<std::string> keys = section.keys();

    for (int i = 0; i < keys.size(); ++i) {
        out << keys[i] << " = " << section.to_string(keys[i]) << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, otl::IniParser& parser) {
    std::vector<std::string> keys = parser.keys();
    for (int i = 0; i < keys.size(); ++i) {
        out << "[" << keys[i] << "]" <<std::endl;
        out << parser[keys[i]];
    }

    return out;
}
#endif //OTL_INIPARSER_H
