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
	const Vec2 gui_leftup = { Scene::Center().x * 1.30 , 75 };
	const Vec2 gui_size = { 300.0, 150.0 };
	const double gui_label_width = 300;
	void update_gui(void);
};
