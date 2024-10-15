#ifndef UNITTEST_H
#define UNITTEST_H

#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <fstream>

class UnitTest {

// This class handles Unit Tests. It follows the same format as the Week 9 workshops.

public:
    void runTests() {
        testSaveLoad();
        testCreateText();
    }

private:

   void testSaveLoad() {
        GameManager gameManager;
        
        int expectedValue = 9;

        std::ofstream save_unitTest;
        save_unitTest.open("saves/unit_test");
        if (!save_unitTest.is_open()) {
            std::cerr << "The saves directory could not be accessed. Game failed to save. \n";
        } else {
            save_unitTest << "test_value=" << expectedValue << std::endl;
            save_unitTest.close();
        }

        std::ifstream load_unitTest;
        load_unitTest.open("saves/unit_test");
        if (!load_unitTest.is_open()) {
            std::cout << "No save detected. \n";
        } else {
            std::string unitTest_str;
            load_unitTest >> unitTest_str;
        if (unitTest_str.substr(0, 11) != "test_value=") {
            std::cerr << "Save loading error, score not set correctly. \n";
            load_unitTest.close();
            return;
        }
        unitTest_str = unitTest_str.substr(11);  
        int resultValue = std::stoi(unitTest_str);
        load_unitTest.close();

        std::cout << "Expected save/load value is: " << expectedValue << std::endl;
        std::cout << "Retrieved save/load value is: " << resultValue << std::endl;
        if (expectedValue = resultValue) {
            std::cout << "Save/load test passed." << std::endl;
        } else {
            std::cout << "Save/load test failed." << std::endl;
        }

    }
}
    
    void testCreateText() {
        GameManager gameManager;

        std::string expectedString = "Test Text";
        std::string expectedColour = "Red";

        sf::Text test_text = gameManager.createText(expectedString, 30, sf::Color::Red, {100, 100});
        sf::RenderWindow window(sf::VideoMode(500, 500), "createText UnitTest");

        if (test_text.getString() != expectedString) {
            std::cout << "Text string test failed, string is incorrect." << std::endl;
        } else {
            std::cout << "String test passed, text should display " << expectedString << std::endl;
        }

        if (test_text.getColor() != sf::Color::Red) {
            std::cout << "Text colour test failed, colour is incorrect." << std::endl;
        } else {
            std::cout << "Colour test passed, text colour should be red." << std::endl;
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.draw(test_text);
            window.display();

        }
    }

 
};

#endif