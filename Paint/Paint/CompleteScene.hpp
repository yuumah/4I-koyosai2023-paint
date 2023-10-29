# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Data.hpp"


class CompleteScene : public App::Scene {
public:
	CompleteScene(const InitData &init);
	void draw(void) const;
	void update(void);

private:
	const int display_time = 10; // [s]
	Stopwatch stopwatch;
	Texture texture;
};
