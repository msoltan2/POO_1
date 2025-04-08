#include "Item.h"
#include <sstream>

Item::Item(const std::string& name, const std::string& description, bool usable, int value)
    : name(name), description(description), usable(usable), value(value) {
}

Item::Item(const Item& other)
    : name(other.name), description(other.description), usable(other.usable), value(other.value) {
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        usable = other.usable;
        value = other.value;
    }
    return *this;
}

Item::~Item() {
}

bool Item::use() {
    if (usable) {
        std::cout << "Using " << name << "..." << std::endl;
        return true;
    }
    std::cout << "Cannot use " << name << "." << std::endl;
    return false;
}

void Item::enhance(int additionalValue) {
    if (additionalValue > 0) {
        value += additionalValue;
        std::cout << name << " has been enhanced. New value: " << value << std::endl;
    } else {
        std::cout << "Cannot enhance " << name << " with non-positive value." << std::endl;
    }
}

std::string Item::getDetailedInfo() const {
    std::stringstream ss;
    ss << "Item: " << name << "\n";
    ss << "Description: " << description << "\n";
    ss << "Value: " << value << "\n";
    ss << "Can be used: " << (usable ? "Yes" : "No");
    return ss.str();
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

bool Item::isUsable() const {
    return usable;
}

int Item::getValue() const {
    return value;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (Value: " << item.value << ")";
    return os;
}