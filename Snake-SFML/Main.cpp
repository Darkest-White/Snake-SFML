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

public:

	int dir;

	Snake()
	{
		position.x = win_width / 2;
		position.x -= position.x % 20;
		position.y = win_height / 2;
		position.y -= position.y % 20;

		size.x = 20;
		size.y = 20;

		shape.setPosition(position.x, position.y);
		shape.setSize(size);
		shape.setFillColor(Color::Red);

		speed = size.x;
		dir = 0;
	}


	void draw(RenderWindow& win)
	{
		win.draw(shape);
	}

	void update()
	{
		switch (dir)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			position.y -= speed;
			shape.setPosition(position.x, position.y);
			break;
		}
		case 2:
		{
			position.y += speed;
			shape.setPosition(position.x, position.y);
			break;
		}
		case 3:
		{
			position.x -= speed;
			shape.setPosition(position.x, position.y);
			break;
		}
		case 4:
		{
			position.x += speed;
			shape.setPosition(position.x, position.y);
			break;
		}
		}
	}
};


int main()
{
	RenderWindow win(VideoMode(win_width, win_height), win_name);
	win.setFramerateLimit(frame_limit);

	Snake snake;

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

		snake.update();

		win.clear(Color::Black);

		snake.draw(win);

		win.display();
	}
}