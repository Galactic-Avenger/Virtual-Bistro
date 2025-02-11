/** Header file for the StationManager class, which manages kitchen stations, dish preparation, ingredient replenishment, and the dish preparation queue. **/

#ifndef STATIONMANAGER_HPP
#define STATIONMANAGER_HPP

#include "LinkedList.hpp"
#include "KitchenStation.hpp"
#include "Dish.hpp"
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

class StationManager : public LinkedList<KitchenStation*> {
    
public:
    /**
     * Default Constructor
     * @post: Initializes an empty station manager.
     */
    StationManager();

    

    /**
     * Adds a new station to the station manager.
     * @param station A pointer to a KitchenStation object.
     * @post: Inserts the station into the linked list.
     */
    bool addStation(KitchenStation* station);

    /**
     * Removes a station from the station manager by name.
     * @param station_name A string representing the station's name.
     * @post: Removes the station from the list and deallocates it.
     * @return: True if the station was found and removed; false otherwise.
     */
    bool removeStation(const std::string& station_name);

    /**
     * Finds a station in the station manager by name.
     * @param station_name A string representing the station's name.
     * @return: A pointer to the KitchenStation if found; nullptr otherwise.
     */
    KitchenStation* findStation(const std::string& station_name) const;

    /**
     * Moves a specified station to the front of the station manager list.
     * @param station_name A string representing the station's name.
     * @post: The station is moved to the front of the list if it exists.
     * @return: True if the station was found and moved; false otherwise.
     */
    bool moveStationToFront(const std::string& station_name);

    /**
     * Merges the dishes and ingredients of two specified stations.
     * @param station_name1 The name of the first station.
     * @param station_name2 The name of the second station.
     * @post: The second station is removed from the list, and its contents are added to the first station.
     * @return: True if both stations were found and merged; false otherwise.
     */
    bool mergeStations(const std::string& station_name1, const std::string& station_name2);

    /**
     * Assigns a dish to a specific station.
     * @param station_name A string representing the station's name.
     * @param dish A pointer to a Dish object.
     * @post: Assigns the dish to the specified station.
     * @return: True if the station was found and the dish was assigned; false otherwise.
     */
    bool assignDishToStation(const std::string& station_name, Dish* dish);

    /**
     * Replenishes an ingredient at a specific station.
     * @param station_name A string representing the station's name.
     * @param ingredient An Ingredient object.
     * @post: Replenishes the ingredient stock at the specified station.
     * @return: True if the station was found and the ingredient was replenished; false otherwise.
     */
    bool replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient);

    /**
     * Checks if any station in the station manager can complete an order for a specific dish.
     * @param dish_name A string representing the name of the dish.
     * @return: True if any station can complete the order; false otherwise.
     */
    bool canCompleteOrder(const std::string& dish_name) const;

    /**
     * Prepares a dish at a specific station if possible.
     * @param station_name A string representing the station's name.
     * @param dish_name A string representing the name of the dish.
     * @post: If the dish can be prepared, reduces the quantities of the used ingredients at the station.
     * @return: True if the dish was prepared successfully; false otherwise.
     */
    bool prepareDishAtStation(const std::string& station_name, const std::string& dish_name);

    /**
     * Retrieves the current dish preparation queue.
     * @return: A copy of the queue containing pointers to Dish objects.
     * @post: The dish preparation queue remains unchanged.
     */
    std::queue<Dish*> getDishQueue() const;

    /**
     * Retrieves the list of backup ingredients.
     * @return: A vector containing Ingredient objects representing backup supplies.
     * @post: The backup ingredients remain unchanged.
     */
    std::vector<Ingredient> getBackupIngredients() const;

    /**
    * Sets the current dish preparation queue.
    * @param dish_queue A queue containing pointers to Dish objects.
    * @pre: The dish_queue contains valid pointers to dynamically allocated
    Dish objects.
    * @post: The dish preparation queue is replaced with the provided
    queue.
    */
    void setDishQueue(const std::queue<Dish*>& dish_queue);
    

    /**
     * Adds a dish to the preparation queue without dietary accommodations.
     * @param dish A pointer to a dynamically allocated Dish object.
     * @pre: The dish pointer is not null.
     * @post: The dish is added to the end of the queue.
     */
    void addDishToQueue(Dish* dish);

    /**
     * Adds a dish to the preparation queue with dietary accommodations.
     * @param dish A pointer to a dynamically allocated Dish object.
     * @param request A DietaryRequest object specifying dietary accommodations.
     * @pre: The dish pointer is not null.
     * @post: The dish is adjusted for dietary accommodations and added to the queue.
     */
    void addDishToQueue(Dish* dish, const Dish::DietaryRequest& request);

    /**
    * Prepares the next dish in the queue if possible.
    * @pre: The dish queue is not empty.
    * @post: The dish is processed and removed from the queue.
    * If the dish cannot be prepared, it stays in the queue
    * @return: True if the dish was prepared successfully; false otherwise.
    */
    bool prepareNextDish();
    
    /**
     * Displays all dishes in the preparation queue.
     * @post: Outputs the names of the dishes in the queue in order, one per line.
     */
    void displayDishQueue() const;

    /**
     * Clears all dishes from the preparation queue.
     * @post: The dish queue is emptied, and all allocated memory is freed.
     */
    void clearDishQueue();

    /**
     * Replenishes a specific ingredient at a given station from the backup stock.
     * @param station_name The name of the station.
     * @param ingredient_name The name of the ingredient to replenish.
     * @param quantity The amount to replenish.
     * @return: True if the ingredient was replenished successfully; false otherwise.
     * @post: The ingredient stock at the station is updated, and the backup stock is adjusted accordingly.
     */
    bool replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity);

    /**
     * Adds a batch of ingredients to the backup stock.
     * @param ingredients A vector of Ingredient objects to add to the backup stock.
     * @return: True if all ingredients were added successfully; false otherwise.
     * @post: The backup stock is updated with the provided ingredients.
     */
    bool addBackupIngredients(const std::vector<Ingredient>& ingredients);

    /**
     * Adds a single ingredient to the backup stock.
     * @param ingredient An Ingredient object to add to the backup stock.
     * @return: True if the ingredient was added; false otherwise.
     * @post: If the ingredient already exists, its quantity is increased. Otherwise, it is added to the stock.
     */
    bool addBackupIngredient(const Ingredient& ingredient);

    /**
     * Clears all ingredients from the backup stock.
     * @post: The backup_ingredients_ vector is emptied.
     */
    void clearBackupIngredients();

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
    void processAllDishes();

private:
    /**
     * Helper function to get index of a station by name.
     * @param station_name The name of the station.
     * @return: The index of the station if found; -1 otherwise.
     */
    int getStationIndex(const std::string& station_name) const;
    std::queue<Dish*> dish_queue_; ///< Queue of dishes awaiting preparation.
    std::vector<Ingredient> backup_ingredients_; ///< Backup ingredients for stations.
};

#endif // STATIONMANAGER_HPP