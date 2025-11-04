/**
*Alan Schmidt
 *Project 4 - Hash Table
 *This project hopefully fully implements a hash table with all relevant methods
 *no time to properly test the project so hopefully it works at least somewhat properly
 */

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
 * insert takes the provided key and corresponding value and attempts to implement them into the hash table
 * if there is a duplicate, or if the value cannot otherwise be implemented, it returns false and the key/value aren't put in
 * otherwise, it puts in the value at the key unless it is marked as NORMAL, in which case it iterates through
 * the offsets vector to put it in the table in a proper location
 * @param key the string key used for implementation
 * @param value the size_t value to be stored with the key
 * @return the boolean value true, if it was inserted properly, or false, if it was not inserted
 */
bool HashTable::insert(string key, size_t value) {

 if (contains(key)) {
  return false;
 } //returns false if key is already in table

 else if (alpha() >= .5) {
  doubleSize();
 }

 else {
  hash<string> hasher;
  size_t tempValue = hasher(key);
  size_t location = (tempValue % capacity()); //sets location to the proper modulos value in the table based off the total size of the table

  if (buckets.at(location).type != HashTableBucket::BucketType::NORMAL) {
   buckets.at(location).load(key, value);
   sizeOfTable++;
   return true;
  } //if BucketType is ESS or EAR, load the key and value at that location

  else {

   for (size_t i = 0; i < offsets.size(); i++) {
    size_t probe = ((location + offsets[i]) % capacity());
    if (buckets.at(probe).type == HashTableBucket::BucketType::NORMAL) {
     buckets.at(probe).load(key, value);
     sizeOfTable++;
     return true;
    } //if the current bucket is not type NORMAL, load the key and value at that location
   } //iterates through the offsets vector until the if condition is met for pseudo-random probing

  } //end inner else

 } //end outer else

return false; //error catcher

} //end insert

/**
 * doubleSize copies the size and contents of buckets to temp variables, doubles the size of buckets,
 * resets the pseudo-random offsets vector, and calls insert on the contents of the temp buckets
 */
void HashTable::doubleSize() {

 //sets temporary values assigned to the old buckets' size and values
 size_t tempSize = buckets.size();
 vector<HashTableBucket> tempBuckets = buckets;

 sizeOfTable = 0; //resets sizeOfTable to 0
 buckets.clear(); //empties buckets' contents
 buckets.resize((tempSize * 2)); //doubles the size of buckets

 //the offsets code copied from my insert method
 for (size_t i = 0; i < buckets.size(); i++) {
  offsets.push_back(i);
 } //adds size_t (i) to offsets vector for shuffling

 //shuffles vector randomly
 //code referenced from website link in project description
 random_device rnd;
 mt19937 gen(rnd());
 shuffle(offsets.begin(), offsets.end(), gen);

 for (int i = 0; i < tempSize; i++) {
  insert(tempBuckets.at(i).key, tempBuckets.at(i).value);
 } //calls insert() on the contents of tempBuckets so they get re-added to buckets properly

 tempBuckets.clear(); //deletes the contents of tempBuckets to maybe save memory?

} //end doubleSize

/**
 * remove first checks if the table contains the key, and returns false if it doesn't
 * otherwise, it probes through the table as needed and sets the key and value parameters to the default constructors
 * and sets the type to EAR
 * @param key the key being used to probe through the hash table
 * @return the boolean value true, for the item was removed, or false, if it was not successfully removed
 */
bool HashTable::remove(string key) {

 if (contains(key)) {

  hash<string> hasher;
  size_t tempValue = hasher(key);
  size_t location = (tempValue % capacity());

  if (buckets.at(location).key == key) {
   buckets.at(location).key = "";
   buckets.at(location).value = 0;
   buckets.at(location).type = HashTableBucket::BucketType::EAR;
   sizeOfTable--;
   return true;
  } //sets bucket to the same as default constructor if found in table

  else {
   for (size_t i = 0; i < offsets.size(); i++) {
    size_t probe = ((location + offsets[i]) % capacity());
    if (buckets.at(probe).key == key) {
     buckets.at(probe).key = "";
     buckets.at(probe).value = 0;
     buckets.at(probe).type = HashTableBucket::BucketType::EAR;
     sizeOfTable--;
     return true;
    } //sets bucket to the same as default constructor if found in table
   } //probes through table using the offset vector's pseudo-randomness

   return false; // error catcher

  } //end else

 } //end if

 else {
  return false;
 } //returns false if contains() returns false

} //end remove

/**
 * contains probes through the array and returns true if the key is in the table and false if it is not
 * @param key the string used as a parameter to probe through the table
 * @return the boolean value if it is or isn't in the table
 */
bool HashTable::contains(const string& key) const {

 hash<string> hasher;
 size_t tempValue = hasher(key);
 size_t location = (tempValue % capacity());

 if (buckets.at(location).key == key) {
  return true;
 } //checks if key is at the initial location in the table

 else {
  for (size_t i = 0; i < offsets.size(); i++) {
   size_t probe = ((location + offsets[i]) % capacity());
   if (buckets.at(probe).key == key) {
    return true;
   } //checks if key is at the current location in the table
  } //probes through table using the offset vector's pseudo-randomness

  return false; //returns false if the key is not found in the table

 } //end else

} //end contains

/**
 * get checks if the key is in the table and, if it is, it returns the value associated with that key
 * if not, it returns nullop
 * @param key the string used to probe through the table
 * @return the value associated with the key or nullopt
 */
optional<int> HashTable::get(const string& key) const {

if (contains(key)) {
 hash<string> hasher;
 size_t tempValue = hasher(key);
 size_t location = (tempValue % capacity());

 if (buckets.at(location).key == key) {
  return buckets.at(location).value;
 } //returns the value at the key's location if the key matches initially

 else {
  for (size_t i = 0; i < offsets.size(); i++) {
   size_t probe = ((location + offsets[i]) % capacity());
   if (buckets.at(probe).key == key) {
    return buckets.at(probe).value;
   }
  }

  return nullopt; //error catcher

 } //end else

} //end outer if

else {
 return nullopt; //returns nullopt if the key is not in the table
}

} //end get

/**
 * I'm not too sure about this one but...
 * operator[] returns a reference to the value found by the provided key parameter
 * if the key is not in the table, an error would be thrown, but we don't have to worry about that
 * @param key the string used to probe through the table
 * @return the reference to the value associated with the key
 */
int& HashTable::operator[](const string& key) {

if (contains(key)) {
 hash<string> hasher;
 size_t tempValue = hasher(key);
 size_t location = (tempValue % capacity());

 if (buckets.at(location).key == key) {
  return buckets.at(location).value;
 }

 else {
  for (size_t i = 0; i < offsets.size(); i++) {
   size_t probe = ((location + offsets[i]) % capacity());
   if (buckets.at(probe).key == key) {
    return buckets.at(probe).value;
   }
  }
 }
} //end outer if

else {
 //return an error if not found
}

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