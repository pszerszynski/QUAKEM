#pragma once

#include "Entity.hpp"

namespace Ents {

class EnemyBase : public Entity {
public:
	EnemyBase(Entity_Type _type, Vec2 _pos=Vec2(0.0,0.0), Vec2 _size=Vec2(32.0,32.0),
	       Vec2 _vel=Vec2(0.0,0.0), Entity_Team _team=TEAM_ENEMY,
	       bool _collide=true, bool _physics = true):
	Entity(_type, _pos, _size, _vel, _team, _collide, _physics) { }

	void Update() = 0;
	virtual void Render() { }
	virtual Rect Hitbox() { return Hull(); }
	virtual Rect Hull() { return Rect(pos, size); }

	virtual void BrushCollision(Brush * brush) { }
	virtual void EntityCollision(Entity * entity) { }
	
	// construct from a list of labelled arguments
	// returns 1 for success, 0 for error
	static const std::string CONSTRUCT_MSG;
	virtual int Construct(const std::vector<Argument>& args) = 0;

	// constructs a string about entity status
	virtual std::string Info()
	  { return "x:" + std::to_string(pos.x) + " y:" + std::to_string(pos.y); }

protected:
	// checks line of sight from middle of enemy to player/entity
	bool CanSeePlayer();	
	bool CanSeeEntity(int UNIQUE_ID);
	bool CanSeeEntity(Entity *);
	int player_id=0;
};

// rushes player and deals contact damage
class Walker : public EnemyBase {
public:
	Walker(): EnemyBase(ENT_ENEMY_WALKER, Vec2(0.0,0.0), Vec2(32.0, 48.0)) {
		rate_timer.Start();
	}

	void Update();
	void Render();

	void EntityCollision(Entity * entity);
	
	// construct from a list of labelled arguments
	// returns 1 for success, 0 for error
	static const std::string CONSTRUCT_MSG;
	int Construct(const std::vector<Argument>& args);

	int damage = 10;
	double rate = 0.5;
	Timer rate_timer;
private:
};

class Gunman : public EnemyBase {
public:
	Gunman(): EnemyBase(ENT_ENEMY_GUNMAN, Vec2(0.0,0.0), Vec2(40.0, 40.0)) {
		rate_timer.Start();
		AddWeapon(WEP_PISTOL, {
		{"ammo",-1}, {"dmg", 15.0}, {"rate", 1.0}, {"vel", 2000.0}, {"life", 0.35},
		{"spread",0.0} });
	}

	void Update();
	void Render();

	void EntityCollision(Entity * entity);

	static const std::string CONSTRUCT_MSG;
	int Construct(const std::vector<Argument>& args);

	int damage = 20;
	double rate   = 1.0;
	double spread = 0.1;
	Timer rate_timer;
private:
};

}
