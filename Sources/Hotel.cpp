#include "../hFiles/Hotel.h"

void Hotel::init() {
    guests = new vector<Guest*>;
    foods = new vector<Food*>;
}

void Hotel::clear() const {
    for(auto iter = foods->begin(); iter != foods->end(); iter++) delete *iter;
    foods->clear();

    for(auto iter = guests->begin(); iter != guests->end(); iter++) delete *iter;
    guests->clear();
}

void Hotel::remove_all_guests() const {
    for(auto iter = guests->begin(); iter != guests->end(); iter++) {
        for(auto it = foods->begin(); it != foods->end(); it++)
            (*it)->remove_food_from_guest(*iter);
        for(auto it = rooms->begin(); it != rooms->end(); it++)
            (*it)->remove_guest((*iter)->get_name());
        delete *iter;
    }
    guests->clear();
}

void Hotel::buy_food(Food* food) const {
    foods->push_back(food);
}

void Hotel::init_room(Room *room) const {
    if(!room)
        return;

    rooms->push_back(room);
}

void Hotel::add_guest(Guest& guest) const {
    // register the given guest to the hotel
    guests->push_back(&guest);

    // add guest to the room
    for(auto iter = rooms->begin(); iter != rooms->end(); iter++) {
        if((*iter)->get_number() == guest.get_room_number())
            (*iter)->add_guest(&guest);
    }
}


Hotel::Hotel() : capacity(10) {
    guests = new vector<Guest*>;
    foods = new vector<Food*>;
    rooms = new vector<Room*>;
}

Hotel::Hotel(const unsigned int capacity) : capacity(capacity) {
    guests = new vector<Guest*>;
    foods = new vector<Food*>;
    rooms = new vector<Room*>;
}

Hotel::Hotel(const Hotel& hotel) {
    *this = hotel;
}

Hotel::~Hotel() {
    clear();
    guests = nullptr;
    foods = nullptr;
    capacity = 0;
}

void Hotel::add_guest(const string& name, const string& surname, const string& dates, const unsigned age,
                      const unsigned room_number, const bool covid, const unsigned amount_of_days) const {
    if(name.empty()) {
        cout << "Guest has to have a name. Please enter a proper name." << endl;
        return;
    }
    if(contains_room(room_number))
        if(!room_occupied(room_number))
            if(guest_count() < capacity) {
                Guest* guest = new Guest(name, surname, dates, age, room_number, covid, amount_of_days);
                add_guest(*guest);
            } else
                cout << "Cannot add guest " << surname << " " << name << " to the hotel. The hotel cannot contain more guests.\n";
        else
            cout << "Cannot add guest " << surname << " " << name << " to the hotel. The given room is already occupied for these days.\n";
    else
        cout << "Cannot add guest to this room" << room_number << ". It does nor exist.\n";

    ofstream file;
    file.open("hotelguests.txt", ios::app);

    file << "**************** Guest ****************" << endl <<
    "Guest name: " << name <<
    "\nGuest surname: " << surname <<
    "\nGuest age: " << age <<
    "\nWill be staying between: " << dates <<
    "\nRoom number: " << room_number <<
    "\nCovid test: " << (covid ? "Positive" : "Negative") <<
    "\nDebt: " << get_guest(name, surname)->get_debt() << "\n\n";

    file.close();
}

bool Hotel::contains_guest(const string& name, const string& surname) const {
    return get_guest(name, surname) ? exists(*get_guest(name, surname)) : false;
}

bool Hotel::contains_food(string& name) const {
    return get_food(name) ? exists(*get_food(name)) : false;
}

bool Hotel::contains_food(const string& name) const {
    return exists(*get_food(name));

}

bool Hotel::contains_room(const int room_number) const {
    if(room_number < 0) return false;

    for(auto iter = rooms->begin(); iter != rooms->end(); iter++)
        if((*iter)->get_number() == room_number)
            return true;
    return false;
}

