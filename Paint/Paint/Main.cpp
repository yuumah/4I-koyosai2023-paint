# include <Siv3D.hpp> // Siv3D v0.6.12
# include "PaintScene.hpp"
# include "ColorPalette.hpp"
# include "ReelScene.hpp"
# include "Data.hpp"



void Main(){
	Window::Resize(1280, 720);
	Scene::SetBackground(Palette::White);

	App manager;
	manager.add<ReelScene>(U"ReelScene");
	manager.add<PaintScene>(U"PaintScene");

	manager.init(U"ReelScene");
	while(System::Update()){
		if(not manager.update()){
			break;
		}
	}

}
