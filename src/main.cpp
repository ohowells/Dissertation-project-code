#include <gl/glut.h>
#include "app.h"

#define TIME_INTERVAL 25

extern Application* getApplication();
Application* app;

void display(void)
{
	app->display();
}

void createWindow(const char* title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow(title);
}

void TimerFunc(int value)
{
	app->update();
	glutTimerFunc(app->getTimeinterval(), TimerFunc, 1);
}

void resize(int width, int height)
{
	app->resize(width, height);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	app = getApplication();

	app->setTimeinterval(TIME_INTERVAL);
	createWindow("Sphere");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(TIME_INTERVAL, TimerFunc, 1);

	app->initGraphics();
	glutMainLoop();

	delete app;
	return 0;
}