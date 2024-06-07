#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <list>
#include <iostream>
#include "TablaHashingAbierto.h"
#include "TablaHashLineal.h"
#include "TablaHashQuadratic.h"
#include "TablaHashDoble.h"

struct Usuario {
    std::string university;
    uint64_t userID;
    std::string userName;
    int numberTweets;
    int friendsCount;
    int followersCount;
    std::string createdAt;
};

struct NodoHash {
    uint64_t key;
    Usuario value;
    NodoHash* next;
};

struct NodoHashUserName {
    std::string key;
    Usuario value;
    NodoHashUserName* next;
};
