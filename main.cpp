#include <SFML/Graphics.hpp>
#include <thread>
#include "animation.hpp"
#include "utils.hpp"
#include "cell.hpp"

#define N 30
#define NUM_OBSTACLES 200

using namespace std;

int main()
{
	Animation animation;
	std::vector<sf::Drawable*> shapes;

	Cell** grid = createGrid(N, NUM_OBSTACLES);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) shapes.push_back(grid[i][j].getDrawable());

	std::thread t1(findPath, 0, 0, std::ref(grid), N);

	animation.animate(shapes);

	t1.join();

	return 0;
}