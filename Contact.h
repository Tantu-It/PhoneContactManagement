#pragma once
#include <iostream>
#include <string>
using namespace std;

// Base class (abstract)
class Contact {
protected:
    string name;
    string phone;

public:
    Contact(const string& name, const string& phone);
    virtual ~Contact() = default;

    // Getter
    const string& getName() const { return name; }
    // Getter
    const string& getPhone() const { return phone; }

    // Pure virtual functions
    virtual string getCategoryKey() const = 0;
    virtual string getCategoryDisplay() const = 0;
    virtual string toFileLine() const = 0;

    friend ostream& operator<<(ostream& os, const Contact& c);

protected:
    virtual void printExtra(ostream& os) const;
};