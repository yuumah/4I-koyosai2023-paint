# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"

class StartScene : public App::Scene {
public:
	StartScene(const InitData &init);
	void draw(void) const;
	void update(void);
private:
	Font font{ 200, U"SourceHanSansJP-Medium.otf" };
	// 開始ボタンの描画
	Rect draw_button_rect(Rect rect, HSV button_color, const HSV &shadow_color)const;
	void draw_button_label(const String &label, const Rect &rect, const HSV &color)const;
	Rect button_rect{ Arg::bottomCenter(Scene::Center().x, Scene::Size().y * 9 / 10), Scene::Size() / 3 };
	HSV button_hsv{ 200, 0.75, 0.85 };
	HSV button_shadow_hsv{ 200, 0.75, 0.65 };
};
