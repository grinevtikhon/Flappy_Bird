#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const bool otladka = false;
//////////////////////////
const int Height = 720;
const int Length = 1080;
const int high_grass = 50;
const int min_dist = 200;
const double width_pipe = 100;
const double horizontal_distance = 300;
const double vertical_distance = 200;
const double tick = 0.001f;
const double g = 2400;


// 1280 * 720

struct flappy_bird
{
	double r;
	double v_x, v_y;
	double x, y;
	bool dead;
	sf::Color c;
	flappy_bird() {
		r = 27;
		v_x = 0;
		v_y = 0;
		x = Length / 2;
		y = Height / 2;
		dead = false;
		c.Yellow;
	}
	void reset() {
		r = 27;
		v_x = 0;
		v_y = 0;
		x = Length / 2;
		y = Height / 2;
		dead = false;
		c = sf::Color::Yellow;
	}
	void next_tick() {
		y = y + v_y * tick + ((g * tick * tick) / 2.0f);
		v_y = v_y + g * tick;
		x = x + v_x * tick;
		if (y > Height - high_grass - r) {
			v_y = 0;
			y = Height - high_grass - r;
		}
		if (y < 0) {
			v_y = abs(v_y);
		}
		if (x > Length) {
			v_x = -abs(v_x);
		}
		if (x < 0) {
			v_x = abs(v_x);
		}
		return;
	}
	void jump() {
		if (dead == true && otladka == false) {
			return;
		}
		v_y = -700;
		return;
	}
	void die() {
		dead = true;
		c = sf::Color::Red;
		return;
	}
};

struct pipe {
	double x1, y1, x2, y2;
	double v_x;
	pipe(double _x1, double _y1, double _y2) {
		x1 = _x1;
		x2 = _x1 + width_pipe;
		y1 = min(_y1, _y2);
		y2 = max(_y2, _y2);
		v_x = -300;
	}
	void next_tick() {
		x1 = x1 + v_x * tick;
		x2 = x1 + width_pipe;
		return;
	}
};

flappy_bird bird;
queue <pipe> pipes;

bool touch(flappy_bird &b, pipe &p) {

	if (b.x < p.x1) {
		if (b.y < p.y1) {
			if ((b.x - p.x1)*(b.x - p.x1) + (b.y - p.y1)*(b.y - p.y1) < b.r * b.r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (p.y1 <= b.y && b.y <= p.y2) {
			if (p.x1 - b.x < b.r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (p.y2 < b.y) {
			if ((b.x - p.x1)*(b.x - p.x1) + (b.y - p.y2)*(b.y - p.y2) < b.r * b.r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (p.x1 <= b.x && b.x <= p.x2) {
		if (b.y < p.y1) {
			if (p.y1 - b.y < b.r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (p.y1 <= b.y && b.y <= p.y2) {
			return true;
		}
		if (p.y2 < b.y) {
			if (b.y - p.y2 < b.r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (p.x2 < b.x) {
		if (b.y < p.y1) {
			if ((b.x - p.x2)*(b.x - p.x2) + (b.y - p.y1)*(b.y - p.y1) < b.r * b.r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (p.y1 <= b.y && b.y <= p.y2) {
			if (b.x - p.x2 < b.r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (p.y2 < b.y) {
			if ((b.x - p.x2)*(b.x - p.x2) + (b.y - p.y2)*(b.y - p.y2) < b.r * b.r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool bird_vresols() {
	bool ans = false;
	for (int i = 0; i < pipes.size(); ++i) {
		if (ans == false) {
			if (touch(bird, pipes.front())) {
				ans = true;
			}
		}
		pipes.push(pipes.front());
		pipes.pop();
	}
	if (bird.y + bird.r >= Height - high_grass) {
		ans = true;
	}
	return ans;
}

void generate_pipe() {
	int buf_y = rand() % (Height - 2 * min_dist) + min_dist;
	if (pipes.empty()) {
		pipes.push(pipe(Length + 300, 0, buf_y - (vertical_distance / 2)));
		pipes.push(pipe(Length + 300, buf_y + (vertical_distance / 2), Height));
	}
	buf_y = rand() % (Height - 2 * min_dist) + min_dist;
	if (pipes.back().x2 < Length) {
		double buf = pipes.back().x2;
		pipes.push(pipe(buf + horizontal_distance, 0, buf_y - (vertical_distance / 2)));
		pipes.push(pipe(buf + horizontal_distance, buf_y + (vertical_distance / 2), Height));
	}
	return;
}

void delete_pipe() {
	if (pipes.empty()) {
		pipes.push(pipe(Length + 1000, 0, 300));
		pipes.push(pipe(Length + 1000, 300 + vertical_distance, Height));
	}
	if (pipes.front().x2 < 0) {
		pipes.pop();
		delete_pipe();
	}
	return;
}

void stop_pipe() {
	for (int i = 0; i < pipes.size(); ++i) {
		pipes.front().v_x = 0.0f;
		pipes.push(pipes.front());
		pipes.pop();
	}
	return;
}

void next_tick() {
	bird.next_tick();
	generate_pipe();
	delete_pipe();
	for (int i = 0; i < pipes.size(); ++i) {
		pipes.front().next_tick();
		pipes.push(pipes.front());
		pipes.pop();
	}
	if (bird_vresols()) {
		bird.jump();
		bird.die();
	}
	return;
}

void restart() {
	bird.reset();
	while (!pipes.empty()) {
		pipes.pop();
	}
	return;
}

int main()
{
	srand(time(NULL));



	sf::RenderWindow window(sf::VideoMode(Length, Height), "SFML works!");
	sf::CircleShape circle(bird.r);
	//circle.setTexture(&bird_texture);
	sf::RectangleShape rectangle;
	circle.setFillColor(sf::Color::Yellow);
	rectangle.setFillColor(sf::Color::Green);
	circle.setFillColor(sf::Color::Yellow);
	//shape.setFillColor(sf::Color::Green);

	//circle.setTexture(bird_texture);

	bool pr_space = false;
	bool now_space = false;
	bool pr_r = false;
	bool now_r = false;

	while (window.isOpen())
	{
		now_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (now_space == true && pr_space == false) {
			bird.jump();
		}
		pr_space = now_space;

		now_r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		if (now_r == true && pr_r == false) {
			restart();
			circle.setFillColor(sf::Color::Yellow);
		}
		pr_r = now_r;

		next_tick();

		if (bird.dead == true) {
			if (otladka == false) {
				circle.setFillColor(sf::Color::Red);
				stop_pipe();
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);


		for (int i = 0; i < pipes.size(); ++i) {
			rectangle.setPosition(pipes.front().x1, pipes.front().y1);
			rectangle.setSize(sf::Vector2f(pipes.front().x2 - pipes.front().x1, pipes.front().y2 - pipes.front().y1));
			window.draw(rectangle);
			//cout << pipes.front().x1 << " | " << pipes.front().x2 << " | " << pipes.front().y1 << " | " << pipes.front().y2 << endl;
			pipes.push(pipes.front());
			pipes.pop();
		}
		//cout << pipes.size() << " | " << pipes.back().x2 << " | " << pipes.front().x2 << endl;

		sf::RectangleShape ground;
		ground.setPosition(0, Height - high_grass);
		ground.setSize(sf::Vector2f(Length, high_grass));
		ground.setFillColor(sf::Color(65, 25, 0));
		window.draw(ground);

		//circle.setFillColor(sf::Color::Yellow);
		circle.setPosition(bird.x - bird.r, bird.y - bird.r);
		window.draw(circle);

		window.display();
	}

	return 0;
}