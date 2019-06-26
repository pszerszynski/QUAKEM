#pragma once

#include <cmath>

#include "Media.hpp"
#include "Vec2.hpp"

enum TEXT_ALIGN { ALIGN_LEFT, ALIGN_MIDDLE , ALIGN_RIGHT };

extern struct Renderer {
	SDL_Renderer * renderer = nullptr;

	void SetColor(const SDL_Color& c);
	void SetColor(const int r, const int g, const int b, const int a);

	void Clear(const SDL_Color c = {0x00,0x00,0x00,0xff});
	void Update();
	
	void RenderPixel(SDL_Point point);
	void RenderPixel(SDL_Point point, const SDL_Color&);

	void RenderLine(Vec2 a, Vec2 b);
	void RenderLine(Vec2 a, Vec2 b, const SDL_Color&);

	void RenderRect(Rect rect);
	void RenderRect(Rect, const SDL_Color&);

	void RenderFillRect(Rect rect);
	void RenderFillRect(Rect, const SDL_Color&);

	void RenderTexture(const std::string& img_name, SDL_Rect* src=nullptr,
	  SDL_Rect* dest=nullptr);
	void RenderTexture(const std::string& img_name, SDL_Rect* src, SDL_Rect* dest,
  	  double angle, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Point * rot_centre = nullptr);

	void RenderTiledTexture(const std::string& tex_name, Rect rect, Vec2 scale, Vec offset);

	void RenderText(const std::string& font_name, const std::string& text, int x, int y,
	  FONT_SIZE, SDL_Color, TEXT_ALIGN align=ALIGN_LEFT);
	void RenderText(TTF_Font * font, const std::string& text, int x, int y, SDL_Color);
} Renderer;
