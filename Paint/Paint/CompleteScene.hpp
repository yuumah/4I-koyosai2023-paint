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
	// 完成した画像の描画
	void draw_completed(void) const;
	const int display_time = 10; // [s]
	Stopwatch stopwatch;
	Texture texture;
	// 完成時のエフェクト
	void update_effect(void);
	Effect effect;
	const int effect_amount = 5; // 1フレームのエフェクト数
};
