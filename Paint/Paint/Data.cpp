# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"

Data::Data(void){}
void Data::set_path(const FilePath &path){
	this->path = path;
}
void Data::set_image_type(const String& type){
	this->image_type = type;
}
const FilePath &Data::get_path(void) const {
	return this->path;
}
const String &Data::get_image_type(void) const {
	return this->image_type;
}


Color to_monochrome(const Color &color){
	return Color(color.r*0.30 + color.g*0.59 + color.b*0.11);
}
