#pragma once
#include <SFML/Graphics.hpp>

const int sizeOfField = 4;//������ �������� ����(� �������)
const int countOfFields = sizeOfField * sizeOfField;//����� ���������� �����
const int pixelSizeOfField = 500;//������ �������� ���� � ��������
const int sizeOfCell = 120;//������ ������ � ��������

enum class Directions { Left, Right, Up, Down }; //���������� ����� ������������
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