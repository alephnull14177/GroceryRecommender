#include "main.h"

void entrance() {
    std::string option;

    do {
        std::cout << "1: build grocery list" << std::endl;
        std::cout << "2: QUIT" << std::endl;
        std::cin >> option;

        if (option == "1") {
            std::cout << "Please choose a data structure:" << std::endl;
            structure();
            break;
        }
        else if (option == "2") {
            EXIT_SUCCESS;
        }
        else {
            std::cout << "not an option!" << std::endl;
        }
    } while(option!="2");
}

void structure() {
    std::string dataStructure;
    do {
        std::cout << "1: Red Black Tree" << std::endl;
        std::cout << "2: Hash Map" << std::endl;
        std::cout << "3: QUIT" << std::endl;
        std::cin >> dataStructure;

        if (dataStructure == "1") {
            ////////////////////////// call red tree /////////////////////////
        } else if (dataStructure == "2") {
            ////////////////////////// call  hash map ////////////////////////
            std::cout << "Filling maps.";
            orderHashmap orders;

            itemHashmap items;
            readDataset(orders);
            std::cout << ".";
            readDataset(items);
            std::cout << "." << std::endl;

//            std::cout << ".";
//            readDataset(orders);
//            //printOut(orders.get(1808));
//            std::cout << ".";
//            itemHashmap items;
//            std::cout << ".";
//            merge(orders, items);
//            std::cout << "." << std::endl;

            std::string option;
            std::string item;

            do {
                std::cout << "1: Add item to cart" << std::endl;
                std::cout << "2: Read recommended to latest item" << std::endl;
                std::cout << "3: Quit" << std::endl;
                std::cin >> option;

                if(option == "1") {
                    std::cin.ignore();
                    std::cout << "What would you like to add to cart?" << std::endl;
                    std::getline(std::cin, item);
                    if(!items.isElement(item)) {
                        std::cout << "Not in store!" << std::endl;
                    }
                }
                else if(option == "2") {
                    if(item == "") {
                        std::cout << "Empty cart" << std::endl;
                    }
                    else {
                        std::vector<std::string> result = calculateRecommendations(orders, items, item);
                        printOut(result);
                    }
                }
                else if(option == "3") {
                    EXIT_SUCCESS;
                }
                else {
                    std::cout << "not an option!" << std::endl;
                }

            } while (option!="3");
            break;
        }
        else if (dataStructure == "3") {
            EXIT_SUCCESS;
        }
        else {
            std::cout << "not an option!" << std::endl;
        }
    } while(dataStructure!="3");
}

int main() {
    std::cout << "Welcome to the Grocery Guru!" << std::endl;
    std::cout << "Please select an option:" << std::endl;
    entrance();
}
