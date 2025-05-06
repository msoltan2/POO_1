#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string message;

public:
    explicit GameException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ItemException : public GameException {
public:
    explicit ItemException(const std::string& msg) : GameException("Item error: " + msg) {}
};

class RoomException : public GameException {
public:
    explicit RoomException(const std::string& msg) : GameException("Room error: " + msg) {}
};

class PlayerException : public GameException {
public:
    explicit PlayerException(const std::string& msg) : GameException("Player error: " + msg) {}
};

class InventoryFullException : public PlayerException {
public:
    InventoryFullException() : PlayerException("Inventory is full") {}
};

class ItemNotFoundException : public PlayerException {
public:
    explicit ItemNotFoundException(const std::string& itemName) 
        : PlayerException("Item not found: " + itemName) {}
};

#endif