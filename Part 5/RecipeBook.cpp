/** RecipeBook.cpp  file implements a recipe management system using a binary search tree data structure where recipes are stored and organized based on their names. 
The implementation includes functionality for adding, removing, finding, and displaying recipes, as well as calculating mastery points and balancing the tree structure. **/


#include "RecipeBook.hpp"


// A class for managing recipes using a binary search tree. Implement the RecipeBook Class as a Subclass of BinarySearchTree
 
    /**
     * @brief Default constructor.
     * @post Initializes an empty RecipeBook.
     */
    RecipeBook::RecipeBook(){} 


    /**
    * Parameterized Constructor.
    * @param filename A const reference to a string representing the name of a CSV file.
    * @post: The RecipeBook is populated with Recipes from the CSV file.
    * The file format is as follows: name,difficulty_level,description,mastered
    * Ignore the first line. Each subsequent line represents a Recipe to be added to the RecipeBook.
    */
    RecipeBook::RecipeBook(const std::string& filename) {
    // Open the specified CSV file
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line); // Skip the header line

    // Process each line in the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, difficulty_str, description, mastered_str;
        
        // Parse the CSV line into individual fields
        if (std::getline(ss, name, ',') && 
            std::getline(ss, difficulty_str, ',') && 
            std::getline(ss, description, ',') && 
            std::getline(ss, mastered_str)) {
            
            try {
                // Convert string values to appropriate types
                int difficulty_level = std::stoi(difficulty_str);
                bool mastered = (mastered_str == "true" || mastered_str == "1");
                // Create and add the recipe to the tree
                Recipe recipe(name, difficulty_level, description, mastered);
                addRecipe(recipe);
            } catch (const std::exception& e) {
                continue; // Skip invalid entries
            }
        }
    }
    file.close();
}
    /**
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult
    level).
    * @return: True if the Recipe was successfully added; false if a Recipe with
    the same name already exists.
    */
    bool RecipeBook::addRecipe(const Recipe &recipe) {
    if (contains(recipe)) {
        return false; // Recipe already exist
    }
    add(recipe); //// Add recipe to BST
    return true;
}