bool Hotel::contains_food_for_guest(const string& guest_name) const {
    for (auto iter = foods->begin(); iter != foods->end(); iter++)
        if ((*iter)->is_applicable_to(guest_name))
            return true;
    return false;
}

bool Hotel::remove_food(Food& food) const {
    for (auto iter = foods->begin(); iter != foods->end(); ++iter)
        if (*iter == &food) {
            foods->erase(iter);
            return true;
        }
    return false;
}

void Hotel::remove_food(string name, int amount) {
    if(!contains_food(name)){
        cout << name << " could not removed. Hotel does not contain such food.";
        return;
    }

    Food* f = get_food(name);

    unsigned old_amount = f->get_amount();
    unsigned cost = f->get_cost();
    unsigned new_amount = old_amount - amount;
    if(old_amount <= amount){
        remove_food(*f);
    }
    else{
        remove_food(*f);

        order_food(name, cost, new_amount);
        /*for(auto iter = foods->begin(); iter != foods->end(); iter++ ){
            cout << **iter << endl;
        }*/
    }



}

Guest* Hotel::get_guest(string& name, string& surname) const {
    if (name.compare("") == 0) return nullptr;

    for (auto iter = guests->begin(); iter != guests->end(); ++iter)
        if (name.compare((*iter)->get_name()) == 0)
            return *iter;
    return nullptr;
}

Guest* Hotel::get_guest(const string& name, const string& surname) const {
    if (name.compare("") == 0) return nullptr;

    for (auto iter = guests->begin(); iter != guests->end(); ++iter)
        if (name.compare((*iter)->get_name()) == 0)
            return *iter;
    return nullptr;
}

