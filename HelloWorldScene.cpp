/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "spine/Json.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	for (int i = 0; i < 1080; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			matrix[i][j] = 0;
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/*MonsterPN* mt = MonsterPN::create();
	mt->initWithFile("CloseNormal.png");*/
	/////////////////////////////
	// 3. add your codes below...
	auto btnHitted = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::spHitted, this));

	if (btnHitted == nullptr ||
		btnHitted->getContentSize().width <= 0 ||
		btnHitted->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - btnHitted->getContentSize().width / 2;
		float y = origin.y + visibleSize.height - btnHitted->getContentSize().height / 2;
		btnHitted->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(btnHitted, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	//tao layer cho nhan vat
	CCLayer* ly = CCLayerColor::create(ccColor4B(126, 55, 15, 50), visibleSize.width, visibleSize.height);
	ly->setPosition(0, 0);
	this->addChild(ly, 5, "lSprite");


	MonsterPN* sp = MonsterPN::create();
	//tao sprite
	sp->initWithFolder("/Character1/adventurer-attack1-00.png");
	sp->setPosition(visibleSize.width / 2, visibleSize.height / 2);




	ly->setCameraMask((unsigned short)CameraFlag::USER2, true);
	ly->addChild(sp, 10, "spNhanVat");




	// tao ket noi server
	/*String* dataTosend = String::create("dataOne=20");
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost/huy1.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestCompleted, this));
	request->setRequestData("dataOne=45", 10);
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();;*/

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0, 15);
	}

	control = LayerColor::create(Color4B(45, 150, 15, 50), 200, 200);
	control->ignoreAnchorPointForPosition(false);
	control->setPosition(Vec2(200 / 2,
		200 / 2));
	//control->setCameraMask((unsigned short)CameraFlag::USER1, true);

	auto joystick = Joystick::create();
	control->addChild(joystick);

	auto _listener = EventListenerCustom::create(JoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
		JoystickEvent* jsevent = static_cast<JoystickEvent*>(event->getUserData());
		//log("--------------got joystick event, %p,  angle=%f", jsevent, jsevent->mAnagle);
		angleControl = jsevent->mAnagle;
		
		//spMove(jsevent->mAnagle);
		// do you business you'd like to

		});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);




	//auto cam = Camera::getDefaultCamera();
	CCCamera* cam1 = CCCamera::createPerspective(60, (float)visibleSize.width / visibleSize.height, 1.0, 1000);
	cam1->setCameraFlag(CameraFlag::USER2);
	cam1->setPosition(sp->getPosition());
	cam1->lookAt(Vec3(sp->getPositionX(), sp->getPositionX(), 0), Vec3(0.0, 1.0, 0.0));
	this->addChild(cam1, 6, "lyCam");


	this->addChild(control, 10, "lControl");

	this->scheduleUpdate();
	return true;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
	std::vector<char>* buffer = response->getResponseData();


	printf("Get data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	printf("\n");
	if (200 != response->getResponseCode())
	{
		printf("Succeeded");

		return;
	}
	else
	{
		printf("Failed");
	}
}

