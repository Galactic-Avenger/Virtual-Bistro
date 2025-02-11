//Author: Abdulla Saleh
//Course: CSCI 235
//Instructor: Prof. Wole Oyekoya 
//Assignment: Project 2 
//Date: Sep/25/2024
// Project 2- Project 2- The Appetizer , MainCourse , and Dessert classes will extend the Dish class by introducing new attributes and functions. This is an exercise in inheritance, where the base class ( Dish ) is extended by specialized subclasses.


#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP
#include <iostream>
#include <string>
#include "Dish.hpp"


//The MainCourse class is a subclass of Dish that represents a main course dish.
class MainCourse : public Dish {

public:

// Describes the method used to cook the main course.
enum CookingMethod { GRILLED, BAKED, FRIED, STEAMED, RAW };

// Describes the category of the side dish.
enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };

// Represents a side dish associated with the main course.
struct SideDish{
std::string name;
Category category;
};



public:
/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse();

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
MainCourse(const std::string &name, const std::vector<std::string> &ingredients, int prep_time, double price, CuisineType cuisine_type, CookingMethod cooking_method, const std::string &protein_type, const std::vector<SideDish> &side_dishes, bool gluten_free);


/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */

void setCookingMethod(CookingMethod cooking_method);

/**
 * @return The cooking method of the main course (as an enum).
 */

CookingMethod getCookingMethod() const;

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */

void setProteinType(const std::string &protein_type);

/**
 * @return The type of protein in the main course.
 */

std::string getProteinType() const;

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */

void addSideDish(const SideDish &side_dish);

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */

std::vector<SideDish> getSideDishes() const;

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */

void setGlutenFree(bool gluten_free);

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool isGlutenFree() const;

private:
CookingMethod cooking_method_;// The cooking method used for the main course.
std::string protein_type_;// A string representing the type of protein used in the main course.
std::vector<SideDish> side_dishes_; // A vector containing SideDish structs representing the side dishes served with the main course.
bool gluten_free_; // A flag indicating if the main course is gluten-free.


};

#endif // MAINCOURSE_HPP
