#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "Tree.h"
#define WIDTH 1800
#define HEIGHT 900
#define RADIUS 20
#define BORDER 2
#define TEXT_SIZE 20
#define USPEED 1000000

using namespace sf;

int main() {
    srand(time(NULL));
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow win(VideoMode(WIDTH, HEIGHT), "SFML", Style::Default, settings);

    Tree tree(WIDTH, HEIGHT, RADIUS, BORDER, TEXT_SIZE, USPEED);

    while (win.isOpen()) {
        Event event;
        while (win.pollEvent(event)) {
            switch (event.type) {
                case Event::MouseButtonPressed:
                    win.close();
                    break;
                case Event::Closed:
                    win.close();
                    break;
                case Event::KeyPressed:
                    tree.clear(tree.getRoot());
                    tree.add(rand() % 1000);

                    if (tree.isUpForShow) {
                        win.clear(Color::White);
                        tree.draw(win);
                        win.display();
                        usleep(USPEED);

                        win.clear(Color::White);
                        tree.move(tree.getRoot(), 0, WIDTH, 10);
                        tree.draw(win);
                        win.display();
                    }
                    break;
                default:
                    break;
            }
        }
        win.clear(Color::White);
        tree.draw(win);
        win.display();
    }

    return 0;
}
