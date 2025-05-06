#include "Item.h"
#include <sstream>

Item::Item(const std::string& name, const std::string& description, bool usable, int value)
    : Entity(name, description), usable(usable), value(value) {
}

Item::Item(const Item& other)
    : Entity(other), usable(other.usable), value(other.value) {
}

Item& Item::operator=(Item other) {
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

Item* Item::clone() const {
    return new Item(*this);
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
        throw ItemException("Cannot enhance item with non-positive value");
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

// Weapon implementation
Weapon::Weapon(const std::string& name, const std::string& description, int value, int damage)
    : Item(name, description, true, value), damage(damage) {
}

Weapon::Weapon(const Weapon& other)
    : Item(other), damage(other.damage) {
}

Weapon& Weapon::operator=(Weapon other) {
    swap(*this, other);
    static_cast<Item&>(*this) = static_cast<Item&>(other);
    std::swap(damage, other.damage);
    return *this;
}

Weapon::~Weapon() {
}

Weapon* Weapon::clone() const {
    return new Weapon(*this);
}

bool Weapon::use() {
    std::cout << "You swing the " << name << " dealing " << damage << " damage!" << std::endl;
    return true;
}

int Weapon::getDamage() const {
    return damage;
}

void Weapon::upgradeDamage(int amount) {
    if (amount <= 0) {
        throw ItemException("Cannot upgrade weapon with non-positive value");
    }
    damage += amount;
    std::cout << name << " damage upgraded to " << damage << std::endl;
}

std::string Weapon::getDetailedInfo() const {
    std::stringstream ss;
    ss << Item::getDetailedInfo() << "\n";
    ss << "Damage: " << damage;
    return ss.str();
}

// ConsumableItem implementation
ConsumableItem::ConsumableItem(const std::string& name, const std::string& description,
                               int value, int healthEffect, int uses)
    : Item(name, description, true, value), healthEffect(healthEffect), usesLeft(uses) {
    if (uses <= 0) {
        throw ItemException("Consumable must have at least one use");
    }
}

ConsumableItem::ConsumableItem(const ConsumableItem& other)
    : Item(other), healthEffect(other.healthEffect), usesLeft(other.usesLeft) {
}

ConsumableItem& ConsumableItem::operator=(ConsumableItem other) {
    swap(*this, other);
    static_cast<Item&>(*this) = static_cast<Item&>(other);
    std::swap(healthEffect, other.healthEffect);
    std::swap(usesLeft, other.usesLeft);
    return *this;
}

ConsumableItem::~ConsumableItem() {
}

ConsumableItem* ConsumableItem::clone() const {
    return new ConsumableItem(*this);
}

bool ConsumableItem::use() {
    if (usesLeft <= 0) {
        std::cout << "This " << name << " has been used up." << std::endl;
        return false;
    }

    std::cout << "You used " << name;
    if (healthEffect > 0) {
        std::cout << " and recovered " << healthEffect << " health points." << std::endl;
    } else if (healthEffect < 0) {
        std::cout << " and took " << -healthEffect << " damage." << std::endl;
    } else {
        std::cout << " but nothing happened." << std::endl;
    }

    usesLeft--;
    return true;
}

int ConsumableItem::getHealthEffect() const {
    return healthEffect;
}

int ConsumableItem::getUsesLeft() const {
    return usesLeft;
}

std::string ConsumableItem::getDetailedInfo() const {
    std::stringstream ss;
    ss << Item::getDetailedInfo() << "\n";
    ss << "Health Effect: " << healthEffect << "\n";
    ss << "Uses Left: " << usesLeft;
    return ss.str();
}

void Item::identifyAndUseItem(Item* item) {
    if (!item) {
        std::cout << "Null item pointer provided." << std::endl;
        return;
    }

    std::cout << "\nIdentifying item: " << item->getName() << std::endl;

    // Try to cast to Weapon
    if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
        std::cout << "This is a Weapon with " << weapon->getDamage() << " damage." << std::endl;
        weapon->use();

        weapon->upgradeDamage(5);
    }
    // Try to cast to ConsumableItem
    else if (ConsumableItem* consumable = dynamic_cast<ConsumableItem*>(item)) {
        std::cout << "This is a ConsumableItem with " << consumable->getHealthEffect()
                  << " health effect and " << consumable->getUsesLeft() << " uses left." << std::endl;
        consumable->use();
    }
    // It's a base Item
    else {
        std::cout << "This is a basic Item." << std::endl;
        item->use();
    }

    std::cout << "\nDetailed information:" << std::endl;
    std::cout << item->getDetailedInfo() << std::endl;
}