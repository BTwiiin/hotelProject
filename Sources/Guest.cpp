#include "../hFiles/Guest.h"
#include "../hFiles/Food.h"

#define COST_OF_ROOM 25

ostream& operator<<(ostream& os, const Guest& guest) {
    os << "Guest name: " << guest.name <<
       "\nGuest surname: " << guest.surname <<
       "\nGuest age: " << guest.age <<
       "\nWill be staying between: " << guest.dates <<
       "\nRoom number: " << guest.room_number <<
       "\nCovid test: " << (guest.covid ? "Positive" : "Negative") <<
       "\nDebt: " << guest.debt << "\n";
    return os;
}

Guest::Guest(const string &name, const string& surname, const string &dates, const unsigned int age, const unsigned int room_number,
             const bool covid , const unsigned amount_of_days)
{
    this->name = name;
    this->surname = surname;
    this->covid = covid;
    this->dates = dates;
    this->room_number = room_number;
    this->age = age < 101 ? age : 17;
    this->covid = covid;
    this->debt = amount_of_days * COST_OF_ROOM;
}

Guest::Guest(const Guest& guest) {
    *this = guest;
}

void Guest::add_debt(unsigned int n_debt) {
    this->debt += n_debt;
}

bool Guest::deliver_food_to_guest(Food &food) {
        cout << "Guest " << surname << " " << name << " has received  " << food.get_name() << "(s)." << endl;
        return true;
}

void Guest::set_age(const unsigned int age) {
    this->age = age;
}

void Guest::set_covid_stage(const bool covid) {
    this->covid = covid;
}

void Guest::set_room_number(const unsigned int room_number) {
    this->room_number = room_number;
}

unsigned int Guest::get_debt() const {
    return debt;
}

string Guest::get_name() const {
    return name;
}

string Guest::get_surname() const {
    return surname;
}

unsigned int Guest::get_age() const {
    return age;
}

string Guest::get_dates() const {
    return dates;
}

unsigned int Guest::get_room_number() const {
    return room_number;
}

bool Guest::get_covid() const {
    return covid;
}

void Guest::change_guest_data(const int age, const int room_number) {
    this->age = age;
    this->room_number = room_number;
}

bool Guest::operator==(const Guest& guest) const {
    return (guest.get_name() == guest.get_name()) == 0 && age == guest.get_age();
}

Guest& Guest::operator=(const Guest& guest) {
    if(this != &guest) {
        name = guest.get_name();
        dates = guest.get_dates();
        age = guest.get_age();
        room_number = guest.get_room_number();
        covid = guest.get_covid();
    }

    return *this;
}