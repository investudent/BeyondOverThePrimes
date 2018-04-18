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
	//コンストラクタ，各種設定／登録
	Mouse() :state_(FREE) {
		InformPoint(0, 0, 0, false, this);
		glutMouseFunc(&MouseFunc);
	}
	//状態確認
	bool isFree() {
		return state_ == FREE;
	}
	bool isClick() {
		return state_ == CLICK;
	}
	bool isHold() {
		return state_ == HOLD;
	}
	//更新関数，コールバックの内容を受けて適切に更新
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
//コールバック関数の内容をマウスクラスに渡す
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
//コールバック関数，マウスのウィンドウ座標を画面内の座標に
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