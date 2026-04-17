#include "WorkContact.h"
#include <iomanip>

WorkContact::WorkContact(const string& name, const string& phone, const string& role)
    : Contact(name, phone), role(role) {}

string WorkContact::getCategoryDisplay() const {
    return (role == "Teacher") ? "Giao vien" : "Dong nghiep";
}

string WorkContact::toFileLine() const {
    return "WORK|" + role + "|" + name + "|" + phone;
}

void WorkContact::printExtra(ostream& os) const {
    os << " (" << ((role == "Teacher") ? "Giao vien" : "Dong nghiep") << ")";
}