//
// Created by akell on 4/23/2023.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "orderHashmap.h"
#include "itemHashmap.h"

void printOut(std::vector<std::string> thing) {
    for(int i=0; i<thing.size(); i++) {
        std::cout << thing[i] << " ";
    }
    std::cout << std::endl;
}

void printOut(std::vector<int> thing) {
    for(int i=0; i<thing.size(); i++) {
        std::cout << thing[i] << " ";
    }
    std::cout << std::endl;
}

void merge(orderHashmap& orders, itemHashmap& items) {
    auto data = orders.retrieve();
    for(int i=0; i<data.size(); i++) {
        for(int j=0; j<data[i].size(); j++) {
            for(int k=0; k<data[i][j].second.size(); k++) {
                std::string key = data[i][j].second[k];
                int value = data[i][j].first;
                items.insert(key, value);
            }
        }
    }
}