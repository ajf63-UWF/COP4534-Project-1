#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>

#include "PasswordUtils.hpp"
#include "HashTable.hpp"

// Helper function to check if a string contains only letters
static bool isAllLetters(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) {
        if (!std::isalpha(ch)) {
            return false;
        }
    }
    return true;
}

// Helper function to modify a password to make it illegal
static std::string makeIllegalPassword(std::string pw) {
    if (pw.empty()) return pw;

    pw[0] = (pw[0] == 'z') ? 'a' : static_cast<char>(pw[0] + 1);
    return pw;
}

// Picks 1st, 3rd, 5th, 7th, 9th entries from rawdata.txt
static std::vector<std::pair<std::string, std::string>> pickFive(const std::string& rawPath) {
    std::ifstream in(rawPath);
    std::vector<std::pair<std::string, std::string>> picked;

    if (!in) return picked;

    std::string userid, pw;
    int row = 0;
    while (in >> userid >> pw) {
        if (!isAllLetters(userid)) continue;
        row++;

        if (row == 1 || row == 3 || row == 5 || row == 7 || row == 9) {
            picked.push_back({userid, pw});
        }
        if (picked.size() == 5) break;
    }
    return picked;
}

// Builds a hash table from encrypteddata.txt
static HashTable buildTableFromEncrypted(const std::string& encPath) {
    HashTable table(101);

    std::ifstream in(encPath);
    std::string userid, encPw;
    while (in >> userid >> encPw) {
        if (!isAllLetters(userid)) continue;
        table.insert(userid, encPw);
    }
    return table;
}

int main() {
    const std::string key = "jones";

    HashTable table = buildTableFromEncrypted("encrypteddata.txt");
    auto tests = pickFive("rawdata.txt");

    if (tests.size() != 5) {
        std::cerr << "Not enough valid test entries found.\n";
        return 2;
    }

    int failures = 0;

    // Legal tests
    std::cout << "Legal:\n";
    std::cout << "Userid Password(file) Password(table/un) Result\n";

    for (const auto& [userid, plainPw] : tests) {
        std::string storedEnc;
        bool found = table.find(userid, storedEnc);

        std::string computedEnc = vigenereEncrypt(plainPw, key);

        bool match = found && (computedEnc == storedEnc);

        std::cout << userid << " "
                  << plainPw << " "
                  << storedEnc << " "
                  << (match ? "match" : "NO MATCH") << "\n";

        if (!match) failures++;
    }

    // Illegal tests
    std::cout << "\nIllegal:\n";
    std::cout << "Userid Password(mod) Password(table/un) Result\n";

    for (const auto& [userid, plainPw] : tests) {
        std::string storedEnc;
        bool found = table.find(userid, storedEnc);

        std::string illegalPw = makeIllegalPassword(plainPw);
        std::string computedEnc = vigenereEncrypt(illegalPw, key);

        bool match = found && (computedEnc == storedEnc);
        bool noMatch = found && !match;

        std::cout << userid << " "
                  << illegalPw << " "
                  << storedEnc << " "
                  << (noMatch ? "no match" : "MATCH (unexpected)") << "\n";

        if (!noMatch) failures++;
    }

    std::cout << "\nTests " << (failures == 0 ? "PASSED." : "FAILED") << " (" << failures << " failures)\n";

    return failures == 0 ? 0 : 1;
}