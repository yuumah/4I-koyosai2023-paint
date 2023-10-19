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
		int x = (i++) * texture.size().x / 2 + 50;
		int y = Scene::Center().y;
		if (not (0 <= x and x <= Scene::Size().x)){
		}else {
			texture.resized(texture.size() / 2).drawAt(x, y);
		}
	}
}



