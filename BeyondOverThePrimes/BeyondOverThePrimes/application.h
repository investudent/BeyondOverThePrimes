#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "window.h"
#include "mouse.h"
#include "gamescreen.h"

#define CAMERA  (Point3d(0,0,30))
#define TARGET  (Point3d(0,0,0))
#define VECTOR  (Point3d(0,1,0))

class Application;

void Update(Application* _app = nullptr);
void IdleFunc();
void Draw(Application* _app = nullptr);
void DisplayFunc();
void Light();

class Application {
private:
	Window window_;
	Vision vision_;
	Mouse mouse_;
	BaseScreen* scr_;
public:
	Application(int& argc, char** argv)
		:window_(argc, argv), vision_(CAMERA, TARGET, VECTOR) {
		scr_ = new GameScreen(mouse_, NORMAL);
		Update(this);
		glutIdleFunc(&IdleFunc);
		Draw(this);
		glutDisplayFunc(&DisplayFunc);
		glDepthFunc(GL_LEQUAL);
		//glClearColor(0.15,0.15,0.15,1.0);
		initTexturePPM();
	}
	~Application() {
		delete scr_;
	}

	void Play() {
		glutMainLoop();
	}

	friend void Update(Application* _app);
	friend void Draw(Application* _app);
};

void Update(Application* _app) {
	static Application& app = *_app;
	Sleep(13);
	app.scr_->Update();
}
void IdleFunc() {
	Update();
	glutPostRedisplay();
}

void Draw(Application* _app) {
	static Application& app = *_app;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	app.vision_.Look();
	Light();
	app.scr_->Draw();
}
void DisplayFunc() {
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Draw();
	glFlush();
	glutSwapBuffers();
}
void Light() {
	GLfloat ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	//GLfloat direction[3] = {0,0,-1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
}