#include <iostream>
#include "RecipeBook.hpp"

int main(){
    auto test = RecipeBook("debug.csv");
    test.preorderDisplay();
    std::cout << "\n\n\n\n";
    test.balance();
    test.preorderDisplay();
}
