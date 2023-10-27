# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"
# include "Connect.hpp"


Connect::Connect(void){
	TextReader reader_url(U"./url.env");
	if(not reader_url){
		throw Error(U"Failed to open 'url.env'");
	}
	reader_url.readLine(this->url_base);
	TextReader reader_token(U"./token.env");
	if(not reader_token){
		throw Error(U"Failed to open 'token.env'");
	}
	reader_token.readLine(this->token);
}

//  https://scrapbox.io/voidproc-siv3d-examples/Base64 BASE64でエンコードした画像をソースコードに埋め込み、表示
String Connect::encode_file(const FilePath &filepath){
	BinaryReader reader(filepath);
	const int64 length = reader.size();
	String imgData;
	imgData.resize(length);
	reader.read(imgData.data(), length);
	return Base64::Encode(imgData.data(), length);
}



void Connect::post_image(const Image &image, const String &image_type){
	image.savePNG(save_png_path);
	this->post_image(save_png_path, image_type);
}

void Connect::post_image(const FilePath &filepath, const String &image_type){
	const URL url = url_base + U"uploadImages?token=" + token;
	const String encoded_file = encode_file(filepath);
	const std::string data = JSON{
		{ U"image", encoded_file },
		{ U"type", image_type },
	}.formatUTF8();
	if (const auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), save_response_path)){
		if(response.isOK()){
			Print << U"OK";
		}else{
			throw Error(U"failed to post file!");
		}
		Print << response.getHeader();
		Print << response.getStatusCodeInt();
		Print << response.getStatusLine();
	}
}
