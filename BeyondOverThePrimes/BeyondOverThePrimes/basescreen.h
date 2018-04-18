#pragma once
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "mouse.h"
#include "texture.h"

class BaseScreen {
protected:
	Mouse& mouse_;
public:
	//コンストラクタ，マウスを登録
	BaseScreen(Mouse& _mouse)
		:mouse_(_mouse) {
	}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};