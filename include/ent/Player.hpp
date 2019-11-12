#pragma once

#include "Entity.hpp"
#include "Weapons.hpp"

namespace Ents {

struct Player : public Entity {
	Player(): Entity(ENT_PLAYER,
	  Vec2(0.0,0.0), Vec2(25.0,50.0), Vec2(0.0,0.0), TEAM_PLAYER)
	{ 
		hitpoints = 100; max_hitpoints = 100;

		AddWeapon(WEP_PISTOL, {
		  {"dmg", 10.0}, {"rate", 0.12}, {"vel", 2500.0}, {"life", 0.35}, {"spread",0.0} }); 
		AddWeapon(WEP_PISTOL, {
		  {"dmg", 4.0}, {"rate", 0.05}, {"vel", 1800.0}, {"life", 0.25}, {"spread",0.2},
		  {"autofire", 1.0} });
		AddWeapon(WEP_ROCKETL, {
		  {"dmg", 65.0}, {"rate", 0.42 }, {"vel", 1000.0 }, {"rad", 100.0} });
		AddWeapon(WEP_GRENADEL, {
		  {"dmg", 65.0}, {"rate", 0.42 }, {"vel", 1000.0 }, {"rad", 100.0}, {"burst", 3.0} });
	}

	std::unique_ptr<Weapon> weapons[9];

	void Update();
	void Render();
	Rect Hitbox();

	void HandleInput();

	static const std::string CONSTRUCT_MSG;
	int Construct(const std::vector<Argument>& args);

	std::string Info();

	bool move_left = false, move_right = true;

	~Player() { }

private:
	void MoveLeft();
	void StopMoveLeft();
	void MoveRight();
	void StopMoveRight();
	void Jump();
	void Fire();
};

}
