# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12

class ColorPalette {
public:
	ColorPalette(void);
	void update(void);
	void draw(void) const;
	Color get_color(void) const;
private:
	Color color = Palette::Black;
	const Vec2 gui_leftup = { Scene::Center().x * 1.45 , 50 };
	const Vec2 gui_size = { 200.0, 100.0 };
	const double gui_label_width = 125;
	void update_gui(void);
	Font font{ 25, U"SourceHanSansJP-Medium.otf" };
	const String description =
		U"スライダーを操作して\n赤・緑・青成分を調整";
	void draw_description(void)const ;
};
