#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "GameExceptions.h"

class Item : public Entity {
private:
    bool usable;
    int value;

public:
    explicit Item(const std::string& name = "Unknown",
                  const std::string& description = "No description",
                  bool usable = false,
                  int value = 0);

    Item(const Item& other);

    Item& operator=(Item other);

    ~Item() override;

    Item* clone() const override;

    bool use();
    void enhance(int additionalValue);
    std::string getDetailedInfo() const override;

    bool isUsable() const;
    int getValue() const;
    static void identifyAndUseItem(Item* item);

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

class Weapon : public Item {
private:
    int damage;

public:
    Weapon(const std::string& name, const std::string& description, int value, int damage);
    Weapon(const Weapon& other);
    Weapon& operator=(Weapon other);
    ~Weapon() override;

    Weapon* clone() const override;

    bool use();
    int getDamage() const;
    void upgradeDamage(int amount);

    std::string getDetailedInfo() const override;
};

class ConsumableItem : public Item {
private:
    int healthEffect;
    int usesLeft;

public:
    ConsumableItem(const std::string& name, const std::string& description,
                   int value, int healthEffect, int uses = 1);
    ConsumableItem(const ConsumableItem& other);
    ConsumableItem& operator=(ConsumableItem other);
    ~ConsumableItem() override;

    ConsumableItem* clone() const override;

    bool use();
    int getHealthEffect() const;
    int getUsesLeft() const;

    std::string getDetailedInfo() const override;
};

#endif