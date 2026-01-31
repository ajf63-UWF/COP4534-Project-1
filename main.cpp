#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "PasswordUtils.hpp"

bool isAllLetters(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream in("names.txt");
    std::ofstream raw("rawdata.txt");
    std::ofstream enc("encrypteddata.txt");

    if (!in || !raw || !enc) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    const std::string key = "jones";
    std::string line;

    while (std::getline(in, line)) {
        std::istringstream iss(line);

        std::string firstCol;
        if (!(iss >> firstCol)) continue; // Skip empty lines

        if (!isAllLetters(firstCol)) continue;

        std::string password = generatePassword();
        std::string encryptedPassword = vigenereEncrypt(password, key);

        raw << firstCol << " " << password << "\n";
        enc << firstCol << " " << encryptedPassword << "\n";
    }

    std::cout << "Done.\n";
    return 0;
}