/**
*Alan Schmidt
 *Project 4 - Hash Table
 *This header file defines all the methods and variables used in the HashTable.cpp file
 */

//defines the header file
#ifndef HashTable_h
#define HashTable_h

//includes code from the following libraries
#include <optional>
#include <string>
#include <vector>
#include <ostream>

//uses namespaced std for easier coding
using namespace std;

class HashTableBucket {

public:

    //enumerated variables copied from project description
    enum class BucketType {NORMAL, ESS, EAR};

    //variables
    string key;
    int value;
    BucketType type;

    //method headers
    HashTableBucket();

    HashTableBucket(string key, int value);

    void load(string key, int value);

    bool isEmpty() const;

    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);

}; //end HashTableBucket

class HashTable {

public:

    //variables
    vector<HashTableBucket> buckets;
    vector<size_t> offsets;
    size_t sizeOfTable = 0;

    //method headers
    HashTable(size_t initCapacity = 8);

    bool insert(string key, size_t value);

    void doubleSize();

    bool remove(string key);

    bool contains(const string& key) const;

    optional<int> get(const string& key) const;

    int& operator[](const string& key);

    vector<string> keys() const;

    double alpha() const;

    size_t capacity() const;

    size_t size() const;

    friend ostream& operator<<(ostream& os, const HashTable& hashTable);

}; //end HashTable

#endif