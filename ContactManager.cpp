#include "ContactManager.h"
#include "FamilyContact.h"
#include "FriendContact.h"
#include "WorkContact.h"
#include <fstream>
#include <sstream>
#include <algorithm>

ContactManager::ContactManager(string filePath) : dataFilePath(filePath) {}

// Destructor: Free all Contact objects
ContactManager::~ContactManager() {
    for (auto c : contacts) delete c;
    contacts.clear();
}

bool ContactManager::phoneExists(const string& phone) const {
    for (const auto* c : contacts) {
        if (c->getPhone() == phone) return true;
    }
    return false;
}

Contact* ContactManager::findByPhone(const string& phone) const {
    for (auto* c : contacts) {
        if (c->getPhone() == phone) return c;
    }
    return nullptr;
}

// Add contact with validation
bool ContactManager::addContact(Contact* c) {
    if (!c || phoneExists(c->getPhone())) {
        delete c;
        return false;
    }
    contacts.push_back(c);
    return true;
}

void ContactManager::displayAll() const {
    for (const auto* c : contacts) {
        cout << *c << endl;
    }
}

vector<Contact*> ContactManager::searchByName(const string& keyword) const {
    vector<Contact*> result;
    for (auto* c : contacts) {
        if (c->getName().find(keyword) != string::npos) {
            result.push_back(c);
        }
    }
    return result;
}

bool ContactManager::updateByPhone(const string& phone) {
    Contact* c = findByPhone(phone);
    if (!c) return false;
    cout << "Thong tin hien tai: " << *c << endl;
    cout << "Ho ten moi: ";
    string newName;
    getline(cin, newName);
    cout << "Cap nhat thanh cong.\n";
    return true;
}

size_t ContactManager::deleteByName(const string& name) {
    size_t count = 0;
    auto it = contacts.begin();
    while (it != contacts.end()) {
        if ((*it)->getName() == name) {
            delete *it;
            it = contacts.erase(it);
            count++;
        } else {
            ++it;
        }
    }
    return count;
}

vector<Contact*> ContactManager::filterByRelationship(RelationshipFilter filter) const {
    vector<Contact*> result;
    for (auto* c : contacts) {
        string key = c->getCategoryKey();
        bool matches = (filter == RelationshipFilter::All);
        
        if (!matches && filter == RelationshipFilter::Family && key == "FAMILY") {
            matches = true;
        }
        if (!matches && filter == RelationshipFilter::Friend && key == "FRIEND") {
            matches = true;
        }
        if (!matches && (filter == RelationshipFilter::Teacher || filter == RelationshipFilter::Colleague)) {
            if (key == "WORK") {
                WorkContact* wc = dynamic_cast<WorkContact*>(c);
                if (wc) {
                    if (filter == RelationshipFilter::Teacher && wc->getRole() == "Teacher") {
                        matches = true;
                    } else if (filter == RelationshipFilter::Colleague && wc->getRole() == "Colleague") {
                        matches = true;
                    }
                }
            }
        }
        
        if (matches) result.push_back(c);
    }
    return result;
}

void ContactManager::saveToFile() const {
    ofstream f(dataFilePath);
    for (const auto* c : contacts) {
        f << c->toFileLine() << endl;
    }
}

void ContactManager::trim(string& s) {
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
}

// Load from file (Format: TYPE|PARAM1|NAME|PHONE)
void ContactManager::loadFromFile() {
    ifstream f(dataFilePath);
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        string type, part1, part2, part3;
        getline(ss, type, '|');
        
        if (type == "WORK") {
            getline(ss, part1, '|');
            getline(ss, part2, '|');
            getline(ss, part3, '|');
            addContact(new WorkContact(part2, part3, part1));
        } else if (type == "FAMILY") {
            getline(ss, part1, '|');
            getline(ss, part2, '|');
            addContact(new FamilyContact(part1, part2));
        } else if (type == "FRIEND") {
            getline(ss, part1, '|');
            getline(ss, part2, '|');
            addContact(new FriendContact(part1, part2));
        }
    }
}