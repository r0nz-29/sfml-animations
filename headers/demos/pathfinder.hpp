#ifndef SFML_DEMO_PATHFINDER_HPP
#define SFML_DEMO_PATHFINDER_HPP

#include <SFML/Graphics.hpp>
#include <thread>

#include "../animation.hpp"
#include "../cell.hpp"
#include "../utils.hpp"

#define NUM_OBSTACLES 2200

using namespace sf;

class PathfinderAnimation : public Animation {
public:
    std::vector<Drawable *> drawables;
    Cell** grid;

    PathfinderAnimation() {
        grid = createGrid(N, NUM_OBSTACLES);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) drawables.push_back(grid[i][j].getDrawable());
    }

    void draw(RenderWindow *renderWindow, Event e) override {
        window->clear(Color(60, 60, 60));

        for (const auto shape: drawables)
            window->draw(*shape);

        window->display();
    }

    void start() override {
        std::thread t1(findPath, 0, 0, std::ref(grid), N);
        this->animate();
        t1.join();
    }
};

#endif // SFML_DEMO_PATHFINDER_HPP