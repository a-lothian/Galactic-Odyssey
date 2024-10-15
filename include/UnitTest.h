#ifndef UNITTEST_H
#define UNITTEST_H

#include <SFML/Graphics.hpp>
#include "GameManager.h"

class UnitTest {

// This class handles Unit Tests. It follows the same format as the Week 9 workshops.

public:
    void runTests() {
        testCreateText();
    }

private:
    void testCreateText() {
        GameManager gameManager;
        sf::Text test_text = gameManager.createText("Test Text", 30, sf::Color::Red, {100, 100});
        sf::RenderWindow window(sf::VideoMode(500, 500), "createText UnitTest");

        if (test_text.getString() != "Test Text") {
            std::cout << "Text string test failed, string is incorrect." << std::endl;
        } else {
            std::cout << "String test passed, text should display correctly." << std::endl;
        }

        if (test_text.getColor() != sf::Color::Red) {
            std::cout << "Text colour test failed, colour is incorrect." << std::endl;
        } else {
            std::cout << "Colour test passed, text colour should display correctly." << std::endl;
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