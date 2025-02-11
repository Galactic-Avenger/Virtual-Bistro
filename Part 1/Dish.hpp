#ifndef DISH_HPP
#define DISH_HPP

#include <iostream> 
#include <sstream>
#include <cctype>
#include <string> 
#include <iomanip>
#include <vector>


// The Dish class represents a dish in the restaurant simulation.
class Dish{

// Provides options for the category of a creature.
public:
enum CuisineType {ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER};

// Private
private:
std::string name_; // The name of dish.
std::vector<std::string> ingredients_; // The ingredients of dish.
int prep_time_; // The preparation time of dish in minutes.
double price_; // The price of dish.
CuisineType cuisine_type_; // The cuisine type of dish.

public:

/**
 * Default constructor.
 * Initializes all private members with default values:
 * - name: "UNKNOWN"
 * - ingredients: Empty list
 * - prep_time: 0
 * - price: 0.0
 * - cuisine_type: OTHER
 */

Dish();

 /**
 * Parameterized constructor.
 * @param name A reference to the name of the dish.
 * @param ingredients A reference to a list of ingredients (default is
empty list).
 * @param prep_time The preparation time in minutes (default is 0).
 * @param price The price of the dish (default is 0.0).
 * @param cuisine_type The cuisine type of the dish (a CuisineType enum)
with default value OTHER.
* @post The private members are set to the values of the corresponding
parameters.
*/

Dish(const std::string& name, const std::vector<std::string>& ingredients, int prep_time = 0 , double price = 0.0, CuisineType cuisine_type = OTHER);


/**
 * Sets the name of the dish.
 * @param name A reference to the new name of the dish.
 * @post Sets the private member `name_` to the value of the parameter.
 */

void setName(const std::string& name);

/**
 * @return The name of the dish.
 */

std::string getName() const;

/**
 * Sets the list of ingredients.
 * @param ingredients A reference to the new list of ingredients.
 * @post Sets the private member `ingredients_` to the value of the
parameter.
 */

bool setIngredients(const std::vector<std::string>& ingredients);

/**
 * @return The list of ingredients used in the dish.
 */

std::vector<std::string> getIngredients() const;

/**
 * Sets the preparation time.
 * @param prep_time The new preparation time in minutes.
 * @post Sets the private member `prep_time_` to the value of the
parameter.
 */

bool setPrepTime(int prep_time);

/**
 * @return The preparation time in minutes.
 */

int getPrepTime() const;

/**
 * Sets the price of the dish.
 * @param price The new price of the dish.
 * @post Sets the private member `price_` to the value of the parameter.
 */

bool setPrice(double price);
/**
 * @return The price of the dish.
 */

double getPrice() const;

/**
 * Sets the cuisine type of the dish.
 * @param cuisine_type The new cuisine type of the dish (a CuisineType
enum).
 * @post Sets the private member `cuisine_type_` to the value of the
parameter.
 */

void setCuisineType(CuisineType cuisine_type);

/**
 * @return The cuisine type of the dish in string form.
 */

std::string getCuisineType() const;

/**
 * Displays the details of the dish.
 * @post Outputs the dish's details, including name, ingredients,
preparation time, price, and cuisine type, to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
*/
void display() const;

};

#endif
