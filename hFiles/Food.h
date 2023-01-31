#pragma once
#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <vector>
#include <string>
#include "Guest.h"

using namespace std;

class Food {
    vector<string> *guest_who_prefer_this_meal; // vector of guests who ordered this meal
    vector<Guest*> *guests; // vector of pointers to guests who ordered this food
    string name; // name of the meal
    unsigned cost; // cost of the meal
    unsigned amount; // amount of ordered food
    void clear() const; // clear
public:
    Food(const string&,const unsigned , const unsigned); /* constructor with name, vector of guests,
    cost and amount of food*/
    Food(const Food&); // copy constructor
    ~Food(); // destructor

    string get_name() const; // return the name of the food

    unsigned get_amount() const;

    unsigned get_cost() const;

    void change_amount(unsigned);

    bool is_applicable_to(const string& guest_name) const; // returns true if this food is applicable to the given guest

    bool is_applicable_to(Guest* guest) const; // returns true if this food is applicable to the given guest pointer

    void order_food_for_guest(string) const; // add meal that can be consumed by guest

    void order_food_for_guest(Guest*, const unsigned) const; // add meal that can be consumed by guest

    void remove_food_from_guest(Guest*) const; // remove meal that can be consumed by guest

    Food& operator=(const Food&);
    bool operator==(const Food&) const;
    void operator delete(void*);
    friend ostream& operator<<(ostream& os, const Food& food); // overloading the operator <<
};

#endif