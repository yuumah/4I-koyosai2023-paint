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

using App = SceneManager<String, Data>;



