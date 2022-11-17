// ��� ��������, ����� ��� �������� � ���� ����


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include <queue>

#include "MyGraphic.h"
#include "Network.h"
#include "Generation.h"

#include "Flappy_bird.h"
#include "Pipe.h"
#include "Barriers.h"


using namespace std;

//��� ����
const bool otladka = false;
//////////////////////////
const int Height = 720;
const int Length = 1080;
const int high_grass = 50;
const int min_dist = 200;
const double width_pipe = 100;
const double horizontal_distance = 300;
const double vertical_distance = 200;
const double tick = 0.004f;
const double g = 2400;


// 1280 * 720

Flappy_bird bird;

Barriers enemy;

void next_tick() {
	bird.next_tick();
	enemy.next_tick();

	bird.check_bird_with_barriers(enemy);

	return;
}

void restart() {
	bird.reset();
	enemy.reset();
	enemy.start_pipes();

	return;
}

int main()
{
	srand(time(NULL));

	enemy.start_pipes();


	sf::RenderWindow window(sf::VideoMode(Length, Height), "SFML works!");
	sf::CircleShape circle(bird.r);

	sf::RectangleShape rectangle;
	circle.setFillColor(sf::Color::Yellow);
	rectangle.setFillColor(sf::Color::Green);

	//���������� ����������(�������)
	bool pr_space = false;
	bool now_space = false;
	bool pr_r = false;
	bool now_r = false;

	while (window.isOpen())
	{
		// ���������� ������� + ������
		now_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (now_space == true && pr_space == false) {
			bird.jump();
		}
		pr_space = now_space;

		now_r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		if (now_r == true && pr_r == false) {
			restart();
		}
		pr_r = now_r;

		next_tick();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// ������ ����
		window.clear(sf::Color::Black);


		enemy.draw_all(window);

		bird.draw(window);

		//for (int i = 0; i < enemy.pipes.size(); ++i)
		//{
		//	if (abs(enemy.pipes[i].first.x1 - enemy.pipes[i].second.x1) < 1) {
		//		cout << "ALAARM !!!!!";
		//	}
		//	if (abs(enemy.pipes[i].first.x2 - enemy.pipes[i].second.x2) < 1) {
		//		cout << "ALAARM &&&&&&&";
		//	}
		//	cout << enemy.pipes[i].first.x1 << " ";
		//}

		//cout << "SCORE:\t" << bird.score << endl;

		window.display();
	}

	return 0;
}