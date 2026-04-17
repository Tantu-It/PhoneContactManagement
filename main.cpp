#include "ContactManager.h"
#include "FamilyContact.h"
#include "FriendContact.h"
#include "WorkContact.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

namespace {

void printAndyBanner() {
    // Print banner
    cout << R"(
NHOM 06: PHONE CONTACT MANAGEMENT APPLICATION
)"
<< endl;
}

// Menu helper functions
void printMenu() {
    cout << "\n========== MENU ==========\n";
    cout << " 1. Hien thi tat ca lien he\n";
    cout << " 2. Them lien he moi\n";
    cout << " 3. Tim kiem theo ten (tuong doi)\n";
    cout << " 4. Cap nhat theo so dien thoai\n";
    cout << " 5. Xoa theo ten (dung ten day du)\n";
    cout << " 6. Loc theo quan he\n";
    cout << " 7. Tai lai tu file\n";
    cout << " 8. Luu ra file\n";
    cout << " 0. Thoat\n";
    cout << "Chon: ";
}

void flushLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

RelationshipFilter askFilter() {
    cout << "1-Gia dinh  2-Ban be  3-Giao vien  4-Dong nghiep  5-Tat ca: ";
    string s;
    getline(cin, s);
    if (s == "1") {
        return RelationshipFilter::Family;
    }
    if (s == "2") {
        return RelationshipFilter::Friend;
    }
    if (s == "3") {
        return RelationshipFilter::Teacher;
    }
    if (s == "4") {
        return RelationshipFilter::Colleague;
    }
    return RelationshipFilter::All;
}

void showSubset(const vector<Contact*>& list) {
    if (list.empty()) {
        cout << "  (Khong co ket qua)\n";
        return;
    }
    cout << left << setw(5) << "STT" << setw(28) << "Ho ten" << setw(16) << "So dien thoai"
    << "Quan he\n";
    cout << string(72, '-') << '\n';
    int i = 1;
    for (const Contact* p : list) {
        cout << setw(5) << i++ << *p << '\n';
    }
    cout << string(72, '-') << '\n';
}

Contact* createContactFromInput() {
    cout << "Loai: 1-Gia dinh  2-Ban be  3-Giao vien  4-Dong nghiep: ";
    string t;
    getline(cin, t);
    cout << "Ho ten: ";
    string name;
    getline(cin, name);
    cout << "So dien thoai: ";
    string phone;
    getline(cin, phone);
    if (t == "1") {
        return new FamilyContact(name, phone);
    }
    if (t == "2") {
        return new FriendContact(name, phone);
    }
    if (t == "3") {
        return new WorkContact(name, phone, "Teacher");
    }
    if (t == "4") {
        return new WorkContact(name, phone, "Colleague");
    }
    cout << "Loai khong hop le — mac dinh Ban be.\n";
    return new FriendContact(name, phone);
}

}  // namespace

// Main program
int main() {
    printAndyBanner();
    
    ContactManager manager("contacts.txt");
    manager.loadFromFile();
    cout << "Da tai du lieu tu '" << manager.getDataFilePath() << "'.\n";

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            flushLine();
            cout << "Nhap so hop le.\n";
            continue;
        }
        flushLine();

        if (choice == 1) {
            manager.displayAll();
        } else if (choice == 2) {
            Contact* c = createContactFromInput();
            if (manager.addContact(c)) {
                cout << "Them thanh cong.\n";
            } else {
                cout << "That bai: so dien thoai da ton tai.\n";
            }
        } else if (choice == 3) {
            cout << "Tu khoa ten: ";
            string kw;
            getline(cin, kw);
            vector<Contact*> r = manager.searchByName(kw);
            showSubset(r);
        } else if (choice == 4) {
            cout << "So dien thoai can cap nhat: ";
            string ph;
            getline(cin, ph);
            if (!manager.updateByPhone(ph)) {
                cout << "Khong tim thay so nay.\n";
            }
        } else if (choice == 5) {
            cout << "Ten day du can xoa: ";
            string nm;
            getline(cin, nm);
            size_t n = manager.deleteByName(nm);
            cout << "Da xoa " << n << " lien he.\n";
        } else if (choice == 6) {
            RelationshipFilter f = askFilter();
            vector<Contact*> r = manager.filterByRelationship(f);
            showSubset(r);
        } else if (choice == 7) {
            manager.loadFromFile();
            cout << "Tai lai xong.\n";
        } else if (choice == 8) {
            try {
                manager.saveToFile();
                cout << "Luu thanh cong.\n";
            } catch (const exception& e) {
                cout << e.what() << '\n';
            }
        } else if (choice == 0) {
            cout << "Tam biet!\n";
        } else {
            cout << "Khong hop le.\n";
        }
    }

    try {
        manager.saveToFile();
    } catch (const exception&) {
    }
    return 0;
}

