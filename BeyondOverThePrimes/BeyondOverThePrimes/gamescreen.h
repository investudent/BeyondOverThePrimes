#pragma once
#include "basescreen.h"
#include "stage.h"

class GameScreen :public BaseScreen {
private:
	Stage stage_;
	bool stopper_;
public:
	//コンストラクタ，各種設定
	GameScreen(Mouse& _mouse, Level _level)
		:BaseScreen(_mouse), stage_(_level, mouse_) {
		stopper_ = true;
	}
	//更新関数，最初の1クリックまで待つ
	void Update() {
		if (mouse_.isClick()) {
			stopper_ = false;
		}
		if (!stopper_) {
			stage_.Update();
		}
		mouse_.Update();
	}
	//描画関数，テクスチャの呼び出しはここで
	void Draw() {
		Yozora();
		Sosu();
		stage_.Draw();
	}
};