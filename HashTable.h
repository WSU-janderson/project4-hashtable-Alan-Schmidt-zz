//header file

//defines the header file
#ifndef HashTable_h
#define HashTable_h

//includes code from the following libraries
#include <string>
#include <vector>
#include <ostream>

class HashTableBucket {

public:

    //enumerated variables copied from project description
    enum class BucketType {NORMAL, ESS, EAR};

    //variables
    std::string key;
    int value;
    BucketType type;

    //method headers
    HashTableBucket();

    HashTableBucket(std::string key, int value);

    void load(std::string key, int value);

    bool isEmpty() const;

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);

}; //end HashTableBucket

class HashTable {

public:

    //variables

    //method headers
    HashTable(size_t initCapacity = 8);

    bool insert(std::string key, size_t value);

    bool remove(std::string key);

    bool contains(const std::string& key) const;

    std::optional<int> get(const std::string& key) const;

    int& operator[](const std::string& key);

    std::vector<std::string> HashTable::keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

}; //end HashTable

#endif //end the header file definition