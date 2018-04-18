#pragma once
#include "font.h"
#include "material.h"

class Tile :public Point3d, public Angle3d {
private:
	float scale_x_;
	float scale_y_;
	float scale_z_;
	Font font_;
	Material mat_;
	bool selectable_;
	bool is_prime_;
	bool center_;
public:
	Tile(float _scale_x, float _scale_y, float _scale_z)
		:scale_x_(_scale_x), scale_y_(_scale_y), scale_z_(_scale_z) {
	}
	Tile(float _scale_x, float _scale_y, float _scale_z, const Point3d& _point, const Angle3d& _angle, const Font& _font, const Material& _mat, bool _is_prime, bool _center = true)
		:scale_x_(_scale_x), scale_y_(_scale_y), scale_z_(_scale_z), Point3d(_point), Angle3d(_angle), font_(_font), mat_(_mat), selectable_(true), is_prime_(_is_prime), center_(_center) {
		TranslateFont();
	}
	void Remat(const Material& _mat) {
		mat_ = _mat;
	}
	void TranslateFont() {
		double str_length = 0;
		float min_scale = std::min(scale_x_, scale_y_);
		for (int i = 0; i<font_.Get_str().length(); i++) {
			str_length += glutStrokeWidth(GLUT_STROKE_ROMAN, font_.Get_str().c_str()[i])*font_.Get_font_size();
		}
		str_length = center_ ? -str_length / 2 : (scale_x_*scale_x_ / (min_scale*pow(2, scale_x_ - 1)) - str_length);
		font_.Move(str_length, -50 * font_.Get_font_size(), scale_z_ + font_.Get_font_size());
	}
	void Break_selectable() {
		selectable_ = false;
	}
	void BlackOut() {
		mat_.Gradate(2);
		font_.BlackOut();
	}

	void Set_str(const char* _str) {
		font_.Set_str(_str);
	}
	void Set_str(const String& _str) {
		font_.Set_str(_str);
	}
	void Set_str(int _int) {
		font_.Set_str(_int);
	}
	const String& Get_str() {
		return font_.Get_str();
	}


	bool Get_selectable() {
		return selectable_;
	}
	bool isPrime() {
		return is_prime_;
	}

	void Draw() {
		TranslateFont();
		glPushMatrix();
		Rotate();
		Translate();
		mat_.Done();
		glScalef(scale_x_, scale_y_, scale_z_);
		glutSolidCube(1);
		float min_scale = std::min(scale_x_, scale_y_);
		glScalef(1 / scale_x_*min_scale, 1 / scale_y_*min_scale, 1);
		font_.Draw();
		glPopMatrix();
	}
};