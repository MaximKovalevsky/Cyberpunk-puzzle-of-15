#include <SFML/Graphics.hpp>
#include "startGame.hpp"
#include "Game.hpp"

void st::startGame::setFont()//устанавливаем шрифт
{
	font.loadFromFile("1.otf");
}

void st::startGame::setText()//утсанавливаем текст в заголовке окна
{
	text.setString("F2 - New Game\t \t \t \t \t \t \t \tEsc - Exit");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(10, 10);
}

void st::startGame::setWindow()//утсанавливаем окно
{
	window.create(sf::VideoMode(height, width), "Cyberpunk <15 Puzle>");
	window.setFramerateLimit(60);
}

void st::startGame::start()//запускаем игру
{	
	setFont();
	setText();
	setWindow();
	gm::Game game;
	game.setPosition(50, 50);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Left)
					game.Move(Directions::Left);
				if (event.key.code == sf::Keyboard::Right)
					game.Move(Directions::Right);
				if (event.key.code == sf::Keyboard::Up)
					game.Move(Directions::Up);
				if (event.key.code == sf::Keyboard::Down)
					game.Move(Directions::Down);
				if (event.key.code == sf::Keyboard::F2)
				{
					game.Init();
					moveCounter = 100;
				}
			}
		}

		if (moveCounter > 0)//если количество ходов больше нул€, перемещаем €чейки в случайном пор€дке
		{
			moveCounter = moveCounter - 1;
			game.Move((Directions)(rand() % 4));//генерирует целое число до 4(не включа€ само число) и присваивает Directions

		}

		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}


}