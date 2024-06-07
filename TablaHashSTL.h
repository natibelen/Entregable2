#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>
#include <unordered_map>

class TablaHashSTL {
private:
    std::unordered_map<uint64_t, Usuario> tableID;
    std::unordered_map<std::string, Usuario> tableName;

public:
    void insert(uint64_t key, Usuario value) {
        tableID[key] = value;
    }

    void insert(const std::string& key, Usuario value) {
        tableName[key] = value;
    }

    Usuario* search(uint64_t key) {
        auto it = tableID.find(key);
        if (it != tableID.end()) {
            return &it->second;
        }
        return nullptr;
    }

    Usuario* search(const std::string& key) {
        auto it = tableName.find(key);
        if (it != tableName.end()) {
            return &it->second;
        }
        return nullptr;
    }
};