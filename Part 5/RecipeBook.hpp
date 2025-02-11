/** RecipeBook.hpp defines specialized binary search tree for managing recipes, and the Recipe struct which represents individual recipes.**/

#ifndef RECIPEBOOK_HPP
#define RECIPEBOOK_HPP

#include "BinarySearchTree.hpp"

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <functional>
#include <memory> 
#include <sstream>



    /**
     * @brief A struct representing a recipe with metadata.
     */
struct Recipe 
{
    std::string name_;         // Name of the recipe.
    int difficulty_level_;     // Difficulty level (1-10).
    std::string description_;  // Description of the recipe.
    bool mastered_;            // Whether the recipe has been mastered.

    /**
     * @brief Default constructor.
     * @post Initializes name and description to empty strings, difficulty_level to 0, and mastered to false.
     */
    Recipe():name_(""),difficulty_level_(0),description_(""),mastered_(false){}

    /**
     * @brief Parameterized constructor.
     * @param name The name of the recipe.
     * @param difficulty_level The difficulty level of the recipe.
     * @param description The description of the recipe.
     * @param mastered Indicates Whether the recipe has been mastered (default is false).
     * @post Initializes the Recipe with the provided values.
     */
    Recipe(const std::string &name, int difficulty_level, const std::string &description, bool mastered){
        name_= name;
        difficulty_level_= difficulty_level;
        description_=description;
        mastered_= mastered;
    }
    
    // Implement the following operators based on name
    /**
     * Equality operator.
     * @param other Another Recipe to compare.
     * @return True if names are equal; false otherwise.
     */
    bool operator==(const Recipe& other) const { 
        return name_ == other.name_; 
        }


    /**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically less than other's name_; false
    otherwise.
    */
    bool operator<(const Recipe& other) const { 
        return name_ < other.name_;
     }   

    /**
    * Greater-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically greater than other's name_;
    false otherwise.
    */
    bool operator>(const Recipe& other) const { 
        return name_ > other.name_; 
        }

};


// A class for managing recipes using a binary search tree.
 
class RecipeBook : public BinarySearchTree<Recipe> {
public:
    /**
     * @brief Default constructor.
     * @post Initializes an empty RecipeBook.
     */
    RecipeBook();

    /**
    * Parameterized Constructor.
    * @param filename A const reference to a string representing the name of a
    CSV file.
    * @post: The RecipeBook is populated with Recipes from the CSV file.
    * The file format is as follows:
    * name,difficulty_level,description,mastered
    * Ignore the first line. Each subsequent line represents a Recipe to be
    added to the RecipeBook.
    */
    RecipeBook(const std::string &filename);

    /**
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult
    level).
    * @return: True if the Recipe was successfully added; false if a Recipe with
    the same name already exists.
    */
    bool addRecipe(const Recipe &recipe);

    /**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */
    std::shared_ptr<BinaryNode<Recipe>> findRecipe(const std::string& name);

    /**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
    */
    bool removeRecipe(const std::string &name);

    /**
     * Clears all recipes from the tree.
     * @post Tree is emptied, and all nodes are deallocated.
     */
    void clear();

    /**
    * Calculates the number of mastery points needed to master a Recipe.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: An integer representing the number of mastery points needed, or
    -1 if the Recipe is not found. If the recipe is already mastered, return 0.
    * Note: Mastery points are calculated as the number of unmastered Recipes in
    the tree with a lower difficulty level than the given Recipe. Add one if the
    Recipe is not mastered.
    */
    int calculateMasteryPoints(const std::string &name);

    /**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
    left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get
    sorted Recipes and rebuilding the tree.
    */
    void balance();

    /**
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)
    */
    void preorderDisplay();

private:

    // Helper Methods
    std::shared_ptr<BinaryNode<Recipe>> buildBalancedTree(const std::vector<Recipe>& sortedRecipes, int start, int end);
    std::shared_ptr<BinaryNode<Recipe>> findNodeByName(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, const std::string& name) const;
    std::shared_ptr<BinaryNode<Recipe>> removeNode(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, const std::string& name);
    std::shared_ptr<BinaryNode<Recipe>> getParentNode(std::shared_ptr<BinaryNode<Recipe>> node);
    void preorderDisplayHelper(const std::shared_ptr<BinaryNode<Recipe>>& node);
    std::vector<Recipe> getSortedList( std::shared_ptr<BinaryNode<Recipe>>root);








};


#endif // RECIPE_BOOK_HPP

