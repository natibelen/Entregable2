#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>

class TablaHashQuadratic {
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
    TablaHashQuadratic(int size) : numBuckets(size), tableID(size, {0, Usuario()}), tableName(size, {"", Usuario()}) {}

    void insert(uint64_t key, Usuario value) {
        int hashIndex = hashFunctionID(key);
        int i = 1;
        while (tableID[hashIndex].first != 0) {
            hashIndex = (hashIndex + i * i) % numBuckets;
            i++;
        }
        tableID[hashIndex] = {key, value};
    }

    void insert(const std::string& key, Usuario value) {
        int hashIndex = hashFunctionName(key);
        int i = 1;
        while (!tableName[hashIndex].first.empty()) {
            hashIndex = (hashIndex + i * i) % numBuckets;
            i++;
        }
        tableName[hashIndex] = {key, value};
    }

    Usuario* search(uint64_t key) {
        int hashIndex = hashFunctionID(key);
        int i = 1;
        while (tableID[hashIndex].first != 0) {
            if (tableID[hashIndex].first == key) {
                return &tableID[hashIndex].second;
            }
            hashIndex = (hashIndex + i * i) % numBuckets;
            i++;
        }
        return nullptr;
    }

    Usuario* search(const std::string& key) {
        int hashIndex = hashFunctionName(key);
        int i = 1;
        while (!tableName[hashIndex].first.empty()) {
            if (tableName[hashIndex].first == key) {
                return &tableName[hashIndex].second;
            }
            hashIndex = (hashIndex + i * i) % numBuckets;
            i++;
        }
        return nullptr;
    }
};