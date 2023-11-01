# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12

struct CompleteEffect : IEffect {
public:
	CompleteEffect(double t);
	bool update(double t) override;
private:
	Circle circle;
	Point circle_start;
	double circle_radius;
	Color circle_color;
	const double circle_time = 1.5; // [s]
};
