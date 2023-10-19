# include <Siv3D.hpp> // Siv3D v0.6.12
# include "LineDrawingReelScene.hpp"

LineDrawingReelScene::LineDrawingReelScene(void) {
	for (const String &path : FileSystem::DirectoryContents(U"line_drawing")){
		textures << Texture(path);
	}
}


void LineDrawingReelScene::draw(void) const {
	int i = 0;
	for(const Texture &texture: textures){
		texture.drawAt();
	}
}



