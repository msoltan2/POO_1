#include <iostream>
#include <string>
#include "Game.h"
#include "Item.h"
#include "Room.h"
#include "Player.h"

// void testAllFunctionality() {
//     std::cout << "--- Testing Item Class ---" << std::endl;
//     Item sword("Sword", "A sharp blade", true, 10);
//     Item shield("Shield", "Protective gear", false, 5);
//     Item potion = sword;
//
//     std::cout << "Item created: " << sword << std::endl;
//     std::cout << "Item copied: " << potion << std::endl;
//
//     potion = shield;
//     std::cout << "Item assigned: " << potion << std::endl;
//
//     sword.enhance(5);
//     std::cout << "Enhanced item: " << sword << std::endl;
//     std::cout << "Detailed info: " << sword.getDetailedInfo() << std::endl;
//     bool used = sword.use();
//     std::cout << "Item used: " << (used ? "Yes" : "No") << std::endl;
//
//     std::cout << "\n--- Testing Room Class ---" << std::endl;
//     Room cave("Cave", "A dark, damp cave");
//     Room forest("Forest", "A lush, green forest");
//     Room tempRoom = cave;
//
//     std::cout << "Room created: " << cave << std::endl;
//     std::cout << "Room copied: " << tempRoom << std::endl;
//
//     tempRoom = forest;
//     std::cout << "Room assigned: " << tempRoom << std::endl;
//
//     cave.addItem(sword);
//     cave.addItem(shield);
//     std::cout << "Added items to room" << std::endl;
//     cave.listItems();
//
//     cave.connectRoom("north", 1);
//     cave.connectRoom("east", 2);
//     std::cout << "Connected exits to room" << std::endl;
//     cave.listExits();
//
//     cave.enter();
//     std::cout << "Entered room: " << (cave.wasVisited() ? "visited" : "not visited") << std::endl;
//
//     Item removedItem("Empty", "", false, 0);
//     bool removed = cave.removeItem("Sword", removedItem);
//     std::cout << "Item removed: " << (removed ? "Yes" : "No") << std::endl;
//     std::cout << "Removed item: " << removedItem << std::endl;
//
//     std::cout << "\n--- Testing Player Class ---" << std::endl;
//     Player hero("Hero", 0, 100, 5);
//     Player sidekick = hero;
//
//     std::cout << "Player created: " << hero << std::endl;
//     std::cout << "Player copied: " << sidekick << std::endl;
//
//     Player villain("Villain", 1, 80, 3);
//     sidekick = villain;
//     std::cout << "Player assigned: " << sidekick << std::endl;
//
//     hero.addToInventory(sword);
//     hero.addToInventory(shield);
//     std::cout << "Added items to inventory" << std::endl;
//     hero.displayInventory();
//
//     hero.move(1);
//     std::cout << "Player moved to room: " << hero.getCurrentRoom() << std::endl;
//
//     hero.changeHealth(-10);
//     std::cout << "Player health changed: " << hero.getHealth() << std::endl;
//
//     bool hasItem = hero.hasItem("Shield");
//     std::cout << "Player has Shield: " << (hasItem ? "Yes" : "No") << std::endl;
//
//     Item usedItem("Empty", "", false, 0);
//     bool itemRemoved = hero.removeFromInventory("Shield", usedItem);
//     std::cout << "Item removed from inventory: " << (itemRemoved ? "Yes" : "No") << std::endl;
//     std::cout << "Used item: " << usedItem << std::endl;
//
//     bool itemUsed = hero.useItem("Sword");
//     std::cout << "Player used Sword: " << (itemUsed ? "Yes" : "No") << std::endl;
//
//     std::cout << "\n--- Testing Game Class ---" << std::endl;
//     Game game("Test Adventure");
//     Game gameCopy = game;
//
//     std::cout << "Game created: " << game << std::endl;
//     std::cout << "Game copied: " << gameCopy << std::endl;
//
//     Game anotherGame("Another Adventure");
//     gameCopy = anotherGame;
//     std::cout << "Game assigned: " << gameCopy << std::endl;
//
//     game.start();
//     game.displayCurrentRoom();
//
//     bool commandProcessed = game.processCommand("look");
//     std::cout << "Command processed: " << (commandProcessed ? "Yes" : "No") << std::endl;
//
//     game.quit();
//     std::cout << "Game over: " << (game.isOver() ? "Yes" : "No") << std::endl;
// }

int main() {
    // std::cout << "Welcome to the Text Adventure Game!" << std::endl;
    
    // testAllFunctionality();
    
    std::cout << "\n--- Starting Actual Game ---" << std::endl;
    Game game("The Enchanted Forest");
    
    game.start();
    
    std::string command;
    while (!game.isOver()) {
        std::cout << "\nEnter command: ";
        std::getline(std::cin, command);
        
        if (!game.processCommand(command)) {
            std::cout << "Unknown command. Try 'help' for a list of commands." << std::endl;
        }
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    
    return 0;
}