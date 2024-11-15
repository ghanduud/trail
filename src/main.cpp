
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

sf::Color operator*(float value, sf::Color color)
{
    return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);

    return (1 - alpha) * start + alpha * end;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Snake", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 80.f);



    const int numCircles = 5;
    std::vector<sf::CircleShape> circles(numCircles, sf::CircleShape(10.f));
    for (auto& circle : circles) {
        circle.setFillColor(sf::Color::Green);
    }

    float lerpAlpha = 0.2;



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time elapsedTime = clock.restart();

        while (elapsedTime > timePerFrame) {




            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            circles[0].setPosition(mousePos);

            for (int i = 1; i < numCircles; ++i) {
                sf::Vector2f targetPos = circles[i - 1].getPosition();
                sf::Vector2f currentPos = circles[i].getPosition();
                sf::Vector2f newPos = lerp(currentPos, targetPos, lerpAlpha);
                circles[i].setPosition(newPos);
            }


            elapsedTime -= timePerFrame;
        }


        window.clear();

        for (const auto& circle : circles) {
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}