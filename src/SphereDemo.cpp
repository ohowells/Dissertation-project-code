#include <random>
#include <iostream>
#include <gl/glut.h>
#include <app.h>
#include "particle.h"
#include "Vector.h"
#include "BoundingSphere.h"

using namespace vector;
using namespace boundingsphere;

#define SPHERE_COUNT		6
#define SPHERE_RADIUS		2
#define SPHERE_VELOCITY		20
#define MEAN(n)				n / SPHERE_COUNT

class SphereDemo
	: public Application
{
public:
	SphereDemo(void);
	virtual void display(void);
	virtual void update(void);

	void calculate_BS(BoundingSphere &bs, Particle p[]);
	void box_collision_resolve(Particle &p);
	void out_of_box_collision_resolve(Particle &p);
	void particle_collision_resolve(Particle &p1, Particle &p2);

private:
	int xstep;
	int ystep;
	int box_width;
	int box_height;

	Particle p[SPHERE_COUNT];
	Particle p1[SPHERE_COUNT];
	Particle centre;
	BoundingSphere bs;
	BoundingSphere bs2;
};

SphereDemo::SphereDemo(void)
	: xstep(1),
	ystep(1),
	box_width(width),
	box_height(height)
{
	width = 600;
	height = 600;

	std::default_random_engine rand;
	std::uniform_real_distribution<float> dis(50, 70);
	std::uniform_real_distribution<float> dis2(-80, -70);

	for (auto i = 0; i < SPHERE_COUNT; i++)
	{
		p[i].setPosition(dis(rand), dis(rand));
		p[i].setVelocity(SPHERE_VELOCITY, -SPHERE_VELOCITY);
		p[i].setAcceleration(0, -900);
		p[i].setDamping(0.5f);
		p[i].setRadius(SPHERE_RADIUS);

		p1[i].setPosition(dis2(rand), dis2(rand));
		p1[i].setVelocity(SPHERE_VELOCITY, -SPHERE_VELOCITY);
		p1[i].setAcceleration(0, -1000);
		p1[i].setDamping(0.6f);
		p1[i].setRadius(SPHERE_RADIUS);
	}

	calculate_BS(bs, p);
	calculate_BS(bs, p1);
}

void SphereDemo::calculate_BS(BoundingSphere &bs, Particle p[])
{
	float sumX = 0;
	float sumY = 0;

	for (auto i = 0; i < SPHERE_COUNT; i++)
	{
		sumX += p[i].getPosition().x;
		sumY += p[i].getPosition().y;
	}

	centre.setPosition(MEAN(sumX), MEAN(sumY));

	float tempMaxX = 0;
	float tempMaxY = 0;
	float biggest = 0;

	for (auto i = 0; i < SPHERE_COUNT; i++)
	{
		tempMaxX = p[i].getPosition().x - centre.getPosition().x;
		tempMaxY = p[i].getPosition().y - centre.getPosition().y;

		auto result = pow(tempMaxX, 2) + pow(tempMaxY, 2);

		if (result > biggest) biggest = result;
	}

	bs.setCentre(centre.getPosition().x, centre.getPosition().y);
	bs.setRadius(sqrt(biggest));
}

