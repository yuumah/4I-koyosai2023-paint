# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Paint.hpp"
# include "ColorPalette.hpp"
# include "Data.hpp"

using App = SceneManager<String, Data>;


void Main(){
	Window::Resize(1280, 720);
	Scene::SetBackground(Palette::White);

	App manager;



	Paint paint(U"line_drawing/ohana.png");
	ColorPalette colorpalette;
	while (System::Update()) {
		paint.draw();
		paint.update();
		colorpalette.draw();
		colorpalette.update();
	}

}
