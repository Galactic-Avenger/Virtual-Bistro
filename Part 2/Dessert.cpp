/** The Appetizer , MainCourse , and Dessert classes will extend the Dish class by introducing new attributes and functions. 
This is an exercise in inheritance, where the base class ( Dish ) is extended by specialized subclasses. **/

#include "Dessert.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert() 
: Dish(), sweetness_level_(0), flavor_profile_(), contains_nuts_(false) { }


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
Dessert::Dessert(const std::string &name, 
const std::vector<std::string> &ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts): Dish(name, ingredients, prep_time, price, cuisine_type), 
  sweetness_level_(sweetness_level), 
  flavor_profile_(flavor_profile), 
  contains_nuts_(contains_nuts) { }

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(FlavorProfile flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert (as an enum).
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */

void Dessert::setSweetnessLevel(int sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */

int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}
/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */

void Dessert::setContainsNuts(bool contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */

bool Dessert::containsNuts() const {
    return contains_nuts_;
}
