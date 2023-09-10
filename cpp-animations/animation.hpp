#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation {
public:
	RenderWindow* window = nullptr;

	Animation() {
		this->window = new RenderWindow(VideoMode(800, 600), "Animation", Style::Default, ContextSettings(0, 0, 8));
		window->setVerticalSyncEnabled(true);
		window->setFramerateLimit(60);
	}

	void animate(std::vector<Drawable*>& drawables) {
		while (window->isOpen()) {
			Event event;
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed)
					window->close();
			}

			window->clear(Color(60, 60, 60));

			for (const auto shape : drawables)
				window->draw(*shape);

			window->display();
		}
	}

	~Animation() {
		delete this->window;
	}
};

#endif // ANIMATION_HPP