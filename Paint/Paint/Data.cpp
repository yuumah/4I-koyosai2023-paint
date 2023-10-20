# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"

Data::Data(void) {}
void Data::set_path(const FilePath &path){
	this->path = path;
}
FilePath Data::get_path(void) {
	return this->path;
}
