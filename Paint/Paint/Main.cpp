# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Paint.hpp"


void Main(){

	Scene::SetBackground(Palette::White);
	Paint paint(U"line_drawing/ohana.png");
	while (System::Update()) {
		paint.draw();
		paint.update();
	}


}
