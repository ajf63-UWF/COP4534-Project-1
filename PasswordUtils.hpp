#ifndef PASSWORD_UTILS_HPP
#define PASSWORD_UTILS_HPP

#include <string>

std::string generatePassword(int length = 9);

std::string vigenereEncrypt(const std::string& plaintext, const std::string& key);

#endif // PASSWORD_UTILS_HPP