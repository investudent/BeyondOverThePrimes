#pragma once
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include "fraction.h"

class Point3d {
protected:
	Fraction point_x_;
	Fraction point_y_;
	Fraction point_z_;
public:
	Point3d()
		:point_x_(0), point_y_(0), point_z_(0) {
	}
	Point3d(double _point_x, double _point_y, double _point_z)
		:point_x_(_point_x), point_y_(_point_y), point_z_(_point_z) {
	}
	Point3d(Fraction _point_x, Fraction _point_y, Fraction _point_z)
		:point_x_(_point_x), point_y_(_point_y), point_z_(_point_z) {
	}
	Point3d(const Point3d& _initializer)
		:point_x_(_initializer.point_x_), point_y_(_initializer.point_y_), point_z_(_initializer.point_z_) {
	}
	~Point3d() = default;


	Fraction Get_point_x()const {
		return point_x_;
	}
	Fraction Get_point_y()const {
		return point_y_;
	}
	Fraction Get_point_z()const {
		return point_z_;
	}
	void Get(Fraction* x, Fraction* y, Fraction* z) {
		if (x != nullptr) {
			*x = point_x_;
		}
		if (y != nullptr) {
			*y = point_y_;
		}
		if (z != nullptr) {
			*z = point_z_;
		}
	}


	void Move(double moved_x, double moved_y, double moved_z) {
		point_x_ = moved_x;
		point_y_ = moved_y;
		point_z_ = moved_z;
	}
	void Slide(double slided_x, double slided_y, double slided_z) {
		point_x_ += slided_x;
		point_y_ += slided_y;
		point_z_ += slided_z;
	}
	void Move(Fraction moved_x, Fraction moved_y, Fraction moved_z) {
		point_x_ = moved_x;
		point_y_ = moved_y;
		point_z_ = moved_z;
	}
	void Slide(Fraction slided_x, Fraction slided_y, Fraction slided_z) {
		point_x_ += slided_x;
		point_y_ += slided_y;
		point_z_ += slided_z;
	}
	void Translate() {
		glTranslatef(point_x_, point_y_, point_z_);
	}
};