#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;
int x_mov = 10; int y_mov = 0;

int main()
{
	//The font for the game texts;
	Font gamefont;
	//The text element for the score;
	Text score;
	//The "BOOST" text element;
	Text boostt;
	//Score text element.
	Text st;
	//"PRESS SPACE TO START" text element;
	Text start;
	//GAME OVER! text;
	Text gameover;
	//Set font for the text element.
	start.setFont(gamefont);
	//Set content for the text element.
	start.setString("PRESS SPACE TO START");
	//Set color of the text element.
	start.setColor(Color::Green);
	//Set font size for the text element.
	start.setCharacterSize(20);
	//Set position for the text element.
	start.setPosition(120,200);
	//
	// Below are the same things, but done for different text elements.
	//
	gameover.setFont(gamefont);
	gameover.setString("GAME OVER");
	gameover.setPosition(170,230);
	gameover.setCharacterSize(20);
	gameover.setColor(Color::Green);
	st.setFont(gamefont);
	st.setColor(Color::Green);
	st.setString("SCORE");
	st.setCharacterSize(30);
	boostt.setFont(gamefont);
	boostt.setColor(Color::Green);
	boostt.setString("BOOST!");
	boostt.setCharacterSize(30);
	score.setCharacterSize(30);
	boostt.setPosition(350,4);
	score.setFont(gamefont);
	score.setPosition(100, 0);
	score.setColor(Color::Green);
	//Load font to font object from file.
	gamefont.loadFromFile("font.ttf");
	//Seed the random generator with the time.
	srand(time(NULL));
	//Open a window for the game.
	RenderWindow window(VideoMode(500 /*Resolution x */,500 /*Resolution y*/), "SUPA SNEK"/*Window title*/);
	//Generate a rectangle for the snakes head.
	RectangleShape r(Vector2f(10,10));
	//Create a deque for the snake tail.
	deque<RectangleShape> snake;
	//Put the snake head in the middle of the screen.
	r.setPosition(250,250);
	//Variable to hold the current size of the snake
	int snakesz = 4;
	//Variable to hold the multiplier for the speed.
	float boost = 1;
	//Make the food cube.
	RectangleShape food(Vector2f(12,12));
	//Set the food color.
	food.setFillColor(Color::Red);
	//Set food starting position.
	food.setPosition(rand() % 489 + 1, rand() % 489 + 1);
	//Count frames since boost.
	int framesfromboost = 0;
	//Variable to store the state of the game.
	int state = 0;
	//MAIN GAME LOOP:
	while(window.isOpen() /*Runs while the window is open*/)
	{
		//Handle events:
		Event event;
		while(window.pollEvent(event))
		{
			//If X button clicked, close window.
			if(event.type == Event::Closed)
			{
				window.close();
			}
		}
		//If state is 0, so the game is in the menu.
		if(state == 0)
		{
			//Some delay to slow down the frame rate.
			sleep(seconds(0.05));
			//Draw the start screen.
			window.clear(Color::Black);
			window.draw(start);
			//If space pressed change state to 1.
			if(Keyboard::isKeyPressed(Keyboard::Space))
			{
				state = 1;
			}
		}
		//If the state is 1, so the game is being played.
		if(state == 1)
		{
			//Is boost is on:
			if(boost != 1)
			{
				//Count frames from boost.
				framesfromboost++;
				//If last boost start was 100 ago, stop boost.
				if(framesfromboost >= 100)
				{
					framesfromboost = 0;
					boost = 1;
				}
			}
			//Change the text element to show the snakesz variable as score.
			score.setString(to_string(snakesz));
			//Delay to slow down the frame rate.
			sleep(seconds(0.05));
			//Controls, if key pressed change movement direction.
			if(Keyboard::isKeyPressed(Keyboard::W) && y_mov == 0) {x_mov = 0; y_mov = boost *  -10; goto rdy;}
			if(Keyboard::isKeyPressed(Keyboard::S) && y_mov == 0) {x_mov = 0; y_mov = boost * 10; goto rdy;}
			if(Keyboard::isKeyPressed(Keyboard::A) && x_mov == 0) {x_mov = boost * -10; y_mov = 0; goto rdy;}
			if(Keyboard::isKeyPressed(Keyboard::D) && x_mov == 0) {x_mov = boost * 10; y_mov = 0;}
			rdy:
			//Clear the window as black.
			window.clear(Color::Black);
			//Add the snake head from last frame to the tail.
			snake.push_back(r);
			//Move the head.
			r.move(x_mov, y_mov);
	//		cout << snake.size() << "\n";
			//Get collider of snake head.
			FloatRect headcollider = r.getGlobalBounds();
			//While the snake is too big, take away a block from the end.
			while(snake.size() > snakesz) 
			{
				snake.pop_front();
			}
			//Draw the whole snake.
			for(int i = 0; i < snake.size(); i++)
			{
				window.draw(snake[i]);
			}
			//Handle snake going outside the screen.
			Vector2f rpos = r.getPosition();
			if(rpos.x > 499) r.setPosition(0, rpos.y);
			if(rpos.y > 499) r.setPosition(rpos.x, 0);
			if(rpos.y < 0) r.setPosition(rpos.x, 489);
			if(rpos.x < 0) r.setPosition(489, rpos.y);
			//Draw the snake text.
			window.draw(score);
			//IF boost is on, draw the boost text element.
			if(boost != 1)	window.draw(boostt);
			//Draw the food block.
			window.draw(food);
			//Draw the snake head.
			window.draw(r);
			//Draw the score.
			window.draw(st);
			//Get food collider.
			FloatRect foodCollider = food.getGlobalBounds();
			//If head intersects with food.
			if(headcollider.intersects(foodCollider))
			{
				//Set boost.
				boost = 1.5;
				//Reset frames from boost counter.
				framesfromboost = 0;
				//Add to the snakes size.
				snakesz += 3;
				//Set the food block in an different position.
				food.setPosition(rand() % 489 + 1, rand() % 489 + 1);
			}
			//Check every block of the snake with the snake head for collision,
			for(int i = 0; i < snake.size(); i++)
			{
				FloatRect tempcollider = snake[i].getGlobalBounds();
				//If collides: 
				if(headcollider.intersects(tempcollider))
				{
					//Draw gameover text.
					window.draw(gameover);
					//Display gameover text.
					window.display();
					//Wait for 2.5 seconds.
					sleep(seconds(2.5));
					//Make the snake tail empty.
					snake = {};
					//Set the snake size to 3.
					snakesz = 3;
					//set State to 0 (menu state)
					state = 0;
					//Reset boost.
					boost = 1;
				}
			}			
		}
		//Display everything that was drawn on the screen.
		window.display();
	}
	//If main game loop breaks, return 0.
	return 0;
}
