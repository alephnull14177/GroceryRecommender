#pragma once
#include <string>
#include <vector>

class orderHashmap {
private:
    double LF = 0.75;
    double capacity = 5000;
    double size = 0;

    std::vector<//vector for int key (order num) to string value (items) paired with frequency
    std::vector< //separate chaining
    std::pair< //pair of key, value
    int,std::vector<std::string>>>> data; //key is order num while value is a vector containing the items in each order

    long hash(int key);
    void rehash();

public:
    orderHashmap() {this->data.resize(this->capacity);};
    void insert(int key, std::string value);
    std::vector<std::string>& get(int key);
    std::vector<std::vector<std::pair<int,std::vector<std::string>>>>& retrieve();
};


