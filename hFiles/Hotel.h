#pragma once
#ifndef HOTEL_H
#define HOTEL_H


#include "Guest.h"
#include "Food.h"
#include "Room.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Room;
using namespace std;

class Hotel {
    vector<Guest*> *guests; // vector which contains all guests
    vector<Food*> *foods; // vector which contains all the meals
    vector<Room*> *rooms; // vector which contains all the rooms

    unsigned int capacity; // capacity of this hotel

    void init(); // initializing vectors

    void clear() const; // clear everything

    void remove_all_guests() const; // remove all guests

    void buy_food(Food*) const; // buy food for the hotel

    void init_room(Room*) const; // initializing rooms

    void add_guest(Guest&) const; // add new guest

    bool remove_guest(Guest&) const; // removes the given guest

    bool exists(Guest&) const; // checks whether guest exists or not

    bool exists(Food&) const; // checks whether food exists or not

    bool exists(Room&) const; // checks whether room exists or not

    bool remove_food(Food& food) const; // removes food

    // Return pointer to the guest which has the given name
    Guest* get_guest(string& name, string& surname) const;

    // Return pointer to the guest which has the given name
    Guest* get_guest(const string& name, const string& surname) const;

    // Return pointer to the food which has the given name
    Food* get_food(string& name) const;

    // Return pointer to the food which has the given const name
    Food* get_food(const string& name) const;

    // Return pointer to the room which has the given number
    Room* get_room(int number) const;
public:
    Hotel(); // default constructor
    explicit Hotel(unsigned int); // constructor with only capacity
    Hotel(const Hotel&); // copy constructor
    ~Hotel(); // destructor

    void add_guest(const string& name, const string& surname, const string& dates, const unsigned age,
                   const unsigned room_number, const bool covid, const unsigned amount_of_days) const; // adding guests to the hotel

    bool contains_guest(const string& name, const string& surname) const; // check if the hotel has such a guest

    bool contains_food(string&) const; // check if the hotel has such a meal

    bool contains_food(const string&) const; // check if the hotel has such a meal

    bool contains_room(int) const; // checks if the hotel contains such room or not

    bool contains_food_for_guest(const string& guest_name) const; // checks if the hotel contains food for the given guest

    unsigned guest_count() const; // returns number of guests in the hotel

    bool is_empty() const; // checks if the hotel is empty or not

    bool room_occupied(int) const; // checks if the such room with room number is occupied or not

    void remove_guest(string, string) const; // removes the given guest from the hotel

    bool deliver_food_to_guest(string, string, string, unsigned) const; // feed a given guest

    void order_food_room(string name, unsigned room_number) const; // buy a new food and set a guest who ordered it

    void order_food(string name, unsigned cost, unsigned amount) const; // buy a new food for a hotel

    void add_room(int, int) const; // add a new room to the hotel

    void remove_food(string name) const; // removes the food from hotel

    void remove_food(string name, int amount);

    void set_capacity(unsigned capacity); // setter to variable capacity

    void print_info_guest(string name_guest, string surname) const; // prints the info about the given guest

    void print_guests() const; // print info about guests

    void print_food() const; // print info about foods

    void print_rooms() const; // print info about rooms

    void change_age(string name, string surname, uint8_t age) const; // change the age of the guest

    void change_covid_stage(string name, string surname, bool is_ill) const; // change the covid state of the guest


    Hotel& operator=(const Hotel&); // assignment operator
    bool operator==(const Hotel&) const; // equality operator
    bool operator!=(const Hotel&) const; // inequality operator
    void operator delete(void*);
    friend ostream& operator<<(ostream&, const Hotel&); // overloading the operator <<
};

#endif