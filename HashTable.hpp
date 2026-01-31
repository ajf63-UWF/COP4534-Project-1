#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <string>
#include <vector>

struct HashEntry {
    std::string userid;
    std::string encryptedPassword;
};

class HashTable {
public:
    explicit HashTable(std::size_t tableSize = 101);

    void insert(const std::string& userid, const std::string& encryptedPassword);

    bool find(const std::string& userid, std::string& encryptedPassword) const;

    std::size_t size() const { return table_.size(); }

private:
    std::size_t hashUserID(const std::string& userid) const;

    std::vector<std::vector<HashEntry>> table_;
};

#endif // HASH_TABLE_HPP