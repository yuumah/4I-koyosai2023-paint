# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "CompleteScene.hpp"
# include "CompleteEffect.hpp"

CompleteScene::CompleteScene(const InitData &init) : IScene(init){
	//const Image &image = getData().get_completed_image();
	const Image &image = Image(U"./completed.png");
	texture = Texture(image);
	stopwatch.start();
}

void CompleteScene::draw(void) const {
	
}

void CompleteScene::update(void){
	draw_completed();
	update_effect();
	if(stopwatch.s() > display_time){
		changeScene(U"StartScene");
		return;
	}
}

void CompleteScene::draw_completed(void) const {
	texture.drawAt(Scene::Center());
}

void CompleteScene::update_effect(void){
	// イージングの進み具合を計算
	const double t = stopwatch.sF() / (double)display_time;
	const double e = EaseOutCirc(t);
	Console << U"e={} \t n={}"_fmt(e, effect_amount * e);
	for (int i = 0; i < effect_amount * e; i++) {
		effect.add<CompleteEffect>();
	}
	effect.update();
	Console << effect.num_effects();
}
