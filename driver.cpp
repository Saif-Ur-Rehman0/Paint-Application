/*
 * CSE/ENGR 142 GP142_Demo
 *
 * 1/25/95
 * Author(s):         Larry Ruzzo
 * Email Address(s):  ruzzo@cs.washington.edu
 *
 * This program is a demo of some of the features of 
 * GP142 --- the CSE/ENGR 142 Graphics Package.
 * It includes simple drawing commands, keyboard and mouse 
 * interaction, and a simple animation.
 *
 * Revision history:
 * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
 *      
 */
#include "GP142.h"
#include <stdio.h>
#include <conio.h>
#include <vector> 
#include <math.h>
#include<cmath>
#include <stdbool.h>
#include<Windows.h>
#include<typeinfo>
#include<vector>
#include<fstream>
#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20
using namespace std;
//You will use the following 5 functions do to all work
//A) DRAWING FUNCTIONS
//the two drawing functions that you will use to make all shapes
struct point {
	double x;
	double y;
};
void draw_line(int x1, int y1, int x2, int y2, int color=WHITE, int width=1){
	GP142_lineXY (color,x1,y1,x2,y2,width);
}
void draw_circle(int x, int y, int radius, int color=WHITE){
	 GP142_circleXY(color, x, y, radius);
}
void draw_rectangle(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {
	GP142_rectangleXY(color, x1, y1, x2, y2, width);
}
void draw_triangle(int x1, int y1, int x2, int y2,int x3,int y3, int color = WHITE, int width = 1) {
	GP142_triangleXY(color, x1, y1, x2, y2, x3, y3, width);
}
void draw_oval(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {
	GP142_ovalXY(color, x1, y1, x2, y2, width);
}
void draw_polygon(int points[], int noofpoints, int color = WHITE, int width = 1) {
	int i = 0;
	for (; i < (noofpoints * 2) - 2; i = i + 2) {
		draw_line(points[i], points[i + 1], points[i + 2], points[i + 3], color,width);
	}
	draw_line(points[0], points[1], points[i], points[i + 1], color, width);
}
void draw_curve(int points[], int noofpoints, int color = WHITE, int width = 1) {
	int i = 0;
	for (; i < (noofpoints * 2) - 2; i = i + 2) {
		draw_line(points[i], points[i + 1], points[i + 2], points[i + 3], color, width);
	}
}
void draw_doted_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) {
	int  x, y, dx, dy, i, e;
	float xinc, yinc;
	dx = x2 - x1;
	dy = y2 - y1;
	if (x1 < x2)
		xinc = 1;
	else
		xinc = -1;
	if (y1 < y2)
		yinc = 1;
	else
		yinc = -1;
	x = x1;
	y = y1;
	if (dx >= dy)
	{
		e = (2 * dy) - dx;
		while (x != x2)
		{
			if (e < 0)
				e = e + (2 * dy);
			else
			{
				e = e + (2 * (dy - dx));
				y = y + yinc;
				y = y + yinc;
			}
			x = x + xinc;
			x = x + xinc;
			GP142_pixelXY(color, x, y);
		}
	}
	else
	{
		e = (2 * dx) - dy;
		while (y != y2)
		{
			if (e < 0)
				e = e + (2 * dx);
			else
			{
				e = e + (2 * (dx - dy));
				x = x + xinc;
				x = x + xinc;
			}
			y = y + yinc;
			y = y + yinc;
			GP142_pixelXY(color, x, y);
		}
	}
}
void draw_dotted_curve(int points[], int noofpoints, int color = WHITE, int width = 1) {
	int i = 0;
	for (; i < (noofpoints * 2) - 2; i = i + 2) {
		draw_doted_line(points[i], points[i + 1], points[i + 2], points[i + 3], color, width);
	}
}
void draw_text(int x, int y, int color = WHITE) {
	char str[100];
	scanf(str);
	GP142_textXY(color, x, y, TEXT_SIZE, str);
}
void fillcolor(int x1, int y1, int x2, int y2, int color = WHITE) {
	if (x1 < x2) {
		for (int i = x1 + 1; i < x2; i++) {
			if (y1 < y2) {
				for (int j = y1 + 1; j < y2; j++) {
					GP142_pixelXY(color, i, j);
				}
			}
			else if (y1 > y2) {
				for (int j = y2 + 1; j < y1; j++) {
					GP142_pixelXY(color, i, j);
				}
			}
		}
	}
	else if (x1 > x2) {
		for (int i = x2 + 1; i < x1; i++) {
			if (y1 < y2) {
				for (int j = y1 + 1; j < y2; j++) {
					GP142_pixelXY(color, i, j);
				}
			}
			else if (y1 > y2) {
				for (int j = y2 + 1; j < y1; j++) {
					GP142_pixelXY(color, i, j);
				}
			}
		}
	}
	else
		GP142_pixelXY(color, x1, y2);
}
void side_bar(int color=WHITE) {
	draw_rectangle(490, 360, 430, 330, color);
	GP142_printfXY(color, 438, 332, TEXT_SIZE, "Save");
	draw_rectangle(490, 330, 430, 300, color);
	GP142_printfXY(color, 440, 302, TEXT_SIZE, "load");

	draw_rectangle(-490, 360, -460, 330, color);
	GP142_printfXY(color, -480, 333, TEXT_SIZE, "/");
	draw_rectangle(-490, 330, -460, 300, color);
	GP142_printfXY(color, -482, 303, TEXT_SIZE, "O");
	draw_rectangle(-490, 300, -460, 270, color);
	draw_rectangle(-482, 292, -468, 278, color,2);
	draw_rectangle(-490, 270, -460, 240, color);
	draw_triangle(-475, 265,-482, 248, -468, 248, color,2);
	draw_rectangle(-490, 240, -460, 210, color);
	int points[] = { -475, 235,-485,225,-482, 218, -468, 218,-465,225 };
	draw_polygon(points, 5, color,2);
	draw_rectangle(-490, 210, -460, 180, color);
	int point[] = { -465,205,-480,198,-470,192,-485,185 };
	draw_curve(point, 4, color,2);
	draw_rectangle(-490, 180, -460, 150, color);
	GP142_printfXY(color, -481, 153, TEXT_SIZE, "T");
	draw_rectangle(-490, 150, -460, 120, color);
	draw_doted_line(-485, 125, -465, 145, color);
	draw_rectangle(-490, 120, -460, 90, color);
	for (int i = 0; i < 8; i++) {
		if (i == 1)
			point[i] = 115;
		if (i == 3)
			point[i] = 112;
		if (i == 5)
			point[i] = 102;
		if (i == 7)
			point[i] = 95;
	}
	draw_curve(point, 4, color, 2);

	draw_rectangle(-460, 360, -430, 330, color);
	fillcolor(-460, 360, -430, 330, WHITE);
	draw_rectangle(-460, 330, -430, 300, color);
	fillcolor(-460, 330, -430, 300, RED);
	draw_rectangle(-460, 300, -430, 270, color);
	fillcolor(-460, 300, -430, 270, BLUE);
	draw_rectangle(-460, 270, -430, 240, color);
	fillcolor(-460, 270, -430, 240, BLACK);
	draw_rectangle(-460, 240, -430, 210, color);
	fillcolor(-460, 240, -430, 210, YELLOW);
	draw_rectangle(-460, 210, -430, 180, color);
	fillcolor(-460, 210, -430, 180, ORANGE);
	draw_rectangle(-460, 180, -430, 150, color);
	fillcolor(-460, 180, -430, 150, GREEN);

	draw_rectangle(-430, 360, -400, 330, color);
	GP142_printfXY(color, -421, 333, TEXT_SIZE, "E");
	draw_rectangle(-430, 330, -400, 300, color);
	GP142_printfXY(color, -421, 303, TEXT_SIZE, "F");
}
int colorpick(int x, int y) {
	if (x > -460 && x < -430 && y>330 && y < 360)
		return WHITE;
	if (x > -460 && x < -430 && y>300 && y < 330)
		return RED;
	if (x > -460 && x < -430 && y>270 && y < 300)
		return BLUE;
	if (x > -460 && x < -430 && y>240 && y < 270)
		return BLACK;
	if (x > -460 && x < -430 && y>210 && y < 240)
		return YELLOW;
	if (x > -460 && x < -430 && y>180 && y < 210)
		return ORANGE;
	if (x > -460 && x < -430 && y>150 && y < 180)
		return GREEN;
}
void eraser() {
	GP142_clear();
	side_bar(BLACK);
}

char mouseclick(int x, int y) {
	if (x > -490 && x < -460) {
		if (y > 330 && y < 360) {
			return 'L';
		}
		else if (y > 300 && y < 330) {
			return 'C';
		}
		else if (y > 270 && y < 300) {
			return 'R';
		}
		else if (y > 240 && y < 270) {
			return 'T';
		}
		else if (y > 210 && y < 240) {
			return 'P';
		}
		else if (y > 180 && y < 210) {
			return '/';
		}
		else if (y > 150 && y < 180) {
			return 't';
		}
		else if (y > 120 && y < 150) {
			return 'k';
		}
		else if (y > 90 && y < 120) {
			return 'j';
		}
	}
}
//B) EVENT HANDLERS
//Mouse handler
void handle_mouse(int x, int y){
	GP142_printfXY(YELLOW, x, y, 9, "Mouse at (%d,%d)", x, y);
}
//Keyboard handler
void handle_kbd(char c, int x = 0, int y = 0,int color=WHITE){
	//put the character anywhere you want to.
	//I'm putting it on the origin
	GP142_printfXY(color, x, y, TEXT_SIZE, "%c", c);
}
//periodic handler you will not need to use because we're not doing animation
void demo_handle_periodic(void){};

class shape {
protected:
	int *points;
	int no_of_points;
	int color;
public:
	shape() {
		points = nullptr;
		no_of_points = 0;
		color = 0;
	}
	shape(int *point, int noofpoints, int colour = 0) {
		points = new int[noofpoints * 2];
		for (int i = 0; i < noofpoints * 2; i++) {
			points[i] = point[i];
		}
		no_of_points = noofpoints;
		color = colour;
	}
	shape(const shape&obj) {
		points = new int[obj.no_of_points * 2];
		for (int i = 0; i < obj.no_of_points * 2; i++) {
			points[i] = obj.points[i];
		}
		no_of_points = obj.no_of_points;
		color = obj.color;
	}
	const shape &operator=(const shape &obj) {
		points = new int[obj.no_of_points * 2];
		for (int i = 0; i < obj.no_of_points * 2; i++) {
			points[i] = obj.points[i];
		}
		no_of_points = obj.no_of_points;
		color = obj.color;
		return *this;
	}
	void seriallize(string fname){
		ofstream ofile(fname, ios::binary);
		ofile.write((char*)this, sizeof(*this));
		ofile.close();
	}
	void unserialize(string fname) {
		ifstream ifile(fname, ios::binary);
		ifile.read((char*)this, sizeof(*this));
		ifile.close();
	}
	virtual void draw() = 0;
	virtual bool contains(point p) = 0;
	~shape() {
		if (points != nullptr)
			delete[]points;
	}
};
class openshape :public shape {
protected:
	bool style;
public:
	openshape() {
		style = false;
	}
	openshape(bool sty,int *point,int noofpoints,int colour):shape(point,noofpoints,colour) {
		style = sty;
	}
	const openshape&operator=(const openshape&obj) {
		shape::operator=(obj);
		style = obj.style;
		return *this;
	}
	virtual void changestyle() = 0;
};
class line :public openshape {
public:
	line() {
		style = false;
		points = nullptr;
		no_of_points = 0;
		color = WHITE;
	}
	line(bool st, int *point, int noofpoints, int colour) :openshape(st, point, noofpoints, colour) {

	}
	void set_points(bool st, int *point, int noofpoints, int color) {
		style = false;
		no_of_points = noofpoints;
		points = new int[no_of_points * 2];
		for (int i = 0; i < no_of_points * 2; i++) {
			points[i] = point[i];
		}
		color = WHITE;
	}
	const line&operator=(const line&obj) {
		shape::operator=(obj);
		style = obj.style;
		return *this;
	}
	void draw() {
		if (style == false) {
			draw_line(points[0], points[1], points[2], points[3], color);
		}
		else {
			draw_doted_line(points[0], points[1], points[2], points[3], color);
		}
	}
	bool contains(point p) {
		int m = (points[3] - points[1]) / (points[2] - points[0]);
		int left = p.y - points[1];
		int right = m * (p.x - points[0]);
		if (left == right) {
			return true;
		}
		else
			return false;
	}
	bool getstyle() {
		return style;
	}
	void setstyle(bool sty) {
		style = sty;
	}
	void changecolor(int colour) {
		color = colour;
		draw();
	}
	void changestyle() {
		if (style == true) {
			style = false;
		}
		else if (style == false) {
			style = true;
		}
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
};
class polygon :public shape {
protected:
	int fillcolor;
public:
	polygon() {
		fillcolor = 0;
	}
	polygon(int *point, int noofpoints, int colour) :shape(point, noofpoints, colour) {

	}
	const polygon&operator=(const polygon&obj) {
		shape::operator=(obj);
		fillcolor = obj.fillcolor;
		return *this;
	}
	void draw() {
		draw_polygon(points, no_of_points, color);
	}
	bool intersect(point p) {
		line l(false, points, 2, color);
		int *point = new int[4];
		int i = 0;
		for (; i < ((no_of_points-1) * 2) - 2; i = i + 2) {
			point[0] = points[i];
			point[1] = points[i + 1];
			point[2] = points[i + 2];
			point[3] = points[i + 3];
			l.set_points(false, point, 2, color);
			if (l.contains(p)) {
				return true;
			}
		}
		i = i + 2;
		point[0] = points[0];
		point[1] = points[1];
		point[2] = points[i];
		point[3] = points[i + 1];
		l.set_points(false, point, 2, color);
		if (l.contains(p)) {
			return true;
		}
		else {
			return false;
		}
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
	bool contains(point p) {
		point p1;
		p1.y = p.y;
		int count = 0;
		for (int i = p.x; i < 500; i++) {
			p1.x = i;
			if (intersect(p1))
				count++;
		}
		if (count % 2 != 0) {
			return true;
		}
		return false;
	}
	void fill(int colour) {
		fillcolor = colour;
	}
};
class circle :public shape {
	int fillcolor;
	int radius;
public:
	circle() {
		radius = 0;
	}
	circle(int *pts, int rad,int colour) :shape(pts, 2, colour) {
		radius = sqrt(pow((points[2] - points[0]), 2) + pow((points[3] - points[1]), 2));
	}
	void set_rad(int rad) {
		radius = rad;
	}
	int get_rad() {
		return radius;
	}
	void draw() {
		draw_circle(points[0], points[1], radius, color);
	}
	const circle&operator=(const circle&obj) {
		shape::operator=(obj);
		fillcolor = obj.fillcolor;
		radius = obj.radius;
		return *this;
	}
	bool contains(point p) {
		int x = p.x - points[0];
		int y = p.y - points[1];
		x = pow(x, 2);
		y = pow(y, 2);
		int left = x + y;
		left = sqrt(left);
		int right = radius;
		if (left < right) {
			return true;
		}
		return false;
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
	void fill(int colour) {
		int x3 = 2 * points[0] - points[2];
		int y3 = 2 * points[1] - points[3];
	}
};
class triangle :public shape {
	int fillcolor;
public:
	triangle() {

	}
	triangle(int *pts, int colour) :shape(pts, 3, colour) {

	}
	void draw() {
		draw_triangle(points[0], points[1], points[2], points[3], points[4], points[5], color);
	}
	const triangle&operator=(const triangle&obj) {
		shape::operator=(obj);
		fillcolor = obj.fillcolor;
		return*this;
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
	float sign(point p1, point p2, point p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}
	bool contains(point p) {
		point p1;
		p1.x = points[0];
		p1.y = points[1];
		point p2;
		p2.x = points[2];
		p2.y = points[3];
		point p3;
		p3.x = points[4];
		p3.y = points[5];
		float d1, d2, d3;
		bool left, right;
		d1 = sign(p, p1, p2);
		d2 = sign(p, p2, p3);
		d3 = sign(p, p3, p1);
		left = (d1 < 0) || (d2 < 0) || (d3 < 0);
		right = (d1 > 0) || (d2 > 0) || (d3 > 0);
		if (left == true && right == true) {
			return false;
		}
		return true;
	}
	void fill(int colour) {
		int x1 = points[0];
		int x2 = points[2];
		int y1 = points[1];
		int y2 = points[3];
		if (x1 < x2) {
			for (int i = x1 + 1; i < x2; i++) {
				if (y1 < y2) {
					for (int j = y1 + 1; j < y2; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
				else if (y1 > y2) {
					for (int j = y2 + 1; j < y1; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
			}
		}
		else if (x1 > x2) {
			for (int i = x2 + 1; i < x1; i++) {
				if (y1 < y2) {
					for (int j = y1 + 1; j < y2; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
				else if (y1 > y2) {
					for (int j = y2 + 1; j < y1; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
			}
		}
		else
			GP142_pixelXY(color, x1, y2);
	}
};
class text :public shape {
	char*word;
public:
	text() {
		word = nullptr;
	}
	void draw() {

	}
	void contains(int *point) {

	}
	void changecolor() {

	}
	~text() {
		if (word != nullptr)
			delete[]word;
	}
};
class curve :public openshape {
public:
	curve() {

	}
	curve(bool st, int *point, int noofpoints, int colour) :openshape(st, point, noofpoints, colour) {

	}
	void draw() {
		int *point = new int[no_of_points * 2];
		for (int i = 0; i < no_of_points * 2; i++) {
			point[i] = points[i];
		}
		if (style == false) {
			draw_curve(point, no_of_points, color);
		}
		else {
			draw_dotted_curve(point, no_of_points, color);
		}
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
	bool contains(point p) {
		int m,left,right;
		for (int i = 0; i < (no_of_points * 2) - 2; i = i + 2) {
			m = (points[i + 3] - points[i + 1]) / (points[i + 2] - points[i]);
			left = p.y - points[i + 1];
			right = m * (p.x - points[i]);
			if (left == right) {
				return true;
			}
		}
		return false;
	}
	const curve&operator=(const curve&obj) {
		openshape::operator=(obj);
		return *this;
	}
	void changecolor(int colour) {
		color = colour;
		draw();
	}
	void changestyle() {
		if (style == true) {
			style = false;
			draw_line(points[0], points[1], points[2], points[3], color);
		}
		else if (style == false) {
			style = true;
			draw_doted_line(points[0], points[1], points[2], points[3], color);
		}
	}
};
class rectangle :public polygon {
public:
	rectangle() {

	}
	rectangle(int *point, int noofpoints, int color) :polygon(point, noofpoints, color) {

	}
	bool contains(point p) {
		if (points[0] < points[2]) {
			if (points[1] < points[3]) {
				if (p.x<points[2] && p.x>points[0] && p.y<points[3] && p.y>points[1])
					return true;
			}
			else {
				if (p.x<points[2] && p.x>points[0] && p.y > points[3] && p.y < points[1])
					return true;
			}
		}
		else {
			if (points[1] < points[3]) {
				if (p.x >= points[2] && p.x <= points[0] && p.y < points[3] && p.y > points[1])
					return true;
			}
			else {
				if (p.x >= points[2] && p.x <= points[0] && p.y > points[3] && p.y < points[1])
					return true;
			}
		}
		return false;
	}
	const rectangle&operator=(const rectangle &obj) {
		polygon::operator=(obj);
		return *this;
	}
	void fill(int colour) {
		int x1 = points[0];
		int x2 = points[2];
		int y1 = points[1];
		int y2 = points[3];
		if (x1 < x2) {
			for (int i = x1 + 1; i < x2; i++) {
				if (y1 < y2) {
					for (int j = y1 + 1; j < y2; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
				else if (y1 > y2) {
					for (int j = y2 + 1; j < y1; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
			}
		}
		else if (x1 > x2) {
			for (int i = x2 + 1; i < x1; i++) {
				if (y1 < y2) {
					for (int j = y1 + 1; j < y2; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
				else if (y1 > y2) {
					for (int j = y2 + 1; j < y1; j++) {
						GP142_pixelXY(color, i, j);
					}
				}
			}
		}
		else
			GP142_pixelXY(color, x1, y2);
	}
	void draw() {
		draw_rectangle(points[0], points[1], points[2], points[3], color);
	}
	void erase(int colour) {
		int temp = color;
		color = colour;
		draw();
		color = temp;
	}
};
void assign(shape*& s1, shape*&s2) {
	if (strcmp(typeid(*s2).name(), "class line") == 0) {
		line *l = dynamic_cast<line*>(s2);
		s1 = new line;
		*s1 = *l;
		l = dynamic_cast<line*>(s1);
		line*l1 = dynamic_cast<line*>(s2);
		l->setstyle(l1->getstyle());
	}
	if (strcmp(typeid(*s2).name(), "class circle") == 0) {
		circle *c = dynamic_cast<circle*>(s2);
		s1 = new circle;
		*s1 = *c;
		c = dynamic_cast<circle*>(s1);
		circle*c1 = dynamic_cast<circle*>(s2);
		c->set_rad(c1->get_rad());
	}
	if (strcmp(typeid(*s2).name(), "class rectangle") == 0) {
		rectangle *r = dynamic_cast<rectangle*>(s2);
		s1 = new rectangle;
		*s1 = *r;
	}
	if (strcmp(typeid(*s2).name(), "class curve") == 0) {
		curve *c = dynamic_cast<curve*>(s2);
		s1 = new curve;
		*s1 = *c;
	}
	if (strcmp(typeid(*s2).name(), "class triangle") == 0) {
		triangle *t = dynamic_cast<triangle*>(s2);
		s1 = new triangle;
		*s1 = *t;
	}
	if (strcmp(typeid(*s2).name(), "class polygon") == 0) {
		polygon *p = dynamic_cast<polygon*>(s2);
		s1 = new polygon;
		*s1 = *p;
	}
}
void reduceshape(shape**&allshapes, int &size, int &cap,int index) {
	if (allshapes == nullptr||size==0) {
		return;
	}
	else if ((size - 1) > cap / 2) {
		shape**temp=new shape*[cap];
		int i = 0;
		for (; i != index; i++) {
			assign(temp[i], allshapes[i]);
		}
		int j = i;
		i++;
		for (; i < size; i++) {
			assign(temp[j], allshapes[i]);
		}
		size--;
		delete[]allshapes;
		allshapes = temp;
		temp = nullptr;

	}
	else if ((size - 1) <= cap / 2) {
		shape**temp = new shape*[cap/2];
		int i = 0;
		for (; i != index; i++) {
			assign(temp[i], allshapes[i]);
		}
		int j = i;
		i++;
		for (; i < size; i++) {
			assign(temp[j], allshapes[i]);
		}
		size--;
		cap = cap / 2;
		delete[]allshapes;
		allshapes = temp;
		temp = nullptr;
	}
}
void erasertool(shape**&allshapes,int &size,int &cap,point p) {
	HDC a;
	int color;
	for (int i = 0; i < size; i++) {
		if (allshapes[i][0].contains(p)) {
			color = GetPixel(a, p.x, p.y);
			color = WHITE;
			if (strcmp(typeid(allshapes[i][0]).name(), "class line") == 0) {
				line *l = dynamic_cast<line*>(allshapes[i]);
				l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class circle") == 0) {
				circle *l = dynamic_cast<circle*>(allshapes[i]);
				l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class rectangle") == 0) {
				rectangle *l = dynamic_cast<rectangle*>(allshapes[i]);
				l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class polygon") == 0) {
				polygon *l = dynamic_cast<polygon*>(allshapes[i]);
				l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class curve") == 0) {
				curve *l = dynamic_cast<curve*>(allshapes[i]);
				l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class triangle") == 0) {
				triangle *l = dynamic_cast<triangle*>(allshapes[i]);
				l->erase(color);
			}
			reduceshape(allshapes, size, cap, i);
		}
	}
}
/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is 
 * relegated to sub-functions, so that the structure of main stays clear and 
 * simple.
 *
 */


void add_shape(shape**&allshapes, int &size, int &cap,shape* Shape) {
	if (size == 0 && cap == 0) {
		allshapes= new shape*;
		assign(allshapes[0],Shape);
		size++; cap++;
	}
	else if (size < cap) {
		assign(allshapes[size], Shape);
		size++;
	}
	else {
		shape**temp = new shape*[cap * 2];
		for (int i = 0; i < cap; i++) {
			assign(temp[i], allshapes[i]);
		}
		assign(temp[size], Shape);
		delete[]allshapes;
		allshapes = temp;
		temp = nullptr;
		size++;
		cap = cap * 2;
	}
}
void saveinfile(vector<int*>a) {
	ofstream fout("C:\\Users\\Saif Ur Rehman\\Desktop\\paint.txt");
	if (!fout.fail()) {
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < 2; j++) {
				fout << a[i][j];
			}
			fout << endl;
		}
	}
	fout.close();
}
void fload_fill(point p,int color) {
	HDC a;
	COLORREF col = BLUE;
	FloodFill(a, p.x, p.y, col);
	

}
void fillscreen(int color,point p) {
	HDC a;
	int col = GetPixel(a, p.x, p.y);
	int colr;
	for (int i = -500; i < 500; i++) {
		for (int j = -370; j < 370; j++) {
			colr = GetPixel(a, i, j);
			if (colr == col) {
				GP142_pixelXY(color, i, j);
			}
			else
				break;
		}
	}
	/*
	for (int i = 500; i > -500; i--) {
		for (int j = -370; j < 370; j++) {
			colr = GetPixel(a, i, j);
			if (colr == col) {
				GP142_pixelXY(color, i, j);
			}
		}
	}
	for (int i = -500; i < 500; i++) {
		for (int j = 370; j > -370; j--) {
			colr = GetPixel(a, i, j);
			if (colr == col) {
				GP142_pixelXY(color, i, j);
			}
		}
	}
	for (int i = 500; i > -500; i--) {
		for (int j = 370; j > -370; j--) {
			colr = GetPixel(a, i, j);
			if (colr == col) {
				GP142_pixelXY(color, i, j);
			}
		}
	}*/
}
bool fillcolorinshape(shape **allshapes, int size,point p,int color) {
	bool flag = false;
	for (int i = 0; i < size; i++) {
		if (allshapes[i][0].contains(p)) {
			flag = true;
			if (strcmp(typeid(allshapes[i][0]).name(), "class line") == 0) {
				line *l = dynamic_cast<line*>(allshapes[i]);
				l->changecolor(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class circle") == 0) {
				circle *l = dynamic_cast<circle*>(allshapes[i]);
				//l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class rectangle") == 0) {
				rectangle *l = dynamic_cast<rectangle*>(allshapes[i]);
				l->fill(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class polygon") == 0) {
				polygon *l = dynamic_cast<polygon*>(allshapes[i]);
				//l->erase(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class curve") == 0) {
				curve *l = dynamic_cast<curve*>(allshapes[i]);
				l->changecolor(color);
			}
			if (strcmp(typeid(allshapes[i][0]).name(), "class triangle") == 0) {
				triangle *l = dynamic_cast<triangle*>(allshapes[i]);
				//l->erase(color);
			}
		}
	}
	return flag;
}

int main(void)
{
	//std::vector<int> abc(5);
    int quit = 0;           /* has user signaled quit yet?                      */
	int mouse_x, mouse_y;
    char key_pressed;
	char c;
    GP142_open();           /* Open and initialize the GP142 Graphics Window    */
	int pcount = 0;
	int *points=new int[100];
	shape**allshapes=nullptr;
	int cap = 0;
	int size = 0;
	side_bar();
	bool draw = false;
	int click = 0;
	int shapesnum = 0;
	int color = WHITE;
	point p;
	HDC a;
	polygon*s = nullptr;
	int num = 0;
    //The Event Loop
    while (!quit) {
        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
            case GP142_QUIT:
                quit = 1;   /* set flag to terminate loop                */
                break;
			case GP142_MOUSE:
				p.x = mouse_x;
				p.y = mouse_y;
                //handle_mouse(mouse_x,mouse_y);
				if (s != nullptr) {
					if (s->contains(p)) {
						draw_circle(num, 0, 10, color);
						num = num + 10;
					}
				}
				if (mouse_x > -490 && mouse_x < -460 && mouse_y>90 && mouse_y < 360) {
					click = 0;
					pcount = 0;
				}
				if (mouse_x > -430 && mouse_x < -400 && mouse_y>330 && mouse_y < 360 && c == 'E') {
					c = '0';
					pcount = 0;
				}
				if (c == 'E') {
					erasertool(allshapes, size, cap, p);
					pcount = 0;
				}
				if (mouse_x > -430 && mouse_x < -400 && mouse_y>330 && mouse_y < 360) {
					c = 'E';
					pcount = 0;
				}
				if (mouse_x > -430 && mouse_x < -400 && mouse_y>300 && mouse_y < 330 && c == 'E') {
					c = '0';
					pcount = 0;
				}
				if (c == 'F') {
					fillcolorinshape(allshapes, size, p, color);
					pcount = 0;
				}
				if (mouse_x > -430 && mouse_x < -400 && mouse_y>300 && mouse_y < 330) {
					c = 'F';
					pcount = 0;
				}
				if (mouse_x < 490 && mouse_x > 430 && mouse_y>330 && mouse_y < 360) {
					shapesnum = size;
					for (int i = 0; i < size; i++) {
						allshapes[i][0].seriallize("abc.ros");
					}
					pcount = 0;
				}
				if (mouse_x < 490 && mouse_x > 430 && mouse_y > 300 && mouse_y < 330) {
					for (int i = 0; i < size; i++) {
						add_shape(allshapes, size, cap, new line);
						allshapes[i][0].unserialize("abc.ros");
						allshapes[i][0].draw();
					}
					pcount = 0;
				}
				if (mouse_x > -460 && mouse_x < -430 && mouse_y>150 && mouse_y < 360) {
					color = colorpick(mouse_x, mouse_y);
					pcount = 0;
					break;
				}
				if (click == 0) {
					c = mouseclick(mouse_x, mouse_y);
					click++;
					break;
				}
				points[2 * pcount] = mouse_x;
				points[2 * pcount + 1] = mouse_y;
				if (pcount >= 2) {
					if (points[2 * pcount] == points[2 * (pcount - 1)] && points[2 * pcount + 1] == points[2 * (pcount - 1) + 1]) {
						draw = true;
					}
				}
				pcount++;
				if (pcount == 2 && c == 'L') {
					pcount = 0;
					//draw_line(points[0], points[1], points[2], points[3], color);
					add_shape(allshapes, size, cap, new line(false, points, 2, color));
					allshapes[size - 1][0].draw();
					break;
				}
				if (pcount == 2 && c == 'k') {
					pcount = 0;
					draw_doted_line(points[0], points[1], points[2], points[3], color);
					break;
				}
				if (draw == true && c == 'j') {
					draw = false;
					draw_dotted_curve(points, pcount, color);
					pcount = 0;
					break;
				}
				if (pcount == 3 && c == 'T') {
					pcount = 0;
					//draw_triangle(points[0], points[1], points[2], points[3], points[4], points[5], color);
					add_shape(allshapes, size, cap, new triangle(points, color));
					allshapes[size - 1][0].draw();
					break;
				}
				if (pcount == 2 && c == 'R') {
					pcount = 0;
					//draw_rectangle(points[0], points[1], points[2], points[3], color);
					add_shape(allshapes, size, cap, new rectangle(points, 2, color));
					allshapes[size - 1][0].draw();
					break;
				}
				if (pcount == 2 && c == 'C') {
					pcount = 0;
					//draw_circle(points[0], points[1], sqrt(pow((points[2] - points[0]), 2) + pow((points[3] - points[1]), 2)), color);
					add_shape(allshapes, size, cap, new circle(points, sqrt(pow((points[2] - points[0]), 2) + pow((points[3] - points[1]), 2)), color));
					allshapes[size - 1][0].draw();
					break;
				}
				if (draw == true && c == 'P') {
					draw = false;
					//draw_polygon(points, pcount, color);
					add_shape(allshapes, size, cap, new polygon(points, pcount, color));
					allshapes[size - 1][0].draw();
					pcount = 0;
					break;
				}
				if (draw == true && c == '/') {
					draw = false;
					//draw_curve(points, pcount, color);
					add_shape(allshapes, size, cap, new curve(false, points, pcount, color));
					allshapes[size - 1][0].draw();
					pcount = 0;
					break;
				}
				if (pcount == 1 && c == 't') {
					pcount = 0;
					draw_text(points[0], points[1], color);
					break;
				}
                break;
            case GP142_KBD:
				//Keyboard handler
				handle_kbd(key_pressed);
				eraser();
                break;
            default:
                break;
        }
    }
    GP142_close();          /* Clean up and close graphics window           */
    return 0;
}
/*float area = points[0] * (points[3] - points[5]);
		area = area + points[2] * (points[5] - points[1]);
		area = area + points[4] * (points[1] - points[3]);
		area = area / 2;
		float area1 = p.x * (points[1] - points[3]);
		area1 = area1 + points[0] * (points[3] - p.y);
		area1 = area1 + points[2] * (p.y - points[1]);
		area1 = area1 / 2;
		float area2 = p.x * (points[3] - points[5]);
		area2 = area2 + points[2] * (points[5] - p.y);
		area2 = area2 + points[4] * (p.y - points[3]);
		area2 = area2 / 2;
		float area3 = p.x * (points[1] - points[5]);
		area3 = area3 + points[0] * (points[5] - p.y);
		area3 = area3 + points[4] * (p.y - points[1]);
		area3 = area3 / 2;
		float sumarea = area1 + area2 + area3;
		if (sumarea == area) {
			return true;
		}
		else
int AB = (points[2] - points[0]) + (points[3] - points[1]);
int BC = (points[4] - points[2]) + (points[5] - points[3]);
int CA = (points[0] - points[4]) + (points[1] - points[5]);
int OA = (points[0] - p.x) + (points[1] - p.y);
int OB = (points[2] - p.x) + (points[3] - p.y);
int OC = (points[4] - p.x) + (points[5] - p.y);
int left = AB + BC + CA;
int right = OA + OB + OC;
if (left > right) {
	return true;
}
else
return false; */


