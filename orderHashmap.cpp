#include "orderHashmap.h"
#include <iostream>

int orderHashmap::hash(int key) {
    return (key % (int) this->capacity);
}

void orderHashmap::rehash() {
    orderHashmap copy;
    copy.capacity = this->capacity * 2;
    copy.data.resize(copy.capacity);

    for(int i=0; i<this->data.size(); i++) {
        for(int j=0; j<this->data[i].size(); j++) {
            for(int k=0; k<this->data[i][j].second.size(); k++) {
                int key = this->data[i][j].first;
                std::string value = this->data[i][j].second[k];
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

void orderHashmap::insert(int key, std::string value) {
    //get position
    int position = hash(key);
    this->size++;
    //loop through separate chain
    for(int i=0; i<this->data[position].size(); i++) {
        //if key is in separate chain already, then just add to its vector
        if(this->data[position][i].first == key) {
            //add item to the order list
            this->data[position][i].second.push_back(value);
            return;
        }
    }

    //create a vector for the elemenet that has nothing
    std::vector<std::string> list;
    list.push_back(value);

    //if there isn't already the key order number, add a pair of the key with the vector of items to the list
    this->data[position].push_back(std::make_pair(key, list));

    if(this->size/this->capacity >= this->LF) {
        rehash();
    }
}

std::vector<std::string>& orderHashmap::get(int key) {
    int position = this->hash(key);

    for(int i=0; i<this->data[position].size(); i++) {
        if(this->data[position][i].first == key) {
            return this->data[position][i].second;
        }
    }
}

std::vector<std::vector<std::pair<int,std::vector<std::string>>>> orderHashmap::retrieve() {
    return this->data;
}