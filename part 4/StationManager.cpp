// StationManager.cpp contains the implementation file for the StationManager class, which manages kitchen stations,dish preparation, and ingredient replenishment.
#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

/**
 * Retrieves the current dish preparation queue.
 * @return: A copy of the queue containing pointers to Dish objects.
 * @post: The dish preparation queue remains unchanged.
 */
std::queue<Dish*> StationManager::getDishQueue() const {
    return dish_queue_;
}

/**
 * Retrieves the list of backup ingredients.
 * @return: A vector containing Ingredient objects representing backup supplies.
 * @post: The backup ingredients remain unchanged.
 */
std::vector<Ingredient> StationManager::getBackupIngredients() const {
    return backup_ingredients_;
}

/**
 * Sets the current dish preparation queue.
 * @param dish_queue A queue containing pointers to Dish objects.
 * @pre: The dish_queue contains valid pointers to dynamically allocated Dish objects.
 * @post: The dish preparation queue is replaced with the provided queue.
 */
void StationManager::setDishQueue(const std::queue<Dish*>& dish_queue) {
    // Clear the current queue to avoid memory leaks
    clearDishQueue();

    // Copy the provided queue to the member variable
    dish_queue_ = dish_queue;
}

/**
 * Adds a dish to the preparation queue without dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @pre: The dish pointer is not null.
 * @post: The dish is added to the end of the queue.
 */
void StationManager::addDishToQueue(Dish* dish) {
    if (!dish) {
        throw std::invalid_argument("Dish pointer must not be null.");
    }
    dish_queue_.push(dish);
}

/**
 * Adds a dish to the preparation queue with dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @param request A DietaryRequest object specifying dietary accommodations.
 * @pre: The dish pointer is not null.
 * @post: The dish is adjusted for dietary accommodations and added to the queue.
 */
void StationManager::addDishToQueue(Dish* dish, const Dish::DietaryRequest& request) {
    if (!dish) {
        throw std::invalid_argument("Dish pointer must not be null.");
    }

    // Adjust the dish for dietary accommodations
    dish->dietaryAccommodations(request);

    // Add the dish to the queue after adjustments
    dish_queue_.push(dish);
}

/**
 * Prepares the next dish in the queue if possible.
 * @pre: The dish queue is not empty.
 * @post: The dish is processed and removed from the queue.
 *        If the dish cannot be prepared, it stays in the queue.
 * @return: True if the dish was prepared successfully; false otherwise.
 */
bool StationManager::prepareNextDish() {
    if (dish_queue_.empty()) {
        return false; // No dish to prepare
    }

    Dish* dish = dish_queue_.front(); // Get the first dish in the queue
    Node<KitchenStation*>* stationNode = getHeadNode(); // Start from the first station

    // Iterate through the stations
    while (stationNode != nullptr) {
        KitchenStation* station = stationNode->getItem();
        if (station->prepareDish(dish->getName())) {
            dish_queue_.pop(); // Remove the prepared dish from the queue
            return true;       // Successfully prepared the dish
        }
        stationNode = stationNode->getNext(); // Move to the next station
    }

    // No station could prepare the dish
    return false;
}

/**
 * Displays all dishes currently in the preparation queue.
 * @pre: None.
 * @post: Outputs the names of the dishes in the queue, one per line.
 */
void StationManager::displayDishQueue() const {
    std::queue<Dish*> temp_queue = dish_queue_; // Temporary copy of the queue

    // Print each dish name in the queue
    while (!temp_queue.empty()) {
        Dish* dish = temp_queue.front();
        std::cout << dish->getName() << std::endl;
        temp_queue.pop();
    }
}

/**
 * Clears all dishes from the preparation queue.
 * @post: The dish queue is emptied, and all allocated memory is freed.
 */
