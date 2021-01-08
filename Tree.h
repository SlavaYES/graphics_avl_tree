#ifndef AVL_TREE_TREE_H
#define AVL_TREE_TREE_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Tree {
public:
    struct Vertex {
        CircleShape circle;
        sf::Vertex lineLeft[2];
        sf::Vertex lineRight[2];
        Text text;
        float x, y;

        int data;
        Vertex *left;
        Vertex *right;
        int balance;
    };
    static bool isUp;
    static bool isUpForShow;
private:
    Vertex *root;
    Font font;
    float width, height;
    float radius, border;
    int text_size, uspeed;
public:
    Tree(float, float, float radius = 50, float border = 1, int text = 12, int uspeed = 10000);
    void add(int data);
    void addRecursion(Vertex *&point, int data, float left, float right, float level);
    void fillData(Vertex *&point, int data, float left, float right, float level);

    void ll(Vertex*&);
    void lr(Vertex*&);
    void rr(Vertex*&);
    void rl(Vertex*&);

    void move(Vertex*&, float left, float right, float level);

    void draw(RenderWindow &win);
    void clear(Vertex *&point);
    void bypass(Vertex *vertex, RenderWindow &win);
    Vertex*& getRoot();
};

#endif