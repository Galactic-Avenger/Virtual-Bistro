
// Testing the functions here for the Dish Class.

#include "Dish.hpp"

int main() {
    // Part 1 - Instantiate a dish with the default constructor
    Dish Dish1;
    // Set preparation time and price using setter functions to 30 and 10.99 respectively
    Dish1.setPrepTime(30);
    Dish1.setPrice(9.99);
    // Print out the dish's information using the display function
    Dish1.display();

    std::cout << std::endl;
    
    // Part 2 - Instantiate a dish with the parameterized constructor
    Dish Dish2("Pasta Carbonara", std::vector<std::string>{"Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper"}, 20, 12.50, Dish::ITALIAN);
    // Print out the dish's information
    Dish2.display();

    return 0;
}

