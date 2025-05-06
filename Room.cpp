#include "Room.h"
#include <algorithm>

Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false) {
}

Room::Room(const Room& other)
    : name(other.name), description(other.description), 
      items(other.items), exits(other.exits), visited(other.visited) {
}

Room& Room::operator=(const Room& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        items = other.items;
        exits = other.exits;
        visited = other.visited;
    }
    return *this;
}

Room::~Room() {
}

bool Room::addItem(const Item& item) {
    items.push_back(item);
    return true;
}

bool Room::removeItem(const std::string& itemName, Item& removedItem) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName) {
            removedItem = *it;
            std::cout << "Removed " << removedItem.getValue() << std::endl;
            items.erase(it);
            return true;
        }
    }
    throw RoomException("Item not found in room: " + itemName);
}

bool Room::connectRoom(const std::string& direction, int roomIndex) {
    if (exits.find(direction) != exits.end()) {
        throw RoomException("Exit already exists in that direction");
    }

    exits[direction] = roomIndex;
    return true;
}

void Room::enter() {
    visited = true;
}

bool Room::hasExit(const std::string& direction) const {
    return exits.find(direction) != exits.end();
}

int Room::getExitIndex(const std::string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    throw RoomException("Exit not found in direction: " + direction);
}

void Room::listItems() const {
    if (items.empty()) {
        std::cout << "There are no items in this room." << std::endl;
        return;
    }
    
    std::cout << "Items in this room:" << std::endl;
    for (const auto& item : items) {
        std::cout << "- " << item << std::endl;
    }
}

void Room::listExits() const {
    if (exits.empty()) {
        std::cout << "There are no visible exits." << std::endl;
        return;
    }
    
    std::cout << "Exits:" << std::endl;
    for (const auto& exit : exits) {
        std::cout << "- " << exit.first << std::endl;
    }
}

bool Room::containsItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

std::string Room::getName() const {
    return name;
}

std::string Room::getDescription() const {
    return description;
}

bool Room::wasVisited() const {
    return visited;
}

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os << room.name << "\n" << room.description;
    return os;
}