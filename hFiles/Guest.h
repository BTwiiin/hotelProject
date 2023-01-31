#pragma once
#ifndef GUEST_H
#define GUEST_H

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

class Food;
using namespace std;

class Guest {
    vector<Food*> *foods;
    string name;
    string surname;
    string dates;
    bool covid;
    unsigned int age;
    unsigned int room_number;
    unsigned int debt;
public:

    Guest(const string& name, const string& surname, const string& dates, const unsigned age,
          const unsigned room_number, const bool covid, const unsigned amount_of_days);

    Guest(const Guest&); // copy constructor

    string get_name() const;
    string get_surname() const;
    string get_dates() const;
    unsigned get_age() const;
    unsigned get_room_number() const;
    unsigned get_debt() const;
    bool get_covid() const;

    void set_age(const unsigned age);
    void set_room_number(const unsigned room_number);
    void set_covid_stage(const bool covid);
    void add_debt(unsigned debt); // adds debt when guest buys anything


    bool deliver_food_to_guest(Food& food); // ordering food

    void change_guest_data(int, int); // change the guest's age and room number

    bool operator==(const Guest& guest) const; // overloading the operator ==
    Guest& operator=(const Guest& guest); // assignment operator
    friend ostream& operator<<(ostream&, const Guest&); // overloading the operator <<
};

#endif