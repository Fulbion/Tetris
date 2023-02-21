#include <SFML/Graphics.hpp>
#include <array>
#include <random>

#include "Common.hpp"

using Grid = std::array<std::array<BYTE, COLUMNS>, ROWS>;

std::array<sf::Color, 8> cellColors =
{
		Gray,
		Cyan,
		Blue,
		Orange,
		Yellow,
		Lime,
		Violet,
		Red
};

enum class Orientation
{
	Up,
	Right,
	Down,
	Left
};

struct Tetromino
{
	std::array<std::array<bool, 4>, 4> shape;
	sf::Color color; BYTE colorNum;
	sf::Vector2i position;
	Orientation orientation;
};

#pragma region Tetrominos

Tetromino tetrominoI =
{
	{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}},

	Cyan, 1,
	{ 3, 0 },
	Orientation::Up
};

Tetromino tetrominoJ =
{
	{{
		{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},

	Blue, 2,
	{ 3, 0 },
	Orientation::Up
};

Tetromino tetrominoL =
{
	{{
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},

	Orange, 3,
	{ 3, 0 },
	Orientation::Up
};

Tetromino tetrominoO =
{
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},

	Yellow, 4,
	{ 4, 0 },
	Orientation::Up
};

Tetromino tetrominoS =
{
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}},

	Lime, 5,
	{ 3, 0 },
	Orientation::Up
};

Tetromino tetrominoT =
{
	{{
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},

	Violet, 6,
	{ 3, 0 },
	Orientation::Up
};

Tetromino tetrominoZ =
{
	{{
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}},

	Red, 7,
	{ 3, 0 },
	Orientation::Up
};

#pragma endregion

void moveTetromino(Tetromino& tetromino, sf::Vector2i movement, Grid& grid)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino.shape[i][j])
			{
				int x = tetromino.position.x + j;
				int y = tetromino.position.y + i;
				grid[y][x] = 0;
			}
		}
	}

	tetromino.position += movement;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino.shape[i][j])
			{
				int x = tetromino.position.x + j;
				int y = tetromino.position.y + i;
				grid[y][x] = tetromino.colorNum;
			}
		}
	}
}

void moveTetrominoDown(Tetromino& tetromino)
{
	tetromino.position.y++;
}

bool collisionDetected(const Tetromino& tetromino, const Grid& grid)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino.shape[i][j])
			{
				int x = tetromino.position.x + j;
				int y = tetromino.position.y + i + 1;

				if ((y < 0 || y >= ROWS) || grid[y][x] != 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void rotateTetrominoClockwise(Tetromino& tetromino)
{
	int n = tetromino.shape.size();

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			std::swap(tetromino.shape[i][j], tetromino.shape[j][i]);
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n / 2; j++)
		{
			std::swap(tetromino.shape[i][j], tetromino.shape[i][n - j - 1]);
		}
	}

	switch (tetromino.orientation)
	{
	case Orientation::Up:
		tetromino.orientation = Orientation::Right;
		break;
	case Orientation::Right:
		tetromino.orientation = Orientation::Down;
		break;
	case Orientation::Down:
		tetromino.orientation = Orientation::Left;
		break;
	case Orientation::Left:
		tetromino.orientation = Orientation::Up;
		break;
	}
}

void drawTetromino(sf::RenderWindow& window, const Tetromino& tetromino)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino.shape[i][j])
			{
				sf::RectangleShape block(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
				block.setFillColor(tetromino.color);
				block.setPosition((tetromino.position.x + j) * CELL_SIZE, (tetromino.position.y + i) * CELL_SIZE);
				window.draw(block);
			}
		}
	}
}

void generateTetromino(Tetromino& tetromino)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> distr(0, 6);

	int pieceType = distr(gen);

	switch (pieceType)
	{
	case 0:
		tetromino = tetrominoI;
		break;

	case 1:
		tetromino = tetrominoJ;
		break;

	case 2:
		tetromino = tetrominoL;
		break;

	case 3:
		tetromino = tetrominoO;
		break;

	case 4:
		tetromino = tetrominoS;
		break;

	case 5:
		tetromino = tetrominoT;
		break;

	case 6:
		tetromino = tetrominoZ;
		break;
	}
}

void resetTetrominoPosition(Tetromino& tetromino)
{
	tetromino.position = sf::Vector2i(COLUMNS / 2 - 2, 0);
}

void lockTetromino(Tetromino& tetromino, Grid& grid)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetromino.shape[i][j])
			{
				int x = tetromino.position.x + j;
				int y = tetromino.position.y + i;
				grid[y][x] = tetromino.colorNum;
			}
		}
	}

	int linesCleared = 0;
	for (int i = ROWS - 1; i >= 0; i--)
	{
		bool isComplete = true;
		for (int j = 0; j < COLUMNS; j++)
		{
			if (grid[i][j] == 0)
			{
				isComplete = false;
				break;
			}
		}

		if (isComplete)
		{
			linesCleared++;

			for (int k = i; k > 0; k--)
			{
				for (int j = 0; j < COLUMNS; j++)
				{
					grid[k][j] = grid[k - 1][j];
				}
			}

			for (int j = 0; j < COLUMNS; j++)
			{
				grid[0][j] = 0;
			}

			i++;
		}
	}
	
	generateTetromino(tetromino);
	resetTetrominoPosition(tetromino);
}

Tetromino currentTetromino = tetrominoO;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));
	window.setFramerateLimit(60);

	sf::Clock clock;
	int16_t tick = 1000;
	Grid grid = { 0 };

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();

			if (e.type == sf::Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case sf::Keyboard::Down:
					tick = 33;
					break;

				case sf::Keyboard::Left:
					moveTetromino(currentTetromino, sf::Vector2i(-CELL_SIZE, 0), grid);
					break;

				case sf::Keyboard::Right:
					moveTetromino(currentTetromino, sf::Vector2i(CELL_SIZE, 0), grid);
					break;
				}
			}

			if (e.type == sf::Event::KeyReleased)
			{
				switch (e.key.code)
				{
				case sf::Keyboard::Down:
					tick = 1000;
					break;
				}
			}
		}

		
		window.clear();

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLUMNS; j++)
			{
				sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

				cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);

				if (grid[i][j])
				{
					cell.setFillColor(cellColors[grid[i][j]]);
				}

				else
				{
					cell.setFillColor(cellColors[0]);
				}

				window.draw(cell);
			}
		}

		if (clock.getElapsedTime().asMilliseconds() >= tick)
		{
			if (!collisionDetected(tetrominoI, grid))
				moveTetrominoDown(tetrominoI);
			else
			{
				lockTetromino(tetrominoI, grid);
			}
			clock.restart();
		}

		drawTetromino(window, tetrominoI);

		window.display();
	}

	return EXIT_SUCCESS;
}
