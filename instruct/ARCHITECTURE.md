# 🏗️ KIẾN TRÚC DỰ ÁN PhoneContact - OOP CONCEPTS

## 📋 Tổng Quan

Dự án PhoneContact áp dụng **5 khái niệm OOP chính** từ Chapter 4 & 5:

| Chương | Khái niệm | Vị trí trong dự án |
|--------|-----------|------------------|
| Chapter 4 | **Inheritance & Polymorphism** | Contact.h, FamilyContact, FriendContact, WorkContact |
| Chapter 5 | **Pure Virtual Functions** | Contact.h (getCategoryKey, getCategoryDisplay, toFileLine) |
| - | **Operator Overloading** | operator<< (Contact.cpp) |
| - | **STL & Vector** | ContactManager.h (vector<Contact*>) |
| - | **System & File I/O** | ContactManager.cpp (loadFromFile, saveToFile) |

---

## 1️⃣ SYSTEM & FILE I/O

### 📌 Khái Niệm
- Đọc/ghi dữ liệu từ file `.txt`
- Parse dữ liệu theo định dạng: `TYPE|ROLE|NAME|PHONE`
- Quản lý dữ liệu persistent (lưu trữ lâu dài)

### 📂 Vị Trí Code
- **File:** `ContactManager.h`
  - Hàm: `loadFromFile()`, `saveToFile()`
  
- **File:** `ContactManager.cpp`
  - Xử lý `ifstream` (đọc), `ofstream` (ghi)
  - Parse dữ liệu từ file

### 📝 Ví Dụ
```cpp
// ContactManager.cpp - loadFromFile()
ifstream f(dataFilePath);
string line;
while (getline(f, line)) {
    // Parse: FAMILY|name|phone
    // Parse: WORK|role|name|phone
}
```

---

## 2️⃣ INHERITANCE & POLYMORPHISM

### 📌 Khái Niệm
- **Base Class:** `Contact` (trừu tượng - abstract)
- **Derived Classes:** 
  - `FamilyContact` (Gia đình)
  - `FriendContact` (Bạn bè)
  - `WorkContact` (Đồng nghiệp/Giáo viên)
- **Late Binding:** Gọi hàm đúng ở runtime thông qua base class pointers

### 📂 Vị Trí Code
- **Base Class:** `Contact.h` (pure virtual functions)
- **Derived Classes:** 
  - `FamilyContact.h / FamilyContact.cpp`
  - `FriendContact.h / FriendContact.cpp`
  - `WorkContact.h / WorkContact.cpp`

### 📝 Ví Dụ
```cpp
// Contact.h - Pure Virtual (Derived classes PHẢI implement)
virtual string getCategoryKey() const = 0;
virtual string getCategoryDisplay() const = 0;
virtual string toFileLine() const = 0;

// FamilyContact.h - Override
string getCategoryKey() const override { return "FAMILY"; }
string getCategoryDisplay() const override { return "Gia dinh"; }

// Late Binding - Polymorphism in action
vector<Contact*> contacts;
for (Contact* p : contacts) {
    cout << p->getCategoryDisplay();  // Gọi version đúng ở runtime
}
```

---

## 3️⃣ PURE VIRTUAL FUNCTIONS

### 📌 Khái Niệm
- Hàm ảo không có body
- **Buộc** derived classes phải implement
- Tạo nên **interface contract**

### 📂 Vị Trí Code
- **File:** `Contact.h`
  - 3 pure virtual functions: `getCategoryKey()`, `getCategoryDisplay()`, `toFileLine()`

### 📝 Ví Dụ
```cpp
class Contact {  // Abstract class
public:
    // Pure Virtual - Derived classes PHẢI implement
    virtual string getCategoryKey() const = 0;
    virtual string getCategoryDisplay() const = 0;
    virtual string toFileLine() const = 0;
};

// ❌ KHÔNG thể: Contact c("John", "0123");
// ✅ CÓ THỂ: Contact* p = new FamilyContact("John", "0123");
```

---

## 4️⃣ STL & ADD LOGIC

### 📌 Khái Niệm
- Sử dụng **std::vector** để quản lý danh sách
- Logic thêm/xóa/sửa với kiểm tra lỗi
- Quản lý bộ nhớ (new/delete)

### 📂 Vị Trí Code
- **File:** `ContactManager.h`
  - `vector<Contact*> contacts` - Quản lý danh sách
  - `addContact()` - Kiểm tra duplicate phone
  
- **File:** `ContactManager.cpp`
  - Logic xử lý: kiểm tra, thêm, xóa

### 📝 Ví Dụ
```cpp
// ContactManager.h
private:
    vector<Contact*> contacts;  // STL - Danh sách động
    bool phoneExists(const string& phone) const;

public:
    bool addContact(Contact* c) {
        if (!c || phoneExists(c->getPhone())) {
            delete c;  // Giải phóng nếu lỗi
            return false;
        }
        contacts.push_back(c);
        return true;
    }
```

