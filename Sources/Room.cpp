#include "../hFiles/Room.h"

vector<Guest *> *Room::get_guests() const {
    return guests;
}

int Room::get_capacity() const {
    return capacity;
}

int Room::get_number() const {
    return number;
}

bool Room::remove_guest(Guest *guest) const {
    for(auto iter = guests->begin(); iter != guests->end(); iter++)
        if((*iter)->get_name().compare(guest->get_name()) == 0) {
            guests->erase(iter);
            return true;
        }
    return false;
}

Room::Room(const int number) : number(number) {
    guests = new vector<Guest*>;
    capacity = 1;
}

Room::Room(const int number, const int capacity) : capacity(capacity), number(number) {
    guests = new vector<Guest*>;
}

Room::Room(vector<Guest*>& guests, const int number, const int capacity) : capacity(capacity), number(number) {
    this->guests = new vector<Guest*>;
    for(auto iter = guests.begin(); iter != guests.end(); iter++)
        this->guests->push_back(*iter);
}

Room::Room(const Room &room) {
    *this = room;
}

bool Room::contains(const string guest_name) const {
    if(guest_name.compare("") == 0) return false;

    for(auto iter = guests->begin(); iter != guests->end(); iter++)
        if((*iter)->get_name().compare(guest_name) == 0)
            return true;
    return false;
}

void Room::add_guest(Guest *guest) const {
    if(guests->size() < capacity) {
        guests->push_back(guest);
        guest->set_room_number(number);
    }
}

void Room::remove_guest(const string guest_name) const {
    if(!contains(guest_name)) return;

    for(auto iter = guests->begin(); iter != guests->end(); iter++)
        if((*iter)->get_name().compare(guest_name) == 0) {
            guests->erase(iter);
            return;
        }
}

int Room::guest_count() const {
    return guests->size();
}

bool Room::is_empty() const {
    return guests->empty();
}

Room& Room::operator=(const Room& room) {
    if(this != &room) {
        guests = new vector<Guest*>;
        capacity = room.capacity;
        number = room.number;

        for(auto iter = room.guests->begin(); iter != room.guests->end(); iter++)
            guests->push_back(*iter);
    }
    return *this;
}


ostream& operator<<(ostream& os, const Room &room) {
    if (room.guests) {
        os << room.number << ": ";
        if(room.is_empty()) os << "empty";
        else {
            for(auto iter = room.guests->begin(); iter != room.guests->end(); iter++) {
                os << (*iter)->get_name() << " " << (*iter)->get_surname();
                if(iter != room.guests->end() - 1)
                    os << ", ";
            }
        }
        os << endl;
    }
    return os;
}