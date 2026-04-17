cmake_minimum_required(VERSION 3.15)
project(PhoneContact LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(phone_contact
    main.cpp
    Contact.cpp
    FamilyContact.cpp
    FriendContact.cpp
    WorkContact.cpp
    ContactManager.cpp
)
