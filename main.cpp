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
#include "TablaHashSTL.h"
#include "Struct.h"

std::vector<Usuario> readCSV(const std::string& filename, size_t limit = SIZE_MAX) {
    std::vector<Usuario> data;
    std::ifstream file(filename);

    size_t count = 0;
    while (std::getline(file, line) && count < limit) {
        std::stringstream ss(line);
        std::string token;

        Usuario user;

        std::getline(ss, user.university, ',');
        std::getline(ss, token, ',');
        user.userID = std::stoull(token);
        std::getline(ss, user.userName, ',');
        std::getline(ss, token, ',');
        user.numberTweets = std::stoi(token);
        std::getline(ss, token, ',');
        user.friendsCount = std::stoi(token);
        std::getline(ss, token, ',');
        user.followersCount = std::stoi(token);
        std::getline(ss, user.createdAt, ',');

        data.push_back(user);
        count++;
    }

    file.close();
    return data;
}

int main() {
  std::cout << "Hola!\n";
}