//set camera
void HelloWorld::setCamera(bool type)
{
	Node* lyControl = this->getChildByName("lControl");
	float controlPosX = lyControl->getPosition().x;
	float controlPosY = lyControl->getPosition().y;
	Node* ly = this->getChildByName("lSprite");
	//auto cam = ly->getChildByName("lyCam");
	auto cam = Camera::getDefaultCamera();

	controlPosX -= cam->getPositionX() ;
	controlPosY -= cam->getPositionY() ;
	float contentX = lyControl->getContentSize().width;
	float contentY = lyControl->getContentSize().height;
	
	//Node* lay = this->getChildByTag(90);
	Node* sp = ly->getChildByName("spNhanVat");
	//vi tri sp
	float px = sp->getPosition().x;
	float py = sp->getPosition().y;
	//vi tri dich chuyen
	/*posX = posX + px;
	posY = posY + py;*/
	//vi tri bien cua map
	float bienTop = 3000;
	float bienRight = 5300;

	float bienLeft = 0;
	float bienBot = 0;
	// do rong cua man hinh
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//log("--------------vi tri x y posx=%f, posY=%f", px, py);*/

	if (type)
	{
		//px < visibleSize.width * 0.5 ? visibleSize.width * 0.5 : px;
		if (px < visibleSize.width * 0.5)
		{
			px = visibleSize.width * 0.5;
		}
		//px >bienRight - visibleSize.width * 0.5 ? bienRight - visibleSize.width * 0.5 : px;
		if (px > bienRight - visibleSize.width * 0.5)
		{
			px = bienRight - visibleSize.width * 0.5;
		}
		//py < visibleSize.height * 0.5 ? visibleSize.height * 0.5 : py;
		if (py < visibleSize.height * 0.5)
		{
			py = visibleSize.height * 0.5;
		}
		//log("vi tri py:%f", py);
		//py > bienTop - visibleSize.height * 0.5 ? bienTop - visibleSize.height * 0.5 : py;
		if (py > bienTop - visibleSize.height * 0.5)
		{
			py = bienTop - visibleSize.height * 0.5;
		}

		cam->setPosition(px, py);
		lyControl->setPosition(px + controlPosX, py + controlPosY);
	}
	else
	{

		//cam->setPosition(px, py);

		// lay vi tri cua camera
		// lay vi tri cua nhan vat
		// lay width height cua khung hinh
		//moc la 120 pixel
		//moc width = width*0.5 - 120     -----(768*0.5 -120 = 264)
		//moc height = height*0.5 - 120   -----(1024*0.5 - 120 =392)
		//neu nvX-camX > 0 => x = nvX-camX - 264 =>> posX = camX+x   (neu x = nvX - camX - 264 > 0  ==> posX = camX + x)
		//neu nvX-camX < 0 => x = nvX-camX + 264 =>> posX = camX+x   (neu x = nvX - camX + 264 < 0  ==> posX = camX + x)

		//neu y = nvY- camY - 392 >0 posY = camY + y
		//neu y = nvY- camY + 392 <0 posY = camY + y

		float camX = cam->getPositionX();
		float camY = cam->getPositionY();
		float pXX = camX;
		float pYY = camY;
		float mocW = visibleSize.width * 0.5 - 120;
		float mocH = visibleSize.height * 0.5 - 120;
		float x1 = px - camX - mocW;
		float x2 = px - camX + mocW;
		if (x1 > 0)
		{
			pXX = camX + x1;
		}
		if (x2 < 0)
		{
			pXX = camX + x2;
		}

		float y1 = py - camY - mocH;
		float y2 = py - camY + mocH;
		if (y1 > 0)
		{
			pYY = camY + y1;
		}
		if (y2 < 0)
		{
			pYY = camY + y2;
		}
		//---------neu vi tri cua camera <1/2 width left va 1/2 height bot thi lay vi tri 1/2 width height
		//px < visibleSize.width * 0.5 ? visibleSize.width * 0.5 : px;
		if (pXX < visibleSize.width * 0.5)
		{
			pXX = visibleSize.width * 0.5;
		}
		//px >bienRight - visibleSize.width * 0.5 ? bienRight - visibleSize.width * 0.5 : px;
		if (pXX > bienRight - visibleSize.width * 0.5)
		{
			pXX = bienRight - visibleSize.width * 0.5;
		}
		//py < visibleSize.height * 0.5 ? visibleSize.height * 0.5 : py;
		if (pYY < visibleSize.height * 0.5)
		{
			pYY = visibleSize.height * 0.5;
		}
		//log("vi tri py:%f", py);
		//py > bienTop - visibleSize.height * 0.5 ? bienTop - visibleSize.height * 0.5 : py;
		if (pYY > bienTop - visibleSize.height * 0.5)
		{
			pYY = bienTop - visibleSize.height * 0.5;
		}

		cam->setPosition(pXX, pYY);
		lyControl->setPosition(pXX + controlPosX, pYY + controlPosY);
	}

}

void HelloWorld::spHitted(cocos2d::Ref* pSender)
{
	Node* ly = this->getChildByName("lSprite");
	Node* sp = ly->getChildByName("spNhanVat");
	(dynamic_cast<MonsterPN*>(sp))->hitted(0, 0);
	//CCObject* ii = ly->getChildByName("spNhanVat");

}

void HelloWorld::spMove(double angle)
{
	float posX = 0, posY = 0;
	if (angle >= 22.5 && angle <= 67.5)
	{
		//move up right
		posX = 1;
		posY = 1;
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		//move up 
		posX = 0;
		posY = 1;
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		//move up left
		posX = -1;
		posY = 1;
	}
	else if ((angle > 157.5 && angle <= 180) || (angle < -157.5 && angle >-180.0))
	{
		//move left
		posX = -1;
		posY = 0;
	}
	else if (angle < -112.5 && angle >= -157.5)
	{
		//move bot left
		posX = -1;
		posY = -1;
	}
	else if (angle < -67.5 && angle >= -112.5)
	{
		//move bot 
		posX = 0;
		posY = -1;
	}
	else if (angle < -22.5 && angle >= -67.5)
	{
		//move bot right
		posX = 1;
		posY = -1;
	}

	else if ((angle >= 0 && angle <= 22.5) || (angle >= -22.5 && angle < 0))
	{
		//move right
		posX = 1;
		posY = 0;
	}
	else
	{
		//stand
		posX = 0;
		posY = 0;
	}
	Node* ly = this->getChildByName("lSprite");
	auto sp = ly->getChildByName("spNhanVat");
	sp->setPosition(sp->getPositionX() + posX, sp->getPositionY() + posY);

}

void HelloWorld::update(float dt)
{


	this->spMove(angleControl);
	/*float posX = (float)(cos(angleControl));
	float posY = (float)(sin(angleControl));
	log("posx:%f---posY:%f--------angle:%f", posX, posY, angleControl);
	Node* ly = this->getChildByName("lSprite");
	auto sp = ly->getChildByName("spNhanVat");
	sp->setPosition(sp->getPositionX() + posX, sp->getPositionY() + posY);
	Node* lyControl = this->getChildByName("lControl");
	lyControl->setPosition(lyControl->getPosition().x + posX, lyControl->getPositionY() + posY);*/
	setCamera(true);
}