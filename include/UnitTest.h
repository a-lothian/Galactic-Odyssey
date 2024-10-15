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
        testUpdateTimer();
        testHUD();
        testInput();
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
            std::cerr << "Save loading error, value not set correctly. \n";
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

    void testUpdateTimer() {
        sf::Clock timer;
        GameManager gameManager;
        int seconds = 590;
        std::string test_timer = "Time: ";
        sf::Text timer_text = gameManager.createText(test_timer, 25, sf::Color::White, {100, 100});
        sf::RenderWindow window(sf::VideoMode(500, 500), "updateTimer UnitTest");
        std::cout << "Expected time should start at 9:50." << std::endl;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (timer.getElapsedTime().asSeconds() >= 1) {
            timer.restart();
            seconds++; 
            int minutes = seconds / 60;
            int remainingSeconds = seconds % 60;

        // Formatting the time
         std::string time_check = "Time: ";
            if (seconds < 600) {
             time_check.append("0");
            }
         time_check.append(std::to_string(minutes));
         time_check.append(":");
         if (remainingSeconds < 10) {
             time_check.append("0");
          }
         time_check.append(std::to_string(remainingSeconds));
         

            timer_text.setString(time_check);
        }
            window.clear();
            window.draw(timer_text);
            window.display();

        }
    }

    void testHUD() {
    GameManager gameManager;
    sf::RenderWindow window(sf::VideoMode(500, 500), "testHUD UnitTest");
    std::string ui_score = "Score: ";
    std::string ui_timer = "Time: ";
    sf::Text score_text = gameManager.createText(ui_score, 25, sf::Color::White, {30, 20});
    sf::Text timer_text = gameManager.createText(ui_timer, 25, sf::Color::White, {340, 20});
    std::cout << "Should display. \n";
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            window.draw(score_text);
            window.draw(timer_text);
            window.display();

        }
    }

    void testInput() {
    GameManager gameManager;
    sf::RenderWindow window(sf::VideoMode(500, 500), "testInput UnitTest");
    std::cout << "Should print up pressed when up is pressed. \n";
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                std::cout << "Up pressed" << std::endl;
            }
            window.display();

        }
    }



 
};

#endif