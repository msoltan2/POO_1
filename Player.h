#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "GameExceptions.h"

class Player {
private:
    std::string name;
    int currentRoom;
    std::vector<Item> inventory;
    int health;
    int maxItems;

public:
    explicit Player(const std::string& name = "Player", 
                   int startRoom = 0, 
                   int health = 100, 
                   int maxItems = 10);
    
    Player(const Player& other);
    
    Player& operator=(const Player& other);
    
    ~Player();
    
    bool addToInventory(const Item& item);
    bool removeFromInventory(const std::string& itemName, Item& removedItem);
    bool useItem(const std::string& itemName);
    
    void displayInventory() const;
    bool hasItem(const std::string& itemName) const;
    void move(int roomIndex);
    void changeHealth(int amount);
    
    std::string getName() const;
    int getCurrentRoom() const;
    int getHealth() const;
    int getInventorySize() const;
    int getMaxItems() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif