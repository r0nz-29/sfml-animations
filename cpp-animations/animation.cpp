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

	void _animate() {
		while (window->isOpen()) {
			Event event;
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed)
					window->close();
			}

			// do stuff

			window->clear();
			window->display();
		}
	}

	~Animation() {
		delete this->window;
	}
};