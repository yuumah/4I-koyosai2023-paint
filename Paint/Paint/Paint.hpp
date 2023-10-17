﻿# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "ColorPalette.hpp"

const Array<Point> dydx = { {1,0},{0,-1},{-1,0},{0,1} };

class Paint {
public:
	Paint(void);
	Paint(const FilePath& path);
	void set_image(const FilePath &path);
	Image& get_image(void);
	void update_texture(void);
	void update_texture(const Image &image);
	DynamicTexture& get_texture(void);
	void draw(void) const;
	void update(void);
private:
	Image image;
	// BFSの探索用に使用する
	Image image_nochange;
	DynamicTexture texture;
	Point texture_center = Scene::Center();
	// 座標が画像のサイズに収まっているか
	bool is_in_image(const Point &point) const;
	// BFSで塗りつぶし領域を走査
	Array<Array<bool>> visited;
	void bfs_bucket(const Point &start);
	// visitedがtrueの部分を色で塗りつぶす
	void paint_visited(const Color &color);
	// マウスが左クリックされた座標を取得
	Optional<Point> get_mousel_pos_pressed(void) const;
	// シーンの座標から画像の座標へ変換
	Optional<Point> scenepos_to_imagepos(const Point &point) const;
	// キャンパスの四角形を表示
	void draw_canpus_rectframe(void) const;
	// カラーパレット
	ColorPalette colorpalette;
};
