#include "PasswordUtils.hpp"
#include <random>
#include <cctype>

std::string generatePassword(int length) {
    static const char letters[] = "abcdefghijklmnopqrstuvwxyz";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 25);

    std::string password;
    for (int i = 0; i < length; ++i) {
        password += letters[dist(gen)];
    }
    return password;
}

std::string vigenereEncrypt(const std::string& plaintext, const std::string& key) {
    std::string result;
    int keyIndex = 0;

    for (char ch : plaintext) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char p = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            char k = static_cast<char>(std::tolower(static_cast<unsigned char>(key[keyIndex % key.size()])));

            int c = ((p - 'a') + (k - 'a')) % 26;
            result += static_cast<char>(c + 'a');
            keyIndex++;
        } else {
            result += ch;
        }
    }

    return result;
}
