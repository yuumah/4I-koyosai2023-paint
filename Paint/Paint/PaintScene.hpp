# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "ColorPalette.hpp"
# include "ProgressBar.hpp"
# include "Connect.hpp"
# include "Data.hpp"

const Array<Point> dydx = { {1,0},{0,-1},{-1,0},{0,1} };

class PaintScene : public App::Scene {
public:
	PaintScene(const InitData &init);
	void initialize(const FilePath &path, const String &img_type);
	void set_image(const FilePath &path);
	Image &get_image(void);
	void update_texture(void);
	void update_texture(const Image &image);
	DynamicTexture &get_texture(void);
	void draw(void) const;
	void update(void);
private:
	Image image;
	Image image_monochrome;
	// BFSの探索用に使用する
	Image image_nopaint;
	DynamicTexture texture;
	Point texture_center = Scene::Center();
	String image_type;
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
	void draw_canpus_rect(void) const;
	// プログレスバーの表示
	void draw_progress_bar(void) const;
	// 完了ボタン
	Font font{ 100, U"SourceHanSansJP-Medium.otf" };
	Rect button_rect{ Scene::Size().x * 0.8, Scene::Size().y * 0.8, Scene::Size().x * 0.1, Scene::Size().y * 0.1 };
	Rect draw_button_rect(Rect rect, HSV button_color, const HSV &shadow_color)const;
	void draw_button_label(const String &label, const Rect &rect, const HSV &color)const;
	// 説明の描画
	void draw_description(void) const;
	const String description_left =
		U"絵をクリックして塗りつぶし\n修正はできないよ！";
	const String description_right =
		U"スライダーを操作して\n赤・緑・青成分を調整";
	const Color description_color = Palette::White;
	// 完成or終了時の処理
	void finish_drawing(void);
	// カラーパレット
	ColorPalette colorpalette;
	// 時間制限
	Stopwatch stopwatch;
	const int time_limit_ms = 120 * 1000;
	// 接続用
	Connect connect;
};
