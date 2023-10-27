# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"

class Connect {
public:
	Connect(void);
	void post_image(const Image &image, const String &image_type);
	void post_image(const FilePath &filepath, const String &image_type);
private:
	String encode_file(const FilePath &filepath);
	const HashTable<String, String> headers{ { U"Content-Type", U"application/json" } };
	URL url_base;
	String token;
	const FilePath save_png_path = U"./completed.png";
	const FilePath save_response_path = U"./post_response.txt";
};



