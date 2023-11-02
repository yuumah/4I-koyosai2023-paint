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
	const double display_time = 30.0; // [s]
	const double display_time_image = display_time * 0.5;
	Stopwatch stopwatch;
	DynamicTexture texture;
	// 完成時のエフェクト
	void update_effect(void);
	Effect effect;
	const int effect_amount = 5; // 1フレームのエフェクト数
	// 完成後のメッセージ
	void draw_description() const;
	const Font font{ FontMethod::MSDF, 75, U"SourceHanSansJP-Medium.otf" };
	const String description = U"ありがとう！\nキミの協力のおかげで、\n世界にまたひとつ色が戻ったよ！\nさぁ、扉を抜けて、\nキミたちの作り上げた色のある世界を見に行こう！";
};
