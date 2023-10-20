# pragma once
# include <Siv3D.hpp>
# include "ProgressBar.hpp"
# include "Data.hpp"


ProgressBar::ProgressBar(const Point p, const int height, const int length) {
	assert(colors.size() + 1 == thresholds.size());
	rect = Rect(p, length, height);
	this->leftup = p;
	this->height = height;
	this->length = length;
}

void ProgressBar::set_color_background(const Color& color_background) {
	this->color_background = color_background;
}

void ProgressBar::draw(const double& percentage) {
	double tmp_percentage = percentage;
	tmp_percentage = Min(tmp_percentage, 1.0);
	rect.draw(color_background);
	for (int i = 0; i < (int)colors.size(); i++) {
		if (thresholds[i + 1] < tmp_percentage and tmp_percentage <= thresholds[i]) {
			rect.scaledAt(leftup, tmp_percentage, 1.0).draw(colors[i]);
			break;
		}
	}
}
void ProgressBar::draw(const double& numerator, const double& denominator) {
	this->draw(numerator / denominator);
}
void ProgressBar::draw_monochrome(const double &percentage){
	double tmp_percentage = percentage;
	tmp_percentage = Min(tmp_percentage, 1.0);
	rect.draw(to_monochrome(color_background));
	for (int i = 0; i < (int)colors.size(); i++) {
		if (thresholds[i + 1] < tmp_percentage and tmp_percentage <= thresholds[i]) {
			rect.scaledAt(leftup, tmp_percentage, 1.0).draw(to_monochrome(colors[i]));
			break;
		}
	}
}
void ProgressBar::draw_monochrome(const double &numerator, const double &demominator){
	this->draw_monochrome(numerator / demominator);
}