Food* Hotel::get_food(string& name) const {
    if (name.compare("") == 0) return nullptr;

    for (vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
        if ((*iter)->get_name().compare(name) == 0)
            return *iter;
    return nullptr;
}

Food* Hotel::get_food(const string& name) const {
    if (name.compare("") == 0) return nullptr;

    for (vector<Food*>::const_iterator iter = foods->begin(); iter != foods->end(); iter++)
        if ((*iter)->get_name().compare(name) == 0)
            return *iter;
    return nullptr;
}

Room* Hotel::get_room(int number) const {
    if(!contains_room(number)) return nullptr;

    for(vector<Room*>::const_iterator iter = rooms->begin(); iter != rooms->end(); iter++)
        if((*iter)->get_number() == number)
            return *iter;
    return nullptr;

}

unsigned Hotel::guest_count() const {
    return guests->size();
}

bool Hotel::is_empty() const {
    if(!guests || !foods || !rooms)
        return true;
    return guests->empty();
}

bool Hotel::room_occupied(const int room_number) const {
    if (room_number < 0) {
        cout << "You entered negative room number." << endl;
        return false;
    }

    return get_room(room_number)->get_capacity() == get_room(room_number)->guest_count();
}

void Hotel::remove_guest(string name, string surname) const {
    if (is_empty()) {
        cout << "Cannot remove any guests from the hotel. Hotel is empty" << endl;
        return;
    }

    if (!contains_guest(name, surname)) {
        cout << "Cannot remove the guest " << name << " " << surname << ". Hotel does not contain this guest.\n";
        return;
    }

    if (remove_guest(*get_guest(name, surname))) {
        cout << "Guest " << name << " " << surname << " removed successfully." << endl;
        return;
    }
    cout << "Guest " << name << " " << surname << " could not be removed." << endl;
}

bool Hotel::remove_guest(Guest& guest) const {
    if (!contains_guest(guest.get_name(), guest.get_surname())) return false;

    for (auto iter = guests->begin(); iter != guests->end(); ++iter)
        if (*iter == &guest) {
            // remove guest from the rooms vector
            for(auto it = rooms->begin(); it != rooms->end(); ++it)
                if((*it)->get_number() == guest.get_room_number())
                    (*it)->remove_guest(guest.get_name());

            delete *iter;
            guests->erase(iter);
            return true;
        }
    return false;
}

bool Hotel::exists(Guest& guest) const {
    if (guest.get_name().compare("") == 0)
        return false;

    for (auto iter = guests->begin(); iter != guests->end(); ++iter)
        if (guest.get_name().compare((*iter)->get_name()) == 0)
            return true;
    return false;
}

bool Hotel::exists(Food& food) const {
    if (food.get_name().compare("") == 0)
        return false;

    for (auto iter = foods->begin(); iter != foods->end(); ++iter)
        if (food.get_name().compare((*iter)->get_name()) == 0)
            return true;
    return false;
}

bool Hotel::exists(Room &room) const {
    for(auto iter = rooms->begin(); iter != rooms->end(); ++iter)
        if(*iter == &room)
            return true;
    return false;
}

void Hotel::order_food(string name, unsigned int cost, unsigned int amount) const {
    if(cost <= 0 || amount < 0){
        cout << "Ordering unsuccessful. Cost or amount is not valid. Please try again with valid values" << endl;
        return;
    }

    if(amount == 0 && cost != get_food(name)->get_cost()){
        if(!contains_food(name)){
            cout << "You cannot change cost of food that does not exist in the Hotel" << endl;
            return;
        }
        else{
            unsigned old_amount = get_food(name)->get_amount();
            if(cost != get_food(name)->get_cost()) {
                cout << "You have changed cost of " << name << " from " << get_food(name)->get_cost() << " to " << cost
                     << endl;
            }
            remove_food(name);

            Food* f = new Food(name, cost, old_amount);
            buy_food(f);
            return;
        }
    }

    if(contains_food(name)){
        unsigned old_amount = get_food(name)->get_amount();
        unsigned new_amount = old_amount + amount;
        if(cost != get_food(name)->get_cost()) {
            cout << "You have changed cost of " << name << " from " << get_food(name)->get_cost() << " to " << cost
                 << endl;
        }
        remove_food(name);

        Food* f = new Food(name, cost, new_amount);
        buy_food(f);
        return;
    }

    Food* f = new Food(name, cost, amount);
    buy_food(f);
}

void Hotel::add_room(const int room_number, const int capacity) const {
    if(room_number <= 0){
        cout << "Room number cannot be lower than 0. " << endl << "Please reenter room number" << endl;
        return;
    }

    if(!contains_room(room_number)) {
        Room *room = new Room(room_number, capacity);
        init_room(room);
    }
}

void Hotel::remove_food(const string name) const {
    if (!contains_food(name)) {
        cout << name << " could not removed. Hotel does not contain such food.";
        return;
    }

    cout << name << " has " << (remove_food(*get_food(name)) ? "" : "not") << " been removed from the hotel." << endl;
}


void Hotel::set_capacity(const unsigned capacity) {
    if (capacity < guest_count()) {
        cout << "Cannot set capacity to " << capacity << ". Please enter a bigger value." << endl;
        return;
    }

    this->capacity = capacity;
}

void Hotel::print_info_guest(string name , string surname) const {
    if(!contains_guest(name, surname)){
        cout << "Cannot print info about " << name << " " << surname << ". Hotel does not have such a guest" << endl;
        return;
    }

    if (contains_guest(name, surname))
        cout << *get_guest(name, surname) << endl;
}

void Hotel::print_guests() const {
    for(auto iter = guests->begin(); iter != guests->end(); iter++)
        cout << **iter << endl;
    cout << endl;
}

void Hotel::print_food() const {
    for(auto iter = foods->begin(); iter != foods->end(); iter++)
        cout << **iter;
    cout << endl;
}

void Hotel::print_rooms() const {
    for(auto iter = rooms->begin(); iter != rooms->end(); iter++)
        cout << **iter;
    cout << endl;
}

void Hotel::change_age(string name, string surname, const uint8_t age) const {
    if(contains_guest(name, surname)) {
        get_guest(name, surname)->set_age(age);
        return;
    }
    cout << "Unable to modify age of " << name << ". Hotel does not contain such a guest." << endl;
}

void Hotel::change_covid_stage(string name, string surname, const bool covid) const {
    if (contains_guest(name, surname)) {
        get_guest(name, surname)->set_covid_stage(covid);
    } else {
        cout << "Unable to modify Covid stage of  " << name << ". Hotel does not contain such a guest." << endl;
    }
}


bool Hotel::deliver_food_to_guest(string f_name, string name, string surname, unsigned amount) const {
    if (is_empty()) {
        cout << "Hotel is empty. Cannot feed any guests." << endl;
        return false;
    }

    if (!contains_guest(name, surname)) {
        cout << "Cannot feed guest " + name + ". Hotel does not contain such an guest." << endl;
        return false;
    }

    if(!contains_food(f_name)) {
        cout << "Unable to deliver food to " << name << " " << surname << ". Hotel does not contain such food." << endl;
        cout << "Order it for him." << endl;

        int cost;

        cout << "Cost: ";
        cin >> cost;

        if (cost <= 0)
            return false;

        order_food(f_name, cost, amount);

    }

    bool delivered = false;
    Guest* guest = get_guest(name ,surname);
    Food* food = get_food(f_name);
    for (auto iter = foods->begin(); iter != foods->end(); iter++)
        if (guest->deliver_food_to_guest(**iter))
            food->change_amount(amount);
            guest->add_debt(food->get_cost() * amount);
            delivered = true;
    return delivered;
}

Hotel& Hotel::operator=(const Hotel& hotel) {
    if (this != &hotel && hotel.guests && hotel.foods && hotel.rooms) {
        if (!is_empty()) clear();

        capacity = hotel.capacity;
        guests = new vector<Guest*>;
        foods = new vector<Food*>;
        rooms = new vector<Room*>;

        for(auto iter = hotel.guests->begin(); iter != hotel.guests->end(); iter++)
            guests->push_back(new Guest(**iter));
        for(auto iter = hotel.foods->begin(); iter != hotel.foods->end(); iter++)
            foods->push_back(new Food(**iter));
        for(auto iter = hotel.rooms->begin(); iter != hotel.rooms->end(); iter++) {
            auto *guests = new vector<Guest*>;
            for(auto it = (*iter)->get_guests()->begin(); it != (*iter)->get_guests()->end(); ++it)
                guests->push_back(get_guest((*it)->get_name(), (*it)->get_surname()));

            rooms->push_back(new Room(*guests, (*iter)->get_number(), (*iter)->get_capacity()));
        }

    }

    return *this;
}

bool Hotel::operator==(const Hotel& hotel) const {
    return guests == hotel.guests;
}

bool Hotel::operator!=(const Hotel& hotel) const {
    return !(*this == hotel);
}

void Hotel::operator delete(void*) { }

ostream& operator<<(ostream& os, const Hotel& hotel) {
    if (!hotel.guests || !hotel.foods) {
        os << "Unable to find such a hotel to print info about." << endl;
        return os;
    }

    cout << "***********************************************************************************" << endl;
    cout << "\t*********List of the Hotel's guests*********" << endl;
    if (hotel.is_empty()) {
        cout << "Hotel does not contain any guests." << endl;
    } else {
        for (auto iter = hotel.guests->begin(); iter != hotel.guests->end(); ++iter)
            os << **iter << endl;
    }
    cout << endl << "\t*********Foods in the hotel*********" << endl;
    if (hotel.foods->empty()) {
        cout << "Hotel does not contain any food." << endl;
    } else {
        for (auto iter = hotel.foods->begin(); iter != hotel.foods->end(); ++iter)
            os << **iter;
    }
    cout << endl << "\t*********Rooms in the hotel*********" << endl;
    if (hotel.rooms->empty()) {
        cout << "Hotel does not have any rooms." << endl;
    } else {
        for (auto iter = hotel.rooms->begin(); iter != hotel.rooms->end(); ++iter)
            os << **iter;
    }

    cout << endl << "***********************************************************************************" << endl;

    return os;
}