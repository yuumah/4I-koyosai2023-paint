# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "CompleteEffect.hpp"

CompleteEffect::CompleteEffect(double e) :
	circle_start(Point{ Random(Scene::Width()), Scene::Height() + Random(Scene::Height() / 3, Scene::Height() / 2) }),
	circle_radius(Random(10, 50)),
	circle_color(RandomColor().setA(Random(0, (int)(127.0 * e)))){
	this->circle = Circle{ circle_start, circle_radius };
}

bool CompleteEffect::update(double t) {
	// 経過時間と持続時間の比
	const double rate = t / circle_time;
	// 円の中心座標を計算
	const double e = EaseInOutQuad(rate);
	const Point circle_center{ circle_start.x, (int)circle_start.y - (int)((2 * circle_start.y - Scene::Height()) * e) };
	Circle moved_circle = Circle{ circle_center, circle_radius };
	moved_circle.draw(circle_color);
	return (moved_circle.bottom().y > 0 or t <= 1.5);
}
