#include "Tree.h"

bool Tree::isUp;
bool Tree::isUpForShow = false;

Tree::Tree(float width, float height, float radius, float border, int text_size, int uspeed) {
    root = nullptr;
    this->width = width;
    this->height = height;
    this->radius = radius;
    this->border = border;
    this->text_size = text_size;
    this->uspeed = uspeed;
    font.loadFromFile("../arial.ttf");
}

void Tree::addRecursion(Vertex *&point,int data, float left, float right, float level) {
    if (point == nullptr) {
        fillData(point, data, left, right, level);
    } else {
        if (data < point->data) {
            addRecursion(point->left, data, left, (left + right) / 2, level + radius * 2 * 2 * 2);
            if (isUp) {
                if (point->balance > 0) {
                    point->balance = 0;
                    isUp = false;
                } else if (point->balance == 0) {
                    point->balance = -1;
                    isUp = true;
                } else if (point->left->balance < 0) {
                    ll(point);
                    point->circle.setOutlineColor(Color::Red);
                    point->circle.setOutlineThickness(border + 5);
                    isUpForShow = true;
                    isUp = false;
                } else {
                    lr(point);
                    point->circle.setOutlineColor(Color::Red);
                    point->circle.setOutlineThickness(border + 5);
                    isUpForShow = true;
                    isUp = false;
                }
            }
        } else if (data > point->data) {
            addRecursion(point->right, data, (left + right) / 2, right, level + radius * 2 * 2 * 2);
            if (isUp) {
                if (point->balance < 0) {
                    point->balance = 0;
                    isUp = false;
                } else if (point->balance == 0) {
                    point->balance = 1;
                    isUp = true;
                } else if (point->right->balance > 0) {
                    rr(point);
                    point->circle.setOutlineColor(Color::Red);
                    point->circle.setOutlineThickness(border + 5);
                    isUpForShow = true;
                    isUp = false;
                } else {
                    rl(point);
                    point->circle.setOutlineColor(Color::Red);
                    point->circle.setOutlineThickness(border + 5);
                    isUpForShow = true;
                    isUp = false;
                }
            }
        } else {
            // data == point->data
        }
    }
}

void Tree::ll(Tree::Vertex *&point) {
    Vertex *quality = point->left;
    point->balance = 0;
    quality->balance = 0;

    point->left = quality->right;
    quality->right = point;

    point = quality;
}

void Tree::rr(Tree::Vertex *&point) {
    Vertex *quality = point->right;
    point->balance = 0;
    quality->balance = 0;

    point->right = quality->left;
    quality->left = point;

    point = quality;
}

void Tree::lr(Tree::Vertex *&point) {
    Vertex *leftVertex = point->left;
    Vertex *quality = leftVertex->right;

    if (quality->balance < 0) {
        point->balance = 1;
    } else {
        point->balance = 0;
    }
    if (quality->balance > 0) {
        leftVertex->balance = -1;
    } else {
        leftVertex->balance = 0;
    }
    quality->balance = 0;

    leftVertex->right = quality->left;
    point->left = quality->right;

    quality->left = leftVertex;
    quality->right = point;
    point = quality;
}

void Tree::rl(Tree::Vertex *&point) {
    Vertex *rightVertex = point->right;
    Vertex *quality = rightVertex->left;

    if (quality->balance > 0) {
        point->balance = -1;
    } else {
        point->balance = 0;
    }
    if (quality->balance < 0) {
        rightVertex->balance = 1;
    } else {
        rightVertex->balance = 0;
    }
    quality->balance = 0;

    rightVertex->left = quality->right;
    point->right = quality->left;

    quality->left = point;
    quality->right = rightVertex;
    point = quality;
}

void Tree::add(int data) {
    isUpForShow = false;
    addRecursion(root, data, 0, width, 10);
}

void Tree::draw(RenderWindow &win) {
    bypass(root, win);
}

void Tree::bypass(Tree::Vertex *vertex, RenderWindow &win) {
    if (vertex == nullptr) {
        return;
    }

    win.draw(vertex->circle);
    win.draw(vertex->text);
    win.draw(vertex->lineLeft, 2, Lines);
    win.draw(vertex->lineRight, 2, Lines);

    bypass(vertex->left, win);
    bypass(vertex->right, win);
}

Tree::Vertex*& Tree::getRoot() {
    return root;
}

void Tree::move(Tree::Vertex *&point, float left, float right, float level) {
    if (point == nullptr) {
        return;
    }
    point->x = (left + right) / 2;
    point->y = level;

    point->circle.setPosition(point->x , point->y);

    point->text.setPosition(point->x  + (radius / 2 + border) - 4, point->y + (radius / 2 + border - 3));

    point->lineLeft[0] = Vector2f(point->x  + radius, level + radius * 2);
    point->lineLeft[1] = Vector2f((point->x + left) / 2 + radius, point->y + radius * 2 * 2 * 2);
    point->lineLeft->color = Color::Black;

    point->lineRight[0] = Vector2f(point->x  + radius, point->y + radius * 2);
    point->lineRight[1] = Vector2f((point->x + right) / 2 + radius, point->y + radius * 2 * 2 * 2);
    point->lineRight->color = Color::Black;

    move(point->left, left, (left + right) / 2, level + radius * 2 * 2 * 2);
    move(point->right, (left + right) / 2, right, level + radius * 2 * 2 * 2);
}

void Tree::clear(Tree::Vertex *&point) {
    if (point == nullptr) {
        return;
    }
    point->circle.setOutlineColor(Color::Black);
    point->circle.setOutlineThickness(border);
    clear(point->left);
    clear(point->right);
}

void Tree::fillData(Vertex *&point, int data, float left, float right, float level) {
    point = new Vertex();
    point->data = data;
    point->balance = 0;
    isUp = true;
    point->left = nullptr;
    point->right = nullptr;

    point->x = (left + right) / 2;
    point->y = level;

    point->circle.setRadius((float)radius);
    point->circle.setPosition(point->x , point->y);
    point->circle.setOutlineColor(Color::Green);
    point->circle.setOutlineThickness(border + 5);

    point->text.setFont(font);
    point->text.setCharacterSize(text_size);
    point->text.setFillColor(Color::Black);
    point->text.setPosition(point->x  + (radius / 2 + border) - 4, point->y + (radius / 2 + border - 3));
    point->text.setString(to_string(data));

    point->lineLeft[0] = Vector2f(point->x  + radius, level + radius * 2);
    point->lineLeft[1] = Vector2f((point->x + left) / 2 + radius, point->y + radius * 2 * 2 * 2);
    point->lineLeft->color = Color::Black;

    point->lineRight[0] = Vector2f(point->x  + radius, point->y + radius * 2);
    point->lineRight[1] = Vector2f((point->x + right) / 2 + radius, point->y + radius * 2 * 2 * 2);
    point->lineRight->color = Color::Black;
}
