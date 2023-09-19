#ifndef CELL_HPP
#define CELL_HPP

#define SIZE 3

#include <SFML/Graphics.hpp>

using namespace sf;

class Cell {
public:
	static int const size = SIZE;
	RectangleShape* shape = nullptr;

	Cell() {}

	Cell(int x, int y) {
		shape = new RectangleShape(Vector2f(size, size));
		shape->setFillColor(Color::White);
		shape->setPosition(x, y);
	}

	Drawable* getDrawable() {
		return shape;
	}
};

#endif // CELL_HPP