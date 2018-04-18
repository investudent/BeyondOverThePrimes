#include"material.h"

//�^�����ȍގ��ɏ���������
Material::Material() {
	diffuse_[0] = 1;
	diffuse_[1] = 1;
	diffuse_[2] = 1;
	diffuse_[3] = 1;
	specular_[0] = 1;
	specular_[1] = 1;
	specular_[2] = 1;
	specular_[3] = 1;
	ambient_[0] = 1;
	ambient_[1] = 1;
	ambient_[2] = 1;
	ambient_[3] = 1;
	shininess_ = 0;
}
Material::Material(const DataSetf& di, const DataSetf& sp, const DataSetf& am, float sh) {
	di.Get(diffuse_);
	sp.Get(specular_);
	am.Get(ambient_);
	shininess_ = sh;
}
Material::Material(const Material& _initializer) {
	for (int i = 0; i<4; i++) {
		diffuse_[i] = _initializer.diffuse_[i];
		specular_[i] = _initializer.specular_[i];
		ambient_[i] = _initializer.ambient_[i];
	}
	shininess_ = _initializer.shininess_;
}
Material& Material::operator=(const Material& rhs) {
	for (int i = 0; i<4; i++) {
		diffuse_[i] = rhs.diffuse_[i];
		specular_[i] = rhs.specular_[i];
		ambient_[i] = rhs.ambient_[i];
	}
	shininess_ = rhs.shininess_;
	return *this;
}
//�ގ��ݒ��K������
void Material::Done() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess_);
}
//���ʔ��ː�����ύX����
void Material::SetRGB(float r, float g, float b) {
	specular_[0] = r;
	specular_[1] = g;
	specular_[2] = b;
}


void Material::Set(const DataSetf& di, const DataSetf& sp, const DataSetf& am, float sh) {
	di.Get(diffuse_);
	sp.Get(specular_);
	am.Get(ambient_);
	shininess_ = sh;
}
//���ʔ��˂̉s����ύX����
void Material::SetS(float s) {
	shininess_ = s;
}
void Material::Gradate(int diviser) {
	if (diviser<0) {
		diviser = 1;
	}
	for (int i = 0; i<4; i++) {
		diffuse_[i] /= diviser;
		specular_[i] /= diviser;
		ambient_[i] /= diviser;
	}
}
//���̍ގ��ɐݒ肷��
Material& Material::Gold() {
	diffuse_[0] = 0.7;
	diffuse_[1] = 0.6;
	diffuse_[2] = 0.2;
	diffuse_[3] = 1;
	specular_[0] = 0.6;
	specular_[1] = 0.5;
	specular_[2] = 0.4;
	specular_[3] = 1;
	ambient_[0] = 0.3;
	ambient_[1] = 0.2;
	ambient_[2] = 0.1;
	ambient_[3] = 1;
	shininess_ = 50;
	return *this;
}
//��̍ގ��ɐݒ肷��
void Material::Silver() {
	diffuse_[0] = 0.6;
	diffuse_[1] = 0.6;
	diffuse_[2] = 0.6;
	diffuse_[3] = 1;
	specular_[0] = 0.5;
	specular_[1] = 0.5;
	specular_[2] = 0.5;
	specular_[3] = 1;
	ambient_[0] = 0.2;
	ambient_[1] = 0.2;
	ambient_[2] = 0.2;
	ambient_[3] = 1;
	shininess_ = 60;
}
//�v���X�`�b�N�̍ގ��ɕύX����
void Material::Plastic() {
	diffuse_[0] = 0.1;
	diffuse_[1] = 0.4;
	diffuse_[2] = 0.1;
	diffuse_[3] = 1;
	specular_[0] = 0.5;
	specular_[1] = 0.6;
	specular_[2] = 0.5;
	specular_[3] = 1;
	ambient_[0] = 0;
	ambient_[1] = 0;
	ambient_[2] = 0;
	ambient_[3] = 1;
	shininess_ = 128;
}
void Material::Normal() {
	diffuse_[0] = 0.8;
	diffuse_[1] = 0.8;
	diffuse_[2] = 0.6;
	diffuse_[3] = 1;
	specular_[0] = 0.1;
	specular_[1] = 0.1;
	specular_[2] = 0.1;
	specular_[3] = 1;
	ambient_[0] = 0.2;
	ambient_[1] = 0.2;
	ambient_[2] = 0.2;
	ambient_[3] = 1;
	shininess_ = 64;
}