#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;


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

const int GLOBAL_PARAMETER = 20;


class Snake
{
private:

	vector<RectangleShape> segments;
	Vector2f last_position;
	int speed;
	int dir;
	int score;
	bool is_alive;

public:

	Snake()
	{
		int x = win_width / 2;
		x -= x % GLOBAL_PARAMETER;
		int y = win_height / 2;
		y -= y % GLOBAL_PARAMETER;

		RectangleShape head;
		head.setPosition(x, y);

		Vector2f parameters(GLOBAL_PARAMETER, GLOBAL_PARAMETER);
		head.setSize(parameters);
		head.setOrigin(GLOBAL_PARAMETER / 2, GLOBAL_PARAMETER / 2);
		head.setFillColor(Color::Red);
		segments.push_back(head);

		last_position = segments[0].getPosition();

		speed = GLOBAL_PARAMETER;

		dir = 0;

		score = 0;

		is_alive = true;
	}


	void set_dir(int a)
	{
		dir = a;
	}

	Vector2f get_position()
	{
		return segments[0].getPosition();
	}

	int get_score()
	{
		return score;
	}

	void draw(RenderWindow& win)
	{
		for (int i = 0; i < segments.size(); i++)
		{
			win.draw(segments[i]);
		}
	}

	void move()
	{
		last_position = segments[segments.size() - 1].getPosition();

		switch (dir)
		{
		case 0:
			break;
		case 1:
			for (int i = segments.size() - 1; i > 0; i--)
			{
				segments[i].setPosition(segments[i - 1].getPosition());
			}
			segments[0].move(0, -speed);
			break;
		case 2:
			for (int i = segments.size() - 1; i > 0; i--)
			{
				segments[i].setPosition(segments[i - 1].getPosition());
			}
			segments[0].move(0, speed);
			break;
		case 3:
			for (int i = segments.size() - 1; i > 0; i--)
			{
				segments[i].setPosition(segments[i - 1].getPosition());
			}
			segments[0].move(-speed, 0);
			break;
		case 4:
			for (int i = segments.size() - 1; i > 0; i--)
			{
				segments[i].setPosition(segments[i - 1].getPosition());
			}
			segments[0].move(speed, 0);
			break;
		}

		check_position();
	}

	void check_position()
	{
		// CheckBorders
		if (segments[0].getPosition().x < 0)
		{
			segments[0].setPosition(win_width, segments[0].getPosition().y);
		}
		if (segments[0].getPosition().x > win_width)
		{
			segments[0].setPosition(0, segments[0].getPosition().y);
		}
		if (segments[0].getPosition().y < 0)
		{
			segments[0].setPosition(segments[0].getPosition().x, win_width);
		}
		if (segments[0].getPosition().y > win_height)
		{
			segments[0].setPosition(segments[0].getPosition().x, 0);
		}

		// CheckCollisionWithBody
		for (int i = 1; i < segments.size(); i++)
		{
			if (segments[0].getPosition() == segments[i].getPosition())
			{
				is_alive = false;
			}
		}
	}

	void grow()
	{
		Vector2f new_segment = segments[segments.size() - 1].getPosition();
		RectangleShape tail;

		if (segments[segments.size() - 1].getPosition().x < last_position.x)
		{
			tail.setPosition(new_segment.x + speed, new_segment.y);
		}
		if (segments[segments.size() - 1].getPosition().x > last_position.x)
		{
			tail.setPosition(new_segment.x - speed, new_segment.y);
		}
		if (segments[segments.size() - 1].getPosition().y < last_position.y)
		{
			tail.setPosition(new_segment.x, new_segment.y + speed);
		}
		if (segments[segments.size() - 1].getPosition().y > last_position.y)
		{
			tail.setPosition(new_segment.x, new_segment.y - speed);
		}

		tail.setSize(segments[0].getSize());
		tail.setOrigin(segments[0].getOrigin());
		tail.setFillColor(segments[0].getFillColor());

		score++;

		segments.push_back(tail);
	}

	bool get_alive()
	{
		return is_alive;
	}

	void kill()
	{
		is_alive = false;
	}
};

class Food
{
private:

	RectangleShape shape;

public:

	Food()
	{
		int x = rand() % win_width;
		x -= x % GLOBAL_PARAMETER;
		int y = rand() % win_height;
		y -= y % GLOBAL_PARAMETER;

		shape.setPosition(x, y);

		Vector2f parameters(GLOBAL_PARAMETER, GLOBAL_PARAMETER);
		shape.setSize(parameters);
		shape.setOrigin(GLOBAL_PARAMETER / 2, GLOBAL_PARAMETER / 2);
		shape.setFillColor(Color::Green);
	}


	Vector2f get_position()
	{
		return shape.getPosition();
	}

	void respawn()
	{
		int x = rand() % win_width;
		x -= x % 20;
		int y = rand() % win_height;
		y -= y % 20;

		shape.setPosition(x, y);
	}

	void draw(RenderWindow& win)
	{
		win.draw(shape);
	}
};

class Block
{
private:

	RectangleShape shape;

public:

	Block()
	{
		int x = rand() % win_width;
		x -= x % GLOBAL_PARAMETER;
		int y = rand() % win_height;
		y -= y % GLOBAL_PARAMETER;

		shape.setPosition(x, y);

		Vector2f parameters(GLOBAL_PARAMETER, GLOBAL_PARAMETER);
		shape.setSize(parameters);
		shape.setOrigin(GLOBAL_PARAMETER / 2, GLOBAL_PARAMETER / 2);
		shape.setFillColor(Color::Blue);
	}

	Vector2f get_position()
	{
		return shape.getPosition();
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
	vector<Block> blocks(4);

	while (win.isOpen())
	{
		while (win.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				win.close();
			}
		}

		// Direction
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			snake.set_dir(1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			snake.set_dir(2);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			snake.set_dir(3);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			snake.set_dir(4);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			snake.set_dir(0);
		}

		// FoodCollision
		if (snake.get_position() == food.get_position())
		{
			do
			{
				food.respawn();
			} while (snake.get_position() == food.get_position());

			snake.grow();
		}

		// BlockCollision
		for (int i = 0; i < blocks.size(); i++)
		{
			if (snake.get_position() == blocks[i].get_position())
			{
				snake.kill();
			}
		}
		

		// CheckDeath
		if (!snake.get_alive())
		{
			win.close();
		}

		// Screen
		win.clear(Color::Black);

		snake.move();

		snake.draw(win);
		food.draw(win);
		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].draw(win);
		}

		win.display();
	}
	cout << "Your score is " << snake.get_score() << endl;
}