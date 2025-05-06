#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Item.h"
#include "GameExceptions.h"

class Room {
private:
    std::string name;
    std::string description;
    std::vector<Item> items;
    std::map<std::string, int> exits;
    bool visited;

public:
    explicit Room(const std::string& name = "Unknown Room", 
                  const std::string& description = "An empty room");
    
    Room(const Room& other);
    
    Room& operator=(const Room& other);
    
    ~Room();
    
    bool addItem(const Item& item);
    bool removeItem(const std::string& itemName, Item& removedItem);
    bool connectRoom(const std::string& direction, int roomIndex);
    
    void enter();
    bool hasExit(const std::string& direction) const;
    int getExitIndex(const std::string& direction) const;
    void listItems() const;
    void listExits() const;
    bool containsItem(const std::string& itemName) const;
    
    std::string getName() const;
    std::string getDescription() const;
    bool wasVisited() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

#endif