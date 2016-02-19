#include "shape.h"

#include <stdio.h>
#include <stdlib.h>

struct Shape {
	int num;
	int type;
	int radius;
	Point * points;
	char * color;
};

Shape * shape_new() {
	Shape * s = malloc(sizeof(Shape));
	Point a, b;
	a.x = 0;
	a.y = 0;
	b.x = 1;
	b.y = 1;
	s->num = 2;
	s->type = LINE;
	s->radius = 0;
	s->points = malloc(2 * sizeof(Point));
	s->points[0] = a;
	s->points[1] = b;
	s->color = "black";
};
void shape_init(Shape * s, int type) {
	s = malloc(sizeof(Shape));

	if (type == LINE) {
		Point a, b;
		a.x = 0;
		a.y = 0;
		b.x = 1;
		b.y = 1;
		shape_initLine(s, a, b);
	} else if (type == TRIANGLE) {
		Point a, b, c;
		a.x = 0;
		a.y = 0;
		b.x = 1;
		b.y = 1;
		c.x = 0;
		c.y = 1;
		shape_initTriangle(s, a, b, c);
	} else if (type == RECTANGLE) {
		Point a, b, c, d;
		a.x = 0;
		a.y = 0;
		b.x = 1;
		b.y = 1;
		c.x = 0;
		c.y = 1;
		d.x = 1;
		d.y = 0;
		shape_initRectangle(s, a, b, c, d);
	} else if (type == CIRCLE) {
		Point center;
		center.x = 0;
		center.y = 0;
		shape_initCircle(s, center, 1);
	}
};
void shape_initLine(Shape * s, Point start, Point end) {
	s->type = LINE;
	s->num = 2;
	s->radius = 0;
	s->points[0] = start;
	s->points[1] = end;
	s->color = "black";
};
void shape_initTriangle(Shape * s, Point a, Point b, Point c) {
	s->type = TRIANGLE;
	s->num = 3;
	s->radius = 0;
	s->points = realloc(s->points, 3);
	s->points[0] = a;
	s->points[1] = b;
	s->points[2] = c;
	s->color = "black";
};
void shape_initRectangle(Shape * s, Point a, Point b, Point c, Point d) {
	s->type = RECTANGLE;
	s->num = 4;
	s->radius = 0;
	s->points = realloc(s->points, 4);
	s->points[0] = a;
	s->points[1] = b;
	s->points[2] = c;
	s->points[3] = d;
	s->color = "black";
};
void shape_initCircle(Shape * s, Point center, int radius) {
	s->type = CIRCLE;
	s->num = 1;
	s->radius = radius;
	s->points = realloc(s->points, 1);
	s->points[0] = center;
	s->color = "black";
};
void shape_setColor(Shape * s, char * color) {
	s->color = color;
}
void shape_setRadius(Shape * s, int radius) {
	if (s->type == CIRCLE)
		s->radius = radius;
	else printf("Only for circles\n");
}
void shape_moveCircleCenter(Shape * s, Point to) {
	if (s->type == CIRCLE)
		s->points[0] = to;
	else printf("Only for circles\n");
};
void shape_print(Shape * s) {
	printf("Shape ");
	switch (s->type) {
		case LINE:
			printf("line\n");
			break;
		case TRIANGLE:
			printf("triangle\n");
			break;
		case RECTANGLE:
			printf("rectangle\n");
			break;
		case CIRCLE:
			printf("circle with radius = %d\n", s->radius);
			break;
	}
	printf("Top left at x = %d, y = %d\n", s->points[0].x, s->points[0].y);
	printf("Color %s\n", s->color);
};
void shape_free(Shape * s) {
	free(s);
};
Point point(int x, int y) {
	Point p;
	p.x = x;
	p.y = y;
};