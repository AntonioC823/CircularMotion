#include "Particle.h"

Particle::Particle(int x_, int y_, int radius_, float velocity_, float radians_, int distanceFromCenter_)
{
	x = x_;
	y = y_;
	radius = radius_;
	velocity = velocity_;
	radians = radians_;
	distanceFromCenter = distanceFromCenter_;
	colorArray[0] = rand() % 255;
	colorArray[1] = rand() % 255;
	colorArray[2] = rand() % 255;
}

sf::CircleShape Particle::draw() const
{
	sf::Color color(colorArray[0], colorArray[1], colorArray[2]);
	sf::CircleShape particle;
	particle.setPosition(x,y);
	particle.setRadius(radius);
	particle.setOrigin(particle.getOrigin().x + radius,particle.getOrigin().y + radius);
	particle.setFillColor(color);

	return particle;
}

void Particle::move(int originX, int originY)
{
	radians += velocity;
	x = originX + cos(radians) * distanceFromCenter;
	y = originY + sin(radians) * distanceFromCenter;
}
