//Write a menu driven program which will maintain a list of car models, their 
//price, name of the manufacture, engine capacity etc. as a doubly linked list. 
//The menu should make provisions for inserting information pertaining to new 
//car models, delete obsolete models, update data such as price besides 
//answering queries such as listing all car models within a price range specified 
//by the client and listing all details given a car model
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Car {
    char model[100];
    char manufacturer[100];
    float price;
    int engineCapacity;
    struct Car* prev;
    struct Car* next;
} Car;

Car* head = NULL;

Car* createCar(char* model, char* manufacturer, float price, int engineCapacity) {
    Car* newCar = (Car*)malloc(sizeof(Car));
    strcpy(newCar->model, model);
    strcpy(newCar->manufacturer, manufacturer);
    newCar->price = price;
    newCar->engineCapacity = engineCapacity;
    newCar->prev = NULL;
    newCar->next = NULL;
    return newCar;
}

void insertCar(char* model, char* manufacturer, float price, int engineCapacity) {
    Car* newCar = createCar(model, manufacturer, price, engineCapacity);
    if (head == NULL) {
        head = newCar;
    } else {
        Car* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newCar;
        newCar->prev = temp;
    }
    printf("Car model added successfully.\n");
}

void deleteCar(char* model) {
    if (head == NULL) {
        printf("No car models available.\n");
        return;
    }
    Car* temp = head;
    while (temp != NULL && strcmp(temp->model, model) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Car model not found.\n");
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Car model deleted successfully.\n");
}

void updatePrice(char* model, float newPrice) {
    Car* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            temp->price = newPrice;
            printf("Price updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Car model not found.\n");
}

void listCarsByPriceRange(float minPrice, float maxPrice) {
    Car* temp = head;
    int found = 0;
    printf("Cars in the price range %.2f - %.2f:\n", minPrice, maxPrice);
    while (temp != NULL) {
        if (temp->price >= minPrice && temp->price <= maxPrice) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %d cc\n",
                   temp->model, temp->manufacturer, temp->price, temp->engineCapacity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No cars found in the specified price range.\n");
    }
}

void listCarDetails(char* model) {
    Car* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %d cc\n",
                   temp->model, temp->manufacturer, temp->price, temp->engineCapacity);
            return;
        }
        temp = temp->next;
    }
    printf("Car model not found.\n");
}

void displayAllCars() {
    if (head == NULL) {
        printf("No car models available.\n");
        return;
    }
    Car* temp = head;
    printf("All Car Models:\n");
    while (temp != NULL) {
        printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %d cc\n",
               temp->model, temp->manufacturer, temp->price, temp->engineCapacity);
        temp = temp->next;
    }
}

int main() {
    int choice;
    char model[100], manufacturer[100];
    float price, minPrice, maxPrice;
    int engineCapacity;

    do {
        printf("\nMenu:\n");
        printf("1. Add Car Model\n");
        printf("2. Delete Car Model\n");
        printf("3. Update Car Price\n");
        printf("4. List Cars by Price Range\n");
        printf("5. List Car Details\n");
        printf("6. Display All Car Models\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Model: ");
                getchar();
                fgets(model, 100, stdin);
                model[strcspn(model, "\n")] = '\0';
                printf("Enter Manufacturer: ");
                fgets(manufacturer, 100, stdin);
                manufacturer[strcspn(manufacturer, "\n")] = '\0';
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Engine Capacity (cc): ");
                scanf("%d", &engineCapacity);
                insertCar(model, manufacturer, price, engineCapacity);
                break;

            case 2:
                printf("Enter Model to delete: ");
                getchar();
                fgets(model, 100, stdin);
                model[strcspn(model, "\n")] = '\0';
                deleteCar(model);
                break;

            case 3:
                printf("Enter Model to update price: ");
                getchar();
                fgets(model, 100, stdin);
                model[strcspn(model, "\n")] = '\0';
                printf("Enter New Price: ");
                scanf("%f", &price);
                updatePrice(model, price);
                break;

            case 4:
                printf("Enter Minimum Price: ");
                scanf("%f", &minPrice);
                printf("Enter Maximum Price: ");
                scanf("%f", &maxPrice);
                listCarsByPriceRange(minPrice, maxPrice);
                break;

            case 5:
                printf("Enter Model to display details: ");
                getchar();
                fgets(model, 100, stdin);
                model[strcspn(model, "\n")] = '\0';
                listCarDetails(model);
                break;

            case 6:
                displayAllCars();
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
