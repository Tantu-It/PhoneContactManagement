#pragma once
#include "Contact.h"

class WorkContact : public Contact {
private:
    string role;

public:
    WorkContact(const string& name, const string& phone, const string& role);

    // Getter
    string getRole() const { return role; }
    string getCategoryKey() const override { return "WORK"; }
    string getCategoryDisplay() const override;
    string toFileLine() const override;

protected:
    void printExtra(ostream& os) const override;
};