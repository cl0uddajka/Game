/*
 * Joystick.cpp
 *
 *  Created on: 2015-2-1
 *      Author: yong
 */

#include "MonsterPN.h"
 //------------------------------------------------------------------------------------------------------------------------------------------------------
MonsterPN::MonsterPN() {
}

MonsterPN::~MonsterPN() {

}

bool MonsterPN::init() {


	return true;
}

bool MonsterPN::initWithFolder(const std::string& filename)
{
	bool ret = Sprite::initWithFile(filename);
	folderResource = filename;
	moveSpeed = 0.2f;
	stand();
	hitted(0.1f, 0.2f);
	//_displayName = filename;
	//std::string cccc = "";
	return ret;
}

void MonsterPN::move()
{
}

void MonsterPN::hitted(float channing, float channingTime)
{
	const int numberSprite = 3;
	//auto gameSprite = Sprite::createWithSpriteFrameName("adventurer-attack1-00.png");

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-hurt-00.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-hurt-01.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-hurt-02.png"));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, moveSpeed);
	Animate* animate = Animate::create(animation);
	this->stopAllActions();

	auto action1 = Repeat::create(animate, 1);
	auto callback = CallFunc::create([this]() {this->stand(); });
	//this->runAction(Repeat::create(animate, 10));
	this->runAction(Sequence::create(action1, callback, NULL));
	//CallFunc::create(CC_CALLBACK_0(MonsterPN::stand, this));
	//Sequence::create(this->runAction(Repeat::create(animate, 10)), CallFunc::create(CC_CALLBACK_0(MonsterPN::stand, this)), this);
}

void MonsterPN::stand()
{


	const int numberSprite = 4;
	//auto gameSprite = Sprite::createWithSpriteFrameName("adventurer-attack1-00.png");

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-00.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-01.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-02.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-03.png"));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, moveSpeed);
	Animate* animate = Animate::create(animation);

	this->runAction(RepeatForever::create(animate));
}

void MonsterPN::stand2()
{
	const int numberSprite = 4;
	//auto gameSprite = Sprite::createWithSpriteFrameName("adventurer-attack1-00.png");

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-2-00.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-2-01.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-2-02.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventurer-idle-2-03.png"));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, moveSpeed);
	Animate* animate = Animate::create(animation);

	this->runAction(RepeatForever::create(animate));
}

void MonsterPN::attack(float channing, float channingTime)
{
}

void MonsterPN::state()
{
}

void MonsterPN::skill(float channing, float channingTime)
{
}
