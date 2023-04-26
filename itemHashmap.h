#pragma once
#include <string>
#include <vector>

class itemHashmap {
private:
    double LF = 0.75;
    double capacity = 5;
    double size = 0;

    std::vector<//vector for int key (order num) to string value (items) paired with frequency
    std::vector< //separate chaining
            std::pair< //pair of key, value
            std::string,std::vector<int>>>> data; //key is order num while value is a vector containing the items in each order

    int hash(std::string key);
    void rehash();

public:
    itemHashmap() {this->data.resize(this->capacity);};
    void insert(std::string key, int value);
    std::vector<int>& get(std::string key);
    std::vector<std::vector<std::pair<std::string,std::vector<int>>>> retrieve();
    bool isElement(std::string key);

};



