#pragma once
#include <SFML\Graphics.hpp>

class Particle
{
public:
	Particle(int x_, int y_, int radius_, float velocity_, float radians_, int distanceFromCenter_);
	sf::CircleShape draw() const;
	void move(int originX, int originY);
private:
	int x;
	int y;
	int radius;
	float velocity;
	float radians;
	int distanceFromCenter;
	int colorArray[3];
};
