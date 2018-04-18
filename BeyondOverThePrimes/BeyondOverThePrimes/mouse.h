#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "point3d.h"

class Mouse;

void InformPoint(double x, double y, double z, bool is_click, Mouse* _mouse = nullptr);
void MouseFunc(int button, int state, int x, int y);

class Mouse :public Point3d {
private:
	enum STATE { FREE, CLICK, HOLD }state_;
	bool updater_;
public:
	//�R���X�g���N�^�C�e��ݒ�^�o�^
	Mouse() :state_(FREE) {
		InformPoint(0, 0, 0, false, this);
		glutMouseFunc(&MouseFunc);
	}
	//��Ԋm�F
	bool isFree() {
		return state_ == FREE;
	}
	bool isClick() {
		return state_ == CLICK;
	}
	bool isHold() {
		return state_ == HOLD;
	}
	//�X�V�֐��C�R�[���o�b�N�̓��e���󂯂ēK�؂ɍX�V
	void Update() {
		if (updater_) {
			updater_ = !updater_;
			return;
		}
		switch (state_) {
		case FREE:state_ = FREE;
			break;
		case CLICK:state_ = HOLD;
			break;
		case HOLD:state_ = HOLD;
			break;
		}
	}
	friend void InformPoint(double x, double y, double z, bool is_click, Mouse* _mouse);
};
//�R�[���o�b�N�֐��̓��e���}�E�X�N���X�ɓn��
void InformPoint(double x, double y, double z, bool is_click, Mouse* _mouse) {
	static Mouse& mouse = *_mouse;
	mouse.point_x_ = x;
	mouse.point_y_ = y;
	mouse.point_z_ = z;
	mouse.updater_ = !is_click;
	switch (mouse.state_) {
	case Mouse::FREE:
		if (is_click) {
			mouse.state_ = Mouse::CLICK;
		}
		break;
	case Mouse::CLICK:
		if (is_click) {
			mouse.state_ = Mouse::HOLD;
		}
		else {
			mouse.state_ = Mouse::FREE;
		}
		break;
	case Mouse::HOLD:
		if (!is_click) {
			mouse.state_ = Mouse::FREE;
		}
		break;
	}
}
//�R�[���o�b�N�֐��C�}�E�X�̃E�B���h�E���W����ʓ��̍��W��
void MouseFunc(int button, int state, int x, int y) {
	GLdouble model[16], proj[16];
	GLint view[4];
	GLfloat z;
	GLdouble ox, oy, oz;

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		glGetDoublev(GL_MODELVIEW_MATRIX, model);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetIntegerv(GL_VIEWPORT, view);

		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, z, model, proj, view, &ox, &oy, &oz);
		InformPoint(ox, oy, oz, true);
	}
	else {
		InformPoint(0, 0, 0, false);
	}
}