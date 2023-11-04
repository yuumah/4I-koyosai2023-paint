# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "PaintScene.hpp"
# include "ProgressBar.hpp"
# include "Connect.hpp"

PaintScene::PaintScene(const InitData &init) : IScene(init){
	initialize(getData().get_path(), getData().get_image_type());
}

void PaintScene::initialize(const FilePath &path, const String &img_type){
	set_image(path);
	image_type = img_type;
	visited.resize(image.height(), Array<bool>(image.width(), false));
	update_texture();
	stopwatch.start();
}

void PaintScene::set_image(const FilePath &path){
	this->image = Image(path);
	this->image_monochrome = Image(path);
	this->image_nopaint = Image(path);
}
Image &PaintScene::get_image(void){
	return this->image;
}

void PaintScene::update_texture(const Image &img){
	texture.fill(img);
}
void PaintScene::update_texture(void){
	texture.fill(this->image);
}

DynamicTexture &PaintScene::get_texture(void){
	return this->texture;
}

bool PaintScene::is_in_image(const Point &point) const{
	return (0 <= point.y and point.y < image.height() and 0 <= point.x and point.x < image.width());
}

void PaintScene::bfs_bucket(const Point &start){
	visited.clear();
	visited.resize(image_nopaint.height(), Array<bool>(image_nopaint.width(), false));
	std::queue<Point> que;
	que.push(start);
	while(not que.empty()){
		const Point now = que.front();
		que.pop();
		// 画面の四隅に到着したらBFSをなかったことにする
		if(now == Point(0, 0) or now == Point(image_nopaint.height()-1, 0) or now == Point(0, image_nopaint.width()-1) or now == Point(image_nopaint.height()-1, image_nopaint.width()-1)){
			visited.clear();
			visited.resize(image_nopaint.height(), Array<bool>(image_nopaint.width(), false));
			break;
		}
		for(const Point &delta : dydx){
			const Point next = now + delta;
			if(is_in_image(next) and (not visited[next.y][next.x])){
				if(image_nopaint[next] != Palette::Black){
					visited[next.y][next.x] = true;
					que.push(next);
				}
			}
		}
	}
}

void PaintScene::paint_visited(const Color &color){
	for(const Point &point : step(image.size())){
		if(visited[point.y][point.x]){
			image[point] = color;
			image_monochrome[point] = to_monochrome(color);
		}
	}
}

Optional<Point> PaintScene::get_mousel_pos_pressed(void) const {
	if(MouseL.down()){
		return Cursor::Pos();
	}else{
		return none;
	}
}

Optional<Point> PaintScene::scenepos_to_imagepos(const Point& point) const {
	if(texture_center != Scene::Center()){
		throw Error(U"texture is not on center!!");
	}
	const Point res = point - (Scene::Size() - image.size()) / 2;
	if(is_in_image(res)){
		return res;
	}else{
		return none;
	}
}

void PaintScene::draw_canpus_rect(void) const {
	Rect(Arg::center(texture_center), image.size()).draw(Palette::White).drawFrame(1, 1, Palette::Black);
}

void PaintScene::draw_progress_bar(void) const {
	ProgressBar(Point(0,0), 50, (int)Scene::Size().x).draw_monochrome(time_limit_ms - stopwatch.ms(), time_limit_ms);
}

Rect PaintScene::draw_button_rect(Rect rect, HSV button_color, const HSV& shadow_color)const {
	Vec2 shadow{ 0, rect.h / 7.5 };
	if (rect.mouseOver()) {
		button_color = button_color.setS(button_color.s * 4 / 5);
	}
	if (rect.leftPressed()) {
		rect = rect.stretched(-shadow.y, 0, shadow.y, 0);
		rect.rounded(10).draw(button_color);
	}
	else {
		rect.rounded(10).drawShadow(shadow, 5, 0, shadow_color).draw(button_color);
	}
	return rect;
}
void PaintScene::draw_button_label(const String& label, const Rect& rect, const HSV& color)const {
	int left = 0, right = 1000;
	while (Abs(right - left) > 1) {
		int mid = (left + right) / 2;
		if (font(label).draw(mid, rect.stretched(-rect.h / 20), HSV{ 0,0 })) {
			left = mid;
		}
		else {
			right = mid;
		}
	}
	font(label).drawAt(left, rect.center(), color);
}

void PaintScene::draw_description(void) const{
	font(description_left).drawAt(50, Scene::Size().x * 3.75 / 20, Scene::Center().y, description_color);
	font(description_right).drawAt(50, Vec2{ Scene::Size().x * 8.0 / 10, Scene::Center().y }, to_monochrome(description_color));
}

void PaintScene::finish_drawing(void){
	stopwatch.reset();
	connect.post_image(this->image, image_type);
	getData().set_completed_image(this->image);
	changeScene(U"CompleteScene");
}

void PaintScene::draw(void) const {
	draw_canpus_rect();
	texture.drawAt(texture_center);
	colorpalette.draw();
	Rect rect = draw_button_rect(button_rect, to_monochrome(Palette::Skyblue), to_monochrome(Palette::Darkblue));
	draw_button_label(U"完成", rect, to_monochrome(Palette::White));
	draw_progress_bar();
	draw_description();
}
void PaintScene::update(void){
	// ボタンが押されるか、時間制限を超えていたら
	if(button_rect.leftReleased()){
		finish_drawing();
		return;
	}
	colorpalette.update();
	texture_center = Scene::Center();
	const Optional<Point> pos_clicked_scene = get_mousel_pos_pressed();
	Optional<Point> pos_clicked_image;
	if(pos_clicked_scene.has_value()){
		pos_clicked_image = scenepos_to_imagepos(pos_clicked_scene.value());
	}
	if(pos_clicked_image.has_value()){
		bfs_bucket(pos_clicked_image.value());
		paint_visited(colorpalette.get_color());
		update_texture(this->image_monochrome);
	}
}
