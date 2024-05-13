#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

#include "listAdjacency.h"
#include "advanceSort.h"
#include "linearSort.h"
#include "basicTraversal.h"
#include "graph.h"
using namespace std;

void visualizeSort(sf::RenderWindow& window, std::vector<int>& arr) {
    AdvanceSort sort;
    sort.mergeSort(window, arr.data(), 0, arr.size() - 1);
    //sort.quickSort(window, arr.data(), 0, arr.size() - 1);
    //sort.bucketSort(window, arr.data(), arr.size());
}

void visualizeTraversal(sf::RenderWindow& window, std::vector<int>& arr) {
	BasicTraversal traversal;
    //traversal.linearTraversal(window, arr.data(), arr.size());
    //traversal.binaryTraversal(window, arr.data(), arr.size());
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

struct Node {
    sf::CircleShape shape;
    sf::Text label;
};

void drawGraph(sf::RenderWindow& window, const std::vector<int>& path, int destination) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font" << std::endl;
        exit(1);
    }

    std::vector<Node> nodes(destination + 1);
    std::vector<int> distances = path;

    // Determine the radius of the circle enclosing the graph
    float radius = std::min(window.getSize().x, window.getSize().y) / 4.0f;

    float angleStep = 2 * 3.14 / destination;
    sf::Vector2f center(window.getSize().x / 2, window.getSize().y / 2);

    // Create nodes and labels
    for (int i = 0; i <= destination; i++) {
        float angle = i * angleStep;
        sf::Vector2f position(center.x + radius * cos(angle), center.y + radius * sin(angle));

        nodes[i].shape.setRadius(20.f); // Adjust node radius
        if (std::find(path.begin(), path.end(), i) != path.end())
            nodes[i].shape.setFillColor(sf::Color::Green); // Highlight path
        else if (i == 0)
            nodes[i].shape.setFillColor(sf::Color::Red); // Source node
        else if (i == destination)
            nodes[i].shape.setFillColor(sf::Color::Blue); // Destination node
        else
            nodes[i].shape.setFillColor(sf::Color::White); // Default color)
        nodes[i].shape.setPosition(position.x - nodes[i].shape.getRadius(), position.y - nodes[i].shape.getRadius());

        nodes[i].label.setFont(font);
        nodes[i].label.setCharacterSize(20); // Adjust font size
        nodes[i].label.setFillColor(sf::Color::Black);
        nodes[i].label.setString(std::to_string(distances[i]));
        nodes[i].label.setOrigin(nodes[i].label.getLocalBounds().width / 2, nodes[i].label.getLocalBounds().height / 2);
        nodes[i].label.setPosition(position);

        window.draw(nodes[i].shape);
        window.draw(nodes[i].label);
    }

    // Connect nodes with lines
    for (int i = 0; i < destination; i++) {
        sf::Vertex line[] = {
            sf::Vertex(nodes[i].shape.getPosition() + sf::Vector2f(nodes[i].shape.getRadius(), nodes[i].shape.getRadius())),
            sf::Vertex(nodes[i + 1].shape.getPosition() + sf::Vector2f(nodes[i + 1].shape.getRadius(), nodes[i + 1].shape.getRadius()))
        };
        window.draw(line, 2, sf::Lines);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "GRAPH VISUAL");

    int source = 0;
    int destination = 24;

    ListAdjacency list(100);
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    dragging = true;
                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    dragging = false;
            }
			else if (event.type == sf::Event::MouseMoved)
			{
				if (dragging)
				{
					const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					const sf::Vector2f delta = oldPos - newPos;

					view.move(delta);
					oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
					view.zoom(0.9f);
				else if (event.mouseWheelScroll.delta < 0)
					view.zoom(1.1f);
			}
        }

        if (dragging)
        {
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            const sf::Vector2f delta = oldPos - newPos;

            view.move(delta);
            oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        }

        window.clear();

        std::vector<int> path = list.dijkstra(source, destination);
        drawGraph(window, path, destination);

        //visualizeSort(window, data);
        window.setView(view);
        window.display();
    }

    return 0;
}
