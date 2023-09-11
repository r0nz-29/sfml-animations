#include <SFML/Graphics.hpp>
#include "animation.hpp"
#include "utils.hpp"
#include "cell.hpp"

#define N 40
#define NUM_OBSTACLES 400

using namespace std;

int main()
{
	Animation animation;
	std::vector<sf::Drawable*> shapes;

    /*int** grid = createGrid();
    printGrid(grid);*/

	Cell** grid = createGrid(N, NUM_OBSTACLES);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) shapes.push_back(grid[i][j].getDrawable());

	findPath(1, 1, grid, N);

	animation.animate(shapes);

    return 0;
}