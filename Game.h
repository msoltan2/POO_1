#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Room.h"
#include "Player.h"

class Game {
private:
    std::vector<Room> rooms;
    Player player;
    bool gameOver;
    std::string gameTitle;
    
    void initializeRooms();
    void initializeItems();
    void displayHelp() const;

public:
    explicit Game(const std::string& gameTitle = "Text Adventure");
    
    Game(const Game& other);
    
    Game& operator=(const Game& other);
    
    ~Game();
    
    bool processCommand(const std::string& command);
    
    void start();
    void displayCurrentRoom() const;
    void quit();
    bool isOver() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};

#endif