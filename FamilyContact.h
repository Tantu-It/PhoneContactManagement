#pragma once
#include "Contact.h"

class FamilyContact : public Contact {
public:
    using Contact::Contact;
    string getCategoryKey() const override { return "FAMILY"; }
    string getCategoryDisplay() const override { return "Gia dinh"; }
    string toFileLine() const override;
};