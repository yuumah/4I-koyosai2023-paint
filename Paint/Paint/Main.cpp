# include <Siv3D.hpp> // Siv3D v0.6.12
# include "PaintScene.hpp"
# include "ColorPalette.hpp"
# include "ReelScene.hpp"
# include "CompleteScene.hpp"
# include "StartScene.hpp"
# include "Data.hpp"



void Main(){
	Window::Resize(1280, 720);
	Scene::SetBackground(Palette::White);

	App manager;
	manager.add<StartScene>(U"StartScene");
	manager.add<ReelScene>(U"ReelScene");
	manager.add<PaintScene>(U"PaintScene");
	manager.add<CompleteScene>(U"CompleteScene");

	manager.init(U"StartScene");
	while(System::Update()){
		if(not manager.update()){
			break;
		}
	}

}
