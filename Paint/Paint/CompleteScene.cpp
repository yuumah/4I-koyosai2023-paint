# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "CompleteScene.hpp"

CompleteScene::CompleteScene(const InitData &init) : IScene(init){
	const Image &image = getData().get_completed_image();
	texture = Texture(image);
	stopwatch.start();
}

void CompleteScene::draw(void) const {
	texture.drawAt(Scene::Center());
}

void CompleteScene::update(void){
	if(stopwatch.s() > display_time){
		changeScene(U"StartScene");
		return;
	}
}