void SphereDemo::display(void)
{
	Application::display();

	for (auto i = 0; i < SPHERE_COUNT; i++)
	{
		// First cluster
		glPushMatrix();
		glTranslatef(p[i].getPosition().x, p[i].getPosition().y, 0.0f);
		glColor3ub(255, 0, 0);
		glutSolidSphere(p[i].getRadius(), 25, 25);
		glPopMatrix();

		// Second cluster
		glPushMatrix();
		glTranslatef(p1[i].getPosition().x, p1[i].getPosition().y, 0.0f);
		glColor3ub(0, 255, 0);
		glutSolidSphere(p1[i].getRadius(), 25, 25);
		glPopMatrix();
	}

	// Show Bounding sphere of cluster
	glPushMatrix();
	glColor3ub(0, 255, 0);
	glBegin(GL_LINE_LOOP);
	// Bounding shpere
	glTranslatef(bs.getCentre().x, bs.getCentre().y, 0.0f);
	for (auto j = 0; j < 25; j++)
		glVertex2d(bs.getCentre().x + sin(PHI * j) * bs.getRadius(),
				   bs.getCentre().y + cos(PHI * j) * bs.getRadius());
	glEnd();
	glPopMatrix();

	// Show Bounding sphere of second cluster
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glBegin(GL_LINE_LOOP);
	// Bounding shpere
	glTranslatef(bs2.getCentre().x, bs2.getCentre().y, 0.0f);
	for (auto j = 0; j < 25; j++)
		glVertex2d(bs2.getCentre().x + sin(PHI * j) * bs2.getRadius(),
				   bs2.getCentre().y + cos(PHI * j) * bs2.getRadius());
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

// detect if the particle collided with each other and produce a response
void SphereDemo::particle_collision_resolve(Particle &particle1, Particle &particle2)
{
	Vector2 p1 = particle1.getPosition();
	Vector2 p2 = particle2.getPosition();
	Vector2 v1 = particle1.getVelocity();
	Vector2 v2 = particle2.getVelocity();
	float r1 = particle1.getRadius();
	float r2 = particle2.getRadius();

	float distance = sqrt(pow((p1.x - p2.x), 2) +
		pow((p1.y - p2.y), 2));

	if (distance <= r1 + r2)
	{
		Vector3 U1x, U1y, U2x, U2y, V1x, V1y, V2x, V2y;

		Vector3 a, b, a_vel, b_vel;
		a = Vector3(p1.x, p1.y, 0);
		b = Vector3(p2.x, p2.y, 0);

		a_vel = Vector3(v1.x, v1.y, 0);
		b_vel = Vector3(v2.x, v2.y, 0);

		float m1, m2, x1, x2;

		Vector3 v1temp, v1, v2, v1x, v2x, v1y, v2y, x(a - b);

		x.normalize();

		x1 = x.dot(a_vel);
		v1x = x * x1;
		v1y = a_vel - v1x;

		m1 = 0.7f;
		x = x * -1;

		x2 = x.dot(b_vel);
		v2x = x * x2;
		v2y = v2 - v2x;

		m2 = 0.7f;

		a_vel = Vector3(v1x*(m1 - m2) / (m1 + m2) +
			v2x*(2 * m2) / (m1 + m2) + v1y);

		b_vel = Vector3(v1x*(2 * m1) / (m1 + m2) +
			v2x*(m2 - m1) / (m1 + m2) + v2y);

		particle1.setVelocity(a_vel[0], a_vel[1]);
		particle2.setVelocity(b_vel[0], b_vel[1]);
	}
}

//  Check bounds. This is in case the window is made
//  smaller while the sphere is bouncing and the 
//  sphere suddenly finds itself outside the new
//  clipping volume
void SphereDemo::out_of_box_collision_resolve(Particle &particle)
{
	Vector2 position = particle.getPosition();
	Vector2 velocity = particle.getVelocity();
	float radius = particle.getRadius();

	if (position.x > (Application::width - radius + xstep))
		position.x = Application::width - radius - 1;
	else if (position.x < -(Application::width + xstep))
		position.x = -Application::width - 1;

	if (position.y >(Application::height + ystep))
		position.y = Application::height - 1;
	else if (position.y < -(Application::height - radius + ystep))
		position.y = -Application::height + radius - 1;

	particle.setPosition(position.x, position.y);
}

// detect if the particle colided with the box and produce a response
void SphereDemo::box_collision_resolve(Particle &particle)
{
	Vector2 position = particle.getPosition();
	Vector2 velocity = particle.getVelocity();
	float radius = particle.getRadius();

	float w = Application::width;
	float h = Application::height;

	// Reverse direction when you reach left or right edge
	if (position.x > w - radius || position.x < -w + radius)
		particle.setVelocity(-velocity.x, velocity.y);

	if (position.y > h - radius || position.y < -h + radius)
		particle.setVelocity(velocity.x, -velocity.y);
}

void SphereDemo::update(void)
{
	// increase the radius of the sphere
	// Find the duration of the last frame in seconds
	float duration = timeinterval / 1000;

	for (auto i = 0; i < SPHERE_COUNT; i++)
	{
		// First Cluster
		p[i].integrate(duration);
		box_collision_resolve(p[i]);
		out_of_box_collision_resolve(p[i]);

		// Second Cluster
		p1[i].integrate(duration);
		box_collision_resolve(p1[i]);
		out_of_box_collision_resolve(p1[i]);

		for (auto j = i + 1; j < SPHERE_COUNT; j++)
		{
			particle_collision_resolve(p[i], p[j]);
			particle_collision_resolve(p1[i], p1[j]);

			if (bs.overlaps(bs2))
			{ // check for collisions inside bounding spheres
				particle_collision_resolve(p[i], p1[j]);
				particle_collision_resolve(p1[i], p[j]);
			}
		}
	}

	calculate_BS(bs, p);
	calculate_BS(bs2, p1);

	Application::update();
}

Application* getApplication(void)
{
	return new SphereDemo();
}