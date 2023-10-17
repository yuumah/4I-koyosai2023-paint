# pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
# include "Paint.hpp"


Paint::Paint(void) {}
Paint::Paint(const FilePath& path) {
	set_image(path);
	visited.resize(image.height(), Array<bool>(image.width(), false));
	update_texture();
}

void Paint::set_image(const FilePath& path) {
	this->image = Image(path);
	this->image_nochange = Image(path);
}
Image& Paint::get_image(void) {
	return this->image;
}

void Paint::update_texture(const Image& image) {
	texture.fill(image);
}
void Paint::update_texture(void) {
	texture.fill(image);
}

DynamicTexture& Paint::get_texture(void) {
	return this->texture;
}

bool Paint::is_in_image(const Point& point) const {
	return (0 <= point.y and point.y < image.height() and 0 <= point.x and point.x < image.width());
}

void Paint::bfs_bucket(const Point& start) {
	visited.clear();
	visited.resize(image_nochange.height(), Array<bool>(image_nochange.width(), false));
	std::queue<Point> que;
	que.push(start);
	while (not que.empty()) {
		Point now = que.front();
		// 画面の四隅に到着したらBFSをなかったことにする
		if (now == Point{ 0, 0 } or now == Point{ image_nochange.height(), 0 } or now == Point{ 0, image_nochange.width() } or now == Point{ image_nochange.height(), image_nochange.width() }){
			visited.clear();
			visited.resize(image_nochange.height(), Array<bool>(image_nochange.width(), false));
			break;
		}
		que.pop();
		for (const Point& delta : dydx) {
			const Point next = now + delta;
			if (is_in_image(next) and (not visited[next.y][next.x])) {	
				if (image_nochange[next] != Palette::Black) {
					visited[next.y][next.x] = true;
					que.push(next);
				}
			}
		}
	}
}

void Paint::paint_visited(const Color &color){
	for (const Point& point : step(image.size())) {
		if (visited[point.y][point.x]) {
			image[point] = color;
		}
	}
}

Optional<Point> Paint::get_mousel_pos_pressed(void) const{
	if (MouseL.down()) {
		return Cursor::Pos();
	}else {
		return none;
	}
}

Optional<Point> Paint::scenepos_to_imagepos(const Point& point) const{
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

void Paint::draw_canpus_rectframe(void) const{
	Rect(Arg::center( texture_center), image.size()).drawFrame(1, 1, Palette::Black);
}

void Paint::draw(void) const {
	texture.drawAt(texture_center);
	draw_canpus_rectframe();
	colorpalette.draw();
}
void Paint::update(void) {
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
		update_texture();
	}
}
