/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"


#include<mmsystem.h>				//PlaySound函数的头文件
#pragma comment(lib, "winmm.lib")	//链接库，PlaySound函数必须使用
#include <cstdlib>					//itoa()
#include <string>
#include <Windows.h>				//MSGBOX(), 获取时间以作为种子
#include <iostream>					//随机数
#include <cstdlib>					//随机数, 网页跳转
#include <sstream>					//score
using namespace std;

//默认设置量
const string githubAddr = "https://github.com/CoolestEnoch/CXK_AvoidBasketball";
const float chickenSpeed = -40;
const float basketballSpeed = 40;
const float cxk_loc_x = -80;
const float cxk_loc_y = 0;
const float chicken_def_pos = 100;
const int chicken_num = 8;
const int caibiLim = 5;

//状态指示
bool running = false;
int score = 0;

//界面元素
CSprite *bgEntry = new CSprite("bgEntry");
CSprite *btnTip = new CSprite("tip");
CTextSprite *scoreText = new CTextSprite("scoreText");
CSprite *cxk = new CSprite("cxk");
CSprite *caibi = new CSprite("caibi");
CSprite *basketball = new CSprite("basketball");
CSprite *btnHelp = new CSprite("btnHelp");
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

void resetChicken(){
	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
}

void startGame(){
	running = true;

	btnHelp->SetSpriteVisible(false);
	bgEntry->SetSpriteVisible(false);
	bgRoom->SetSpriteVisible(true);

	string sounds[2] = {"game/data/audio/jntm_crazy.wav", "game/data/audio/jntm.wav"};
	PlaySound(sounds[randNum(1) - 1].data(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

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
	cxk->SetSpriteLinearVelocity(0,0);

	for(int i = 0; i < chicken_num; i++){
		chickenStop(i);
	}
	int result = MessageBoxShow("菜碧", "律师函来咯~~~\n\n重来吗？");
	if (result == 6)
	{
		//点击了确定
		startGame();
	}else{
		//点击了取消
		exit(1);
	}
}
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;	

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	0;
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	scoreText->SetTextValue(score);
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( true )
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{				
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	bgRoom->SetSpriteVisible(false);
	cxk->SetSpriteVisible(false);
	basketball->SetSpriteVisible(false);
	scoreText->SetSpriteVisible(false);
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
	
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{
	cxk->SetSpriteLinearVelocity(0,0);
	cxk->SetSpritePosition(fMouseX,fMouseY);
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if((fMouseX > (btnHelp->GetSpritePositionX() - btnHelp->GetSpriteWidth()/2)) && (fMouseX < (btnHelp->GetSpritePositionX() + btnHelp->GetSpriteWidth()/2)) && 
		(fMouseY > (btnHelp->GetSpritePositionY() - btnHelp->GetSpriteHeight()/2)) && (fMouseY < (btnHelp->GetSpritePositionY() + btnHelp->GetSpriteHeight()/2))){
			stringstream ss;
			ss << "WASD或者方向键移动蔡徐坤，当分数大于";
			ss << 5;
			ss << "分的时候按CTRL键可以开大招。" << endl << endl;
			ss << "访问开源项目地址?";
			int respond = MessageBoxShow("帮助", ss.str().data());
			if(respond == 6){
				//点击了确定
				string cmd = "start " + githubAddr;
				system(cmd.data());
			}else{
				//点击了取消
			}
	}else{
		//开始游戏
		if(!running)
			startGame();
		else
			initBasketball();
	}
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	
}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{	
	switch(iKey){
	case KEY_W:
	case KEY_UP:
		cxk->SetSpriteLinearVelocityY(-30);
		break;
	case KEY_A:
	case KEY_LEFT:
		cxk->SetSpriteLinearVelocityX(-30);
		break;
	case KEY_S:
	case KEY_DOWN:
		cxk->SetSpriteLinearVelocityY(30);
		break;
	case KEY_D:
	case KEY_RIGHT:
		cxk->SetSpriteLinearVelocityX(30);
		break;
	case KEY_LCONTROL:
	case KEY_RCONTROL:
	case KEY_CONTROL:
		if(running && score >= caibiLim){
			score -= caibiLim;
			caibi->SetSpriteLinearVelocityX(basketballSpeed + 5);
		}
		break;
	case KEY_SPACE:
		if(!running)
			startGame();
		else
			initBasketball();
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
	switch(iKey){
	case KEY_W:
	case KEY_S:
	case KEY_UP:
	case KEY_DOWN:
		cxk->SetSpriteLinearVelocityY(0);
		break;
	case KEY_A:
	case KEY_D:
	case KEY_LEFT:
	case KEY_RIGHT:
		cxk->SetSpriteLinearVelocityX(0);
		break;
	}
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	if(string(szSrcName).find("chicken") == 0){
		if(running && strcmp(szTarName, "cxk") == 0){
			stopGame();
		}else{
			initBasketball();
			int index = szSrcName[7];
			chickenReGo(index);
		}
	}

	if(running && string(szTarName).find("chicken") == 0 && strcmp(szSrcName, "caibi") != 0){
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
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if(strcmp(szName,"basketball") == 0 && iColSide == 1){
		initBasketball();
	}else if(string(szName).find("chicken") == 0){
		int index = szName[7] - 48;
		chickenReGo(index);
	}else if(strcmp(szName, "caibi") == 0){
		caibi->SetSpritePositionX(-128);
		caibi->SetSpriteLinearVelocityX(0);
		resetChicken();
	}
}

