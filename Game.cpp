#include "Game.hpp"
#include "iostream"

gm::Game::Game()//инициализируем игру
{
	font.loadFromFile("1.otf");
	Init();
}

void gm::Game::Init()//заполн€ем игровое поле
{
	for (int i = 0; i < countOfFields - 1; i++)
		elements[i] = i + 1;
	emptyField = countOfFields - 1; //при запуске игры последн€€ €чейка будет пустой
	elements[emptyField] = 0;
	statusOfGame = true; //при запуске головмка будет в решенном виде
}

bool gm::Game::Check()//провер€ем решена ли головоломка
{
	for (unsigned int i = 0; i < countOfFields; i++)
		{
			if (elements[i] > 0 && elements[i] != i+1) //провер€ем на неправильность расположени€ элементов в таблице
				return false;
		}
	return true;
}

void gm::Game::Move(Directions direction)//делаем ход
{

	int col = emptyField % sizeOfField;//вычисл€ем колонку пустой €чейки
	int row = emptyField / sizeOfField;//вычисл€ем строку пустой €чейки

	//определ€ем какое перемещние нужно выполнить и находим номер €чейки которую нужно сдвинуть
	int numberOfMovingField = -1;//ставим -1 чтобы не перемещать одни €чейки через другие
	if (direction == Directions::Left && col < (sizeOfField - 1)) 
		numberOfMovingField = emptyField + 1;
	if (direction == Directions::Right && col > 0)
		numberOfMovingField = emptyField - 1;
	if (direction == Directions::Up && row < (sizeOfField - 1)) 
		numberOfMovingField = emptyField + sizeOfField;
	if (direction == Directions::Down && row > 0) 
		numberOfMovingField = emptyField - sizeOfField;

	if (emptyField >= 0 && numberOfMovingField >= 0)//мен€ем местами пустую €чейку и ту которую хотим сдвинуть
		{
			int tmp = elements[emptyField];
			elements[emptyField] = elements[numberOfMovingField];
			elements[numberOfMovingField] = tmp;
			emptyField = numberOfMovingField;
		}
	statusOfGame = Check();//в конце каждого хода провер€ем решена ли головоломка
}

void gm::Game::draw(sf::RenderTarget& field, sf::RenderStates states) const//рисуем игровое поле в соответствии со статусом головоломки
{
	states.transform *= getTransform();//задаем координаты игровому полю
	sf::Color color = sf::Color(255, 255, 0);

	//рисуем все поле
	sf::RectangleShape shape(sf::Vector2f(pixelSizeOfField, pixelSizeOfField));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	field.draw(shape, states);

	//рисуем €чейки
	shape.setSize(sf::Vector2f(sizeOfCell-2, sizeOfCell-2)); //отнимаем нужные значение чтобы кра€ полей не пересекались
	shape.setOutlineThickness(2);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	sf::Text text("", font, 52);

	for (unsigned int i = 0; i < countOfFields; i++)
		{
			shape.setOutlineColor(color);
			text.setFillColor(color);
			text.setString(std::to_string(elements[i]));
			if (statusOfGame)//если головоломка решена выдел€ем €чейки другим цветом
				{
					shape.setOutlineColor(sf::Color(255, 255, 0));
					text.setFillColor(sf::Color::Cyan);
				}
			else if (elements[i] == i + 1)//во врем€ решени€ головоломки €чейки которые сто€т на своих местах выдел€ем другим цветом
				{
					text.setFillColor(sf::Color::Cyan);
				}

			if (elements[i] > 0)//рисуем все €чейки за исключением пустой
				{
					sf::Vector2f position(i % sizeOfField * sizeOfCell + 10, i / sizeOfField * sizeOfCell + 10);//у позицию €чейки относительно игрового пол€ дл€ отрисовки
					shape.setPosition(position);
					text.setPosition(position.x + 30, position.y + 20);//устанавливаем позицию текста дл€ номеров €чеек
					field.draw(shape, states);
					field.draw(text, states);
				}
		}
}