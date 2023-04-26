//
// Created by akell on 4/23/2023.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "orderHashmap.h"
#include "itemHashmap.h"

void entrance();
void structure();

void printOut(std::vector<std::string> thing) {
    for(int i=0; i<thing.size(); i++) {
        std::cout << thing[i] << ", ";
    }
    std::cout << std::endl;
}

void printOut(std::vector<int> thing) {
    for(int i=0; i<thing.size(); i++) {
        std::cout << thing[i] << ", ";
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

void readDataset(orderHashmap& orders) {
    std::ifstream file("Groceries_dataset.csv");
    if (file.is_open()) {
        std::string header;
        getline(file, header);

        std::string line;
        int orderNum = 0;
        std::string item = "";
        while (getline(file, line)) {
            orderNum = stoi(line.substr(0, 4));
            item = line.substr(16);
            //cout << orderNum << "->" << item << endl;
            orders.insert(orderNum, item);
        }
    }
    file.close();
}

void readDataset(itemHashmap& items) {
    std::ifstream file("Groceries_dataset.csv");
    if (file.is_open()) {
        std::string header;
        getline(file, header);

        std::string line;
        int orderNum = 0;
        std::string item = "";
        while (getline(file, line)) {
            orderNum = stoi(line.substr(0, 4));
            item = line.substr(16);
            items.insert(item, orderNum);
        }
    }
    file.close();
}

std::vector<std::string> calculateRecommendations(orderHashmap& orders, itemHashmap& items, std::string& item) {
    std::vector<int> ordersPresent = items.get(item);

    //create a histogram
    itemHashmap histogram;
    for(int i=0; i<ordersPresent.size(); i++) {
        for(int j=0; j<orders.get(ordersPresent[i]).size(); j++) {
            histogram.insert(orders.get(ordersPresent[i])[j], 1);
        }
    }

    int max = 0;
    std::vector<std::pair<std::string, int>> common;
    auto data = histogram.retrieve();

    for(int i=0; i<data.size(); i++) {
        for(int j=0; j<data[i].size(); j++) {
            //push back items with highest occurence rate
            std::string name = data[i][j].first;
            int occurences = data[i][j].second.size();
            if(occurences > max && name!=item) {
                max = data[i][j].second.size();
                common.push_back(std::make_pair(data[i][j].first, max));
            }}

    }
    std::vector<std::string> result;

    for(int i=common.size()-1; i>common.size()-4; i--) {
        result.push_back(common[i].first);
    }

    return result;
}