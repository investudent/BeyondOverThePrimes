#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

class Angle3d {
protected:
	double angle_x_;
	double angle_y_;
	double angle_z_;
public:
	Angle3d()
		:angle_x_(0), angle_y_(0), angle_z_(0) {
	}
	Angle3d(double _angle_x, double _angle_y, double _angle_z)
		:angle_x_(_angle_x), angle_y_(_angle_y), angle_z_(_angle_z) {
	}
	Angle3d(const Angle3d& _initializer)
		:angle_x_(_initializer.angle_x_), angle_y_(_initializer.angle_y_), angle_z_(_initializer.angle_z_) {
	}
	~Angle3d() = default;

	void Turn(double _angle_x, double _angle_y, double _angle_z) {
		angle_x_ += _angle_x;
		angle_y_ += _angle_y;
		angle_z_ += _angle_z;
	}
	void Rotate() {
		glRotatef(angle_x_, 1, 0, 0);
		glRotatef(angle_y_, 0, 1, 0);
		glRotatef(angle_z_, 0, 0, 1);
	}
};