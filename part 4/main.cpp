#include "StationManager.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

// Concrete implementation of Dish
class ConcreteDish : public Dish {
public:
    // Constructor for ConcreteDish
    ConcreteDish(const std::string& name, const std::vector<Ingredient>& ingredients, int prep_time, double price, CuisineType cuisine_type)
        : Dish(name, ingredients, prep_time, price, cuisine_type) {}

    // Implement the pure virtual method `display`
    void display() const override {
        std::cout << "Dish: " << getName() << " (" << getCuisineType() << ")" << std::endl;
    }

    // Implement the pure virtual method `dietaryAccommodations`
    void dietaryAccommodations(const DietaryRequest& request) override {
        std::cout << "Applying dietary accommodations for: " << getName() << std::endl;
    }
};

void testProcessAllDishes() {
    // Initialize StationManager
    StationManager manager;

    // Create and add stations
    KitchenStation* grillStation = new KitchenStation("Grill Station");
    KitchenStation* ovenStation = new KitchenStation("Oven Station");
    KitchenStation* saladStation = new KitchenStation("Salad Station");
    KitchenStation* pastaStation = new KitchenStation("Pasta Station");
    manager.addStation(grillStation);
    manager.addStation(ovenStation);
    manager.addStation(saladStation);
    manager.addStation(pastaStation);

    // Add dishes to the queue using ConcreteDish
    Dish* grilledChicken = new ConcreteDish("Grilled Chicken", {{"Chicken", 1, 1, 5.0}, {"Salt", 1, 1, 0.5}}, 15, 10.0, Dish::CuisineType::AMERICAN);
    Dish* beefWellington = new ConcreteDish("Beef Wellington", {{"Beef", 2, 2, 10.0}, {"Pastry", 1, 1, 2.0}}, 45, 25.0, Dish::CuisineType::FRENCH);
    Dish* veganSalad = new ConcreteDish("Vegan Salad", {{"Lettuce", 1, 1, 0.5}, {"Tomato", 1, 1, 0.5}}, 10, 8.0, Dish::CuisineType::OTHER);
    Dish* unknownDish = new ConcreteDish("Unknown Dish", {{"Mystery", 1, 1, 5.0}}, 20, 15.0, Dish::CuisineType::OTHER);

    manager.addDishToQueue(grilledChicken);  // Case 1: Prepared immediately
    manager.addDishToQueue(beefWellington); // Case 2: Needs replenishment
    manager.addDishToQueue(veganSalad);     // Case 1: Prepared immediately
    manager.addDishToQueue(unknownDish);    // Case 3: Cannot be prepared

    // Add backup ingredients for replenishment
    std::vector<Ingredient> backupIngredients = {
        Ingredient("Chicken", 1, 1, 5.0),
        Ingredient("Salt", 1, 1, 0.5),
        Ingredient("Beef", 2, 2, 10.0),
        Ingredient("Pastry", 1, 1, 2.0),
        Ingredient("Lettuce", 1, 1, 0.5),
        Ingredient("Tomato", 1, 1, 0.5),
    };
    manager.addBackupIngredients(backupIngredients);

    // Assign ingredients to stations
    grillStation->replenishStationIngredients(Ingredient("Chicken", 1, 1, 5.0));
    grillStation->replenishStationIngredients(Ingredient("Salt", 1, 1, 0.5));
    ovenStation->replenishStationIngredients(Ingredient("Beef", 2, 2, 10.0));
    saladStation->replenishStationIngredients(Ingredient("Lettuce", 1, 1, 0.5));
    saladStation->replenishStationIngredients(Ingredient("Tomato", 1, 1, 0.5));

    // Run the processAllDishes method
    manager.processAllDishes();

    // Verify expected output
    std::queue<Dish*> remainingQueue = manager.getDishQueue();

    // Ensure that only "Unknown Dish" remains in the queue
    assert(remainingQueue.size() == 1 && "Expected one unprepared dish in the queue.");
    assert(remainingQueue.front()->getName() == "Unknown Dish" && "The remaining dish should be 'Unknown Dish'.");

    // Clean up memory
    delete grillStation;
    delete ovenStation;
    delete saladStation;
    delete pastaStation;
    delete grilledChicken;
    delete beefWellington;
    delete veganSalad;
    delete unknownDish;

    std::cout << "Test passed: Outputs matched project specifications.\n";
}

int main() {
    testProcessAllDishes();
    return 0;
}
