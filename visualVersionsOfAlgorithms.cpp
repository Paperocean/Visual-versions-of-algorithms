#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "listAdjacency.h"
#include "advanceSort.h"
#include "linearSort.h"
#include "basicTraversal.h"
using namespace std;


//void drawArray(sf::RenderWindow& window, const std::vector<int>& arr) {
//    window.clear(sf::Color::Black);
//    int barWidth = window.getSize().x / arr.size();
//    float barHeight = window.getSize().y / *max_element(arr.begin(), arr.end());
//    for (size_t i = 0; i < arr.size(); i++) {
//        sf::RectangleShape bar(sf::Vector2f(barWidth - 1, -arr[i] * barHeight));
//        bar.setPosition(i * barWidth, barHeight);
//        bar.setFillColor(sf::Color::White);
//        window.draw(bar);
//    }
//    window.display();
//}

void visualizeSort(sf::RenderWindow& window, std::vector<int>& arr) {
    AdvanceSort sort;
    sort.mergeSort(window, arr.data(), 0, arr.size() - 1);
}

void handleEvents(sf::RenderWindow& window, sf::View& view, sf::Vector2f& oldPos, bool& dragging) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta > 0)
                view.zoom(0.9f);
            else if (event.mouseWheelScroll.delta < 0)
                view.zoom(1.1f);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                dragging = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                dragging = false;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                view.setCenter(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }
    }
}

void drawGraph(sf::RenderWindow& window, const std::vector<int>& path, ListAdjacency& list, int destination) {
    std::vector<sf::Color> colors(list.getV(), sf::Color::White);
    std::vector<int> distances = path;

    colors[0] = sf::Color::Green;
    colors[24] = sf::Color::Red;

    float xStep = window.getSize().x / (destination + 1);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        exit(1);
    }

    for (int i = 0; i <= destination; i++) {
        sf::CircleShape centerNode(10.f);
        centerNode.setPosition(window.getSize().x / 2 - centerNode.getRadius(), window.getSize().y / 2 - centerNode.getRadius());
        centerNode.setFillColor(sf::Color::Green);
        window.draw(centerNode);

        float angleStep = 2 * 3.14159f / destination;
        for (int i = 1; i <= destination; i++) {
            sf::CircleShape node(10.f);
            float radius = i * 20.f; // Change this value to adjust the distance between nodes
            float angle = i * angleStep;
            node.setPosition(window.getSize().x / 2 + radius * cos(angle) - node.getRadius(), window.getSize().y / 2 + radius * sin(angle) - node.getRadius());
            node.setFillColor(colors[i]);
            window.draw(node);

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(centerNode.getPosition().x + centerNode.getRadius(), centerNode.getPosition().y + centerNode.getRadius())),
                sf::Vertex(sf::Vector2f(node.getPosition().x + node.getRadius(), node.getPosition().y + node.getRadius()))
            };
            window.draw(line, 2, sf::Lines);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(distances[i]));
            text.setCharacterSize(10);
            text.setFillColor(sf::Color::Magenta);
            text.setPosition(node.getPosition().x + node.getRadius(), node.getPosition().y + node.getRadius());
            window.draw(text);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "GRAPH VISUAL");

    ListAdjacency list(100);
    int source = 0;
    int destination = 24;

    for (int i = 0; i < 100; i++) {
        list.addEdge(i, (i + 1) % 100, i);
    }

    // give random data to sort
    std::vector<int> data(100);
    for (int i = 0; i < 100; i++) {
		data[i] = rand() % 100;
	}

    sf::View view(sf::FloatRect(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    window.setView(view);

    sf::Vector2f oldPos;
    bool dragging = false;

    while (window.isOpen())
    {
        handleEvents(window, view, oldPos, dragging);

        if (dragging)
        {
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            const sf::Vector2f delta = oldPos - newPos;

            view.move(delta);
            oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        }

        window.clear();

        //std::vector<int> path = list.dijkstra(source, destination);
        //drawGraph(window, path, list, destination);

        visualizeSort(window, data);

        window.setView(view);
        window.display();
    }

    return 0;
}
