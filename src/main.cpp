#include "include/core/SlideRepository.hpp"
#include "include/parser/Tokenizer.hpp"
#include "include/parser/Parser.hpp"
#include "include/command factory/CommandFactory.hpp"
#include <iostream>
#include <memory>
#include <string>

void printWelcome() {
    std::cout << "================================\n";
    std::cout << "    Welcome to SlideEditor\n";
    std::cout << "================================\n";
    std::cout << "Commands:\n";
    std::cout << "  create              - Create a new slide\n";
    std::cout << "  move <from> <to>    - Move slide from position to position\n";
    std::cout << "  addshape <idx> <type> - Add shape (Rectangle, Circle, Triangle) to slide\n";
    std::cout << "  addtext <idx> <text> - Add text to slide\n";
    std::cout << "  list                - List all slides\n";
    std::cout << "  display <idx>       - Display slide details\n";
    std::cout << "  save <filename>     - Save presentation to JSON\n";
    std::cout << "  load <filename>     - Load presentation from JSON\n";
    std::cout << "  exit                - Exit the application\n";
    std::cout << "================================\n\n";
}

int main() {
    auto repository = std::make_unique<SlideRepository>();
    printWelcome();
    
    std::string line;
    bool running = true;
    
    while (running) {
        std::cout << "> ";
        
        if (!std::getline(std::cin, line)) {
            break;
        }
        
        if (line.empty()) {
            continue;
        }
        
        try {
            auto tokens = Tokenizer::tokenizeString(line);
            auto parsedCommand = Parser::parse(tokens);
            auto command = CommandFactory::createCommand(parsedCommand);
            
            if (parsedCommand.command == "exit" || 
                parsedCommand.command == "quit") {
                command->execute(repository.get());
                running = false;
            } else {
                command->execute(repository.get());
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    
    return 0;
}