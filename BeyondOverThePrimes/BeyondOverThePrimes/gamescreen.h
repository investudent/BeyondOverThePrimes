#pragma once
#include "basescreen.h"
#include "stage.h"

class GameScreen :public BaseScreen {
private:
	Stage stage_;
	bool stopper_;
public:
	//�R���X�g���N�^�C�e��ݒ�
	GameScreen(Mouse& _mouse, Level _level)
		:BaseScreen(_mouse), stage_(_level, mouse_) {
		stopper_ = true;
	}
	//�X�V�֐��C�ŏ���1�N���b�N�܂ő҂�
	void Update() {
		if (mouse_.isClick()) {
			stopper_ = false;
		}
		if (!stopper_) {
			stage_.Update();
		}
		mouse_.Update();
	}
	//�`��֐��C�e�N�X�`���̌Ăяo���͂�����
	void Draw() {
		Yozora();
		Sosu();
		stage_.Draw();
	}
};