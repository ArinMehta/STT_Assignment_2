// inventory_manager.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LEN 50

// Structure to hold product information
struct Product {
    int id;
    char name[MAX_NAME_LEN];
    int quantity;
    double price;
};

// Global inventory array and product counter
struct Product inventory[MAX_PRODUCTS];
int product_count = 0;

// Function Prototypes
void print_menu();
void add_product();
void search_product();
void display_inventory();
void update_stock();
int find_product_by_id(int id);

/**
 * @brief Main function to run the inventory management system.
 *
 * It displays a menu and processes user choices in a loop until the user decides to exit.
 */
int main() {
    int choice = 0;

    // Main application loop
    while (1) {
        print_menu();
        int scan_result = scanf("%d", &choice);

        // Clear input buffer
        while (getchar() != '\n');

        if (scan_result != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                add_product();
                break;
            case 2:
                search_product();
                break;
            case 3:
                display_inventory();
                break;
            case 4:
                update_stock();
                break;
            case 5:
                printf("\nExiting the inventory management system. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Please select a valid option from the menu.\n");
        }
    }

    return 0;
}

/**
 * @brief Displays the main menu options to the user.
 */
void print_menu() {
    printf("\n--- Inventory Management System ---\n");
    printf("1. Add a new product\n");
    printf("2. Search for a product by ID\n");
    printf("3. Display all products\n");
    printf("4. Update product stock\n");
    printf("5. Exit\n");
    printf("-----------------------------------\n");
    printf("Enter your choice: ");
}

/**
 * @brief Adds a new product to the inventory if there is space.
 *
 * Prompts the user for product details (ID, name, quantity, price).
 * Checks for duplicate IDs.
 */
void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("\nInventory is full. Cannot add more products.\n");
        return;
    }

    struct Product new_product;
    printf("\nEnter new product ID: ");
    scanf("%d", &new_product.id);

    // Check if product ID already exists
    if (find_product_by_id(new_product.id) != -1) {
        printf("\nError: A product with ID %d already exists.\n", new_product.id);
        while (getchar() != '\n'); // Clear buffer
        return;
    }

    printf("Enter product name: ");
    scanf(" %[^\n]", new_product.name);
    printf("Enter product quantity: ");
    scanf("%d", &new_product.quantity);
    printf("Enter product price: ");
    scanf("%lf", &new_product.price);

    inventory[product_count] = new_product;
    product_count++;

    printf("\nProduct added successfully!\n");
    while (getchar() != '\n'); // Clear buffer
}

/**
 * @brief Searches for a product by its ID and displays its details.
 */
void search_product() {
    int id;
    printf("\nEnter the product ID to search for: ");
    scanf("%d", &id);

    int index = find_product_by_id(id);

    if (index != -1) {
        printf("\n--- Product Found ---\n");
        printf("ID:       %d\n", inventory[index].id);
        printf("Name:     %s\n", inventory[index].name);
        printf("Quantity: %d\n", inventory[index].quantity);
        printf("Price:    $%.2f\n", inventory[index].price);
        printf("---------------------\n");
    } else {
        printf("\nProduct with ID %d not found in the inventory.\n", id);
    }
    while (getchar() != '\n'); // Clear buffer
}

/**
 * @brief Displays a formatted list of all products in the inventory.
 */
void display_inventory() {
    if (product_count == 0) {
        printf("\nThe inventory is currently empty.\n");
        return;
    }

    printf("\n--- Current Inventory ---\n");
    printf("----------------------------------------------------------\n");
    printf("| %-5s | %-30s | %-10s | %-10s |\n", "ID", "Name", "Quantity", "Price");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < product_count; i++) {
        printf("| %-5d | %-30s | %-10d | $%-9.2f |\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].quantity,
               inventory[i].price);
    }
    printf("----------------------------------------------------------\n");
}

/**
 * @brief Updates the stock quantity of an existing product.
 *
 * The user can add to or remove from the stock.
 */
void update_stock() {
    int id;
    printf("\nEnter the product ID to update stock: ");
    scanf("%d", &id);

    int index = find_product_by_id(id);

    if (index != -1) {
        int change;
        printf("Current quantity for '%s' is %d.\n", inventory[index].name, inventory[index].quantity);
        printf("Enter the change in quantity (positive to add, negative to remove): ");
        scanf("%d", &change);

        if ((inventory[index].quantity + change) < 0) {
            printf("\nError: Cannot have negative stock. Operation cancelled.\n");
        } else {
            inventory[index].quantity += change;
            printf("\nStock updated successfully. New quantity: %d\n", inventory[index].quantity);
        }
    } else {
        printf("\nProduct with ID %d not found.\n", id);
    }
    while (getchar() != '\n'); // Clear buffer
}

/**
 * @brief Finds the array index of a product given its ID.
 *
 * @param id The ID of the product to find.
 * @return The array index if found, otherwise -1.
 */
int find_product_by_id(int id) {
    for (int i = 0; i < product_count; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1; // Not found
}