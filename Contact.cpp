#include "Contact.h"
#include <iomanip>

Contact::Contact(const string& name, const string& phone)
    : name(name), phone(phone) {}

void Contact::printExtra(ostream&) const {}

ostream& operator<<(ostream& os, const Contact& c) {
    os << left << setw(28) << c.name 
    << setw(16) << c.phone 
    << c.getCategoryDisplay();
    c.printExtra(os);
    return os;
}