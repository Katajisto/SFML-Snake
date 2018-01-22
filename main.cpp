#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;
int x_mov = 10; int y_mov = 0;

int main()
{
	Font gamefont;
	Text score;
	Text boostt;
	Text st;
	st.setFont(gamefont);
	st.setFillColor(Color::Green);
	st.setString("SCORE");
	st.setCharacterSize(30);
	boostt.setFont(gamefont);
	boostt.setFillColor(Color::Green);
	boostt.setString("BOOST!");
	boostt.setCharacterSize(30);
	score.setCharacterSize(30);
	boostt.setPosition(350,4);
	score.setFont(gamefont);
	score.setPosition(100, 0);
	score.setFillColor(Color::Green);
	gamefont.loadFromFile("font.ttf");
	srand(time(NULL));
	RenderWindow window(VideoMode(500,500), "SUPA SNEK");
	RectangleShape r(Vector2f(10,10));
	deque<RectangleShape> snake;
	r.setPosition(250,250);
	int snakesz = 4;
	float boost = 1;
	RectangleShape food(Vector2f(12,12));
	food.setFillColor(Color::Red);
	food.setPosition(rand() % 489 + 1, rand() % 489 + 1);
	int framesfromboost = 0;
	while(window.isOpen())
	{
		if(boost != 1)
		{
			framesfromboost++;
			if(framesfromboost >= 100)
			{
				framesfromboost = 0;
				boost = 1;
			}
		}
		score.setString(to_string(snakesz));
		sleep(seconds(0.05));
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::W) && y_mov == 0) {x_mov = 0; y_mov = boost *  -10; goto rdy;}
		if(Keyboard::isKeyPressed(Keyboard::S) && y_mov == 0) {x_mov = 0; y_mov = boost * 10; goto rdy;}
		if(Keyboard::isKeyPressed(Keyboard::A) && x_mov == 0) {x_mov = boost * -10; y_mov = 0; goto rdy;}
		if(Keyboard::isKeyPressed(Keyboard::D) && x_mov == 0) {x_mov = boost * 10; y_mov = 0;}
		rdy:
		window.clear(Color::Black);
		snake.push_back(r);
		r.move(x_mov, y_mov);
//		cout << snake.size() << "\n";
		FloatRect headcollider = r.getGlobalBounds();
		while(snake.size() > snakesz) 
		{
			snake.pop_front();
		}
		for(int i = 0; i < snake.size(); i++)
		{
			window.draw(snake[i]);
		}
		Vector2f rpos = r.getPosition();
		if(rpos.x > 499) r.setPosition(0, rpos.y);
		if(rpos.y > 499) r.setPosition(rpos.x, 0);
		if(rpos.y < 0) r.setPosition(rpos.x, 489);
		if(rpos.x < 0) r.setPosition(489, rpos.y);
		window.draw(score);
		if(boost != 1)	window.draw(boostt);
		window.draw(food);
		window.draw(r);
		window.draw(st);
		FloatRect foodCollider = food.getGlobalBounds();
		if(headcollider.intersects(foodCollider))
		{
			boost = 1.5;
			framesfromboost = 0;
			snakesz += 3;
			food.setPosition(rand() % 489 + 1, rand() % 489 + 1);
		}
		for(int i = 0; i < snake.size(); i++)
		{
			FloatRect tempcollider = snake[i].getGlobalBounds();
			if(headcollider.intersects(tempcollider))
			{
				sleep(seconds(1.5));
				window.close();
				cout << "YOU LOST" << "\n";
			}
		}
		window.display();
	}
	return 0;
}
