#include <iostream>
#include <fstream>
#include "PasswordUtils.hpp"

int main() {
    std::ifstream in("names.txt");
    std::ofstream raw("rawdata.txt");
    std::ofstream enc("encrypteddata.txt");

    if (!in || !raw || !enc) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    const std::string key = "jones";
    std::string name;

    while (in >> name) {
        std::string password = generatePassword();
        std::string encryptedPassword = vigenereEncrypt(password, key);

        raw << name << " " << password << "\n";
        enc << name << " " << encryptedPassword << "\n";
    }

    std::cout << "Done.\n";
    return 0;
}