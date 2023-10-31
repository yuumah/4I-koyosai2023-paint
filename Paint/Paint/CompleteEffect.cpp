# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "CompleteEffect.hpp"

CompleteEffect::CompleteEffect(void) :
	circle_start(Point{- Random(Scene::Width() / 3), - Random(Scene::Height() / 3)}),
	circle_radius(Random(10, 50)),
	circle_color(RandomColor()){
	this->circle = Circle{ circle_start, circle_radius };
}

bool CompleteEffect::update(double t) {
	Circle moved_circle = circle.moveBy(circle_velocity * t);
	moved_circle.draw(circle_color);
	return (moved_circle.top().y < Scene::Height() and moved_circle.left().x < Scene::Width());
}
