#include <SFML\Graphics.hpp>

#include <iostream>
#include <cmath>
#include <vector>

const int Window_width = 1700;
const int Window_height = 900;
const float Pi = 3.141592;
//force lines' size parametrs
const int fl_length = 15;
const int fl_width = 3;

struct Particle {
	Particle(int diameter, float val, float x, float y) : //constructor has size of particle, its value and position
		x(x), y(y), charge_value(val), circle(sf::CircleShape(diameter)) {

		if (charge_value > 0)
			circle.setFillColor(sf::Color(255, 160, 122)); //if particle is negatively charged - colour it in cold shame
		if (charge_value < 0)
			circle.setFillColor(sf::Color(123, 104, 238)); //if particle is positively charged - colour it in warm shame

		circle.setOrigin(diameter / 2, diameter / 2); //putting coordinates point in the center
		circle.setPosition(x, y);
	};
	float charge_value;
	float x;
	float y;
	sf::CircleShape circle;
	void Draw(sf::RenderWindow& window);
};

void Particle::Draw(sf::RenderWindow& window) {

	window.draw(circle);
}

struct ForceLines {
	ForceLines(float angle, float x, float y) :
		x(x), y(y), angle(angle) {

		line = sf::RectangleShape(sf::Vector2f(fl_length, fl_width));
		line.setFillColor({ 255,255,255 });

		line.setOrigin({ fl_length / 2, fl_width / 2 });
		line.setPosition(x, y);
		line.setRotation(angle * 180 / 3.1415);
	};
	float x;
	float y;
	float angle;
	sf::RectangleShape line;
	void Draw(sf::RenderWindow& window);
};

void ForceLines::Draw(sf::RenderWindow& window) {

	window.draw(line);
}

std::vector<ForceLines> countigElectricFieldStrengh(std::vector<Particle>& particle) { //function has type: array of force lines, function input arguments: array of particles

	std::vector<ForceLines> resultingLines; //array of changed force lines

	for (int i = 0; i < Window_width; i += 20) { //20 is a value of distance between the position of lines

		for (int j = 0; j < Window_height; j += 20) {
			float pos_x, pos_y;
			float electric_field_strength;

			sf::Vector2f E(0, 0); //two-dimensional array of electric field strength vector which has x-component and y-component 
			for (auto& element : particle) {

				pos_x = i - element.x;
				pos_y = j - element.y;

				electric_field_strength = element.charge_value / (std::pow((pos_x * pos_x + pos_y * pos_y), 2));
				sf::Vector2f E_elem(pos_x * electric_field_strength, pos_y * electric_field_strength);

				E = E + E_elem;
			}

			ForceLines lines(std::atan2(E.y, E.x), i, j);
			resultingLines.push_back(lines);
		}
	}

	return resultingLines;
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(Window_width, Window_height), "force lines");
	std::vector<Particle> particles;
	while (window.isOpen())
	{

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			Particle p(10, 1000, mousePosition.x, mousePosition.y);
			particles.push_back(p);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Particle p(10, -1000, mousePosition.x, mousePosition.y);
			particles.push_back(p);
		}
		auto lines = countigElectricFieldStrengh(particles);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		for (auto& elem : particles) {
			elem.Draw(window);
		}
		for (auto& elem : lines) {
			elem.Draw(window);
		}

		window.display();
		window.clear();
	}
	return 0;
}
