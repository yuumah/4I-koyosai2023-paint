# include <Siv3D.hpp> // Siv3D v0.6.12
# include "ReelScene.hpp"

ReelScene::ReelScene(const InitData &init) :IScene( init ) {
	const CSV csv{ U"line_drawing.csv" };
	if (not csv) {
		throw Error{ U"Failed to load `line_drawing.csv`" };
	}
	HashTable<String, double> weight_table;
	for (int i = 0; i < (int)csv.rows(); i++) {
		assert(csv[i].size() == 2);
		weight_table[csv[i][0]] = Parse<double>(csv[i][1]);
	}
	Array<std::pair<int, int>> image_type_range;
	Array<double> weights;
	int index = 0;
	for (const String &directory : FileSystem::DirectoryContents(U"line_drawing", Recursive::No)) {
		if(!FileSystem::IsDirectory(directory)) continue;

		const String image_type = FileSystem::FileName(directory);
		const int cur = index;
		for (const String &path : FileSystem::DirectoryContents(directory)) {
			const Texture texture = Texture(path);
			const Vec2 point(index * (texture.size().x * scaled_rate + texture_blank), Scene::Center().y);
			assert(texture.size() == original_texture_size);
			line_drawings.emplace_back(texture, path, point, image_type, index);
			index++;
		}
		weights.push_back(weight_table[image_type]);
		image_type_range.emplace_back(cur, index);
	}
	reel_length = (original_texture_size.x * scaled_rate + texture_blank) * line_drawings.size();
	// 開始位置をランダムに調整
	DiscreteDistribution distribution(weights);
	const std::pair<int,int> range = DiscreteSample(image_type_range, distribution);
	const LineDrawing selected_drawing = line_drawings[Random(range.first, range.second-1)];
	getData().set_path(selected_drawing.path);
	getData().set_image_type(selected_drawing.type);
	//Print << U"selected: " << selected_drawing.type << U" " << selected_drawing.index;
	const int start_pos = selected_drawing.index + ((int)line_drawings.size() - 17 % (int)line_drawings.size());
	for (LineDrawing &p : line_drawings) {
		p.pos.moveBy(Vec2((-start_pos * (p.texture.size().x * scaled_rate + texture_blank)) + 50, 0));
		// 左端まで来たら右端に移動させる
		while (p.pos.x < Scene::Center().x - reel_length / 2) {
			p.pos.x += reel_length;
		}
	}
}

void ReelScene::update(void) {
	if (not stopwatch.isStarted()) {
		stopwatch.start();
	}
	// イージング一覧 https://easings.net/
	const double move_speed_rate = 1.0 - easing(Min((double)stopwatch.ms() / move_time_ms, 1.0));
	// イージングに合わせてtextureの中心位置を移動
	for (LineDrawing &p : line_drawings) {
		p.pos.moveBy(max_move_speed * move_speed_rate * Scene::DeltaTime());
		// 左端まで来たら右端に移動させる
		if (p.pos.x < Scene::Center().x - reel_length/2) {
			p.pos.x += reel_length;
		}
		if (p.pos.x > Scene::Center().x + reel_length / 2) {
			p.pos.x -= reel_length;
		}
	}
	// リールが止まったら
	if (stopwatch.ms() >= move_time_ms) {
		std::pair<Vec2, int> picked_vec2_idx = {line_drawings[0].pos, 0};
		for(int i = 1; i < line_drawings.size(); i++){
			if (Abs(picked_vec2_idx.first.x - Scene::Center().x) > Abs(line_drawings[i].pos.x - Scene::Center().x)) {
				picked_vec2_idx = {line_drawings[i].pos, i};
			}
		}
		System::Sleep(sleep_time);
		changeScene(U"PaintScene", 1.0s);
	}
}

void ReelScene::draw(void) const {
	for (const LineDrawing &p : line_drawings) {
		p.texture.scaled(scaled_rate).drawAt(p.pos);
	}
}

// https://easings.net/ja#easeInOutElastic
double ReelScene::easing(const double &t){
	const double c = (2 * Math::Pi) / 4.5;
	if (t == 0) {
		return 0;
	}else if (t == 1) {
		return 1;
	}else if(t < 0.5){
		return -(Math::Pow(2, 20 * t - 10) * Math::Sin((20 * t - 11.125) * c)) / 2;
	}else{
		return (Math::Pow(2, -20 * t + 10) * Math::Sin((20 * t - 11.125) * c)) / 2 + 1;
	}
}


