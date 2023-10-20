# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12


class Data {
public:
	Data(void);
	void set_path(const FilePath &path);
	FilePath get_path(void);
private:
	FilePath path;
};

// RGBの値の平均値で出す
Color to_monochrome(const Color &color);

using App = SceneManager<String, Data>;



