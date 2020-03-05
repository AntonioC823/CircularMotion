#include <SFML\Graphics.hpp>
#include "Particle.h"
#include <random>
#include <vector>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float PI = 3.141592;
const int FRAME_RATE = 60;

float randomFloat(float, float);
int randomInt(int, int);

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Circular Motion");
	window.setFramerateLimit(FRAME_RATE);

	// Initialize all variables used throughout the program
	srand(time(NULL));
	int numberOfParticles = 40;
	int radius = 10;
	float velocity = 0.05f;
	float dragIntensity = 0.05f;
	int setOriginX = WINDOW_WIDTH / 2;
	int setOriginY = WINDOW_HEIGHT / 2;
	bool followMouse = false;

	// Create particles with random radii and random distances from the initial point of rotational origin
	std::vector<Particle> particles;
	for (int i = 0; i < numberOfParticles; i++)
	{
		particles.push_back(Particle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, radius, velocity, randomFloat(0.0, 2 * PI), randomInt(50, 150)));
	}

	sf::Mouse mouse;
	int lastMouseX = WINDOW_WIDTH / 2;
	int lastMouseY = WINDOW_HEIGHT / 2;
	
	// Font and text initialized once to be used for drag intensity output onto the screen
	sf::Font font;
	font.loadFromFile("Roboto-Bold.ttf");
	sf::Text text;
	text.setFont(font);
	text.setPosition(10,50);
	text.setCharacterSize(15);

	sf::Clock clock;
	sf::Time timer;

	timer = clock.restart();
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			followMouse = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			followMouse = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			timer = clock.getElapsedTime();
			if (dragIntensity < 1.0f && timer.asSeconds() >= 0.25f)
			{
				dragIntensity += 0.05f;
				timer = clock.restart();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			timer = clock.getElapsedTime();
			if (dragIntensity > 0.0f && timer.asSeconds() >= 0.25f)
			{
				dragIntensity -= 0.05f;
				timer = clock.restart();
			}
		}

		// Update
		lastMouseX += (mouse.getPosition(window).x - lastMouseX) * dragIntensity;
		lastMouseY += (mouse.getPosition(window).y - lastMouseY) * dragIntensity;

		for (int i = 0; i < particles.size(); i++)
		{
			if (followMouse)
			{
				particles[i].move(lastMouseX, lastMouseY);
				setOriginX = lastMouseX;
				setOriginY = lastMouseY;
			}
			else
			{
				particles[i].move(setOriginX, setOriginY);
			}
		}

		text.setString("Drag Intensity: " + std::to_string(dragIntensity));

		// Clear window
		window.clear();

		// Draw objects
		for (int i = 0; i < particles.size(); i++)
		{
			window.draw(particles[i].draw());
		}
		window.draw(text);
		window.display();
	}

	return 0;
}

// Returns random float between two given numbers
float randomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float difference = max - min;

	return random * difference + min;
}

// Returns random integer between two given numbers
int randomInt(int min, int max)
{
	int difference = max - min;

	return rand() % difference + min;
}
