// utilities.h
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "cell.hpp"
#ifndef UTILITIES_H
#define UTILITIES_H

using namespace std;

int randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Cell** createGrid(int n, int num_obs) {
    std::unordered_map<int, int> MAP;
    Cell** grid = new Cell * [n];
    int obs = 0;

    for (int i = 0; i < n; i++) {
        grid[i] = new Cell[n];
        for (int j = 0; j < n; j++)
            grid[i][j] = Cell(i * Cell::size, j * Cell::size);
    }

    while (obs < num_obs) {
        int i, j;

        do {
            i = randomNumber(0, n);
            j = randomNumber(0, n);
        } while (
            (i == 0 && j == 0) ||
            i >= n - 1 ||
            j >= n - 1 ||
            (MAP.count(i) > 0 && MAP[i] == j)
            );

        grid[i][j].shape->setFillColor(sf::Color::Black);

        MAP[i] = j;
        obs++;
    }

    return grid;
}

vector<Cell*> colorPath(int i, int j, Cell** grid, int n, unordered_map<int, unordered_set<int>>& MAP, vector<vector<vector<Cell*>>>& memo) {
    if (i < 0 || j < 0 || i >= n || j >= n) return {};
    if (MAP.count(i) > 0 && MAP[i].find(j) != MAP[i].end()) return memo[i][j];
    if (grid[i][j].shape->getFillColor() == sf::Color::Black) return {};

    grid[i][j].shape->setFillColor(sf::Color::Red);
    sleep(sf::milliseconds(10));
    if (i == n - 1 && j == n - 1) {
        vector<Cell*> path = {};
        path.push_back(&grid[i][j]);
        grid[i][j].shape->setFillColor(sf::Color::Green);
        return path;
    }

    MAP[i].insert(j);

    vector<Cell*> rightResult = colorPath(i, j + 1, grid, n, MAP, memo);
    vector<Cell*> bottomResult = colorPath(i + 1, j, grid, n, MAP, memo);
    vector<Cell*> leftResult = colorPath(i, j - 1, grid, n, MAP, memo);
    vector<Cell*> topResult = colorPath(i - 1, j, grid, n, MAP, memo);

    if (!rightResult.empty()) {
        sleep(sf::milliseconds(10));
        rightResult.push_back(&grid[i][j]);
        memo[i][j] = rightResult;
        grid[i][j].shape->setFillColor(sf::Color::Green);
        return rightResult;
    }

    if (!bottomResult.empty()) {
        sleep(sf::milliseconds(10));
        bottomResult.push_back(&grid[i][j]);
        memo[i][j] = bottomResult;
        grid[i][j].shape->setFillColor(sf::Color::Green);
        return bottomResult;
    }

    if (!topResult.empty()) {
        sleep(sf::milliseconds(10));
        topResult.push_back(&grid[i][j]);
        memo[i][j] = topResult;
        grid[i][j].shape->setFillColor(sf::Color::Green);
        return topResult;
    }

    if (!leftResult.empty()) {
        sleep(sf::milliseconds(10));
        leftResult.push_back(&grid[i][j]);
        memo[i][j] = leftResult;
        grid[i][j].shape->setFillColor(sf::Color::Green);
        return leftResult;
    }
    sleep(sf::milliseconds(10));
    grid[i][j].shape->setFillColor(sf::Color::White);
    memo[i][j] = {};
    return {};
}


void findPath(int i, int j, Cell** grid, int n) {
    unordered_map<int, unordered_set<int>> MAP;
    vector<vector<vector<Cell*>>> memo(n, vector<vector<Cell*>>(n));

    if (grid[i][j].shape->getFillColor() == sf::Color::Black) {
        cout << "NOT EXISTS";
        return;
    }

    //vector<Cell*> path = colorPath(0, 0, grid, n, MAP, memo);
    vector<Cell*> path = colorPath(i, j, grid, n, MAP, memo);

    if (path.empty()) {
        cout << "NOT EXISTS";
        return;
    }


}

#endif // UTILITIES_H
