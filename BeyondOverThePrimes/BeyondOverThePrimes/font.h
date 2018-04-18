#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "string.h"
#include "point3d.h"
#include "angle3d.h"
#include "material.h"

class Font :public Point3d, public Angle3d {
private:
	String str_;
	float font_size_;
	constexpr static float default_font_size_ = 0.001;
	Material mat_;
public:
	Font()
		:font_size_(default_font_size_) {
	}
	Font(const String& _str, float _font_size = 1, const Material& _mat = Material())
		:str_(_str), font_size_(_font_size*default_font_size_), mat_(_mat) {
	}
	Font(const String& _str, float _font_size, const Material& _mat, const Point3d& _point, const Angle3d& _angle)
		:str_(_str), font_size_(_font_size*default_font_size_), mat_(_mat), Point3d(_point), Angle3d(_angle) {
	}
	Font(const Font& initializer_)
		:str_(initializer_.str_), font_size_(initializer_.font_size_), mat_(initializer_.mat_), Point3d(*(Point3d*)&initializer_), Angle3d(*(Angle3d*)&initializer_) {
	}
	~Font() = default;

	void Set_str(const char* _str) {
		str_ = _str;
	}
	void Set_str(const String& _str) {
		str_ = _str;
	}
	void Set_str(int _int) {
		str_ = _int;
	}
	void Set_mat(const Material& _mat) {
		mat_ = _mat;
	}
	void Set_font_size(float _font_size) {
		font_size_ = _font_size*default_font_size_;
	}
	float Get_font_size() {
		return font_size_;
	}
	String& Get_str() {
		return str_;
	}
	void BlackOut() {
		mat_.Gradate(2);
	}

	void Draw() {
		glPushMatrix();
		Rotate();
		Translate();
		mat_.Done();
		glLineWidth(1000 * font_size_);
		glScalef(font_size_, font_size_, font_size_);
		for (int i = 0; i<str_.length(); i++) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str_.c_str()[i]);
		}
		glPopMatrix();
	}
};