#include "Player.h"
#include <algorithm>
#include "GameExceptions.h"

Player::Player(const std::string& name, int startRoom, int health, int maxItems)
    : name(name), currentRoom(startRoom), health(health), maxItems(maxItems) {
}

Player::Player(const Player& other)
    : name(other.name), currentRoom(other.currentRoom),
      inventory(other.inventory), health(other.health), maxItems(other.maxItems) {
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        currentRoom = other.currentRoom;
        inventory = other.inventory;
        health = other.health;
        maxItems = other.maxItems;
    }
    return *this;
}

Player::~Player() {
}

bool Player::addToInventory(const Item& item) {
    if (inventory.size() >= static_cast<size_t>(maxItems)) {
        throw InventoryFullException();
    }

    inventory.push_back(item);
    std::cout << "Added " << item.getName() << " to inventory." << std::endl;
    return true;
}

bool Player::removeFromInventory(const std::string& itemName, Item& removedItem) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getName() == itemName) {
            removedItem = *it;
            inventory.erase(it);
            std::cout << "Removed " << itemName << " from inventory." << std::endl;
            return true;
        }
    }

    throw ItemNotFoundException(itemName);
}

bool Player::useItem(const std::string& itemName) {
    for (auto& item : inventory) {
        if (item.getName() == itemName) {
            bool result = item.use();
            if (result) {
                std::cout << "You used " << itemName << "." << std::endl;
            }
            return result;
        }
    }

    throw ItemNotFoundException(itemName);
}

void Player::displayInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
        return;
    }
    
    std::cout << "Inventory (" << inventory.size() << "/" << maxItems << "):" << std::endl;
    for (const auto& item : inventory) {
        std::cout << "- " << item << std::endl;
    }
}

bool Player::hasItem(const std::string& itemName) const {
    for (const auto& item : inventory) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}

void Player::move(int roomIndex) {
    currentRoom = roomIndex;
    std::cout << "You moved to room index " << roomIndex << "." << std::endl;
}

void Player::changeHealth(int amount) {
    health += amount;
    if (health < 0) {
        health = 0;
    }
    
    if (amount > 0) {
        std::cout << "You gained " << amount << " health. Current health: " << health << std::endl;
    } else if (amount < 0) {
        std::cout << "You lost " << -amount << " health. Current health: " << health << std::endl;
    }
}

std::string Player::getName() const {
    return name;
}

int Player::getCurrentRoom() const {
    return currentRoom;
}

int Player::getHealth() const {
    return health;
}

int Player::getInventorySize() const {
    return static_cast<int>(inventory.size());
}

int Player::getMaxItems() const {
    return maxItems;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.name << " (Health: " << player.health 
       << ", Room: " << player.currentRoom 
       << ", Items: " << player.inventory.size() << "/" << player.maxItems << ")";
    return os;
}