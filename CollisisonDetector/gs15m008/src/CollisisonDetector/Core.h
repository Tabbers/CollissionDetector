#pragma once
#include <SFML\Graphics.hpp>

class Simulation;
class Display;

class Core
{
public:
	Core();
	~Core();
	void Init();
	void Run();
private:

	sf::ContextSettings context;
	sf::RenderWindow* window;
	sf::Clock clock;

	Display* disp;
	Simulation* sim;
};

