#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "objects.h"

int longueur_chaine(char *s) {
    int l = 0;
    while (s[l] != '\0') {
        l++;
    }
    return l;
}

Car *car_create(char *brand, char *model, char *license) {
    Car *car = malloc(sizeof(Car));

    if (car == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    int brand_length = longueur_chaine(brand);
    car->brand = malloc(strlen(brand) + 1);

    if (car->brand == NULL) {
        // Handle memory allocation failure
        free(car);
        return NULL;
    }

    strcpy(car->brand, brand);
    car->model = strdup(model);  // Use strdup to allocate and copy the string
    car->license = strdup(license);

    return car;
}

Customer *customer_create(char *name, char *address){
    Customer *customer = malloc(sizeof(Customer));

    if (customer == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    customer->name = strdup(name);
    customer->address = strdup(address);

    return customer;
}

Registry *registry_create(Customer **customers, int size){

    Registry *registry = malloc(size * sizeof(Customer));

    registry->customers = customers;

    return registry;
}

void car_destroy(Car *car){

    free(car->brand);
    free(car->model);
    free(car->license);

    free(car);
}

void customer_destroy(Customer *customer){

    free(customer->address);
    free(customer->name);

    free(customer);
}

void registry_destroy(Registry *registry){

    // Free each Customer structure
    if (registry->customers != NULL) {
        for (int i = 0; registry->customers[i] != NULL; i++) {
            free(registry->customers[i]);
        }

        // Free the array of Customer pointers
        free(registry->customers);
    }

    // Free the array of Car structures
    free(registry->cars);

    // Finally, free the Registry structure itself
    free(registry);
}

void link_car(Car *car, Customer *customer){
    customer->car = car;
}

void print_registry(Registry *registry){

    int l = sizeof(registry) / sizeof(registry->customers);

    if (registry->customers != NULL) {
        for (int i = 0; i <= l; i++) {
            printf("%s\n", registry->customers[i]->name);
            printf("%s\n", registry->customers[i]->address);
            printf("%s\n", registry->customers[i]->car->brand);
            printf("%s\n", registry->customers[i]->car->model);
            printf("%s\n", registry->customers[i]->car->license);
            printf("\n");
        }
    }
}
