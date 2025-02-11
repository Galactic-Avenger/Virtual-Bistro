#include "Dish.hpp"

// Default constructor.
// Initializes all private members with default values:
// - name: "UNKNOWN"
// - ingredients: Empty list
// - prep_time: 0
// - price: 0.0
// - cuisine_type: OTHER
Dish::Dish()
  : name_("UNKNOWN"), ingredients_(), prep_time_(0), price_(0.0), cuisine_type_(OTHER) {}

/**
 * Parameterized constructor.
 * @param name A reference to the name of the dish.
 * @param ingredients A reference to a list of ingredients (default is empty list).
 * @param prep_time The preparation time in minutes (default is 0).
 * @param price The price of the dish (default is 0.0).
 * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
 * @post The private members are set to the values of the corresponding parameters.
 */
Dish::Dish(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type)
  : name_(name), ingredients_(ingredients), prep_time_(prep_time), price_(price), cuisine_type_(cuisine_type) {}

/**
 * Sets the name of the dish.
 * @param name A reference to the new name of the dish.
 * @post Sets the private member `name_` to the value of the parameter.
 */
void Dish::setName(const std::string& name) {
  name_ = name;
}
/**
 * @return The name of the dish.
 */
std::string Dish::getName() const {
  return name_;
}
/**
 * Sets the list of ingredients.
 * @param ingredients A reference to the new list of ingredients.
 * @post Sets the private member `ingredients_` to the value of the parameter.
 */
bool Dish::setIngredients(const std::vector<std::string>& ingredients) {
  ingredients_ = ingredients;
  return true;
}
/**
 * @return The list of ingredients used in the dish.
 */
std::vector<std::string> Dish::getIngredients() const {
  return ingredients_;
}
/**
 * Sets the preparation time.
 * @param prep_time The new preparation time in minutes.
 * @post Sets the private member `prep_time_` to the value of the parameter.
 */
bool Dish::setPrepTime(int prep_time) {
  prep_time_ = prep_time;
  return true;
}
/**
 * @return The preparation time in minutes.
 */
int Dish::getPrepTime() const {
  return prep_time_;
}
/**
 * Sets the price of the dish.
 * @param price The new price of the dish.
 * @post Sets the private member `price_` to the value of the parameter.
 */
bool Dish::setPrice(double price) {
  price_ = price;
  return true;
}
/**
 * @return The price of the dish.
 */
double Dish::getPrice() const {
  return price_;
}
/**
 * Sets the cuisine type of the dish.
 * @param cuisine_type The new cuisine type of the dish (a CuisineType enum).
 * @post Sets the private member `cuisine_type_` to the value of the parameter.
 */
void Dish::setCuisineType(CuisineType cuisine_type) {
  cuisine_type_ = cuisine_type;
}
/**
 * @return The cuisine type of the dish in string form.
 */
std::string Dish::getCuisineType() const {
  switch (cuisine_type_) {
    case ITALIAN: return "ITALIAN";
    case MEXICAN: return "MEXICAN";
    case CHINESE: return "CHINESE";
    case INDIAN: return "INDIAN";
    case AMERICAN: return "AMERICAN";
    case FRENCH: return "FRENCH";
    default: return "OTHER";
  }
}
/**
 * Displays the details of the dish.
 * @post Outputs the dish's details, including name, ingredients, preparation time, price, and cuisine type, to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 */
void Dish::display() const {
  std::ostringstream oss;
  oss << "Dish Name: " << name_ << "\n"
      << "Ingredients: ";
  for (size_t i = 0; i < ingredients_.size(); ++i) {
    oss << ingredients_[i];
    if (i < ingredients_.size() - 1) {
      oss << ", ";
    }
  }
  oss << "\n"
      << "Preparation Time: " << prep_time_ << " minutes\n"
      << std::fixed << std::setprecision(2)
      << "Price: $" << price_ << "\n"
      << "Cuisine Type: " << getCuisineType();
  std::cout << oss.str() << std::endl;
}
