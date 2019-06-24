#pragma once

#include <SDL2/SDL.h>

struct Vec2 {
	Vec2(): x(0.0), y(0.0) { }
	Vec2(const double& _x, const double& _y): x(_x), y(_y) { }
	double x,y;
};

struct Rect {
	Rect(): x(0.0),y(0.0),w(0.0),h(0.0) { }
	Rect(const double& _x,const double& _y,
	     const double& _w,const double& _h)
	: x(_x), y(_y), w(_w), h(_h) { }
	Rect(const Vec2& pos, const Vec2& size)
	: x(pos.x), y(pos.y), w(size.x), h(size.y) { }

	double x,y,w,h;

	Vec2 Pos();
	Vec2 Size();
	void SetPos(const Vec2& v);
	void SetSize(const Vec2& s);

	SDL_Rect ToSDLRect();
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
Vec2 operator*(const Vec2& a, const double& s);
Vec2 operator/(const Vec2& a, const double& s);
