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

    virtual void draw(RenderWindow* window, Event e) = 0;
    virtual void start() = 0;

	void animate() {
		while (window->isOpen()) {
			Event event;
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed)
					window->close();
			}

            draw(window, event);
		}
	}

	~Animation() {
        destroy();
	}

    void destroy() const {
        delete this->window;
    }
};

#endif // ANIMATION_HPP