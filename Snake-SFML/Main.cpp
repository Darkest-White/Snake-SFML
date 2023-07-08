#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;


//class Snake
//{
//private:
//
//	RectangleShape shape;
//	Vector2i position;
//	Vector2f size;
//
//public:
//
//	Snake()
//	{
//		position.x = 100;
//		position.y = 100;
//
//		shape.setPosition(position.x, position.y);
//
//		size.x = 20;
//		size.y = 20;
//
//		shape.setSize(size);
//		shape.setOrigin(size.x / 2, size.y / 2);
//
//		shape.setFillColor(Color::Red);
//	}
//
//	void draw(RenderWindow win)
//	{
//		win.draw(shape);
//	}
//};

//class Core
//{
//private:
//
//	RenderWindow* win;
//	Event ev;
//
//	int win_width = 640;
//	int win_height = 480;
//
//	string win_name = "Snake";
//
//	const int frame_limit = 60;
//
//	void update()
//	{
//		while (win->pollEvent(ev))
//		{
//			if (ev.type == Event::Closed)
//			{
//				win->close();
//			}
//		}
//	}
//
//	void draw()
//	{
//		win->clear(Color::Black);
//
//		win->display();
//	}
//
//public:
//
//	Core()
//	{
//		win = new RenderWindow(VideoMode(win_width, win_height), win_name, Style::Default);
//		win->setFramerateLimit(frame_limit);
//	}
//
//	~Core()
//	{
//		delete win;
//	}
//
//	void process()
//	{
//		while (win->isOpen())
//		{
//			update();
//			draw();
//		}
//	}
//};


int win_width = 640;
int win_height = 480;
string win_name = "Snake";
int frame_limit = 10;
Event ev;


struct Point
{
	int x, y;
};


class Snake
{
private:

	RectangleShape shape;
	Point position;
	Vector2f size;
	int speed;
	int score;

public:

	int dir;

	Snake()
	{
		position.x = win_width / 2;
		position.x -= position.x % 20;
		position.y = win_height / 2;
		position.y -= position.y % 20;

		shape.setPosition(position.x, position.y);

		size.x = 20;
		size.y = 20;

		shape.setOrigin(size.x / 2, size.y / 2);
		shape.setSize(size);
		shape.setFillColor(Color::Red);

		speed = size.x;
		dir = 0;

		score = 0;
	}


	Vector2f get_position()
	{
		return shape.getPosition();
	}

	void score_up()
	{
		score++;
	}

	int get_score()
	{
		return score;
	}

	void draw(RenderWindow& win)
	{
		win.draw(shape);
	}

	void move()
	{
		switch (dir)
		{
		case 0:
			break;
		case 1:
			position.y -= speed;
			shape.setPosition(position.x, position.y);
			break;
		case 2:
			position.y += speed;
			shape.setPosition(position.x, position.y);
			break;
		case 3:
			position.x -= speed;
			shape.setPosition(position.x, position.y);
			break;
		case 4:
			position.x += speed;
			shape.setPosition(position.x, position.y);
			break;
		}

		if (position.x < 0)
			position.x = win_width;
		if (position.x > win_width)
			position.x = 0;
		if (position.y < 0)
			position.y = win_height;
		if (position.y > win_height)
			position.y = 0;
	}
};

class Food
{
private:

	RectangleShape shape;
	Point position;
	Vector2f size;

public:

	Food()
	{
		position.x = rand() % win_width;
		position.x -= position.x % 20;
		position.y = rand() % win_height;
		position.y -= position.y % 20;

		shape.setPosition(position.x, position.y);

		size.x = 20;
		size.y = 20;

		shape.setOrigin(size.x / 2, size.y / 2);
		shape.setSize(size);
		shape.setFillColor(Color::Green);
	}

	Vector2f get_position()
	{
		return shape.getPosition();
	}

	void respawn()
	{
		position.x = rand() % win_width;
		position.x -= position.x % 20;
		position.y = rand() % win_height;
		position.y -= position.y % 20;

		shape.setPosition(position.x, position.y);
	}

	void draw(RenderWindow& win)
	{
		win.draw(shape);
	}
};


int main()
{
	srand(time(0));

	RenderWindow win(VideoMode(win_width, win_height), win_name);
	win.setFramerateLimit(frame_limit);

	Snake snake;
	Food food;

	while (win.isOpen())
	{
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			snake.dir = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			snake.dir = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			snake.dir = 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			snake.dir = 4;
		}

		if (snake.get_position() == food.get_position())
		{
			food.respawn();
			snake.score_up();
		}


		win.clear(Color::Black);

		snake.move();

		snake.draw(win);
		food.draw(win);

		win.display();
	}
	cout << "Your score is " << snake.get_score() << endl;
}