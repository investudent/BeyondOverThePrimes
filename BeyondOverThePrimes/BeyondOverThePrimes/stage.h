#pragma once
#include <vector>
#include <list>
#include <random>
//#include "human.h"
#include "tile.h"
#include "mouse.h"
#include "prime.h"

#define TILE_X  (3)
#define TILE_Y  (3)
#define TILE_Z  (0.5)

#define BLACK_MAT Material(DataSetf{0,0,0,1},DataSetf{0,0,0,1},DataSetf{0,0,0,1},0)

enum Level { EASY = 3, NORMAL = 5, HARD = 7 };

class Stage {
private:
	const Level level_;
	//Human human_;
	std::list<std::vector<Tile*>> tiles_;
	std::list<std::vector<Tile*>>::iterator current_tiles_;
	const int starting_point_;
	enum Index { MAKE, DELETES, HUMAN, nIndex };
	std::list<bool(Stage::*)()> update_funcs_[nIndex];
	//std::list<bool(Stage::*)()> updates_funcs_;

	unsigned int score_;
	Tile* char_tile_;
	Tile* score_tile_;

	const int WAIT_FRAME = 100000000;
	int left_frame;
	int frame_advance;
	int conbo;

	Mouse& mouse_;
public:
	//コンストラクタ，初期のタイル列やスコア欄，各種フラグの初期化
	Stage(Level _level, Mouse& _mouse)
		:level_(_level),/*human_(0,0,0),*/starting_point_(_level*TILE_Y), mouse_(_mouse), score_(0) {
		left_frame = WAIT_FRAME;
		frame_advance = WAIT_FRAME / 100;
		conbo = 0;

		MakeStartTiles();
		current_tiles_ = tiles_.begin();
		Break_selectables(*current_tiles_);
		for (int i = 0; i<level_; i++) {
			FirstSlideTiles();
			MakeQuestTiles();
		}

		char_tile_ = new Tile(4, 4, TILE_Z, Point3d(-1, -8.5, 5 + TILE_Z / 2), Angle3d(0, 0, 0), Font("Score:", 2), BLACK_MAT, false, false);
		Font score("", 2);
		score.Set_str(score_);
		score_tile_ = new Tile(6, 4, TILE_Z, Point3d(4, -8.5, 5 + TILE_Z / 2), Angle3d(0, 0, 0), score, BLACK_MAT, false, false);
		//human_.SetMat(Human::NORMAL);
	}
	//デストラクタ，全て解放
	~Stage() {
		for (; !tiles_.empty(); tiles_.pop_front()) {
			DeleteTiles(tiles_.front());
		}
		delete char_tile_;
		delete score_tile_;
	}
private:
	//タイルを生成する
	Tile* MakeTile(int tile_index, const Font& _font, const Material& _mat, bool _is_prime) {
		return new Tile(TILE_X, TILE_Y, TILE_Z, Point3d((tile_index - (int)(level_ / 2))*TILE_X, starting_point_, -TILE_Z / 2), Angle3d(0, 0, 0), _font, _mat, _is_prime);
	}
	//タイルを消す
	bool DeleteTiles(std::vector<Tile*>& target) {
		for (auto e : target) {
			delete e;
		}
		return false;
	}
	//タイル列を消す
	bool DeleteBackTiles() {
		bool tmp = DeleteTiles(tiles_.back());
		tiles_.pop_back();
		return tmp;
	}
	//タイルを落下させる
	bool DropTile(Tile* tile) {
		static int count = -18;
		static const int count_up = 18;
		if ((count += count_up) >= 360) {
			count = -18;
			return false;
		}
		tile->Slide(0, 0, -TILE_Z*count / 360);
		return true;
	}
	//タイル列を落下させる
	bool DropTiles() {
		bool tmp;
		for (auto e : tiles_.back()) {
			tmp = DropTile(e);
		}
		return tmp;
	}
	//画面内座標からタイルを特定する
	void PointToNextTile(double _x, double _y, int& distance, int& index) {
		//index = (int)((_x + TILE_X * 5 / 2) / TILE_X);
		index = (int)((_x * 2 / TILE_X+1) / 2+2);
		distance = (int)(_y * 2 / TILE_Y + 1) / 2;
	}
	//タイル崩落までのカウントを進める
	bool CountDown() {
		if ((left_frame -= frame_advance) <= 0) {
			left_frame = WAIT_FRAME;
			return false;
		}
		return true;
	}
	//タイル列の選択可能フラグを折る
	void Break_selectables(std::vector<Tile*>& tiles) {
		for (auto e : tiles) {
			e->Break_selectable();
		}
	}
	//タイル列を暗くする
	void BlackOuts(std::vector<Tile*>& tiles) {
		for (auto e : tiles) {
			e->BlackOut();
		}
	}
	//コンボの時のカウンター計算
	void ConboCount() {
		conbo++;
		score_ += conbo;
		frame_advance = (int)(frame_advance*pow(0.99, conbo));
	}
	//見逃した時のカウンター計算
	void MissCount(std::vector<Tile*>& tiles) {
		int miss_tiles = 0;
		for (int i = 0; i<tiles.size(); i++) {
			if (tiles[i]->Get_selectable()) {
				miss_tiles++;
			}
		}
		conbo = 0;
		frame_advance = (int)(frame_advance*pow(1.0001, miss_tiles));
	}
	//現在地によるカウンター計算
	void LevelCount(int add_level) {
		static int total_level = 1;
		total_level += add_level;
		double factor = 1 + ((double)total_level*level_ / 10000);
		frame_advance = (int)(pow(frame_advance,factor));
	}
public:
	//最初のタイル列を生成
	void MakeStartTiles() {
		static const Font no_text("", 2);
		static const Material start_tile(DataSetf{ 0.05f,0.05f,0.05f,1.0f },
										 DataSetf{ 0.0f,0.0f,0.0f,1.0f },
										 DataSetf{ 0.005f,0.005f,0.005f,1.0f },
										 0);
		tiles_.push_front(std::vector<Tile*>());
		for (int i = 0; i<level_; i++) {
			tiles_.front().push_back(MakeTile(i, no_text, start_tile, false));
		}
	}
	//問題のタイル列を生成
	bool MakeQuestTiles() {
		Number* numbers = new Number[level_];
		prime_device.GetPrimes(numbers, level_);
		Font number("", 2);
		static const Material red_tile(DataSetf{ 1,0,0,1 }, DataSetf{ 0,0,0,1 }, DataSetf{ 0.5f,0,0,1 }, 0);
		static const Material black_tile(DataSetf{ 0,0,0,1 }, DataSetf{ 0,0,0,1 }, DataSetf{ 0,0,0,1 }, 0);
		static bool is_red = true;
		tiles_.push_front(std::vector<Tile*>());
		for (int i = 0; i<level_; i++) {
			number.Set_str(numbers[i].number_);
			tiles_.front().push_back(MakeTile(i, number, is_red ? red_tile : black_tile, numbers[i].prime_));
			is_red = !is_red;
		}
		delete numbers;
		return false;
	}
	//タイルをスライドする
	bool SlideTiles() {
		static const int count_up = 18;
		static int count = -count_up;
		if ((count += count_up) >= 360) {
			count = -count_up;
			return false;
		}
		Fraction _y = -Fraction(TILE_Y)*Fraction(count_up) / Fraction(360);
		for (auto itr = tiles_.begin(); itr != tiles_.end(); itr++) {
			for (auto e : *itr) {
				e->Slide(Fraction(0), _y, Fraction(0));
			}
		}
		return true;
	}
	//ゲームを終了する
	bool Exit() {
		Tile(16, 4, TILE_Z, Point3d(0, 0, TILE_Z), Angle3d(0, 0, 0), Font("GAME OVER", 2), BLACK_MAT, false).Draw();
		glutSwapBuffers();
		Sleep(3000);
		Font last_score("Result Score : ", 2);
		last_score.Get_str()+=String(score_);
		Tile(16, 4, TILE_Z, Point3d(0, 0, 2*TILE_Z), Angle3d(0, 0, 0), last_score, BLACK_MAT, false).Draw();
		glutSwapBuffers();
		Sleep(3000);
		exit(0);
		return true;
	}
	//初期タイル列用スライド関数
	void FirstSlideTiles() {
		for (auto itr = tiles_.begin(); itr != tiles_.end(); itr++) {
			for (auto e : *itr) {
				e->Slide(0, -TILE_Y, 0);
			}
		}
	}
	//更新関数，クリックに対する反応やそれによる処理，カウントダウンと崩落処理の呼び出し
	void Update() {
		if (!update_funcs_[DELETES].empty() &&
			!(this->*update_funcs_[DELETES].front())()) {
			update_funcs_[DELETES].pop_front();
		}
		if (!update_funcs_[MAKE].empty()) {
			if (!(this->*update_funcs_[MAKE].front())()) {
				update_funcs_[MAKE].pop_front();
			}
			return;
		}
		if (mouse_.isClick()) {
			Fraction x, y, z;
			int distance = 0, index = 0;
			mouse_.Get(&x, &y, &z);
			PointToNextTile(x, y, distance, index);
			if (distance >= 0&&0<=index&&index<level_) {
				LevelCount(distance);
				for (int i = 0; i<distance; i++) {
					if (current_tiles_ != tiles_.end()) {
						BlackOuts(*current_tiles_);
						MissCount(*current_tiles_);
					}
					current_tiles_--;
					update_funcs_[MAKE].push_back(&Stage::SlideTiles);
					update_funcs_[MAKE].push_back(&Stage::MakeQuestTiles);
				}
				if ((*current_tiles_)[index]->isPrime() && (*current_tiles_)[index]->Get_selectable()) {
					if (!update_funcs_[DELETES].empty() && update_funcs_[DELETES].back() == &Stage::Exit) {
						update_funcs_[DELETES].pop_back();
					}
					ConboCount();
					(*current_tiles_)[index]->BlackOut();
					(*current_tiles_)[index]->Break_selectable();
					int tmp;
					sscanf_s((*current_tiles_)[index]->Get_str().c_str(), "%d", &tmp);
					score_ += tmp;
					int frame_point = frame_advance * 100 / WAIT_FRAME;
					score_ += pow(frame_point, 4);
					score_tile_->Set_str(score_);
				}
				else if (!(*current_tiles_)[index]->Get_selectable()) {
				}
				else if (!(*current_tiles_)[index]->isPrime()) {
					update_funcs_[DELETES].push_front(&Stage::Exit);
				}
			}
		}
		if (!CountDown()) {
			update_funcs_[DELETES].push_back(&Stage::DropTiles);
			update_funcs_[DELETES].push_back(&Stage::DeleteBackTiles);
			if (current_tiles_ == (--tiles_.end())) {
				//exit(0);
				if (update_funcs_[DELETES].size() < 3) {
					update_funcs_[DELETES].push_back(&Stage::Exit);
				}
				else {
					auto itr = update_funcs_[DELETES].begin();
					for (int i = 0; i < 2; itr++, i++);
					//update_funcs_[DELETES].insert(itr, &Stage::Exit);
					update_funcs_[DELETES].push_front(&Stage::Exit);
				}
			}
		}
		//human_.Update();
	}
	//描画関数
	void Draw() {
		for (auto itr = tiles_.begin(); itr != tiles_.end(); itr++) {
			for (auto e : *itr) {
				e->Draw();
			}
		}
		glShadeModel(GL_FLAT);
		char_tile_->Draw();
		score_tile_->Draw();
	}
};