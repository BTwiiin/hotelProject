#include "../hFiles/Food.h"

void Food::clear() const {
    guests->clear();
}

Food::Food(const string& name, const unsigned cost, const unsigned amount){
    guests = new vector<Guest*>;
    guest_who_prefer_this_meal = new vector<string>;
    this->name = name;
    this->cost = cost;
    this->amount = amount;
}

Food::Food(const Food& food) {
    *this = food;
}

Food::~Food() {
    clear();
    guests = nullptr;
}

string Food::get_name() const {
    return name;
}

unsigned int Food::get_amount() const {
    return amount;
}

unsigned int Food::get_cost() const {
    return cost;
}

void Food::change_amount(unsigned n_amount) {
    this->amount -= n_amount;
}

bool Food::is_applicable_to(const string& guest_name) const {
    for(auto iter = guest_who_prefer_this_meal->begin(); iter != guest_who_prefer_this_meal->end(); iter++)
        if((*iter).compare(guest_name) == 0) return true;
    return false;
}

bool Food::is_applicable_to(Guest* guest) const {
    for(auto it = guests->begin(); it != guests->end(); ++it)
        if(*it == guest)
            return true;
    return false;
}

void Food::order_food_for_guest(const string guest_name) const {
    guest_who_prefer_this_meal->push_back(guest_name);
}

void Food::order_food_for_guest(Guest *guest, const unsigned debt) const {
    if(!is_applicable_to(guest))
        guests->push_back(guest);
    guest->add_debt(debt);
}

void Food::remove_food_from_guest(Guest *guest) const {
    for(auto iter = guests->begin(); iter != guests->end(); iter++)
        if(*iter == guest) {
            guests->erase(iter);
            return;
        }
}

Food& Food::operator=(const Food& food) {
    //guests = new vector<Guest*>;
    //guest_who_prefer_this_meal = new vector<string>;

    if(this != &food) {
        if(!guests->empty()) clear();

        name = food.name;
        for(auto iter = food.guests->begin(); iter != food.guests->end(); iter++)
            guests->push_back(new Guest(**iter));
        for(auto iter = food.guest_who_prefer_this_meal->begin(); iter != food.guest_who_prefer_this_meal->end(); iter++)
            guest_who_prefer_this_meal->push_back(*iter);
    }
    return *this;
}

bool Food::operator==(const Food& food) const {
    return name.compare(food.get_name()) == 0;
}

void Food::operator delete(void*) { }

ostream& operator<<(ostream& os, const Food& food) {
    if(food.get_amount() == 0){
        os << "Hotel currently does not have food named: " << food.get_name() << endl;
    }
    else {
        os << food.get_amount() << " " << food.get_name() << "(s): ";

        os << endl << "Cost of " << food.get_name() << " is " << food.get_cost() << endl;
    }
    os << endl;

    return os;
}