# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12


class Data {
public:
	Data(void);
	void set_path(const FilePath &path);
	void set_image_type(const String &type);
	void set_completed_image(const Image &img);
	const FilePath &get_path(void) const;
	const String &get_image_type(void) const;
	const Image &get_completed_image(void) const;
private:
	FilePath path;
	String image_type;
	Image image;
};

// RGBの値の平均値で出す
Color to_monochrome(const Color &color);

using App = SceneManager<String, Data>;
