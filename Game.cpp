#include "Game.h"
#include <sstream>
#include <algorithm>

Game::Game(const std::string& gameTitle)
    : gameOver(false), gameTitle(gameTitle), player("Player", 0, 100, 5) {
    initializeRooms();
    initializeItems();
}

Game::Game(const Game& other)
    : rooms(other.rooms), player(other.player), 
      gameOver(other.gameOver), gameTitle(other.gameTitle) {
}

Game& Game::operator=(const Game& other) {
    if (this != &other) {
        rooms = other.rooms;
        player = other.player;
        gameOver = other.gameOver;
        gameTitle = other.gameTitle;
    }
    return *this;
}

Game::~Game() {
}

void Game::initializeRooms() {
    Room entrance("Forest Entrance", "A clearing at the edge of a dense forest.");
    Room path("Forest Path", "A narrow path winding through tall trees.");
    Room cave("Dark Cave", "A damp, dark cave with strange markings on the walls.");
    
    entrance.connectRoom("north", 1);
    path.connectRoom("south", 0);
    path.connectRoom("east", 2);
    cave.connectRoom("west", 1);
    // Maybe generate rooms randomly
    
    rooms.push_back(entrance);
    rooms.push_back(path);
    rooms.push_back(cave);
}

void Game::initializeItems() {
    Item map("map", "A worn map of the forest area", true, 5);
    Item sword("sword", "A rusty old sword", true, 10);
    Item gem("gemstone", "A glowing blue gemstone", false, 20);
    
    rooms[0].addItem(map);
    rooms[1].addItem(sword);
    rooms[2].addItem(gem);
}

bool Game::processCommand(const std::string& command) {
    std::string cmd = command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    if (cmd == "help") {
        displayHelp();
        return true;
    }
    else if (cmd == "look") {
        displayCurrentRoom();
        return true;
    }
    else if (cmd == "inventory" || cmd == "inv") {
        player.displayInventory();
        return true;
    }
    else if (cmd == "quit" || cmd == "exit") {
        quit();
        return true;
    }
    else if (cmd.substr(0, 4) == "take" && cmd.length() > 5) {
        std::string itemName = cmd.substr(5);
        int currentRoomIndex = player.getCurrentRoom();
        Item takenItem("", "", false, 0);
        
        if (rooms[currentRoomIndex].containsItem(itemName)) {
            if (rooms[currentRoomIndex].removeItem(itemName, takenItem)) {
                player.addToInventory(takenItem);
                return true;
            }
        } else {
            std::cout << "There is no " << itemName << " here." << std::endl;
            return true;
        }
    }
    else if (cmd.substr(0, 4) == "drop" && cmd.length() > 5) {
        std::string itemName = cmd.substr(5);
        int currentRoomIndex = player.getCurrentRoom();
        Item droppedItem("", "", false, 0);
        
        if (player.removeFromInventory(itemName, droppedItem)) {
            rooms[currentRoomIndex].addItem(droppedItem);
            return true;
        }
        return true;
    }
    else if (cmd.substr(0, 3) == "use" && cmd.length() > 4) {
        std::string itemName = cmd.substr(4);
        player.useItem(itemName);
        return true;
    }
    else if (cmd == "north" || cmd == "south" || cmd == "east" || cmd == "west") {
        int currentRoomIndex = player.getCurrentRoom();
        
        if (rooms[currentRoomIndex].hasExit(cmd)) {
            int newRoomIndex = rooms[currentRoomIndex].getExitIndex(cmd);
            player.move(newRoomIndex);
            rooms[newRoomIndex].enter();
            displayCurrentRoom();
            return true;
        } else {
            std::cout << "You cannot go that way." << std::endl;
            return true;
        }
    }
    
    return false;
}

void Game::start() {
    std::cout << "Welcome to " << gameTitle << "!" << std::endl;
    std::cout << "Type 'help' for a list of commands." << std::endl;
    displayCurrentRoom();
}

void Game::displayCurrentRoom() const {
    int currentRoomIndex = player.getCurrentRoom();
    std::cout << "\n" << rooms[currentRoomIndex] << std::endl;
    rooms[currentRoomIndex].listItems();
    rooms[currentRoomIndex].listExits();
}

void Game::quit() {
    std::cout << "Thank you for playing!" << std::endl;
    gameOver = true;
}

bool Game::isOver() const {
    return gameOver;
}

void Game::displayHelp() const {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  look - Look around the current room" << std::endl;
    std::cout << "  inventory (or inv) - Check your inventory" << std::endl;
    std::cout << "  take [item] - Pick up an item" << std::endl;
    std::cout << "  drop [item] - Drop an item" << std::endl;
    std::cout << "  use [item] - Use an item" << std::endl;
    std::cout << "  north, south, east, west - Move in a direction" << std::endl;
    std::cout << "  quit - Quit the game" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "Game: " << game.gameTitle << " (Player: " << game.player << ")";
    return os;
}