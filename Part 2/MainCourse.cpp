
#include"MainCourse.hpp"




/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
: Dish(), cooking_method_(), protein_type_(), side_dishes_(), gluten_free_(false) {}

  /**
   * Parameterized constructor.
   * @param name The name of the main course.
   * @param ingredients A vector of the ingredients used in the main
course.
   * @param prep_time The preparation time in minutes.
   * @param price The price of the main course.
   * @param cuisine_type The cuisine type of the main course.
   * @param cooking_method The cooking method used for the main course.
   * @param protein_type The type of protein used in the main course.
   * @param side_dishes A vector of the side dishes served with the main
course.
   * @param gluten_free Boolean flag indicating if the main course is
gluten-free.
   */

MainCourse::MainCourse(const std::string &name, const std::vector<std::string> &ingredients, int prep_time,
double price, CuisineType cuisine_type, CookingMethod cooking_method, const std::string &protein_type, const std::vector<SideDish> &side_dishes, bool gluten_free)
: Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}


/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the
parameter.
 */
void MainCourse::setCookingMethod(MainCourse::CookingMethod cooking_method) {
    cooking_method_ = cooking_method;
}


/**
 * @return The cooking method of the main course (as an enum).
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the
parameter.
 */
void MainCourse::setProteinType(const std::string &protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category
of the side dish.
* @post Adds the side dish to the `side_dishes_` vector.
*/
void MainCourse::addSideDish(const SideDish &side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes
served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-
free.
 * @post Sets the private member `gluten_free_` to the value of the
parameter.
 */
void MainCourse::setGlutenFree(bool gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const{
    return gluten_free_;
}

