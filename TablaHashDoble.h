#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>

class TablaHashDoble {
private:
    std::vector<std::pair<uint64_t, Usuario>> tableID;
    std::vector<std::pair<std::string, Usuario>> tableName;
    int numBuckets;

    int hashFunctionID1(uint64_t key) {
        return key % numBuckets;
    }

    int hashFunctionID2(uint64_t key) {
        return 1 + (key % (numBuckets - 1));
    }

    int hashFunctionName1(const std::string& key) {
        std::hash<std::string> hash_fn;
        return hash_fn(key) % numBuckets;
    }

    int hashFunctionName2(const std::string& key) {
        std::hash<std::string> hash_fn;
        return 1 + (hash_fn(key) % (numBuckets - 1));
    }

public:
    TablaHashDoble(int size) : numBuckets(size), tableID(size, {0, Usuario()}), tableName(size, {"", Usuario()}) {}

    void insert(uint64_t key, Usuario value) {
        int hashIndex = hashFunctionID1(key);
        int stepSize = hashFunctionID2(key);
        while (tableID[hashIndex].first != 0) {
            hashIndex = (hashIndex + stepSize) % numBuckets;
        }
        tableID[hashIndex] = {key, value};
    }

    void insert(const std::string& key, Usuario value) {
        int hashIndex = hashFunctionName1(key);
        int stepSize = hashFunctionName2(key);
        while (!tableName[hashIndex].first.empty()) {
            hashIndex = (hashIndex + stepSize) % numBuckets;
        }
        tableName[hashIndex] = {key, value};
    }

    Usuario* search(uint64_t key) {
        int hashIndex = hashFunctionID1(key);
        int stepSize = hashFunctionID2(key);
        while (tableID[hashIndex].first != 0) {
            if (tableID[hashIndex].first == key) {
                return &tableID[hashIndex].second;
            }
            hashIndex = (hashIndex + stepSize) % numBuckets;
        }
        return nullptr;
    }

    Usuario* search(const std::string& key) {
        int hashIndex = hashFunctionName1(key);
        int stepSize = hashFunctionName2(key);
        while (!tableName[hashIndex].first.empty()) {
            if (tableName[hashIndex].first == key) {
                return &tableName[hashIndex].second;
            }
            hashIndex = (hashIndex + stepSize) % numBuckets;
        }
        return nullptr;
    }
};