void StationManager::clearDishQueue() {
    // Free memory for each dish and remove it from the queue
    while (!dish_queue_.empty()) {
        Dish* dish = dish_queue_.front();
        delete dish;          // Free dynamically allocated memory
        dish_queue_.pop();    // Remove the dish from the queue
    }
}

/**
 * Replenishes a specific ingredient at a given station from the backup stock.
 * @param station_name The name of the station.
 * @param ingredient_name The name of the ingredient to replenish.
 * @param quantity The amount to replenish.
 * @return: True if the ingredient was replenished successfully; false otherwise.
 * @post: Updates the ingredient stock at the station and adjusts the backup stock.
 */
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity) {
    KitchenStation* station = findStation(station_name); // Find the station by name
    if (!station) {
        return false; // Station not found
    }

    // Search for the ingredient in the backup stock
    for (size_t i = 0; i < backup_ingredients_.size(); ++i) {
        Ingredient& ingredient = backup_ingredients_[i];

        // Check if the ingredient matches and has sufficient quantity
        if (ingredient.name == ingredient_name && ingredient.quantity >= quantity) {
            // Replenish the station with the ingredient
            station->replenishStationIngredients(Ingredient(ingredient.name, quantity, 0, ingredient.price));

            // Deduct the used quantity from the backup stock
            ingredient.quantity -= quantity;

            // Remove the ingredient from backup if it's fully used up
            if (ingredient.quantity == 0) {
                backup_ingredients_.erase(backup_ingredients_.begin() + i);
            }

            return true; // Replenishment successful
        }
    }

    // Ingredient not found or insufficient quantity in backup
    return false;
}

/**
 * Adds a batch of ingredients to the backup stock.
 * @param ingredients A vector of Ingredient objects to add to the backup stock.
 * @return: True if all ingredients were added successfully; false otherwise.
 * @post: The backup stock is updated with the provided ingredients.
 */
bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients) {
    if (ingredients.empty()) {
        return false; // Nothing to add
    }

    // Replace the current backup ingredients with the new batch
    backup_ingredients_ = ingredients;
    return true;
}

/**
 * Adds a single ingredient to the backup stock.
 * @param ingredient An Ingredient object to add to the backup stock.
 * @return: True if the ingredient was added; false otherwise.
 * @post: If the ingredient already exists, its quantity is increased; otherwise, it is added.
 */
bool StationManager::addBackupIngredient(const Ingredient& ingredient) {
    // Check if the ingredient already exists in the backup stock
    for (Ingredient& backup_ingredient : backup_ingredients_) {
        if (backup_ingredient.name == ingredient.name) {
            // Increase the quantity of the existing ingredient
            backup_ingredient.quantity += ingredient.quantity;
            return true;
        }
    }

    // Add the new ingredient to the backup stock
    backup_ingredients_.push_back(ingredient);
    return true;
}


/**
 * Clears all ingredients from the backup stock.
 * @post: The backup_ingredients_ vector is emptied.
 */
void StationManager::clearBackupIngredients() {
    backup_ingredients_.clear();
}

/**
* Processes all dishes in the queue and displays detailed results.
* @pre: None.
* @post: All dishes are processed, and detailed information is displayed
(as per the format in the specifications), including station replenishments
and preparation results.
* If a dish cannot be prepared even after replenishing ingredients, it
stays in the queue in its original order...
* i.e. if multiple dishes cannot be prepared, they will remain in the queue
in the same order
*/
/**
 * Processes all dishes in the queue and displays preparation details.
 * @pre: None.
 * @post: Dishes are processed sequentially. If a dish cannot be prepared, it is returned to the queue.
 *        Logs the preparation status, replenishment details, and unavailability of dishes.
 */
