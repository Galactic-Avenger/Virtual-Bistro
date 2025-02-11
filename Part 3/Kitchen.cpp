// The Kitchen implementation is a subclass of ArrayBag that stores Dish objects. Provides the implementation for adding and serving dishes, calculating aggregate preparation times, counting elaborate dishes, releasing dishes based on criteria like cuisine type or preparation time, and generating detailed reports on the current state of dishes in the kitchen.

#include "Kitchen.hpp"


/**
* Default constructor.
* Default-initializes all private members.
*/

Kitchen::Kitchen(): ArrayBag<Dish>(), totalprep_time(0), countelaborate(0) {}

  /**
  * @param : A reference to a `Dish` being added to the kitchen.
  * @post : If the given `Dish` is not already in the kitchen, adds the`Dish` to the kitchen and updates the preparation time sum and elaborate dish count if the dish is elaborate.
  * @return : Returns true if a `Dish` was successfully added to the
  kitchen, false otherwise.
  Hint: Use the above definition of equality to help determine if a
  `Dish` is already in the kitchen.
  */

bool Kitchen::newOrder(const Dish& dish) {
    // Check if the dish is already in the kitchen
    if (this->contains(dish)) {
        return false;
    }
    // Add the dish to the kitchen
    if (this->add(dish)) {
        // Update the total preparation time
        totalprep_time += dish.getPrepTime();
        // Check if the dish meets the criteria for being elaborate
        if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60) {
            countelaborate++;  // Update the elaborate dish count
        }

        return true;
    }
    return false;
}

  /**
  * @param : A reference to a `Dish` leaving the kitchen.
  * @return : Returns true if a dish was successfully removed from the
  kitchen (i.e.,
  items_), false otherwise.
  * @post : Removes the dish from the kitchen and updates the preparation
  time sum.
  If the `Dish` is elaborate, it also updates the elaborate count.
  */

bool Kitchen::serveDish(const Dish& dish) {
    if (this->remove(dish)) {
        totalprep_time -= dish.getPrepTime();
        // Check if the dish meets the criteria for being elaborate
        if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60) {
            countelaborate--;  // Update the elaborate dish count
        }

        return true;
    }
    return false;
}

  /**
 * @return : The integer sum of preparation times for all the dishes currently in the kitchen. 
 */

int Kitchen::getPrepTimeSum() const {
    return totalprep_time;
}

/**
* @return : The average preparation time (int) of all the dishes in the
kitchen. The lowest possible average prep time should be 0.
* @post : Computes the average preparation time (double) of the kitchen
rounded to the NEAREST integer.
*/

int Kitchen::calculateAvgPrepTime() const {
    int itemCount = this->getCurrentSize(); // Assumes ArrayBag has this method.
    if (itemCount == 0) return 0;
    return std::round(static_cast<double>(totalprep_time) / itemCount);
}


/**
* @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const {
    return countelaborate;
}

 /**
 * @return : The percentage (double) of all the elaborate dishes in the
 kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 rounded up to 2 decimal places.
 */

double Kitchen::calculateElaboratePercentage() const {
    int itemCount = this->getCurrentSize();
    if (itemCount == 0) return 0.0;
    double percentage = static_cast<double>(countelaborate) * 100.0 / itemCount;
        // Round up to two decimal places
        return std::ceil(percentage * 100) / 100;
    }

 /**
 * @param : A reference to a string representing a cuisine type with a
 value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
 "FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the
 given cuisine type.
 If the argument string does not match one of the expected
 cuisine types, the tally is zero.
 NOTE: No pre-processing of the input string necessary, only
 uppercase input will match.
 */

int Kitchen::tallyCuisineTypes(const std::string& cuisineType) const {
    int tally = 0;
    for (int i = 0; i < getCurrentSize(); ++i) {
        if (items_[i].getCuisineType() == cuisineType) {
            ++tally;
        }
    }
    return tally;
}

/**
* @param : A reference to an integer representing the preparation time
threshold of the dishes to be removed from the kitchen.
* @post : Removes all dishes from the kitchen whose preparation time is less than the given time.
* @return : The number of dishes removed from the kitchen.
*/

int Kitchen::releaseDishesBelowPrepTime(int prep_time) {
    int removed_count = 0;
    for (int i = 0; i < getCurrentSize();) {
        if (items_[i].getPrepTime() < prep_time) {
            remove(items_[i]);
            ++removed_count;
                  } else {
                      ++i;
                  }
              }
    return removed_count;
}

/**
* @param : A reference to a string representing a cuisine type with a value in ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN","FRENCH", "OTHER"].
* @post : Removes all dishes from the kitchen whose cuisine type matches the given type.
* @return : The number of dishes removed from the kitchen.
NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
If the input string does not match one of the expected cuisine types, do not remove any dishes.
*/

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisineType) {
    int removed_count = 0;
    for (int i = 0; i < getCurrentSize(); ++i) {
        if (items_[i].getCuisineType() == cuisineType) {
            if (this->serveDish(items_[i])) {
                ++removed_count;
                --i;  // Adjust index to account for item removal
            }
        }
    }
    return removed_count;
}

/**
form:
* @post : Outputs a report of the dishes currently in the kitchen in the
"ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
{x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
Note that the average preparation time should be rounded to the NEAREST integer, and the percentage of elaborate dishes in the kitchen should be rounded to 2 decimal places.
Example output:
ITALIAN: 2
MEXICAN: 3
CHINESE: 2
INDIAN: 1
AMERICAN: 1
FRENCH: 2
OTHER: 2
AVERAGE PREP TIME: 62
ELABORATE DISHES: 53.85%
*/

void Kitchen::kitchenReport() const {
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}
