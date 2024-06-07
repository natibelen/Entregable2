#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>

class TablaHashingAbierto {
private:
    std::vector<std::list<NodoHash>> tableID;
    std::vector<std::list<NodoHashUserName>> tableName;
    int numBuckets;

    int hashFunctionID(uint64_t key) {
        return key % numBuckets;
    }

    int hashFunctionName(const std::string& key) {
        std::hash<std::string> hash_fn;
        return hash_fn(key) % numBuckets;
    }

public:
    TablaHashingAbierto(int size) : numBuckets(size) {
        tableID.resize(numBuckets);
        tableName.resize(numBuckets);
    }

    void insert(uint64_t key, Usuario value) {
        int hashIndex = hashFunctionID(key);
        tableID[hashIndex].push_back({key, value, nullptr});
    }

    void insert(const std::string& key, Usuario value) {
        int hashIndex = hashFunctionName(key);
        tableName[hashIndex].push_back({key, value, nullptr});
    }

    Usuario* search(uint64_t key) {
        int hashIndex = hashFunctionID(key);
        for (auto& node : tableID[hashIndex]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }

    Usuario* search(const std::string& key) {
        int hashIndex = hashFunctionName(key);
        for (auto& node : tableName[hashIndex]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }
};