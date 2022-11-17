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

#include "MyCostants.h"

#include "MyGraphic.h"
#include "Network.h"
#include "Generation.h"

#include "Flappy_bird.h"
#include "Pipe.h"
#include "Barriers.h"
#include "Scoreboard.h"


using namespace std;

const bool otladka = false;
//////////////////////////


// 1280 * 720
vector<int> sloi{ 6,6,  1 };

int group_size = 300;
int nnn = 25;

Generation gen(sloi, group_size, nnn, 1); // vector<int> _v, int _group_size, int _n, double _dispersion

vector<Flappy_bird> bird(group_size * nnn);

//Flappy_bird tester;

Barriers enemy;



void next_tick() {

	enemy.next_tick();

	//tester.next_tick();
	//tester.check_bird_with_barriers(enemy);
	//tester.update_information(enemy);

	for (int i = 0; i < bird.size(); ++i)
	{
		if (bird[i].alive)
		{
			bird[i].next_tick();
			bird[i].check_bird_with_barriers(enemy);
			bird[i].update_information(enemy);
		}
	}
	return;
}

void restart() {

	for (int i = 0; i < bird.size(); ++i)
	{
		gen.gen[i].set_mistake(-bird[i].score);
		//cout << gen.gen[i].mistake << " ";
	}

	//cout << endl;

	gen.calculate_generation();
	gen.generate_next_generation();

	for (int i = 0; i < bird.size(); ++i)
		bird[i].reset();
	enemy.reset();

	bird[0].color = sf::Color::White;

	//tester.reset();

	enemy.start_pipes();

	cout << -gen.best_mistake << endl << endl;


	return;
}

int main()
{



	//sf::RenderWindow window(sf::VideoMode(Length, Height), "SFML works!");

	//sf::Text text;

	//sf::Font font;

	//const string str = "Flappy_bird/resources/Flappy_birdPixeboy.ttf";

	//if (!font.loadFromFile(str))
	//{
	//	cout << "PANICAAAA!!!! AAAAAAAAAAAAAA" << endl;
	//}
	//text.setFont(font);
	// set the string to display
	//text.setString("Hello world");

	// set the character size
	//text.setCharacterSize(24); // in pixels, not points!

	// set the color
	//text.setFillColor(sf::Color::Red);

	// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	//while (window.isOpen())
	//{

	//	window.clear();
	//	// inside the main loop, between window.clear() and window.display()
	//	window.draw(text);

	//	window.display();
	//}






	//return 0;
	//tick = 0.05;

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(Length, Height), "SFML works!");


	enemy.start_pipes();

	bool pr_space = false;
	bool now_space = false;
	bool pr_r = false;
	bool now_r = false;

	int number_geration = 1;

	while (window.isOpen())
	{
		//now_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		//if (now_space == true && pr_space == false) {
		//	bird.jump();
		//}
		//pr_space = now_space;

		//now_r = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		//if (now_r == true && pr_r == false) {
		//	restart();
		//}
		//pr_r = now_r;

		next_tick();



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// ������ ����
		window.clear(sf::Color::Black);


		int anyboody_alive = 0;

		for (int i = 0; i < bird.size(); ++i)
		{
			if (bird[i].alive == false)
				continue;

			++anyboody_alive;

			double prigat = gen.gen[i].fuction(bird[i].information);

			if (prigat > 0)
				bird[i].jump();

		}

		enemy.draw_all(window);

		//for (int i = 2; i < bird[0].information.size(); ++i)
		//	cout << bird[0].information[i] << " ";
		//cout << endl;
		//cout << anyboody_alive << endl;

		int codttt = 0;

		for (int i = bird.size() - 1; i >= 0; --i)
		{
			if (bird[i].alive)
			{
				bird[i].draw(window);
				++codttt;
				if (codttt > 300)
					break;
			}
		}
		//bird[0].draw(window);

		//if (anyboody_alive < 10)
		//{
		//	tick = 0.005;
		//}

		if (anyboody_alive == 0 || (anyboody_alive < nnn && number_geration % 20 != 0 && number_geration < 15))
		{
			cout << "Generation " << number_geration << " : " << '\t';
			++number_geration;
			restart();

		}



		window.display();
	}

	return 0;
}