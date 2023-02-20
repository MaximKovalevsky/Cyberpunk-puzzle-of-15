#pragma once
#include <SFML/Graphics.hpp>

namespace st
{
	class startGame
	{
		private:
			int height = 600;
			int width = 600;
			sf::Font font;
			sf::Text text;
			sf::Event event;
			sf::RenderWindow window;
			int moveCounter = 0;
		public:
			void setFont();
			void setText();
			void setWindow();
			void start();
	};
}