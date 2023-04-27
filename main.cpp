#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "orderHashmap.h"
#include "itemHashmap.h"
#include "RedBlackTree.h"

//////////////////////////// prototypes //////////////////////////////
void entrance();
void structure();
void readDataset(orderHashmap& orders, itemHashmap& items);
void ReadDataset(RedBlackTree<int, std::string>& order_to_items, RedBlackTree<std::string, int>& item_to_orders);
void cart(orderHashmap& orders, itemHashmap& items);
void cart(RedBlackTree<int, std::string> &orders_to_items, RedBlackTree<std::string, int> &item_to_orders);
std::vector<std::string> calculateRecommendations(orderHashmap& orders, itemHashmap& items, std::string& item);
std::vector<std::string> calculateRecommendations(RedBlackTree<std::string,int>& histogram, RedBlackTree<int, std::string>& order_to_items, RedBlackTree<std::string, int>& item_to_orders, std::string item);
///////////////////////// end of prototypes //////////////////////////

//main -> entrance
int main() {
    std::cout << "Welcome to the Grocery Guru!" << std::endl;
    entrance();
}

//entrance -> structure
void entrance() {
    bool loop = true;
    do {
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1: Build grocery list" << std::endl;
        std::cout << "2: QUIT" << std::endl;
        std::string option;
        std::cin >> option;

        if (option == "1") {
            std::cout << std::endl;
            structure();
            break;
        }
        else if (option == "2") {
            EXIT_SUCCESS;
            std::cout << std::endl;
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << std::endl;
            std::cout << "Non viable option" << std::endl;
            std::cout << std::endl;
        }
    } while(loop);
}

//structure -> readDataset & cart
void structure() {
    bool loop = true;
    do{
        std::cout << "Please choose a data structure:" << std::endl;
        std::cout << "1: Red Black Tree" << std::endl;
        std::cout << "2: Hash Map" << std::endl;
        std::cout << "3: QUIT" << std::endl;
        std::string dataStructure;
        std::cin >> dataStructure;

        if (dataStructure == "1") {
            ////////////////////////// call red tree /////////////////////////
            std::cout << "Filling trees.";
            std::cout << ".";
            RedBlackTree<int, std::string> orders_to_items;
            std::cout << ".";
            RedBlackTree<std::string, int> item_to_orders;
            std::cout << ".";
            auto start = std::chrono::high_resolution_clock::now();
            ReadDataset(orders_to_items, item_to_orders);
            auto stop = std::chrono::high_resolution_clock::now();
            std::cout << "." << std::endl;
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "Filling trees took: " << duration.count() << " milliseconds!" << std::endl;
            cart(orders_to_items, item_to_orders);
            break;

        } else if (dataStructure == "2") {
            ////////////////////////// call  hash map ////////////////////////
            std::cout << "Filling maps.";
            std::cout << ".";
            orderHashmap orders;
            std::cout << ".";
            itemHashmap items;
            std::cout << ".";
            auto start = std::chrono::high_resolution_clock::now();
            readDataset(orders, items);
            auto stop = std::chrono::high_resolution_clock::now();
            std::cout << "." << std::endl;
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "Filling maps took: " << duration.count() << " milliseconds!" << std::endl;
            cart(orders, items);
            break;

        }else if (dataStructure == "3"){
            EXIT_SUCCESS;
            std::cout << std::endl;
            std::cout << "Goodbye!" << std::endl;
            break;

        }else{
            std::cout << std::endl;
            std::cout << "Non viable option" << std::endl;
            std::cout << std::endl;
        }

    }while(loop);
}

//readDataset -> (parse through .csv file and fill Hashmaps)
void readDataset(orderHashmap& orders, itemHashmap& items) {
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
            orders.insert(orderNum, item);
            items.insert(item, orderNum);
        }
    }
    file.close();
}

//readDataset -> (parse through .csv file and fill RedBlackTrees)
void ReadDataset(RedBlackTree<int, std::string>& order_to_items, RedBlackTree<std::string, int>& item_to_orders) {
    std::ifstream file("Groceries_dataset.csv");
    if (file.is_open()) {
        std::string header;
        getline(file, header);

        std::string line;
        int orderNum;
        std::string item = "";
        while (getline(file, line)) {
            orderNum = stoi(line.substr(0, 4));
            item = line.substr(16);
            order_to_items.Insert(orderNum, item);
            item_to_orders.Insert(item, orderNum);
        }
    }
    file.close();
}

