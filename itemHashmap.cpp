#include "itemHashmap.h"
#include <cmath>

int itemHashmap::hash(std::string key) {
    int number = 0;
    for(int i=0; i<key.length(); i++) {
        number += std::pow(31, i) * key[i];
    }
    return (number % (int) this->capacity);
}

void itemHashmap::rehash() {
    itemHashmap copy;
    copy.capacity = this->capacity * 2;
    copy.data.resize(copy.capacity);

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
    //empty list
    while(this->data.size() > 0) {
        this->data.pop_back();
    }

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
            //add item to the order list
            for(int j=0; j<this->data[position][i].second.size(); j++) {
                //no need to add repeats
                if(this->data[position][i].second[j] == value) {
                    return;
                }
            }
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

std::vector<int>& itemHashmap::get(std::string key) {
    int position = this->hash(key);

    for(int i=0; i<this->data[position].size(); i++) {
        if(this->data[position][i].first == key) {
            return this->data[position][i].second;
        }
    }
}