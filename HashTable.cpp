#include "HashTable.hpp"

HashTable::HashTable(std::size_t tableSize) : table_(tableSize) {}

std::size_t HashTable::hashUserID(const std::string& userid) const {
    std::size_t hash = 0;
    for (unsigned char c : userid) {
        hash = (hash * 31 + c) % table_.size();
    }
    return hash;
}

void HashTable::insert(const std::string& userid, const std::string& encryptedPassword) {
    std::size_t index = hashUserID(userid);
    table_[index].push_back({userid, encryptedPassword});
}

bool HashTable::find(const std::string& userid, std::string& outEncryptedPassword) const {
    std::size_t index = hashUserID(userid);

    for (const auto& entry : table_[index]) {
        if (entry.userid == userid) {
            outEncryptedPassword = entry.encryptedPassword;
            return true;
        }
    }
    return false;
}