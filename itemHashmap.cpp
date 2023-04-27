#include "itemHashmap.h"

long itemHashmap::hash(std::string key) {
    unsigned long number = 0;
    unsigned long power = 1;

    //hash function with powers of 37
    for(int i=0; i<key.length(); i++) {
        number += power*key[i];
        power = power*37;
    }
    return (number % (long) this->capacity);
}

void itemHashmap::rehash() {
    itemHashmap copy;
    copy.capacity = this->capacity * 2;
    copy.data.resize(copy.capacity);

    //create a copy of map with new hash placements
    for(int i=0; i<this->data.size(); i++) {
        for(int j=0; j<this->data[i].size(); j++) {
            for(int k=0; k<this->data[i][j].second.size(); k++) {
                std::string key = this->data[i][j].first;
                int value = this->data[i][j].second[k];
                copy.insert(key, value);
            }
        }
    }

    this->capacity = this->capacity*2;

    //empty current map
    while(this->data.size() > 0) {
        this->data.pop_back();
    }

    //replace all the values in new position
    this->data.resize(this->capacity);
    for(int i=0; i<copy.data.size(); i++) {
        for(int j=0; j<copy.data[i].size(); j++) {
            for(int k=0; k<copy.data[i][j].second.size(); k++) {
                this->insert(copy.data[i][j].first, copy.data[i][j].second[k]);
            }
        }
    }
}

void itemHashmap::insert(std::string key, int value) {
    //get position
    int position = hash(key);
    this->size++;
    //loop through separate chain
    for(int i=0; i<this->data[position].size(); i++) {
        //if key is in separate chain already, then just add to its vector
        if(this->data[position][i].first == key) {
            //add order to the item list
            this->data[position][i].second.push_back(value);
            return;
        }
    }

    //create a vector for the elemenet that has nothing
    std::vector<int> list;
    list.push_back(value);

    //if there isn't already the key order number, add a pair of the key with the vector of items to the list
    this->data[position].push_back(std::make_pair(key, list));

    if(this->size/this->capacity >= this->LF) {
        rehash();
    }
}

//gets a vector tied to a key
std::vector<int>& itemHashmap::get(std::string key) {
    int position = this->hash(key);

    //loop through separate chain
    for(int i=0; i<this->data[position].size(); i++) {
        if(this->data[position][i].first == key) {
            return this->data[position][i].second;
        }
    }
}

bool itemHashmap::isElement(std::string key) {
    //get possible hash
    int possiblePosition = this->hash(key);

    //check separate chain for occurence
    for(int i=0; i<this->data[possiblePosition].size(); i++) {
        if(this->data[possiblePosition][i].first == key) {
            return true;
        }
    }
    return false;
}

//grabs reference of data internals
std::vector<std::vector<std::pair<std::string,std::vector<int>>>>& itemHashmap::retrieve() {
    return this->data;
}