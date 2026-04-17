CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = phone_contact
SOURCES = main.cpp Contact.cpp FamilyContact.cpp FriendContact.cpp WorkContact.cpp ContactManager.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: clean