void StationManager::processAllDishes() {
    std::queue<Dish *> unPreparedDishes; // Queue to hold unprepared dishes

    // Process each dish in the preparation queue
    while (!dish_queue_.empty()) {
        Dish* dish = dish_queue_.front(); // Get the dish at the front of the queue
        bool isPrepared = false;         // Tracks whether the dish has been successfully prepared
        bool isFound = false;            // Tracks whether the dish is found in the current station

        std::cout << "PREPARING DISH: " << dish->getName() << std::endl;

        // Iterate through all kitchen stations
        for (int i = 0; i < item_count_; ++i) {
            KitchenStation* kitchenStation = getEntry(i); // Get the current station
            std::cout << kitchenStation->getName() << ": attempting to prepare " << dish->getName() << "..." << std::endl;

            isFound = false; // Reset dish found flag for the current station

            // Check if the dish is available in the current station
            for (Dish* station_dish : kitchenStation->getDishes()) {
                if (station_dish->getName() == dish->getName()) {
                    isFound = true; // Dish is found in this station

                    // Check if the station can complete the order
                    if (kitchenStation->canCompleteOrder(dish->getName())) {
                        // Attempt to prepare the dish
                        if (kitchenStation->prepareDish(dish->getName())) {
                            isPrepared = true;
                            std::cout << kitchenStation->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                        }
                    } else {
                        // Handle replenishment if ingredients are insufficient
                        std::cout << kitchenStation->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;

                        // Replenish all required ingredients
                        for (const Ingredient& requiredIngredient : station_dish->getIngredients()) {
                            bool isIngredientFound = false; // Tracks if the ingredient is in stock

                            // Check the station's ingredient stock
                            for (const Ingredient& stockIngredient : kitchenStation->getIngredientsStock()) {
                                if (requiredIngredient.name == stockIngredient.name) {
                                    isIngredientFound = true;

                                    // Calculate the shortage
                                    int requiredQuantity = requiredIngredient.required_quantity - stockIngredient.quantity;

                                    // Replenish if there is a shortage
                                    if (requiredQuantity > 0) {
                                        if (!replenishStationIngredientFromBackup(kitchenStation->getName(), requiredIngredient.name, requiredQuantity)) {
                                            std::cout << kitchenStation->getName() 
                                                      << ": Unable to replenish ingredients. Failed to prepare " 
                                                      << dish->getName() << "." << std::endl;
                                            break;
                                        }
                                    }
                                    break; // Stop searching once the ingredient is found
                                }
                            }

                            // If the ingredient was not found in stock, attempt replenishment
                            if (!isIngredientFound) {
                                if (!replenishStationIngredientFromBackup(kitchenStation->getName(), requiredIngredient.name, requiredIngredient.required_quantity)) {
                                    std::cout << kitchenStation->getName() 
                                              << ": Unable to replenish ingredients. Failed to prepare " 
                                              << dish->getName() << "." << std::endl;
                                    break; // Stop replenishment attempts if one ingredient fails
                                }
                            }
                        }

                        // Retry preparing the dish after replenishment
                        if (kitchenStation->prepareDish(dish->getName())) {
                            std::cout << kitchenStation->getName() << ": Ingredients replenished." << std::endl;
                            std::cout << kitchenStation->getName() << ": Successfully prepared " 
                                      << dish->getName() << "." << std::endl;
                            isPrepared = true;
                            break; // Stop iterating through stations
                        }
                    }
                }
            }

            // Log if the dish is not available at the current station
            if (!isFound) {
                std::cout << kitchenStation->getName() << ": Dish not available. Moving to next station..." << std::endl;
            }

            // Stop searching if the dish has been prepared
            if (isPrepared) {
                break;
            }
        }

        // If the dish could not be prepared, add it to the unprepared dishes queue
        if (!isPrepared) {
            std::cout << dish->getName() << " was not prepared." << std::endl;
            unPreparedDishes.push(dish);
        }

        dish_queue_.pop(); // Remove the dish from the original queue
        std::cout << std::endl; // Add a blank line for readability
    }

    // Restore unprepared dishes to the main queue
    setDishQueue(unPreparedDishes);

    // Final message
    std::cout << std::endl << std::endl << "All dishes have been processed." << std::endl;
}


