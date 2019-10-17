#include "rectangle.h"

RectangleRegion::RectangleRegion(int x, int y, int width, int height):x(x),y(y),width(width), height(height) {
}

Mat RectangleRegion::computeFeature(Mat ii) {
	return ii;
}