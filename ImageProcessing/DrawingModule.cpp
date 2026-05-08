#include "DrawingModule.h"
#include <algorithm>


void safeSet(Image& img, int x, int y, unsigned char color) {
	if (x >= 0 && y >= 0 && x < img.width() && y < img.height()) {
		img.at(x, y) = color;
	}
}

/*
void DrawingModule::drawLine(Image& img, Point p1, Point p2, unsigned char color) {
	int y1 = p1.getY(), y2 = p2.getY(), x1 = p1.getX(), x2 = p2.getX();
	float dx = x2 - x1;
	float dy = y2 - y1;

	if (dx == 0) {
		dx = 1;
	}
	
	float m = dy / dx;
	float c = y2 - m * x2;

	if (std::abs(m) < 1) {
		int start = (dx < 0) ? x2 : x1;
		int end = (dx < 0) ? x1 : x2;

		for (int x = start; x < end; ++x) {
			float y = std::round(m * x + c);
			safeSet(img, x, y, color);
		}
	}
	else {
		int start = (dy < 0) ? y2 : y1;
		int end = (dy < 0) ? y1 : y2;

		for (int y = start; y < end; ++y) {
			float x = std::round(-(c - y) / m);
			safeSet(img, x, y, color);
		}
	}
}
*/

void DrawingModule::drawLine(Image& img, Point p1, Point p2, unsigned char color) {
	int x1 = p1.getX(), y1 = p1.getY();
	int x2 = p2.getX(), y2 = p2.getY();

	float dx = x2 - x1;
	float dy = y2 - y1;

	if (dx == 0 && dy == 0) {
		safeSet(img, x1, y1, color);
		return;
	}

	if (dx == 0) dx = 0.00001;

	float m = dy / dx;
	float c = y1 - m * x1;

	if (std::abs(m) <= 1.0f) {
		int start = (x1 < x2) ? x1 : x2;
		int end = (x1 < x2) ? x2 : x1;

		for (int x = start; x <= end; ++x) {
			int y = std::round(m * x + c);
			safeSet(img, x, y, color);
		}
	}
	else {
		int start = (y1 < y2) ? y1 : y2;
		int end = (y1 < y2) ? y2 : y1;

		for (int y = start; y <= end; ++y) {
			int x = std::round((y - c) / m);
			safeSet(img, x, y, color);
		}
	}
}

void DrawingModule::drawCircle(Image& img, Point center, int radius, unsigned char color) {
	int cx = center.getX();
	int cy = center.getY();
	int r2 = radius * radius;

	for (int x = -radius; x <= radius; ++x) {
		int y = std::round(std::sqrt(r2 - x * x));
		safeSet(img, cx + x, cy + y, color);
		safeSet(img, cx + x, cy - y, color);
		safeSet(img, cx - x, cy + y, color);
		safeSet(img, cx - x, cy - y, color);
		safeSet(img, cx + y, cy + x, color);
		safeSet(img, cx + y, cy - x, color);
		safeSet(img, cx - y, cy + x, color);
		safeSet(img, cx - y, cy - x, color);
	}
}

void DrawingModule::drawRectangle(Image& img, Rectangle r, unsigned char color) {
	Point tl(r.getX(), r.getY());
	Point tr(r.getX() + r.getWidth(), r.getY());
	Point bl(r.getX(), r.getY() + r.getHeight());
	Point br(r.getX() + r.getWidth(), r.getY() + r.getHeight());

	drawLine(img, tl, tr, color);
	drawLine(img, tl, bl, color); 
	drawLine(img, tr, br, color); 
	drawLine(img, bl, br, color); 
}

void DrawingModule::drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
	drawRectangle(img, Rectangle(tl.getX(), tl.getY(), br.getX() - tl.getX(), br.getY() - tl.getY()), color);
}







