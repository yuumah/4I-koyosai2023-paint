# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"


class LineDrawing {
public:
	LineDrawing(const Texture &t, const String &pth, const Vec2 &p, const String &tp, const int idx) :
		texture(t), path(pth), pos(p), type(tp), index(idx){}

	const Texture &get_texture() const;
	const String &get_path() const;
	const Vec2 &get_pos() const;
	const double get_posx() const;
	const String &get_type() const;
	const int get_index() const;
	void move_posx(const double d);

private:
	Texture texture;
	String path;
	Vec2 pos;
	String type;
	int index;
};


class ReelScene : public App::Scene {
public:
	// コンストラクタで線画をTextureにしてセット
	ReelScene(const InitData &init);
	void draw(void) const;
	void update(void);
private:
	// 線画のtextureとその描画の中心座標、パス
	Array<LineDrawing> line_drawings;
	// 元の画像の大きさ
	const Size original_texture_size = Size(512, 512);
	// textureの描画倍率
	const double scaled_rate = 0.5;
	// textureの間の間隔
	const int texture_blank = 100;
	// textureの速度ベクトル
	const double max_move_speed = -2000.0;
	// 動いている時間
	const int move_time_ms = 5450;
	Stopwatch stopwatch;
	// リールの長さ
	int reel_length = 0;
	// お絵かきシーンに移行するまでの時間
	const Duration sleep_time = 2.0s;
	// イージング関数
	double easing(const double &t) const;
};
