# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"
# include "CompleteEffect.hpp"

class CompleteScene : public App::Scene {
public:
	CompleteScene(const InitData &init);
	void draw(void) const;
	void update(void);

private:
	// 透明から不透明へアップデート
	void update_texture(void);
	Image image;
	Image image_nochange;
	// 完成した画像の描画
	void draw_completed(void) const;
	const double display_time = 10.0; // [s]
	Stopwatch stopwatch;
	DynamicTexture texture;
	// 完成時のエフェクト
	void update_effect(void);
	Effect effect;
	const int effect_amount = 5; // 1フレームのエフェクト数
};
