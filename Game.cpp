#include "Game.hpp"
#include "iostream"

gm::Game::Game()//�������������� ����
{
	font.loadFromFile("1.otf");
	Init();
}

void gm::Game::Init()//��������� ������� ����
{
	for (int i = 0; i < countOfFields - 1; i++)
		elements[i] = i + 1;
	emptyField = countOfFields - 1; //��� ������� ���� ��������� ������ ����� ������
	elements[emptyField] = 0;
	statusOfGame = true; //��� ������� �������� ����� � �������� ����
}

bool gm::Game::Check()//��������� ������ �� �����������
{
	for (unsigned int i = 0; i < countOfFields; i++)
		{
			if (elements[i] > 0 && elements[i] != i+1) //��������� �� �������������� ������������ ��������� � �������
				return false;
		}
	return true;
}

void gm::Game::Move(Directions direction)//������ ���
{

	int col = emptyField % sizeOfField;//��������� ������� ������ ������
	int row = emptyField / sizeOfField;//��������� ������ ������ ������

	//���������� ����� ���������� ����� ��������� � ������� ����� ������ ������� ����� ��������
	int numberOfMovingField = -1;//������ -1 ����� �� ���������� ���� ������ ����� ������
	if (direction == Directions::Left && col < (sizeOfField - 1)) 
		numberOfMovingField = emptyField + 1;
	if (direction == Directions::Right && col > 0)
		numberOfMovingField = emptyField - 1;
	if (direction == Directions::Up && row < (sizeOfField - 1)) 
		numberOfMovingField = emptyField + sizeOfField;
	if (direction == Directions::Down && row > 0) 
		numberOfMovingField = emptyField - sizeOfField;

	if (emptyField >= 0 && numberOfMovingField >= 0)//������ ������� ������ ������ � �� ������� ����� ��������
		{
			int tmp = elements[emptyField];
			elements[emptyField] = elements[numberOfMovingField];
			elements[numberOfMovingField] = tmp;
			emptyField = numberOfMovingField;
		}
	statusOfGame = Check();//� ����� ������� ���� ��������� ������ �� �����������
}

void gm::Game::draw(sf::RenderTarget& field, sf::RenderStates states) const//������ ������� ���� � ������������ �� �������� �����������
{
	states.transform *= getTransform();//������ ���������� �������� ����
	sf::Color color = sf::Color(255, 255, 0);

	//������ ��� ����
	sf::RectangleShape shape(sf::Vector2f(pixelSizeOfField, pixelSizeOfField));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	field.draw(shape, states);

	//������ ������
	shape.setSize(sf::Vector2f(sizeOfCell-2, sizeOfCell-2)); //�������� ������ �������� ����� ���� ����� �� ������������
	shape.setOutlineThickness(2);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	sf::Text text("", font, 52);

	for (unsigned int i = 0; i < countOfFields; i++)
		{
			shape.setOutlineColor(color);
			text.setFillColor(color);
			text.setString(std::to_string(elements[i]));
			if (statusOfGame)//���� ����������� ������ �������� ������ ������ ������
				{
					shape.setOutlineColor(sf::Color(255, 255, 0));
					text.setFillColor(sf::Color::Cyan);
				}
			else if (elements[i] == i + 1)//�� ����� ������� ����������� ������ ������� ����� �� ����� ������ �������� ������ ������
				{
					text.setFillColor(sf::Color::Cyan);
				}

			if (elements[i] > 0)//������ ��� ������ �� ����������� ������
				{
					sf::Vector2f position(i % sizeOfField * sizeOfCell + 10, i / sizeOfField * sizeOfCell + 10);//� ������� ������ ������������ �������� ���� ��� ���������
					shape.setPosition(position);
					text.setPosition(position.x + 30, position.y + 20);//������������� ������� ������ ��� ������� �����
					field.draw(shape, states);
					field.draw(text, states);
				}
		}
}