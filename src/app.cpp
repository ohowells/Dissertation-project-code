#include <gl/glut.h>
#include "app.h"

float Application::getTimeinterval(void)
{
	return timeinterval;
}

void Application::setTimeinterval(float timeinterval)
{
	Application::timeinterval = timeinterval;
}

void Application::initGraphics(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Application::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Application::update(void)
{
	glutPostRedisplay();
}

void Application::resize(int width, int height)
{
	GLfloat nRange = 100.0f;
	GLfloat aspectRatio = static_cast<GLfloat>(width / height);

	// Prevent a divide by zero
	if (height == 0) height = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, width, height);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Establish clipping volume (left, right, bottom, top, near, far)
	if (width <= height)
	{
		Application::width = nRange;
		Application::height = nRange / aspectRatio;
		glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange*2.0f, nRange*2.0f);
	}
	else
	{
		Application::width = nRange*aspectRatio;
		Application::height = nRange;
		glOrtho(-nRange*aspectRatio, nRange*aspectRatio, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	}

	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}