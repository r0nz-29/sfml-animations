// utilities.h
#include <random>
#include <unordered_map>
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
    Cell** grid = new Cell*[n];
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

vector<Cell*>* colorPath(int i, int j, Cell** grid, int n, unordered_map<int, int>& MAP, vector<vector<vector<Cell*>>>& memo) {
    if (i >= n || j >= n) return nullptr;
    if (MAP.count(i) > 0 && MAP[i] == j) return nullptr;
    if (grid[i][j].shape->getFillColor() == sf::Color::Black) return nullptr;

    if (i == n - 1 && j == n - 1) {
        vector<Cell*>* path = new vector<Cell*>;
        path->push_back(&grid[i][j]);
        return path;
    }

    if (memo[i][j].size() > 0) {
        return &memo[i][j];
    }

    MAP[i] = j;

    vector<Cell*>* rightResult = colorPath(i, j + 1, grid, n, MAP, memo);
    vector<Cell*>* bottomResult = colorPath(i + 1, j, grid, n, MAP, memo);

    if (rightResult != nullptr) {
        rightResult->push_back(&grid[i][j]);
        memo[i][j] = *rightResult;
        return rightResult;
    }

    if (bottomResult != nullptr) {
        bottomResult->push_back(&grid[i][j]);
        memo[i][j] = *bottomResult;
        return bottomResult;
    }

    return nullptr;
}


void findPath(Cell** grid, int n) {
    unordered_map<int, int> MAP;
    vector<vector<vector<Cell*>>> memo(n, vector<vector<Cell*>>(n));

    vector<Cell*>* path = colorPath(0, 0, grid, n, MAP, memo);

    if (path == nullptr) {
        cout << "NOT EXISTS";
        return;
    }

    for (int i = 0; i < path->size(); i++) {
        (*path)[i]->shape->setFillColor(sf::Color::Green);
    }
}

#endif // UTILITIES_H
