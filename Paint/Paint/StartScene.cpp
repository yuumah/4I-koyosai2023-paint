# pragma once
# include "StartScene.hpp"


StartScene::StartScene(const InitData &init) : IScene(init){
}

void StartScene::draw(void) const {
}

void StartScene::update(void){
	if(SimpleGUI::Button(U"始める", Scene::Center())){
		changeScene(U"ReelScene", 1.0s);
	}
}
