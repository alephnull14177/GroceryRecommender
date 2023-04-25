#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include "itemHashmap.h"
#include "orderHashmap.h"
//#pragma once
void complaint1(std::string &inp);
void complaint2(std::string &inp2);
void entrance();
void structure();
void read_file_map(std::vector<std::pair<std::string, std::string>> &test);
void printy(std::vector<std::pair<std::string, std::string>> &test);
void merge(orderHashmap& order_to_items, itemHashmap& item_to_orders);
void printOut(std::vector<int> thing);
void printOut(std::vector<std::string> thing);

int main() {
    std::cout << "Welcome to the Grocery Guru!" << std::endl;
    std::cout << "Please select an option:" << std::endl;
    entrance();
}

void entrance() {
    std::string inp;
    int option = 0;
    std::cout << "1: build grocery list" << std::endl;
    std::cout << "2: QUIT" << std::endl;
    std::cin >> inp;

    try {
        option = stoi(inp);
        if (option == 1) {
            std::cout << "Please choose a data structure:" << std::endl;
            structure();
        } else if (option == 2) {
            EXIT_SUCCESS;
        } else {
            complaint1(inp);
        }
    }catch(std::invalid_argument & e){
        complaint1(inp);
    }catch(std::out_of_range & e){
        complaint1(inp);
    }
}

void structure(){
    std::string inp2;
    int data_structure = 0;
    //orderHashmap order_to_items;

    std::cout << "1: Hash Map" << std::endl;
    std::cout << "2: Red Black Tree" << std::endl;
    std::cout << "3: QUIT" << std::endl;
    std::cin >> inp2;

    try{
        data_structure = stoi(inp2);
        if(data_structure == 1){
            std::vector<std::pair<std::string, std::string>> test;
            read_file_map(test);

        }else if(data_structure == 2){
            ////////////////////////// call  hash map ////////////////////////
        }else if(data_structure == 3){
            EXIT_SUCCESS;
        }else{
            complaint2(inp2);
        }
    }catch(std::invalid_argument & e){
        complaint2(inp2);
    }catch(std::out_of_range & e){
        complaint2(inp2);
    }
}

void complaint1(std::string &inp) {
    std::cout << inp << " is not an option!" << std::endl;
    std::cout << "Input: '1' or '2'" << std::endl;
    entrance();
}

void complaint2(std::string &inp2) {
    std::cout << inp2 << " is not an option!" << std::endl;
    std::cout << "Input: '1' or '2'" << std::endl;
    structure();
}

void read_file_map(std::vector<std::pair<std::string, std::string>> &test){
    std::ifstream openFile("Groceries_dataset.csv");
    if(openFile.is_open()){

        std::string file_lines;
        std::istringstream lines(file_lines);

        std::string title;
        getline(lines,title);

        while(getline(openFile, file_lines)){
            std::istringstream line(file_lines);

            std::string smember_number;
            getline(lines, smember_number, ',');
            //int member_number = stoi(smember_number);

            std::string date;
            getline(lines, date, ',');

            std::string item;
            getline(lines, item);

            test.push_back(std::make_pair(smember_number, item));
        }
        openFile.close();
    }
    printy(test);
}

void printy(std::vector<std::pair<std::string, std::string>> &test){
    std::cout << test[0].first << test[0].second << std::endl;
}

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

void merge(orderHashmap& order_to_items, itemHashmap& item_to_orders) {
    auto data = order_to_items.retrieve();
    for(int i=0; i<data.size(); i++) {
        for(int j=0; j<data[i].size(); j++) {
            for(int k=0; k<data[i][j].second.size(); k++) {
                std::string key = data[i][j].second[k];
                int value = data[i][j].first;
                item_to_orders.insert(key, value);
            }
        }
    }
}