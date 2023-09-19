//
// Created by raunits on 17/09/23.
//

#ifndef SFML_DEMO_GRAVITY_HPP
#define SFML_DEMO_GRAVITY_HPP

#include "../animation.hpp"
#include "../utils.hpp"

#define G 0.1

using namespace sf;

class Planet {
public:
    float mass;
    float vx = 0, vy = 0;
    CircleShape *shape = nullptr;
    const Color CENTER_SPHERE_COLOR = Color::Magenta;

    Planet(float mass, float radius) {
        this->mass = mass;
        shape = new CircleShape(radius);
        shape->setFillColor(CENTER_SPHERE_COLOR);
    }

    void setPosition(float x, float y) const {
        this->shape->setPosition(x, y);
    }
};

class GravityAnimation : public Animation {
public:
    const float CENTER_SPHERE_RADIUS = 50;
    const float CENTER_SPHERE_MASS = 300;

    const float ASTEROID_RADIUS = 5;
    const float ASTEROID_MASS = 100;
    const Color ASTEROID_COLOR = Color(20, 20, 20);

    bool preventSpamming = false;

    Planet *centerSphere = nullptr;
    std::vector<Planet> asteroids{};

    GravityAnimation() {
        initCenterSphere();
    }

    void draw(RenderWindow *renderWindow, Event e) override {
        listenEvents(e);
        window->clear(Color(60, 60, 60));

        window->draw(*(centerSphere->shape));

        for (Planet asteroid: asteroids) {
            updatePosition(asteroid);
            window->draw(*(asteroid.shape));
        }

        window->display();
    }

    void start() override {
        this->animate();
    }

    void listenEvents(Event &event) {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            int x = event.mouseButton.x - ASTEROID_RADIUS;
            int y = event.mouseButton.y - ASTEROID_RADIUS;
            createAsteroid(x, y);
            preventSpamming = true;
        }
        else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            preventSpamming = false;
        }
    }

    void updatePosition(Planet &ast) {
        float dx = centerSphere->shape->getPosition().x + CENTER_SPHERE_RADIUS - ast.shape->getPosition().x;
        float dy = centerSphere->shape->getPosition().y + CENTER_SPHERE_RADIUS - ast.shape->getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float M1 = centerSphere->mass;
        float M2 = ast.mass;

        // Calculate gravitational force
        float force = (float) 100.4 * ((M1 * M2) / (distance * distance));

        // Calculate acceleration due to gravity
        float ax = (force / M2) * (dx / distance);
        float ay = (force / M2) * (dy / distance);

//      Update velocity using acceleration
        ast.vx += ax;
        ast.vy += ay;

//      Update position using velocity
        ast.setPosition(
                ast.shape->getPosition().x + ast.vx,
                ast.shape->getPosition().y + ast.vy
        );
    }

    void createAsteroid(int x1, int y1) {
        if (preventSpamming) return;
        auto *ast = new Planet(ASTEROID_MASS, ASTEROID_RADIUS);
        int x2 = centerSphere->shape->getPosition().x;
        int y2 = centerSphere->shape->getPosition().y;

        int delX = x2 - x1;
        int delY = y2 - y1;

        float theta = atan(((float) delX / (float)delY));
        
        ast->vx = 10;
        ast->vy = 10;
        ast->shape->setFillColor(ASTEROID_COLOR);
        ast->setPosition(x1, y1);

        this->asteroids.push_back(*ast);
    }

    void initCenterSphere() {
        centerSphere = new Planet(CENTER_SPHERE_MASS, CENTER_SPHERE_RADIUS);
        float x = (float) (window->getSize().x / 2.0 - CENTER_SPHERE_RADIUS);
        float y = (float) (window->getSize().y / 2.0 - CENTER_SPHERE_RADIUS);
        centerSphere->setPosition(x, y);
    }
};

#endif //SFML_DEMO_GRAVITY_HPP
