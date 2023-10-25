# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"

class ReelScene : public App::Scene{
public:
	// コンストラクタで線画をTextureにしてセット
	ReelScene(const InitData &init);
	void draw(void) const;
	void update(void);
private:
	// 線画のtextureとその描画の中心座標、パス
	Array<std::pair<Texture, Vec2>> line_drawings;
	Array<String> pathes;
	// 元の画像の大きさ
	Size original_texture_size = Size(512, 512);
	// textureの描画倍率
	double scaled_rate = 0.5;
	// textureの間の間隔
	int texture_blank = 100;
	// textureの速度ベクトル
	Vec2 max_move_speed = { -2000.0, 0 };
	// 動いている時間
	double move_time_ms = 7500.0;
	Stopwatch stopwatch;
	// リールの長さ
	int reel_length = 0;
	// リールが回る時間の揺れ幅
	int reel_random_amplitude = 2000;
	// お絵かきシーンに移行するまでの時間
	Duration sleep_time = 2.5s;
	// イージング関数
	double easing(const double &t);
};
