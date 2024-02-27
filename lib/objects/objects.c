#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct car Car;
typedef struct customer Customer;
typedef struct registry Registry;

struct car
{
    char *brand;
    char *model;
    char *license;
};

struct customer
{
    char *name;
    char *address;
    Car *car;
};

struct registry
{
    Customer **customers;
    Car *cars;
};

int implementation(){

    Car* car1 = car_create("VW", "POLO", "GE123456");
    Car* car2 = car_create("VW", "POLO", "GE123457");
    Customer* customer1 = customer_create("John Doe", "Some Street 123");
    Customer* customer2 = customer_create("Jane Doe", "Some Street 321");

    link_car(car1, customer1);
    link_car(car2, customer2);

    Customer** customers = (Customer*[]){customer1, customer2};

    Registry* registry = registry_create(customers, 2);

    return 0;
}
