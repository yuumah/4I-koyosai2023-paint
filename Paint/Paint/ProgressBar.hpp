# pragma once
# include <Siv3D.hpp>
# include "Data.hpp"

class ProgressBar {
public:
	/// @brief プログレスバーの座標を大きさを指定
	/// @param p 四角形の左上の大きさ
	/// @param height 縦方向の長さ
	/// @param length 横方向の最大長
	ProgressBar(const Point p, const int height, const int length);

	void draw(const double &percentage);
	void draw(const double &numerator, const double &denominator);
	void draw_monochrome(const double &percentage);
	void draw_monochrome(const double &numerator, const double &demominator);
	void set_color_background(const Color &color_background);
private:
	// プログレスバーの高さと長さ(最大値)
	int length = 0;
	int height = 0;
	// 左上の座標
	Point leftup;
	// プログレスバーの四角形
	Rect rect;
	// プログレスバーの背景色
	Color color_background = Palette::Gray;
	// thresholdsの閾値で表示する色
	Array<Color> colors = { Palette::Green, Palette::Yellow, Palette::Red, Palette::Black };
	Array<double> thresholds = { 1.000, 0.667, 0.333, 0.100, 0.000 };
};
