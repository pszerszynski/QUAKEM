#include "HUD.hpp"
#include "Game.hpp"

struct HUD HUD;

void HUD::Update() {
	for (auto h = elements.begin(); h != elements.end(); ++h) {
		(*h)->Update();
	}

	for (auto h = elements.begin(); h != elements.end();) {
		if ((*h)->destroy) {
			elements.erase(h);
		} else ++h;
	}
}

void HUD::Render() {
	for (auto h = elements.begin(); h != elements.end(); ++h) {
		(*h)->Render();
	}

}

void HUD::Clear() {
	elements.clear();
}

void HUD::Add(std::unique_ptr<HUD_Element> element) {
	elements.push_back(std::move(element));
}

namespace HUD_Elements {

void HP_Bar::Update() {
	auto ent = Game.GetEntityByID(ENT_ID);
	if (ent == nullptr) {
		destroy = true;
		return;
	} else if (ent->destroy) {
		destroy = true;
		return;
	}

	pos = ent->Hull().Middle();
	pos.y = ent->pos.y - 15.0;
	ratio = ent->hitpoints / (double)ent->max_hitpoints;
	if (ratio < 0.0) ratio = 0.0;
}

void HP_Bar::Render() {
	Vec2 tr = Vec2(pos.x, pos.y);
	tr = Renderer.TransformVec2(tr);

	Rect rect;
	rect.x = tr.x * Renderer.zoom - size.x/2;
	rect.y = tr.y * Renderer.zoom - size.y;
	//rect.x = pos.x - size.x/2;
	//rect.y = pos.y - size.y;

	rect.w = size.x;
	rect.h = size.y;

	Rect top_rect = rect;
	top_rect.w *= ratio;

	SDL_Color e = {0xff,0x10,0x10,0xff};
	SDL_Color f = {0x10,0xff,0x10,0xff};
	
	SDL_Color c = Renderer.HSLToRGB(ratio/3.0, 1.0, 0.5);

	Renderer.CameraStop();
	Renderer.RenderFillRect(    rect, {0x40,0x00,0x00,0xff});
	Renderer.RenderFillRect(top_rect, c);
	Renderer.CameraUpdate();
}

};
