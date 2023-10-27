# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "PaintScene.hpp"
# include "ProgressBar.hpp"
# include "Connect.hpp"

PaintScene::PaintScene(const InitData& init) : IScene( init ) {
	initialize(getData().get_path(), getData().get_image_type());
}

void PaintScene::initialize(const FilePath& path, const String &img_type) {
	set_image(path);
	image_type = img_type;
	visited.resize(image.height(), Array<bool>(image.width(), false));
	update_texture();
	stopwach.start();
}

void PaintScene::set_image(const FilePath& path) {
	this->image = Image(path);
	this->image_monochrome = Image(path);
	this->image_nopaint = Image(path);
}
Image& PaintScene::get_image(void) {
	return this->image;
}

void PaintScene::update_texture(const Image& image) {
	texture.fill(image);
}
void PaintScene::update_texture(void) {
	texture.fill(image);
}

DynamicTexture& PaintScene::get_texture(void) {
	return this->texture;
}

bool PaintScene::is_in_image(const Point& point) const {
	return (0 <= point.y and point.y < image.height() and 0 <= point.x and point.x < image.width());
}

void PaintScene::bfs_bucket(const Point& start) {
	visited.clear();
	visited.resize(image_nopaint.height(), Array<bool>(image_nopaint.width(), false));
	std::queue<Point> que;
	que.push(start);
	while (not que.empty()) {
		Point now = que.front();
		// 画面の四隅に到着したらBFSをなかったことにする
		if (now == Point{ 0, 0 } or now == Point{ image_nopaint.height(), 0 } or now == Point{ 0, image_nopaint.width() } or now == Point{ image_nopaint.height(), image_nopaint.width() }){
			visited.clear();
			visited.resize(image_nopaint.height(), Array<bool>(image_nopaint.width(), false));
			break;
		}
		que.pop();
		for (const Point& delta : dydx) {
			const Point next = now + delta;
			if (is_in_image(next) and (not visited[next.y][next.x])) {	
				if (image_nopaint[next] != Palette::Black) {
					visited[next.y][next.x] = true;
					que.push(next);
				}
			}
		}
	}
}

void PaintScene::paint_visited(const Color &color){
	for (const Point& point : step(image.size())) {
		if (visited[point.y][point.x]) {
			image[point] = color;
			image_monochrome[point] = to_monochrome(color);
		}
	}		
}

Optional<Point> PaintScene::get_mousel_pos_pressed(void) const{
	if (MouseL.down()) {
		return Cursor::Pos();
	}else {
		return none;
	}
}

Optional<Point> PaintScene::scenepos_to_imagepos(const Point& point) const{
	if (texture_center != Scene::Center()) {
		throw Error{ U"texture is not on center!!" };
	}
	Point res = point - (Scene::Size() - image.size()) / 2;
	if (is_in_image(res)) {
		return res;
	}else {
		return none;
	}
}

void PaintScene::draw_canpus_rectframe(void) const{
	Rect(Arg::center( texture_center), image.size()).drawFrame(1, 1, Palette::Black);
}

void PaintScene::draw_progress_bar(void) const {
	ProgressBar({ 0,0 }, 50, (int)Scene::Size().x).draw_monochrome(time_limit_ms - stopwach.ms(), time_limit_ms);
}

void PaintScene::draw(void) const {
	texture.drawAt(texture_center);
	colorpalette.draw();
	draw_canpus_rectframe();
	draw_progress_bar();
}
void PaintScene::update(void) {
	// ボタンが押されるか、時間制限を超えていたら
	if (SimpleGUI::Button(U"完成！", Vec2{Scene::Center().x * 1.5, Scene::Center().y}, unspecified) or stopwach.ms() > time_limit_ms) {
		stopwach.reset();
		connect.post_image(this->image, image_type);
		changeScene(U"ReelScene");
		return;
	}
	colorpalette.update();
	texture_center = Scene::Center();
	Optional<Point> pos_clicked_scene = get_mousel_pos_pressed();
	Optional<Point> pos_clicked_image;
	if (pos_clicked_scene.has_value()){
		pos_clicked_image = scenepos_to_imagepos(pos_clicked_scene.value());
	}
	if (pos_clicked_image.has_value()) {
		bfs_bucket(pos_clicked_image.value());
		paint_visited(colorpalette.get_color());
		update_texture(this->image_monochrome);
	}
}