//Helper method to find a recipe node by name using recursive search
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findNodeByName(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, const std::string &name) const {
    if (!subtree_ptr) return nullptr; // Base case: empty subtree
    
    if (subtree_ptr->getItem().name_ == name) {
        return subtree_ptr; // Found the recipe
    } 
    // Recursively search left or right subtree based on name comparison
    else if (subtree_ptr->getItem().name_ > name) {
        return findNodeByName(subtree_ptr->getLeftChildPtr(), name);
    } else {
        return findNodeByName(subtree_ptr->getRightChildPtr(), name);
    }
}
    /**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findRecipe(const std::string &name) {
    return findNodeByName(getRoot(), name); // Start search from root
}


    /**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
    */
    bool RecipeBook::removeRecipe(const std::string& name) {
        std::shared_ptr<BinaryNode<Recipe>> foundRecipeNode = findNodeByName(getRoot(), name); // Find the recipe node
        if(foundRecipeNode){
            // Create temporary recipe with same name for removal
            std::string recipeNAME = foundRecipeNode->getItem().name_; 
            Recipe tempRecipe(recipeNAME, 0, "", false);
            return BinarySearchTree<Recipe>::remove(tempRecipe);

        }
    return false;
}

    /**
     * Clears all recipes from the tree.
     * @post Tree is emptied, and all nodes are deallocated.
     */
    void RecipeBook::clear() {
     setRoot(nullptr);  // Set root to null which will deallocate all nodes
}
// Helper function to find parent node of a given node
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::getParentNode(std::shared_ptr<BinaryNode<Recipe>> node){
    // Base case: If the tree is empty or node is null
    if (this->isEmpty() || node == nullptr) {
        return nullptr;
    }
    
    // Start from the root
    auto current = this->getRoot();
    
    // If node is the root, it has no parent
    if (current == node) {
        return nullptr;
    }
    
    // Searrch for parent node
    while (current != nullptr) {
        // Check if the current node's left or right child is the target node
        if (current->getLeftChildPtr() == node || current->getRightChildPtr() == node) {
            return current; // Found the parent node
        }
        // Move to the left or right child based on BST property 
        else if (current->getItem() > node->getItem()) {
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    // If while loop existed, it will means the parent node was not found in the tree
    return nullptr;
}
    

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
   int RecipeBook::calculateMasteryPoints(const std::string &name) {
    auto recipe_node = findRecipe(name);
    if (!recipe_node) {
        return -1; // Recipe not found
    }

    Recipe target_recipe = recipe_node->getItem();
    if (target_recipe.mastered_) {
        return 0; // Already mastered
    }

    int mastery_points = 0;

    std::function<void(const std::shared_ptr<BinaryNode<Recipe>> &)> traverse;
    traverse = [&traverse, &mastery_points, &target_recipe](const std::shared_ptr<BinaryNode<Recipe>> &node) {
        if (!node) return;

        // Count unmastered recipes with lower difficulty
        if (node->getItem().difficulty_level_ < target_recipe.difficulty_level_ &&
            !node->getItem().mastered_) {
            mastery_points++;
        }

        traverse(node->getLeftChildPtr());// Traverse left
        traverse(node->getRightChildPtr());// Traverse right
    };

    traverse(getRoot());

    return mastery_points + 1; // Include target recipe itself
}
// Helper function to build a balanced BST from sorted vector
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::buildBalancedTree(const std::vector<Recipe> &vec, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2; // find middle element
    auto root = std::make_shared<BinaryNode<Recipe>>(vec[mid]);
    // Build left & Right subtrees
    root->setLeftChildPtr(buildBalancedTree(vec, start, mid - 1));
    root->setRightChildPtr(buildBalancedTree(vec, mid + 1, end));

    return root;
}

//Helper function to get sorted list of recipes using inorder traversal
std::vector<Recipe> RecipeBook::getSortedList( std::shared_ptr<BinaryNode<Recipe>> root) {
    std::vector<Recipe> result;
    // function for inorder traversal
    std::function<void(std::shared_ptr<BinaryNode<Recipe>>)> inOrderTraverse =
        [&result, &inOrderTraverse](std::shared_ptr<BinaryNode<Recipe>> node) {
            if (!node) return;
            inOrderTraverse(node->getLeftChildPtr()); // visit left node
            result.push_back(node->getItem()); // visit node
            inOrderTraverse(node->getRightChildPtr()); // visit right node
        };
    inOrderTraverse(root);
    return result;
}

    /**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
    left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get
    sorted Recipes and rebuilding the tree.
    */
    void RecipeBook::balance() {
    std::vector<Recipe> sorted_recipes = getSortedList(getRoot()); // Get sorted recipes
    clear(); // Clear current tree
    setRoot(buildBalancedTree(sorted_recipes, 0, sorted_recipes.size() - 1)); // Rebuild balanced tree
}

// Helper function for preorder display
void RecipeBook::preorderDisplayHelper(const std::shared_ptr<BinaryNode<Recipe>> &node) {
    if (!node) {
        return;
    }
    // Display current node's recipe information
    const Recipe &recipe = node->getItem();
    std::cout << "Name: " << recipe.name_ << "\n"
              << "Difficulty Level: " << recipe.difficulty_level_ << "\n"
              << "Description: " << recipe.description_ << "\n"
              << "Mastered: " << (recipe.mastered_ ? "Yes" : "No") << "\n\n";

    preorderDisplayHelper(node->getLeftChildPtr()); // Visit left subtree
    preorderDisplayHelper(node->getRightChildPtr()); // Visit right subtree
}
    /**
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)
    */
void RecipeBook::preorderDisplay() {
    preorderDisplayHelper(getRoot()); // Start the display from root
}

