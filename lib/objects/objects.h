#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct car Car;
typedef struct customer Customer;
typedef struct registry Registry;

struct car
{
    // TODO: Implement
};

struct customer
{
    // TODO: Implement
};

struct registry
{
    // TODO: Implement
};

Car *car_create(char *brand, char *model, char *license);
Customer *customer_create(char *name, char *address);
Registry *registry_create(Customer **customers, int size);

void car_destroy(Car *car);
void customer_destroy(Customer *customer);
void registry_destroy(Registry *registry);

void link_car(Car *car, Customer *customer);
void print_registry(Registry *registry);

#endif
