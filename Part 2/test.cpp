#include <iostream>
#include <vector>
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"

int main() {
    /** 1. Instantiate an appetizer with the default constructor:
    Set its spiciness level to 7 using the appropriate setter function. Set its serving style to FAMILY_STYLE using the appropriate setter function. Set the vegetarian flag to true using the appropriate setter function.
    Print out the appetizer's information using the accessor functions. */
    Appetizer appetizer("UNKNOWN", {}, 0, 0.0, Dish::CuisineType::OTHER, Appetizer::FAMILY_STYLE, 7, true);

    /**
    Expected Output:
    Dish Name: UNKNOWN
    Ingredients:
    Preparation Time: 0 minutes
    Price: $0.00
    Cuisine Type: OTHER
    Spiciness Level: 7
    Serving Style: FAMILY_STYLE
    Vegetarian: True 
    */
    
    std::cout << "Dish Name: " << appetizer.getName() << std::endl;
    std::cout << "Ingredients: ";
    for (const auto& ingredient : appetizer.getIngredients()) {
        std::cout << ingredient << " ";
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << appetizer.getPrepTime() << " minutes" << std::endl;
    std::cout << "Price: $" << appetizer.getPrice() << std::endl;
    std::cout << "Cuisine Type: " << appetizer.getCuisineType() << std::endl;
    std::cout << "Spiciness Level: " << appetizer.getSpicinessLevel() << std::endl;
    std::cout << "Serving Style: " << (appetizer.getServingStyle() == Appetizer::FAMILY_STYLE ? "FAMILY_STYLE" : "OTHER") << std::endl;
    std::cout << "Vegetarian: " << (appetizer.isVegetarian() ? "True" : "False") << std::endl;

    /**
    Instantiate a main course with the parameterized constructor:
    Name: "Grilled Chicken"
    Ingredients: ["Chicken", "Olive Oil", "Garlic", "Rosemary"]
    Preparation Time: 30
    Price: 18.99
    Cuisine Type: AMERICAN
    Cooking Method: GRILLED
    Protein Type: "Chicken"
    Add side dishes: "Mashed Potatoes" with category "Starches" and "Green Beans" with category "Vegetable"
    Set the gluten-free flag to true using the appropriate setter function. Print out the main course's information using the accessor functions.
    */
    std::vector<std::string> main_course_ingredients = {"Chicken", "Olive Oil", "Garlic", "Rosemary"};
    std::vector<MainCourse::SideDish> side_dishes = {
        {"Mashed Potatoes", MainCourse::STARCHES},
        {"Green Beans", MainCourse::VEGETABLE}
    };
    MainCourse main_course(
        "Grilled Chicken", main_course_ingredients, 30, 18.99, Dish::CuisineType::AMERICAN, 
        MainCourse::GRILLED, "Chicken", side_dishes, true
    );

    /**
    Expected Output:
     Dish Name: Grilled Chicken
    Ingredients: Chicken, Olive Oil, Garlic, Rosemary
    Preparation Time: 30 minutes
    Price: $18.99
    Cuisine Type: AMERICAN
    Cooking Method: GRILLED
    Protein Type: Chicken
    Side Dishes: Mashed Potatoes (Starches), Green Beans (Vegetable)
    Gluten-Free: True
    */
    std::cout << "" << std::endl;
    main_course.display();
    std::cout << "Cooking Method: " << (main_course.getCookingMethod() == MainCourse::GRILLED ? "GRILLED" : "OTHER") << std::endl;
    std::cout << "Protein Type: " << main_course.getProteinType() << std::endl;
    std::cout << "Side Dishes:";
    for (const auto &side_dish : main_course.getSideDishes()) {
        std::cout << " " << side_dish.name << " (" << (side_dish.category == MainCourse::STARCHES ? "Starches" : "Vegetable") << ")";
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << (main_course.isGlutenFree() ? "True" : "False") << std::endl;

    /**
    Instantiate a dessert with the parameterized constructor:
    Name: "Chocolate Cake"
    Ingredients: ["Flour", "Sugar", "Cocoa Powder", "Eggs"]
    Preparation Time: 45
    Price: 7.99
    Cuisine Type: FRENCH
    Flavor Profile: SWEET
    Sweetness Level: 9
    Set the contains_nuts flag to false using the appropriate setter function. Print out the dessert's information using the accessor functions.
    Expected Output:
     Dish Name: Chocolate Cake
    Ingredients: Flour, Sugar, Cocoa Powder, Eggs
    Preparation Time: 45 minutes
    
    */
    std::vector<std::string> dessert_ingredients = {"Flour", "Sugar", "Cocoa Powder", "Eggs"};
    Dessert dessert(
        "Chocolate Cake", dessert_ingredients, 45, 7.99, Dish::CuisineType::FRENCH, Dessert::SWEET, 9, false
    );

    /**
    Price: $7.99
    Cuisine Type: FRENCH
    Flavor Profile: SWEET
    Sweetness Level: 9
    Contains Nuts: False
    */
    std::cout << "" << std::endl;
    dessert.display();
    dessert.setContainsNuts(false);
    std::cout << "Flavor Profile: " << (dessert.getFlavorProfile() == Dessert::SWEET ? "SWEET" : "OTHER") << std::endl;
    std::cout << "Sweetness Level: " << dessert.getSweetnessLevel() << std::endl;
    std::cout << "Contains Nuts: " << (dessert.containsNuts() ? "True" : "False") << std::endl;

    return 0;

    /** Test the setName() function */
    appetizer.setName("Bruschetta");
    /** Test the setIngredients() function */
    std::vector<std::string> new_ingredients = {"Tomatoes", "Basil", "Olive Oil", "Garlic"};
    appetizer.setIngredients(new_ingredients);


    /** Test the setPrepTime() function */
    appetizer.setPrepTime(15);
    std::cout << "Preparation Time: " << appetizer.getPrepTime() << " minutes" << std::endl;

    /** Test the setPrice() function */
    appetizer.setPrice(5.99);
    std::cout << "Price: $" << appetizer.getPrice() << std::endl;
    /** Test the setCuisineType() function */
    appetizer.setCuisineType(Dish::CuisineType::ITALIAN);
    std::cout << "Cuisine Type: " << appetizer.getCuisineType() << std::endl;
    /** Test the setSpicinessLevel() function */
    appetizer.setSpicinessLevel(5);
    std::cout << "Spiciness Level: " << appetizer.getSpicinessLevel() << std::endl;
    /** Test the setServingStyle() function */
    appetizer.setServingStyle(Appetizer::BUFFET);
    std::cout << "Serving Style: " << (appetizer.getServingStyle() == Appetizer::BUFFET ? "BUFFET" : "OTHER") << std::endl;
    /** Test the setVegetarian() function */
    appetizer.setVegetarian(false);
    std::cout << "Vegetarian: " << (appetizer.isVegetarian() ? "True" : "False") << std::endl;


    /** Test the setter methods for dessert */
    dessert.setName("Brownie");
    dessert.setIngredients({"Butter", "Sugar", "Cocoa Powder", "Eggs"});
    dessert.setPrepTime(30);
    dessert.setPrice(6.49);
    dessert.setCuisineType(Dish::CuisineType::AMERICAN);
    dessert.setFlavorProfile(Dessert::BITTER);
    dessert.setSweetnessLevel(6);
    dessert.setContainsNuts(true);

    // Test setters
    main_course.setName("BBQ Chicken");
    main_course.setIngredients({"Chicken", "BBQ Sauce"});
    main_course.setPrepTime(40);
    main_course.setPrice(19.99);
    main_course.setCuisineType(Dish::CuisineType::AMERICAN);
    main_course.setCookingMethod(MainCourse::BAKED);
    main_course.setProteinType("Chicken");
    main_course.addSideDish({"Coleslaw", MainCourse::VEGETABLE});
    main_course.setGlutenFree(false);
}
