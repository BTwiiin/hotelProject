#pragma once
#ifndef ROOM_H
#define ROOM_H

#include "Hotel.h"
#include <ostream>

class Room {
    vector<Guest*> *guests; // vector of pointers to the guests that live in the room
    int capacity; // number of guests that can live in the room
    int number; // room number
    bool remove_guest(Guest*) const; // remove the given guest from the room
public:
    Room(int number, int capacity);
    Room(int number);
    Room(vector<Guest*>&, const int number, const int capacity);
    Room(const Room&); // copy constructor
    vector<Guest*>* get_guests() const;

    int get_capacity() const;

    int get_number() const;

    bool contains(string) const; // checks if the given guest lives in the room

    void add_guest(Guest*) const; // add the given guest to the room

    void remove_guest(string) const; // remove the given guest from the room

    int guest_count() const; // return the number of guests who's living in the room

    bool is_empty() const;  // checks if the room is empty or not

    Room& operator=(const Room&);

    friend ostream& operator<<(ostream&, const Room&);
};

#endif