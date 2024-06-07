#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>

class TablaHashLineal {
private:
    std::vector<std::pair<uint64_t, Usuario>> tableID;
    std::vector<std::pair<std::string, Usuario>> tableName;
    int numBuckets;

    int hashFunctionID(uint64_t key) {
        return key % numBuckets;
    }

    int hashFunctionName(const std::string& key) {
        std::hash<std::string> hash_fn;
        return hash_fn(key) % numBuckets;
    }

public:
    TablaHashLineal(int size) : numBuckets(size), 
                                tableID(size, {0, Usuario()}),
                                tableName(size, {"", Usuario()}) {}

    void insert(uint64_t key, Usuario value) {
        int hashIndex = hashFunctionID(key);
        while (tableID[hashIndex].first != 0) {
            hashIndex = (hashIndex + 1) % numBuckets;
        }
        tableID[hashIndex] = {key, value};
    }

    void insert(const std::string& key, Usuario value) {
        int hashIndex = hashFunctionName(key);
        while (!tableName[hashIndex].first.empty()) {
            hashIndex = (hashIndex + 1) % numBuckets;
        }
        tableName[hashIndex] = {key, value};
    }

    Usuario* search(uint64_t key) {
        int hashIndex = hashFunctionID(key);
        while (tableID[hashIndex].first != 0) {
            if (tableID[hashIndex].first == key) {
                return &tableID[hashIndex].second;
            }
            hashIndex = (hashIndex + 1) % numBuckets;
        }
        return nullptr;
    }

    Usuario* search(const std::string& key) {
        int hashIndex = hashFunctionName(key);
        while (!tableName[hashIndex].first.empty()) {
            if (tableName[hashIndex].first == key) {
                return &tableName[hashIndex].second;
            }
            hashIndex = (hashIndex + 1) % numBuckets;
        }
        return nullptr;
    }
};