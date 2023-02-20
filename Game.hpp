#pragma once
#include <SFML/Graphics.hpp>

const int sizeOfField = 4;//размер игрового пол€(в €чейках)
const int countOfFields = sizeOfField * sizeOfField;//общее количество €чеек
const int pixelSizeOfField = 500;//размер игрового пол€ в пиксел€х
const int sizeOfCell = 120;//размер €чейки в пиксел€х

enum class Directions { Left, Right, Up, Down }; //определ€ем класс перечислени€
namespace gm
{
	class Game:
		public sf::Drawable, public sf::Transformable
	{
		private:
			int elements[countOfFields];
			int emptyField;
			bool statusOfGame;
			sf::Font font;
		public:
			Game();
			void Init();
			bool Check();
			void Move(Directions direction);
			void draw(sf::RenderTarget& field, sf::RenderStates states) const;
	};
}