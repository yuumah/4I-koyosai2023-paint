# pragma once
# include "StartScene.hpp"


StartScene::StartScene(const InitData &init) : IScene(init){
}

void StartScene::draw(void) const {
	Rect rect = draw_button_rect(button_rect, button_hsv, button_shadow_hsv);
	draw_button_label(U"開始", rect, Palette::White);
}

void StartScene::update(void){
	if(button_rect.leftReleased()){
		changeScene(U"ReelScene", 1.0s);
	}
}

Rect StartScene::draw_button_rect(Rect rect, HSV button_color, const HSV& shadow_color)const {
    Vec2 shadow{ 0, rect.h / 7.5 };
    if (rect.mouseOver()) {
        button_color = button_color.setS(button_color.s * 4 / 5);
    }
    if (rect.leftPressed()) {
        rect = rect.stretched(-shadow.y, 0, shadow.y, 0);
        rect.rounded(100).draw(button_color);
    }else {
        rect.rounded(100).drawShadow(shadow, 5, 0, shadow_color).draw(button_color);
    }
    return rect;
}
void StartScene::draw_button_label(const String& label, const Rect& rect, const HSV& color)const {
    int left = 0, right = 1000;
    while (Abs(right - left) > 1) {
        int mid = (left + right) / 2;
        if (font(label).draw(mid, rect.stretched(-rect.h / 20), HSV{ 0,0 })) {
            left = mid;
        }else {
            right = mid;
        }
    }
	font(label).drawAt(left, rect.center(), color);
}
