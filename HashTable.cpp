//HashTable setup

//includes code from the following libraries
#include "HashTable.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

//uses namespaced std for easier coding
using namespace std;

/**
 *This version of HashTableBucket is a default constructor that sets key to "", value to 0, and BucketType to ESS
 */
HashTableBucket::HashTableBucket() {

  key = "";
  value = 0;
  type = BucketType::ESS;

} //end HashTableBucket no parameter constructor

/**
 * This version of HashTableBucket is a parameterized constructor to make a new bucket. It takes a provided
 * string key an int value to make the bucket and sets the BucketType to NORMAL
 * @param key the string used as they key to decide where to place the value in the hash table
 * @param value the value to be put in the specifed key in the hash table
 */
HashTableBucket::HashTableBucket(string key, int value) {

 this->key = key;
 this->value = value;
 type = BucketType::NORMAL;

} //end HashTableBucket constructor

/**
 * load takes a given key with a value and stores them into the bucket and markes the BucketType as NORMAL
 * @param key the string used as they key to decide where to place the value in the hash table
 * @param value the value to be put in the specifed key in the hash table
 */
void HashTableBucket::load(string key, int value) {

 this->key = key;
 this->value = value;
 type = BucketType::NORMAL;

} //end load

/**
 * isEmpty returns true if the bucket is currently empty
 * @return the boolean value expressing if it is empty or not
 */
bool HashTableBucket::isEmpty() const {

 if (type != BucketType::NORMAL) {
  return true;
 } //returns true if the bucket is ESS or EAR

 else {
  return false;
 } //returns false if the bucket is NORMAL

} //end isEmpty

/**
 * operator<< prints the key and the value of the provided bucket to the console
 * @param os ostream used for formatting and printing
 * @param bucket the provided bucket of the hash table that will have its key and value printed
 * @return os needed to properly exit the method after printing
 */
ostream& operator<<(ostream& os, const HashTableBucket& bucket) {

 os << "The key " << bucket.key << " contains " << bucket.value << endl;

 return os;

} //end operator<<


/**
 * HashTable sets up the initial hash table with the provided number of buckets and creates a randomized vector for
 * pseudo-random probing
 * @param initCapacity the provided initial size of the capacity (if nothing is provided, it is set to 8)
 */
HashTable::HashTable(size_t initCapacity) {

 //sets the buckets vector's size to the provided initCapacity
 buckets.resize(initCapacity);

 for (size_t i = 0; i < initCapacity; i++) {
  offsets.push_back(i);
 } //adds size_t (i) to offsets vector for shuffling

 //shuffles vector randomly
 //code referenced from website link in project description
 random_device rnd;
 mt19937 gen(rnd());
 shuffle(offsets.begin(), offsets.end(), gen);

} //end HashTable

 /**
 * Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
 * method should return true if the insertion was successful. If the insertion was
 * unsucessful, such as when a duplicate is attempted to be inserted, the method
 * should return false
 */
 bool HashTable::insert(string key, size_t value) {



} //end insert

 /**
 * If the key is in the table, remove will “erase” the key-value pair from the
 * table. This might just be marking a bucket as empty-after-remove
 */
 bool HashTable::remove(string key) {



} //end remove

 /**
 * contains returns true if the key is in the table and false if the key is not in
 * the table.
 */
 bool HashTable::contains(const string& key) const {



} //end contains

/**
 * If the key is found in the table, find will return the value associated with
 * that key. If the key is not in the table, find will return something called
 * nullopt, which is a special value in C++. The find method returns an
 * optional<int>, which is a way to denote a method might not have a valid value
 * to return. This approach is nicer than designating a special value, like -1, to
 * signify the return value is invalid. It's also much better than throwing an
 * exception if the key is not found.
 */
 std::optional<int> HashTable::get(const string& key) const {



} //end get

/**
 * The bracket operator lets us access values in the map using a familiar syntax,
 * similar to C++ std::map or Python dictionaries. It behaves like get, returnin
 * the value associated with a given key:
 int idNum = hashTable[“James”];
 * Unlike get, however, the bracker operator returns a reference to the value,
 * which allows assignment:
 hashTable[“James”] = 1234;
 If the key is not
 * in the table, returning a valid reference is impossible. You may choose to
 * throw an exception in this case, but for our implementation, the situation
 * results in undefined behavior. Simply put, you do not need to address attempts
 * to access keys not in the table inside the bracket operator method.
 */
 int& HashTable::operator[](const string& key) {



 } //end operator[]

/**
 * keys creates and returns a vector containing all the keys currently occupied in the hash table
 * @return the newly created vector of strings
 */
vector<string> HashTable::keys() const {

 vector<string> keys; //sets up a new vector called keys

 for (size_t i = 0; i < buckets.size(); i++) {

  if (buckets.at(i).type == HashTableBucket::BucketType::NORMAL) {
   keys.push_back(buckets.at(i).key);
  } //only adds the key for the bucket if the type is NORMAL

 } //end for

 return keys;

} //end keys

/**
 * alpha returns the value of (size / capacity) cast as a double
 * @return the double value resulted from the division
 */
double HashTable::alpha() const {

 double load = static_cast<double>(size()) / static_cast<double>(capacity());
 return load;

} //end alpha

/**
 * capacity returns the total number of buckets in the hash table by calling the method size()
 * @return the size_t variable returned by size()
 */
size_t HashTable::capacity() const {

 return buckets.size();

} //end capacity

/**
 * size returns the size_t variable sizeOfTable which changes as elements are added/removed from the table
 * @return the size of the table
 */
size_t HashTable::size() const {

 return sizeOfTable;

} //end size

/**
 * operator<< runs through the hash table and prints out the bucket, key, and value for each bucket if that bucket is occupied
 * @param os ostream used for formatting and printing
 * @param hashTable the hashTable that is being iterated through for printing its contents
 * @return os needed to properly exit the method after printing
 */
ostream& operator<<(ostream& os, const HashTable& hashTable) {

 for (size_t i = 0; i < hashTable.size(); i++) {

  HashTableBucket current = hashTable.buckets[i];

  if (current.type == HashTableBucket::BucketType::NORMAL) {
   os << "Bucket " << i << " has the key " << current.key << " that contains " << current.value << endl;
  } //prints message to console if bucket is occupied; the type is NORMAL

 } //end for

 return os;

} //end operator<<