#pragma once
#include "Contact.h"
#include <vector>

// Filter by relationship type
enum class RelationshipFilter {
    Family,
    Friend,
    Teacher,
    Colleague,
    All
};

// Manages contact list
class ContactManager {
private:
    vector<Contact*> contacts;
    string dataFilePath;
    bool phoneExists(const string& phone) const;
    Contact* findByPhone(const string& phone) const;
    static void trim(string& s);  // Trim whitespace

public:
    explicit ContactManager(string filePath = "contacts.txt");
    ~ContactManager();

    // Getter
    const string& getDataFilePath() const { return dataFilePath; }
    
    // File I/O
    void loadFromFile();
    void saveToFile() const;
    
    // Add/Display
    bool addContact(Contact* c);
    void displayAll() const;
    
    // Search/Filter
    vector<Contact*> searchByName(const string& keyword) const;
    bool updateByPhone(const string& phone);
    size_t deleteByName(const string& name);
    void deleteByPhone(const string& phone);
    vector<Contact*> filterByRelationship(RelationshipFilter filter) const;
};