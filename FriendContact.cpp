#include "FriendContact.h"

string FriendContact::toFileLine() const {
    return "FRIEND|" + name + "|" + phone;
}