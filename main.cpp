#include <iostream>
#include <stdlib.h>
void complaint1(std::string &inp);
void complaint2(std::string &inp2);
void entrance();
void structure();

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
    std::cout << "1: Red Black Tree" << std::endl;
    std::cout << "2: Hash Map" << std::endl;
    std::cout << "3: QUIT" << std::endl;
    std::cin >> inp2;

    try{
        data_structure = stoi(inp2);
        if(data_structure == 1){
            ////////////////////////// call red tree /////////////////////////
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