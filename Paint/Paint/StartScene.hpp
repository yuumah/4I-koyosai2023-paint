# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"

class StartScene : public App::Scene {
public:
	StartScene(const InitData &init);
	void draw(void) const;
	void update(void);
};