//cart -> calculateRecommendations
void cart(orderHashmap& orders, itemHashmap& items){
    std::string option;
    std::string item;
    bool loop = true;
    std::vector<std::string> cart;
    do{
        if(cart.empty()) {
            std::cout << std::endl;
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: Quit" << std::endl;

            std::cin >> option;
            if(option == "1"){
                std::cout << std::endl;
                std::cout << "Input food item: ";
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2"){
                EXIT_SUCCESS;
                std::cout << std::endl;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else{
                std::cout << std::endl;
                std::cout << "Non viable option" << std::endl;
            }
        }else {
            std::cout << std::endl;
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: See recommendations" << std::endl;
            std::cout << "3: Print grocery list" << std::endl;
            std::cout << "4: QUIT" << std::endl;

            std::cin >> option;
            if(option == "1") {
                std::cout << std::endl;
                std::cout << "Input food item: ";
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2") {
                if(items.isElement(item)) {
                    std::vector<std::string> recommendations;
                    auto start = std::chrono::high_resolution_clock::now();
                    recommendations = calculateRecommendations(orders, items, item);
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                    std::cout << std::endl;
                    std::cout << "With " << item << " people also bought: ";
                    for(int i = 0; i <= recommendations.size() - 2; i++){
                        std::cout << recommendations[i] << ", ";
                    }
                    std::cout << recommendations[recommendations.size() - 1] << std::endl;
                    std::cout << "The calculateRecommendations function for the hashmap took: " << duration.count() << " milliseconds!" << std::endl;
                }else {
                    std::cout << std::endl;
                    std::cout << "Last input item was not in dataset" << std::endl;
                }

            }else if(option == "3"){
                std::cout << std::endl;
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************\n" << std::endl;
            }else if(option == "4") {
                std::cout << std::endl;
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************\n" << std::endl;
                EXIT_SUCCESS;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else {
                std::cout << std::endl;
                std::cout << "Non viable option" << std::endl;
            }
        }
    }while(loop);
}

//cart -> calculateRecommendations
void cart(RedBlackTree<int, std::string> &orders_to_items, RedBlackTree<std::string, int> &item_to_orders){
    std::string option;
    std::string item;
    bool loop = true;
    std::vector<std::string> cart;
    do{
        if(cart.empty()) {
            std::cout << std::endl;
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: Quit" << std::endl;

            std::cin >> option;
            if(option == "1"){
                std::cout << std::endl;
                std::cout << "Input food item: ";
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2"){
                EXIT_SUCCESS;
                std::cout << std::endl;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else{
                std::cout << std::endl;
                std::cout << "Non viable option" << std::endl;
            }
        }else {
            std::cout << std::endl;
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: See recommendations" << std::endl;
            std::cout << "3: Print grocery list" << std::endl;
            std::cout << "4: QUIT" << std::endl;

            std::cin >> option;
            if(option == "1") {
                std::cout << std::endl;
                std::cout << "Input food item: ";
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2") {
                RedBlackTree<std::string, int> histogram;
                std::vector<std::string> recommendations;
                auto start = std::chrono::high_resolution_clock::now();
                recommendations = calculateRecommendations(histogram, orders_to_items, item_to_orders, item);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                if (item_to_orders.find(item)){
                    std::cout << std::endl;
                    std::cout << "With " << item << " people also bought: ";
                    for(int i = 0; i <= recommendations.size() - 2; i++){
                        std::cout << recommendations[i] << ", ";
                    }
                    std::cout << recommendations[recommendations.size() - 1] << std::endl;
                    std::cout << "The calculateRecommendations function for the tree took: " << duration.count() << " milliseconds!" << std::endl;
                }
            }else if(option == "3"){
                std::cout << std::endl;
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************" << std::endl;
            }else if(option == "4") {
                item_to_orders.clear();
                orders_to_items.clear();
                std::cout << std::endl;
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************" << std::endl;
                EXIT_SUCCESS;
                std::cout << std::endl;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else {
                std::cout << std::endl;
                std::cout << "Non viable option" << std::endl;
            }
        }
    }while(loop);
}

//calculateRecommendations -> (create histogram and find top 3 groceries that have same order number)
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
            //push back items that occurred most
            std::string name = data[i][j].first;
            int occurences = data[i][j].second.size();
            if(occurences > max && name!=item) {
                max = occurences;
                common.push_back(std::make_pair(name, max));
            }
        }
    }
    std::vector<std::string> result;
    for(int i=common.size()-1; i>common.size()-4; i--) {
        result.push_back(common[i].first);
    }
    return result;
}

//calculateRecommendations -> (create histogram and find top 3 groceries that have same order number)
std::vector<std::string> calculateRecommendations(RedBlackTree<std::string,int>& histogram, RedBlackTree<int, std::string>& order_to_items, RedBlackTree<std::string, int>& item_to_orders, std::string item) {
    std::vector<std::string> recs;
    // populate histogram
    auto orders_list = item_to_orders.Get(item);
    for (auto& i : orders_list) {
        auto orderNum = i;
        auto itemsList = order_to_items.Get(orderNum);
        for (auto& j : itemsList) {
            if (j != item) {
                histogram.Insert(j, 1);
            }
        }
    }
    if (item_to_orders.find(item)) {
        auto iter = histogram.GetKeys();
        std::string recommendation;
        int peak = 0;
        for (int z = 0; z < 3; ++z) {
            for (auto &k: iter) {
                if (histogram.Get(k).size() > peak) {
                    peak = histogram.Get(k).size();
                    recommendation = k;
                }
            }
            recs.push_back(recommendation);
            histogram.ClearVals(recommendation);
            peak = 0;
        }
        histogram.clear();
    }
    else {
        std::cout << "Last input item was not in dataset\n";
    }
    return recs;
}