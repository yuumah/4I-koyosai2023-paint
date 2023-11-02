# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"

Data::Data(void){}

void Data::set_path(const FilePath &p){
	this->path = p;
}

void Data::set_image_type(const String &type){
	this->image_type = type;
}

void Data::set_completed_image(const Image &img){
	this->image = img;
}

const FilePath &Data::get_path(void) const {
	return this->path;
}

const String &Data::get_image_type(void) const {
	return this->image_type;
}

const Image &Data::get_completed_image(void) const {
	return this->image;
}


Color to_monochrome(const Color &color){
	return Color((uint8)(color.r*0.30 + color.g*0.59 + color.b*0.11));
}

constexpr int sliderHeight = 50;
constexpr int paddingLeft = 20;

void Slider(const StringView label, double &rate, const Point &pos, const int labelWidth, const int sliderWidth, const bool enabled) {
	static const Font font = Font(50);
	Rect(pos, labelWidth + sliderWidth + paddingLeft, sliderHeight).draw(Scene::GetBackground());
	Rect(pos + Point(labelWidth, sliderHeight / 3), sliderWidth, sliderHeight / 3).rounded(4.2).draw(ColorF(0.7));
	Rect(pos + Point(labelWidth, sliderHeight / 3), int(sliderWidth * rate), sliderHeight / 3).rounded(4.2).draw(ColorF(0.5));
	font(label).draw(Arg::leftCenter(pos + Point(5, sliderHeight / 2)), Palette::White);
	const RectF smallRect(Arg::center(pos + Vec2(labelWidth + int(sliderWidth * rate), sliderHeight / 2)), 16, 24);
	const RoundRect smallRoundRect = smallRect.rounded(4.2);
	smallRoundRect.draw(Palette::White).drawFrame(1, ColorF(0.67));
	if (enabled && Cursor::OnClientRect() && Rect(pos + Point(labelWidth, 0), sliderWidth, sliderHeight).leftPressed()) {
		const double p = Cursor::PosF().x - pos.x - labelWidth;
		rate = p / sliderWidth;
	}
}
