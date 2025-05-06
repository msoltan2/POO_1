#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

class Entity {
protected:
    std::string name;
    std::string description;

public:
    Entity(const std::string& name = "Unknown", const std::string& description = "No description");
    Entity(const Entity& other);
    virtual ~Entity();


    friend void swap(Entity& first, Entity& second) noexcept;

    virtual Entity* clone() const = 0;

    std::string getName() const;
    std::string getDescription() const;

    virtual std::string getDetailedInfo() const;

    static int countEntities;
    static int getCount();
};

#endif