#pragma once
#include "Contact.h"

class FriendContact : public Contact {
public:
    using Contact::Contact;
    string getCategoryKey() const override { return "FRIEND"; }
    string getCategoryDisplay() const override { return "Ban be"; }
    string toFileLine() const override;
};