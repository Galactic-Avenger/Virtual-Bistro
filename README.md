# Virtual Bistro Simulation

## Project Overview
The **Virtual Bistro** is a comprehensive simulation project developed to explore **Object-Oriented Programming (OOP)**, **inheritance**, **polymorphism**, and **data structures** in **C++**. This project evolves over multiple phases, starting from the basic implementation of a `Dish` class and extending to **kitchen management, dish queues, and recipe books**.

The repository can be found at: [GitHub Repository](https://github.com/Galactic-Avenger/Virtual-Bistro)

## Features
- **Dish Class Implementation**: Encapsulates dish attributes such as name, ingredients, preparation time, price, and cuisine type.
- **Inheritance and Polymorphism**: Includes subclasses such as `Appetizer`, `MainCourse`, and `Dessert`.
- **Kitchen Management**: Implements `Kitchen` to manage dish objects efficiently.
- **Dish Queues**: Manages dish preparation order using **queues**.
- **Binary Recipe Book**: Uses a **Binary Search Tree (BST)** to efficiently store and retrieve recipes.

## Project Structure
```
📂 virtual-bistro
 ├── 📂 src              # Source code files
 │   ├── Dish.cpp        # Implementation of Dish class
 │   ├── Dish.hpp        # Header file for Dish class
 │   ├── Kitchen.cpp     # Kitchen class implementation
 │   ├── Kitchen.hpp     # Kitchen class header
 │   ├── RecipeBook.cpp  # Recipe book BST implementation
 │   ├── RecipeBook.hpp  # Recipe book header
 │   ├── test.cpp        # Test file
 ├── Makefile            # Compilation script
 ├── README.md           # Project description
 ├── .gitignore          # Ignore unnecessary files
```

## Installation & Compilation
### 1. Clone the Repository
```sh
git clone https://github.com/Galactic-Avenger/Virtual-Bistro.git
cd Virtual-Bistro
```

### 2. Compile the Project
Ensure you have `g++` installed, then run:
```sh
make rebuild
```
This will compile the source files and create an executable.

### 3. Run the Test Program
Execute the compiled binary to test the **Dish** and **Kitchen** functionalities:
```sh
./test
```

## Usage
The `test.cpp` file includes test cases for validating the project’s core functionalities:
1. **Instantiate a dish using the default constructor.**
2. **Modify dish attributes using setters.**
3. **Create and manage a kitchen.**
4. **Add and remove dishes dynamically.**
5. **Test recipe management using BST-based `RecipeBook` class.**

## Contributing
Feel free to submit pull requests if you find improvements!

## Author
**Abdulla Saleh**
