#include "FamilyContact.h"

string FamilyContact::toFileLine() const {
    return "FAMILY|" + name + "|" + phone;
}