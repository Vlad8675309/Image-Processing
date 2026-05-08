#include "Image.h"
#include "ImageProcessing.h"
#include "DrawingModule.h"
#include <iostream>
#include <algorithm>


int main() {
	
	Image img1, img2, img3, img4;
	BrightnessContrast bc = BrightnessContrast(100, 100);
	GammaCorrection gc = GammaCorrection(0.6);
	Convolution conv1 = Convolution({ {1, 2, 1}, {2, 4, 2}, {1, 2, 1} }, scaleBlur);
	Convolution conv2 = Convolution({{ 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 }}, scaleSobel);
	bool load = img1.load("img1.ascii.pgm");
	bc.process(img1, img2);
	bool save = img2.save("img2.ascii.pgm");
	load = img1.load("img1.ascii.pgm");
	gc.process(img1, img3);
	save = img3.save("img3.ascii.pgm");
	load = img1.load("img1.ascii.pgm");
	conv2.process(img1, img4);
	save = img4.save("img4.ascii.pgm");
	
	Image draw = Image(300, 300);
	DrawingModule::drawLine(draw, { 100, 100 }, { 400, 160 }, 100); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 50, 160 }, 5); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 160, 400 }, 100); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 400, 60 }, 100); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 150, 0 }, 100); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 50, 0 }, 100); 
	DrawingModule::drawLine(draw, { 100, 100 }, { 0, 50 }, 100); 



	DrawingModule::drawCircle(draw, { 10, 10 }, 50, 50);
	DrawingModule::drawRectangle(draw, Rectangle(250, 250, 100, 200), 20);
	DrawingModule::drawRectangle(draw, Point(275, 275), Point(350, 350), 10);
	DrawingModule::drawRectangle(draw, Rectangle(50, 50, 150, 200), 20);
	DrawingModule::drawCircle(draw, { 150, 150 }, 50, 50);

	save = draw.save("draw2.ascii.pgm");
	
	Image draw2 = Image(300, 300);

	return 0;
}