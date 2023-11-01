# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"
# include "CompleteScene.hpp"
# include "CompleteEffect.hpp"

CompleteScene::CompleteScene(const InitData &init) : IScene(init){
	this->image = getData().get_completed_image();
	this->image_nochange = this->image;
	texture = DynamicTexture(image);
	stopwatch.start();
}

void CompleteScene::draw(void) const {
	if (stopwatch.sF() > display_time_image) {
		draw_description();
	}
}

void CompleteScene::update(void){
	update_texture();
	draw_completed();
	update_effect();
	if(stopwatch.sF() > display_time){
		changeScene(U"StartScene");
		return;
	}
}

void CompleteScene::draw_completed(void) const {
	texture.drawAt(Scene::Center());
}

void CompleteScene::draw_description() const {
	const double alpha = (stopwatch.sF() - display_time_image) / ((display_time - display_time_image) / 2.0);
	font(description).drawAt(TextStyle::Outline(0.2, ColorF{ 1.0,1.0,1.0,alpha }), Scene::Center(), ColorF{ 0.0, 0.0, 0.0, alpha });
}

void CompleteScene::update_texture(void) {
	double rate = stopwatch.sF() / (display_time_image * 0.5);
	if (rate <= 1.0) {
		for (auto p : step(image_nochange.size())){
			if (image_nochange[p].a != 0) {
				image[p].setA(rate * 255);
			}
		}
		texture.fill(image);
	}
}

void CompleteScene::update_effect(void){
	effect.update();
	// イージングの進み具合を計算
	const double t = (stopwatch.sF() * 1.2) / (double)display_time;
	if (not(0.0 <= t and t <= 1.0)) {
		return;
	}
	const double e = EaseOutCirc(t);
	for (int i = 0; i < effect_amount *(1.0 - e); i++) {
		effect.add<CompleteEffect>(1.0 - e);
	}
}
