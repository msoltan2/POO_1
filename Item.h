#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
private:
    std::string name;
    std::string description;
    bool usable;
    int value;

public:
    explicit Item(const std::string& name = "Unknown", 
                  const std::string& description = "No description", 
                  bool usable = false, 
                  int value = 0);

    Item(const Item& other);
    
    Item& operator=(const Item& other);
    
    ~Item();
    
    bool use();
    void enhance(int additionalValue);
    std::string getDetailedInfo() const;
    
    std::string getName() const;
    std::string getDescription() const;
    bool isUsable() const;
    int getValue() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif