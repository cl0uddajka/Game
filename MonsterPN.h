/*
 * Joystick.h
 *
 *  Created on: 2015-2-1
 *      Author: yong
 */

#ifndef MONSTERPN_H_
#define MONSTERPN_H_

#include "cocos2d.h"
using namespace cocos2d;


class MonsterPN: public Sprite {
private:
	MonsterPN();

protected:
	/*bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);*/

public:
	virtual ~MonsterPN();
	virtual bool init();
	bool initWithFolder(const std::string& filename);
	CREATE_FUNC(MonsterPN);

	///source folder
	std::string folderResource;
	//thuoc tinh
	int mau;
	int mana;
	float moveSpeed;
	float attSpeed;
	int exp;
	int findMagicChance;
	//5 hanh
	int fireDame;
	int waterDame;
	int landDame;
	int steelDame;
	int treeDame;
	int baseDame;
	float amor;
	float fireResistance;
	float waterResistance;
	float landResistance;
	float steelResistance;
	float treeResistance;

	float streng;//dame phys and health
	float intelligent;// magic dame, magic res, mana
	float agility;// move speed, att speed.

	float blockPoint;
	float avoid;
	float stamina;//ma khi

	float channing;
	float channingTime;
	bool disable;
	void move();
	void hitted(float channing, float channingTime);
	void stand();
	void stand2();
	void attack(float channing, float channingTime);
	void state();
	void skill(float channing, float channingTime);
private:
	/*Sprite* mJsBg;
	Sprite* mJsCenter;
	Vec2 mJsPos = Vec2(100, 100);*/
};

#endif /* MONSTERPN_H_ */
