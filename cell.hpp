#ifndef CELL_HPP
#define CELL_HPP

#define SIZE 10

#include <SFML/Graphics.hpp>

using namespace sf;

class Cell {
public:
	int x=0, y=0;
	static int const size = SIZE;
	RectangleShape* shape = nullptr;

	Cell() {}

	Cell(int x, int y) {
		this->x = x;
		this->y = y;
		shape = new RectangleShape(Vector2f(size, size));
		shape->setFillColor(Color::White);
		shape->setPosition(x, y);
	}

	Drawable* getDrawable() {
		return shape;
	}
};

#endif // CELL_HPP