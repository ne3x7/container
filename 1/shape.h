#define LINE 0
#define TRIANGLE 1
#define RECTANGLE 2
#define CIRCLE 3

typedef struct Point {
	int x, y;
} Point;
typedef struct Shape Shape;

Shape * shape_new();
void shape_init(Shape * s, int type);
void shape_initLine(Shape * s, Point start, Point end);
void shape_initColoredLine(Shape * s, Point start, Point end, double color);
void shape_initTriangle(Shape * s, Point a, Point b, Point c);
void shape_initColoredTriangle(Shape * s, Point a, Point b, Point c, double color);
void shape_initRectangle(Shape * s, Point a, Point b, Point c, Point d);
void shape_initColoredRectangle(Shape * s, Point a, Point b, Point c, Point d, double color);
void shape_initCircle(Shape * s, Point center, int radius);
void shape_initColoredCircle(Shape * s, Point center, int radius, double color);
void shape_moveTopLeft(Shape * s, Point to);
void shape_moveCircleCenter(Shape * s, Point to);
void shape_print(Shape * s);
void shape_free(Shape * s);
Point point(int x, int y);