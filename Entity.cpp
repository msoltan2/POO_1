#include "Entity.h"

int Entity::countEntities = 0;

Entity::Entity(const std::string& name, const std::string& description)
    : name(name), description(description) {
    countEntities++;
}

Entity::Entity(const Entity& other)
    : name(other.name), description(other.description) {
    countEntities++;
}

Entity::~Entity() {
    countEntities--;
}

void swap(Entity& first, Entity& second) noexcept {
    using std::swap;
    swap(first.name, second.name);
    swap(first.description, second.description);
}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getDescription() const {
    return description;
}

std::string Entity::getDetailedInfo() const {
    return name + ": " + description;
}

int Entity::getCount() {
    return countEntities;
}