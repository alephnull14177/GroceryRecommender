#include "main.h"
void entrance() {
    bool loop = true;
    do {
        std::string option;
        std::cout << "1: Build grocery list" << std::endl;
        std::cout << "2: QUIT" << std::endl;
        std::cin >> option;

        if (option == "1") {
            std::cout << std::endl;
            std::cout << "Please choose a data structure:" << std::endl;
            structure();
            break;
        }
        else if (option == "2") {
            EXIT_SUCCESS;
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Non viable option" << std::endl;
        }
    } while(loop);
}

void cart(RedBlackTree<int, std::string> orders_to_items, RedBlackTree<std::string, int> item_to_orders){
    std::string option;
    std::string item;
    bool loop = true;
    std::vector<std::string> cart;
    do{
        if(cart.empty()) {
            std::cout << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: Quit" << std::endl;

            std::cin >> option;
            if(option == "1"){
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2"){
                EXIT_SUCCESS;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else{
                std::cout << "Non viable option" << std::endl;
            }
        }else {
            std::cout << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: See recommendations" << std::endl;
            std::cout << "3: Print grocery list" << std::endl;
            std::cout << "4: QUIT" << std::endl;

            std::cin >> option;
            if(option == "1") {
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2") {
                RedBlackTree<std::string, int> histogram;
                std::vector<std::string> recommendations;
                recommendations = calculateRecommendations(histogram, orders_to_items, item_to_orders, item);
                if (item_to_orders.find(item)){
                    std::cout << "With " << item << " people also bought: ";
                    for(int i = 0; i <= recommendations.size() - 2; i++){
                        std::cout << recommendations[i] << ", ";
                    }
                    std::cout << recommendations[recommendations.size() - 1] << std::endl;
                }
            }else if(option == "3"){
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************" << std::endl;
            }else if(option == "4") {
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************" << std::endl;
                EXIT_SUCCESS;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else {
                std::cout << "Non viable option" << std::endl;
            }
        }
    }while(loop);
}

void cart(orderHashmap& orders, itemHashmap& items){

    std::string option;
    std::string item;
    bool loop = true;
    std::vector<std::string> cart;
    do{
        if(cart.empty()) {
            std::cout << std::endl;
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: Quit" << std::endl;

            std::cin >> option;
            if(option == "1"){
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2"){
                EXIT_SUCCESS;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else{
                std::cout << "Non viable option" << std::endl;
            }
        }else {
            std::cout << "1: Add item to cart" << std::endl;
            std::cout << "2: See recommendations" << std::endl;
            std::cout << "3: Print grocery list" << std::endl;
            std::cout << "4: QUIT" << std::endl;

            std::cin >> option;
            if(option == "1") {
                std::cin.ignore();
                std::getline(std::cin, item);
                cart.push_back(item);
            }else if(option == "2") {
                if(items.isElement(item)) {
                    std::vector<std::string> recommendations;
                    recommendations = calculateRecommendations(orders, items, item);
                    std::cout << "With " << item << " people also bought: ";
                    for(int i = 0; i <= recommendations.size() - 2; i++){
                        std::cout << recommendations[i] << ", ";
                    }
                    std::cout << recommendations[recommendations.size() - 1] << std::endl;
                }else {
                    std::cout << "Last input item was not in dataset" << std::endl;
                }

            }else if(option == "3"){
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************\n" << std::endl;
            }else if(option == "4") {
                std::cout << "******************GROCERIES********************" << std::endl;
                for(int i = 1; i <= cart.size(); i++){
                    std::cout << i << ": " << cart[i - 1] << std::endl;
                }
                std::cout << "***********************************************\n" << std::endl;
                EXIT_SUCCESS;
                std::cout << "Goodbye!" << std::endl;
                break;
            }else {
                std::cout << "Non viable option" << std::endl;
            }
        }
    }while(loop);
}

void structure() {
    bool loop = true;
    do{
        std::string dataStructure;
        std::cout << "1: Red Black Tree" << std::endl;
        std::cout << "2: Hash Map" << std::endl;
        std::cout << "3: QUIT" << std::endl;
        std::cin >> dataStructure;

        if (dataStructure == "1") {
            ////////////////////////// call red tree /////////////////////////
            std::cout << "Filling trees.";
            std::cout << ".";
            RedBlackTree<int, std::string> orders_to_items;
            std::cout << ".";
            RedBlackTree<std::string, int> item_to_orders;
            std::cout << ".";
            ReadDataset(orders_to_items, item_to_orders);
            std::cout << "." << std::endl;
            cart(orders_to_items, item_to_orders);
            break;

        } else if (dataStructure == "2") {
            ////////////////////////// call  hash map ////////////////////////
            std::cout << "Filling maps.";
            orderHashmap orders;
            itemHashmap items;
            readDataset(orders, items);
            cart(orders, items);
            break;

        }else if (dataStructure == "3"){
            EXIT_SUCCESS;
            std::cout << "Goodbye!" << std::endl;
            break;

        }else{
            std::cout << "Non viable option" << std::endl;
        }

    }while(loop);
}

int main() {
    std::cout << "Welcome to the Grocery Guru!" << std::endl;
    std::cout << "Please select an option:" << std::endl;
    entrance();
}