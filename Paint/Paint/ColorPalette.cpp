# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "ColorPalette.hpp"
# include "Data.hpp"

ColorPalette::ColorPalette(void){}

Color ColorPalette::get_color(void) const {
	return this->color;
}

void ColorPalette::update_gui(void){
	ColorF colorf((double)this->color.r/255.0, (double)this->color.g / 255.0, (double)this->color.b / 255.0);
	if(SimpleGUI::Slider(U"Red:     {:>3}"_fmt(colorf.r*255), colorf.r, gui_leftup, gui_label_width, gui_size.x)){
		this->color.r = (uint8)(colorf.r * 255);
	}
	if(SimpleGUI::Slider(U"Green: {:>3}"_fmt(colorf.g*255), colorf.g, Vec2(gui_leftup.x, gui_leftup.y + gui_size.y * 1 / 2), gui_label_width, gui_size.x)){
		this->color.g = (uint8)(colorf.g * 255);
	}
	if(SimpleGUI::Slider(U"Blue:    {:>3}"_fmt(colorf.b*255), colorf.b, Vec2(gui_leftup.x, gui_leftup.y + gui_size.y * 2 / 2), gui_label_width, gui_size.x)){
		this->color.b = (uint8)(colorf.b * 255);
	}
}

void ColorPalette::draw_description(void)const {
	font(description).drawAt(Vec2{Scene::Size().x * 8.5 / 10, Scene::Center().y}, to_monochrome(this->color));
}

void ColorPalette::update(void){
	update_gui();
}
void ColorPalette::draw(void) const {
	draw_description();
}
