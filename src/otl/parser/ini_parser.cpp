//
// Created by kevin on 2022/9/24.
//

#include "otl/parser/ini_parser.h"

namespace otl {

    IniSection::self& IniSection::insert(const std::string& key, const std::string& value) {
        m_map_section[key] = value;
        return *this;
    }

    IniSection::self& IniSection::remove(const std::string& key) {
        auto it = m_map_section.find(key);
        if (it != m_map_section.end()) {
            m_map_section.erase(it);
        }
        return *this;
    }

    bool IniSection::has_key(const std::string& key) const {
        auto iter = m_map_section.find(key);
        return iter != m_map_section.end();
    }

    bool IniSection::to_bool(const std::string& key, bool default_val)  {
        if (!has_key(key)) return default_val;
        std::string val = m_map_section[key];
        for (auto& ch : val) ch = std::tolower(ch);
        if (val == "true") return true;
        return false;
    }

    std::string IniSection::to_string(const std::string& key, std::string default_val)  {
        if (!has_key(key)) return default_val;
        std::string val = m_map_section[key];
        return val;
    }

    float IniSection::to_float(const std::string& key, float default_val)  {
        if (!has_key(key)) return default_val;
        std::string val = m_map_section[key];
        float result = (float)std::atof(val.c_str());
        return result;
    }

    int IniSection::to_int(const std::string& key, int default_val)  {
        int result = static_cast<int>((to_float(key, default_val)));
        return result;
    }

    std::string& IniSection::operator[](const std::string& key) {
        return m_map_section[key];
    }

    std::vector<std::string> IniSection::keys() const {
        std::vector<std::string> keys;

        auto iter = m_map_section.begin();
        for (; iter != m_map_section.end(); ++iter) {
            keys.emplace_back(iter->first);
        }
        return keys;
    }

    std::unordered_map<std::string, std::string>::iterator IniSection::begin()  {
        return m_map_section.begin();
    }

    std::unordered_map<std::string, std::string>::iterator  IniSection::end()  {
        return m_map_section.end();
    }

    IniParser::IniParser(const std::string ini_path) {
        this->load(ini_path);
    }

    void IniParser::load(const std::string& ini_path) {
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

    IniSection& IniParser::append_section(const std::string& sec_name) {
        auto it = m_map_sections.find(sec_name);
        if (it == m_map_sections.end()) {
            IniSection section;
            m_map_sections[sec_name] = section;
        }
        return m_map_sections[sec_name];
    }

    void IniParser::remove_section(const std::string& sec_name) {
        auto it = m_map_sections.find(sec_name);
        if (it != m_map_sections.end()) {
            m_map_sections.erase(it);
        }
    }

    bool IniParser::has_section(const std::string& key) {
        auto iter = m_map_sections.find(key);
        return iter != m_map_sections.end();
    }

    IniSection& IniParser::get(const std::string& key) {
        return this->operator[](key);
    }

    IniSection& IniParser::operator[](const std::string& key) {
        return m_map_sections[key];
    }

    std::vector<std::string> IniParser::keys() const {
        std::vector<std::string> keys;

        auto iter = m_map_sections.begin();
        for (; iter != m_map_sections.end(); ++iter) {
            keys.emplace_back(iter->first);
        }
        return keys;
    }

    std::string IniParser::trim(const std::string& line) {
        if(line.size() <= 0) return line;

        size_t begin = line.find_first_not_of(' ');
        size_t end = line.find_last_not_of(' ');

        return line.substr(begin, end - begin + 1);
    }

    bool IniParser::save(const std::string& ini_path)  {
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

}