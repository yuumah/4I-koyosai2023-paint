# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"

class Connect {
public:
	Connect(void);
	void post_image(const Image &image);
	void post_image(const FilePath &filepath);
private:
	String encode_file(const FilePath& filepath);
	const HashTable<String, String> headers{ { U"Content-Type", U"multipart/form-data" } };
	URL url_base;
	String token;
	FilePath save_png_path = U"./completed.png";
	const FilePath save_response_path = U"./post_response.txt";
};



