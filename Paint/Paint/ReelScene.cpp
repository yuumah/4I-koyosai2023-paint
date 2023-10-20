# include <Siv3D.hpp> // Siv3D v0.6.12
# include "ReelScene.hpp"

ReelScene::ReelScene(const InitData &init) :IScene( init ) {
	int i = 0;
	for (const String &path : FileSystem::DirectoryContents(U"line_drawing")){
		Texture texture = Texture(path);
		Vec2 point = Vec2{ i++ * (texture.size().x * scaled_rate + texture_blank), Scene::Center().y };
		assert(texture.size() == original_texture_size);
		line_drawings << std::make_pair(Texture(path), point);
		pathes << path;
	}
	move_time_ms += Random(-reel_random_amplitude, reel_random_amplitude);
	reel_length = (original_texture_size.x * scaled_rate + texture_blank) * (line_drawings.size());
}

void ReelScene::update(void) {
	if (not stopwatch.isStarted()) {
		stopwatch.start();
	}
	// イージング一覧 https://easings.net/
	const double move_speed_rate = 1.0 - EaseInOutElastic(Min((double)stopwatch.ms() / move_time_ms, 1.0));
	// イージングに合わせてtextureの中心位置を移動
	for (std::pair<Texture, Vec2> &p : line_drawings) {
		p.second.moveBy(max_move_speed * move_speed_rate * Scene::DeltaTime());
		// 左端まで来たら右端に移動させる
		if (p.second.x < Scene::Center().x - reel_length/2) {
			p.second.x = Scene::Center().x + reel_length/2;
		}
	}
	// リールが止まったら
	if (stopwatch.ms() >= move_time_ms) {
		std::pair<Vec2, int> picked_vec2_idx = {line_drawings[0].second, 0};
		for(int i = 1; i < line_drawings.size(); i++){
			if (Abs(picked_vec2_idx.first.x - Scene::Center().x) > Abs(line_drawings[i].second.x - Scene::Center().x)) {
				picked_vec2_idx = {line_drawings[i].second, i};
			}
		}
		getData().set_path(pathes[picked_vec2_idx.second]);
		System::Sleep(sleep_time);
		changeScene(U"PaintScene", 1.0s);
	}
}

void ReelScene::draw(void) const {
	for (const std::pair<Texture, Vec2> &p : line_drawings) {
		p.first.scaled(scaled_rate).drawAt(p.second);
	}
}



