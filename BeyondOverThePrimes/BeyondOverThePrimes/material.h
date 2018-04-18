#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

struct DataSetf {
	float data_[4];
	void Get(float(&target)[4])const {
		for (int i = 0; i<4; i++) {
			target[i] = data_[i];
		}
	}
};

class Material {
private:
	float diffuse_[4];//ŠgŽU”½ŽË
	float specular_[4];//‹¾–Ê”½ŽË
	float ambient_[4];//ŠÂ‹«
	float shininess_;
public:
	Material();
	Material(const DataSetf& di, const DataSetf& sp, const DataSetf& am, float sh);
	Material(const Material& _initializer);
	Material& operator=(const Material& rhs);
	void Done();
	void SetRGB(float r, float g, float b);
	void Set(const DataSetf& di, const DataSetf& sp, const DataSetf& am, float sh);
	void SetS(float s);
	void Gradate(int diviser);
	Material& Gold();
	void Silver();
	void Plastic();
	void Normal();
};
