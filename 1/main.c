#include "shape.h"

int main (int argc, char * argv[]) {
	Shape * shape = shape_new();

	shape_print(shape);
	shape_init(shape, TRIANGLE);
	shape_print(shape);
	shape_initRectangle(shape, point(0, 0), point(2, 2), point(0, 2), point(2, 0));
	shape_print(shape);
	shape_setColor(shape, "white");
	shape_print(shape);
	shape_initCircle(shape, point(0, 0), 1);
	shape_print(shape);
	shape_moveCircleCenter(shape, point(2, 2));
	shape_print(shape);
	shape_free(shape);
}