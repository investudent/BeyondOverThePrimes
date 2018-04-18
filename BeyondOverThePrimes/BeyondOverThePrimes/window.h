#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "mouse.h"
#include "point3d.h"

#define WINDOW_HIGHT (720)
#define WINDOW_WIDTH (480)

#define INIT_FOVY   (45)
#define INIT_ASPECT ((double)WINDOW_WIDTH/(double)WINDOW_HIGHT)
#define INIT_Z_NEAR (1)
#define INIT_Z_FAR  (100)

class Vision {
private:
	double fov_y_;
	double aspect_;
	double z_near_;
	double z_far_;
public:
	Point3d camera_;
	Point3d target_;
	Point3d vector_;
public:
	//コンストラクタ，視点の設定
	Vision(const Point3d& _camera, const Point3d& _target, const Point3d& _vector)
		:fov_y_(INIT_FOVY), aspect_(INIT_ASPECT), z_near_(INIT_Z_NEAR), z_far_(INIT_Z_FAR), camera_(_camera), target_(_target), vector_(_vector) {
	}
	void Look() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov_y_, aspect_, z_near_, z_far_);		// ここを適切に設定する
		gluLookAt(camera_.Get_point_x(), camera_.Get_point_y(), camera_.Get_point_z(),
			target_.Get_point_x(), target_.Get_point_y(), target_.Get_point_z(),
			vector_.Get_point_x(), vector_.Get_point_y(), vector_.Get_point_z());
	}
};

class Window {
public:
	//コンストラクタ，ウィンドウの生成
	Window(int& argc, char **argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIGHT);
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HIGHT);
		//glutInitWindowPosition(200, 200);
		glutCreateWindow("Game");
	}
};