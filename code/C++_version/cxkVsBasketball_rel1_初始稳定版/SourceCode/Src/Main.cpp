//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"

#include<mmsystem.h>				//PlaySound函数的头文件
#pragma comment(lib, "winmm.lib")	//链接库，PlaySound函数必须使用
#include <cstdlib>					//itoa()
#include <string>
#include <Windows.h>				//MSGBOX(), 获取时间以作为种子
#include <iostream>					//随机数
#include <cstdlib>					//随机数
#include <sstream>					//score
using namespace std;

//默认设置量
const float chickenSpeed = -40;
const float basketballSpeed = 40;
const float cxk_loc_x = -80;
const float cxk_loc_y = 0;
const float chicken_def_pos = 96;
const int chicken_num = 8;

//状态指示
bool running = false;
int score = 0;

//界面元素
CSprite *bgEntry = new CSprite("bgEntry");
CSprite *btnTip = new CSprite("tip");
CTextSprite *scoreText = new CTextSprite("scoreText");
CSprite *cxk = new CSprite("cxk");
CSprite *basketball = new CSprite("basketball");
CSprite *bgRoom = new CSprite("bgRoom");
string chickens[chicken_num] = {"chicken0", "chicken1", "chicken2", "chicken3", "chicken4", "chicken5", "chicken6", "chicken7"};
CSprite *chickensPtr[chicken_num];

int randNum(int maxRange){
	srand(unsigned int(GetTickCount64()));
	return ( rand() % ( maxRange + 1 ) + 1 );
}

void initBasketball(){
	if(running){
		basketball->SetSpritePosition(cxk->GetSpritePositionX()+15, cxk->GetSpritePositionY());
		basketball->SetSpriteLinearVelocityX(basketballSpeed);
	}
}

int MessageBoxShow(const char* title, const char* msg) {
	static HINSTANCE hInstance = GetModuleHandle(0);
	tagMSGBOXPARAMSA* tms = new tagMSGBOXPARAMSA;
	tms->cbSize = sizeof(*tms);
	tms->hwndOwner = NULL;
	tms->lpszCaption = title;
	tms->lpszText = msg;
	tms->dwStyle = MB_USERICON + MB_YESNO;
	tms->lpszIcon = MAKEINTRESOURCEA(105);
	tms->hInstance = hInstance;
	int result = MessageBoxIndirectA(tms);
	return result;
}

void chickenReGo(int index){
	if(running){
		chickensPtr[index]->SetSpritePositionX(chicken_def_pos);
		chickensPtr[index]->SetSpriteLinearVelocityX(chickenSpeed);
	}
}

void chickenStop(int i){
	chickensPtr[i]->SetSpriteLinearVelocityX(0);
	chickensPtr[i]->SetSpritePositionX(chicken_def_pos);
}

void startGame(){
	running = true;

	bgEntry->SetSpriteVisible(false);
	bgRoom->SetSpriteVisible(true);

	const int soundCnt = 2;
	string sounds[soundCnt] = {"game/data/audio/jntm.wav", "game/data/audio/jntm_crazy.wav"};
	PlaySound(sounds[randNum(soundCnt - 1) - 1].data(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	cxk->SetSpriteVisible(true);
	basketball->SetSpriteVisible(true);
	scoreText->SetSpriteVisible(true);
	initBasketball();

	if(btnTip->GetSpritePositionY() == 32){
		btnTip->SetSpriteLinearVelocityY(30);
	}

	//随机出发一只鸡
	for(int i = 0; i < chicken_num; i++){
		chickensPtr[i] = new CSprite(chickens[i].data());
	}
	int index = randNum(chicken_num - 1);
	chickenReGo(index - 1);
	//chickens[0].SetSpriteLinearVelocityX(-40);
}

void stopGame(){
	running = false;
	score = 0;

	basketball->SetSpriteLinearVelocityX(0);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);

	cxk->SetSpritePosition(cxk_loc_x,cxk_loc_y);

	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
	int result = MessageBoxShow("菜碧", "吃律师函吧\n\n重来吗？");
	if (result == 6)
	{
		//点击了确定
		startGame();
	}else{
		//点击了取消
		exit(1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	// 初始化游戏引擎
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : 在此使用API更改窗口标题
	CSystem::SetWindowTitle("蔡徐坤打篮球");

	bgRoom->SetSpriteVisible(false);
	cxk->SetSpriteVisible(false);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);

	// 引擎主循环，处理屏幕图像刷新等工作
	while( CSystem::EngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		float	fTimeDelta	=	CSystem::GetTimeDelta();

		// 执行游戏主循环
		g_GameMain.GameMainLoop( fTimeDelta );

		scoreText->SetTextValue(score);
	};

	// 关闭游戏引擎
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnMouseMove(fMouseX, fMouseY);
	cxk->SetSpritePosition(fMouseX,fMouseY);
}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnMouseClick(iMouseType, fMouseX, fMouseY);

	//开始游戏
	if(!running)
		startGame();
	else
		initBasketball();
}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnMouseUp(iMouseType, fMouseX, fMouseY);
}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
//
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
	/*switch(iKey){
		case KEY_W:
			cxk->SetSpriteLinearVelocityY(-30);
			break;
		case KEY_A:
			cxk->SetSpriteLinearVelocityX(-30);
			break;
		case KEY_S:
			cxk->SetSpriteLinearVelocityY(30);
			break;
		case KEY_D:
			cxk->SetSpriteLinearVelocityX(30);
			break;
	}*/
}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
//
void CSystem::OnKeyUp( const int iKey )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnKeyUp(iKey);
	/*switch(iKey){
		case KEY_W:
		case KEY_S:
			cxk->SetSpriteLinearVelocityY(0);
			break;
		case KEY_A:
		case KEY_D:
			cxk->SetSpriteLinearVelocityX(0);
			break;
	}*/
}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
//
void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnSpriteColSprite(szSrcName, szTarName);

	if(string(szSrcName).find("chicken") == 0){
		if(running && strcmp(szTarName, "cxk") == 0){
			stopGame();
		}else{
			initBasketball();
			int index = szSrcName[7];
			chickenReGo(index);
		}
	}

	if(running && string(szTarName).find("chicken") == 0){
		score++;
	}

	if(running){
		int index = randNum(chicken_num - 1);
		if(chickensPtr[index - 1]->GetSpriteLinearVelocityX() == 0)
			chickenReGo(index - 1);
	}
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
//
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnSpriteColWorldLimit(szName, iColSide);
	
	if(strcmp(szName,"basketball") == 0 && iColSide == 1){
		initBasketball();
	}else if(string(szName).find("chicken") == 0){
		int index = szName[7] - 48;
		chickenReGo(index);
	}

}