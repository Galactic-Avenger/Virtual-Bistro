/** The Appetizer , MainCourse , and Dessert classes will extend the Dish class by introducing new attributes and functions. This is an exercise in inheritance, 
where the base class ( Dish ) is extended by specialized subclasses. **/

#ifndef DESSERT_HPP
#define DESSERT_HPP
#include <iostream>
#include <string>
#include <vector>
#include "Dish.hpp"

//The Dessert class is a subclass of Dish that represents a dessert dish.
class Dessert : public Dish{

// Flavor 
public:
enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };

public:
/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert();

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert(const std::string &name, const std::vector<std::string> &ingredients, int prep_time, 
double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts);


/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void setFlavorProfile(FlavorProfile flavor_profile);

/**
 * @return The flavor profile of the dessert (as an enum).
 */
FlavorProfile getFlavorProfile() const;

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */

void setSweetnessLevel(int sweetness_level);
/**
 * @return The sweetness level of the dessert.
 */

int getSweetnessLevel() const;
/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */

void setContainsNuts(bool contains_nuts);
/**
 * @return True if the dessert contains nuts, false otherwise.
 */

bool containsNuts() const;

private:
int sweetness_level_; // The flavor profile of the dessert.
FlavorProfile flavor_profile_; // An integer representing the sweetness level of the dessert on a scale of 1 to 10.
bool contains_nuts_; //A flag indicating if the dessert contains nuts.


};

#endif //DESSERT_HPP