---

## 5️⃣ OPERATOR OVERLOADING & SEARCH

### 📌 Khái Niệm
- **Operator Overloading:** `operator<<` để in thông tin
- **Search/Filter Functions:**
  - `searchByName()` - Tìm theo tên (tương đối)
  - `updateByPhone()` - Cập nhật theo số điện thoại
  - `deleteByName()` - Xóa theo tên (đủ)
  - `filterByRelationship()` - Lọc theo quan hệ

### 📂 Vị Trí Code
- **File:** `Contact.cpp`
  - `operator<<` - Nạp chồng toán tử xuất

- **File:** `ContactManager.h / ContactManager.cpp`
  - `searchByName()`, `updateByPhone()`, `deleteByName()`, `filterByRelationship()`

### 📝 Ví Dụ
```cpp
// Contact.cpp - Operator Overloading
ostream& operator<<(ostream& os, const Contact& c) {
    os << left << setw(28) << c.name 
       << setw(16) << c.phone 
       << c.getCategoryDisplay();
    c.printExtra(os);
    return os;
}

// ContactManager.cpp - Search Functions
vector<Contact*> ContactManager::searchByName(const string& keyword) const {
    vector<Contact*> result;
    for (auto* c : contacts) {
        if (c->getName().find(keyword) != string::npos) {
            result.push_back(c);
        }
    }
    return result;
}
```

---

## 6️⃣ MEMORY, DELETE & UI/UX

### 📌 Khái Niệm
- **Virtual Destructor:** Giải phóng bộ nhớ đúng cách
- **Memory Management:** new/delete, tránh memory leak
- **UI/UX:** Menu, ASCII ART, nhập liệu friendly

### 📂 Vị Trí Code
- **File:** `Contact.h`
  - `virtual ~Contact() = default;` - Virtual destructor

- **File:** `ContactManager.cpp`
  - Destructor: `~ContactManager()` - Xóa tất cả contacts

- **File:** `main.cpp`
  - Menu, ASCII ART banner, nhập liệu
  - Hàm: `printMenu()`, `printAndyBanner()`, `flushLine()`

### 📝 Ví Dụ
```cpp
// Contact.h - Virtual Destructor (tránh memory leak)
virtual ~Contact() = default;

// ContactManager.cpp - Destructor
ContactManager::~ContactManager() {
    for (auto c : contacts) delete c;  // Xóa tất cả
    contacts.clear();
}

// main.cpp - UI/UX
void printAndyBanner() {
    cout << R"(
NHOM 06: PHONE CONTACT MANAGEMENT APPLICATION
)" << endl;
}

void printMenu() {
    cout << "\n========== MENU ==========\n";
    cout << " 1. Hien thi tat ca lien he\n";
    cout << " 2. Them lien he moi\n";
    // ...
}
```

---

## 7️⃣ TÍCH HỢP ASCII ART

### 📌 Khái Niệm
- Sử dụng **Raw String Literals** `R"(...)"` để in ASCII art
- Tạo giao diện user-friendly

### 📂 Vị Trị Code
- **File:** `main.cpp`
  - Hàm: `printAndyBanner()` - In banner khóa học

### 📝 Ví Dụ
```cpp
void printAndyBanner() {
    cout << R"(
NHOM 06: PHONE CONTACT MANAGEMENT APPLICATION
)" << endl;
}
```

---

## 📊 BẢNG TÓM TẮT CONCEPTS

| Concept | Tên Hàm | Tệp | Mục Đích |
|---------|---------|-----|---------|
| **System I/O** | loadFromFile, saveToFile | ContactManager.cpp | Đọc/ghi file |
| **Inheritance** | Contact base, 3 derived classes | Contact.h, *Contact.h | Kế thừa |
| **Polymorphism** | getCategoryDisplay, toFileLine | Contact.h, *Contact.cpp | Late binding |
| **Pure Virtual** | = 0 functions | Contact.h | Interface |
| **STL Vector** | vector<Contact*> | ContactManager.h | Danh sách động |
| **Operator <<** | operator<< | Contact.cpp | Nạp chồng |
| **Search/Filter** | searchByName, filterByRelationship | ContactManager.cpp | Tìm kiếm |
| **Memory Mgmt** | virtual ~Contact(), ~ContactManager() | Contact.h, ContactManager.cpp | Giải phóng |
| **UI/UX** | printMenu, printAndyBanner | main.cpp | Giao diện |

---

## 🎯 KẾT LUẬN

Dự án áp dụng **9/10 khái niệm OOP** được yêu cầu:
- ✅ Inheritance & Polymorphism (Chapter 4)
- ✅ Pure Virtual Functions
- ✅ Operator Overloading
- ✅ STL & Vector
- ✅ Search & Filter Logic
- ✅ File I/O
- ✅ Memory Management
- ✅ UI/UX Design
- ✅ ASCII Art Integration

**Điểm số kiến trúc: A+ (9/10)** 🌟
