//////////////////////////////////////////////////////////////////////////
// Name:	DirectXFramework.cpp
// Date:	April 2nd, 2010
// Author:	Kyle Lauing [klauing@devry.edu] or [kylelauing@gmail.com]
// Purpose: This file is used to create a very simple framework for using
//			DirectX 9 for the GSP 381 course for DeVry University.
// Disclaimer:	
//			Copyright © 2010 by DeVry Educational Development Corporation.
//			All rights reserved.  No part of this work may be reproduced 
//			or used in any form or by any means – graphic, electronic, or 
//			mechanical, including photocopying, recording, Web distribution 
//			or information storage and retrieval systems – without the 
//			prior consent of DeVry Educational Development Corporation.
//////////////////////////////////////////////////////////////////////////
#include "DirectXFramework.h"
#include "sprite.h"
#include "Gamelevel.h"
#include "Player.h"
#include "fmod.hpp"
#include "dshow.h"
#include <string>
#include <fstream>
#include <Windows.h>


#include<vector>
#include<sstream>
//#include<allegro>

using namespace std;

#define DIRECTINPUT_VERSION 0x0800

bool keyDown(BYTE [], The_Sprite &, float);
bool mouseDown(DIMOUSESTATE2, The_Sprite &, int &);


CDirectXFramework::CDirectXFramework(void)
{
	// Init or NULL objects before use to avoid any undefined behavior
	m_bVsync		= false;
	m_pD3DObject	= 0;
	m_pD3DDevice	= 0;
	
}

CDirectXFramework::~CDirectXFramework(void)
{
	// If Shutdown is not explicitly called correctly, call it when 
	// this class is destroyed or falls out of scope as an error check.
	Shutdown();
}

void CDirectXFramework::Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	CoInitialize(NULL);

		m_hWnd = hWnd;

	//////////////////////////////////////////////////////////////////////////
	// Direct3D Foundations - D3D Object, Present Parameters, and D3D Device
	//////////////////////////////////////////////////////////////////////////

	// Create the D3D Object
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Find the width and height of window using hWnd and GetWindowRect()
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// Set D3D Device presentation parameters before creating the device
	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));  // NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= height;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= width;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}
	
	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}
	
	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&m_pD3DDevice);			// returned device pointer

	//*************************************************************************

	//////////////////////////////////////////////////////////////////////////
	// Create a Font Object
	//////////////////////////////////////////////////////////////////////////
	
	// Load a font for private use for this process


	// Load D3DXFont, each font style you want to support will need an ID3DXFont



	//////////////////////////////////////////////////////////////////////////
	// Create Sprite Object and Textures
	//////////////////////////////////////////////////////////////////////////

	// Create a sprite object, note you will only need one for all 2D sprites


	// Create a texture, each different 2D sprite to display to the screen
	// will need a new texture object.  If drawing the same sprite texture
	// multiple times, just call that sprite's Draw() with different 
	// transformation values.


	//*************************************************************************
	AddFontResourceEx(L"Delicious-Roman.otf", NULL, 0);
	D3DXCreateFont(m_pD3DDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                         L"Delicious-Roman.otf", &m_pD3DFont);
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);
	
	

	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_DInput, 0);

	m_DInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard, 0);
	m_DInput->CreateDevice(GUID_SysMouse, &m_Mouse, 0);
	m_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_Mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_Mouse->SetDataFormat(&c_dfDIMouse2);

	//FMOD input

	result = FMOD::System_Create(&system);
	//ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
	}
	result = system->getNumDrivers(&numdrivers);
	//ERRCHECK(result);

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		//ERRCHECK(result);
	}
	else
	{
		result = system->getDriverCaps(0, &caps, 0, &speakermode);
		//ERRCHECK(result);
	}

	result = system->setSpeakerMode(speakermode);
	//ERRCHECK(result);

	if (caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = system->setDSPBufferSize(1024, 10);
		//ERRCHECK(result);
	}

	result = system->getDriverInfo(0, name, 256, 0);
	//ERRCHECK(result);

	if (strstr(name, "SigmaTel"))
	{
		result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
		//ERRCHECK(result);
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		//ERRCHECK(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}


	system->createSound("Supralightning - Breaking Bad 16.mp3", FMOD_DEFAULT, 0, &sound);

	
	gameboard.init();
	
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"testbackground.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &m_pTexture);
	/*D3DXCreateTextureFromFileEx(m_pD3DDevice, L"ground.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &w_pTexture[0]);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"platform.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &w_pTexture[1]);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"goal.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &w_pTexture[2]);*/
	gameboard.getLevel(0)->getBackground()->setTexture(m_pTexture);
	gameboard.getLevel(0)->getBackground()->setWidth(800);
	gameboard.getLevel(0)->getBackground()->setHeight(600);
	gameboard.getLevel(0)->getBackground()->setScalex(800 / 640);
	gameboard.getLevel(0)->getBackground()->setScaley(640 / 480);
	gameboard.getLevel(0)->getBackground()->setRotation(0.0f);
	gameboard.getLevel(0)->getBackground()->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	gameboard.getLevel(0)->getBackground()->setRect();

	/*gameboard.getPlayer()->setRect();
	
	gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground1.txt");
	gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground2.txt");
	gameboard.loadFromFile(m_pD3DDevice, w_pTexture[1], "platform.txt");
	gameboard.getPlayer()->setPosition(D3DXVECTOR3((gameboard.getSprite(0, 0)->getPosition().x + 200), 
												   (gameboard.getSprite(0, 0)->getPosition().y - 50 - 16), 0.0f));
	gameboard.getSprite(2, 0)->setTexture(w_pTexture[2]);
	gameboard.getSprite(2, 0)->setWidth(75);
	gameboard.getSprite(2, 0)->setHeight(100);
	gameboard.getSprite(2, 0)->setRect();
	gameboard.getSprite(2, 0)->setScalex(1.0f);
	gameboard.getSprite(2, 0)->setScaley(1.0f);
	gameboard.getSprite(2, 0)->setRotation(0.0f);
	gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(1300.0f, 300.0f, 0.0f));
	*/

	for (int i = 0; i < 256; i++)
	{
		pressed[i] = false;
	}

	for (int i = 0; i < 8; i++)
	{
		mousePressed[i] = false;
	}

	timer = 0.0f;

	the_state = PROGRAM;

	gameStart = true;
	scene2 = false;

	menuyposition = 250;

	movepositions = new D3DXVECTOR3[20];
}

bool CDirectXFramework::Update(float & dt)
{
	bool playingmusic = false;
	long evCode;
    LONG_PTR eventParam1, eventParam2;
	m_Keyboard->Acquire();
	m_Mouse->Acquire();
	m_Keyboard->GetDeviceState(sizeof(buffer), (void **)&buffer);
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void **)&m_MouseState);
	int oldpositionx = gameboard.getPlayer()->getPosition().x;
	int oldpositiony = gameboard.getPlayer()->getPosition().y;
	switch(the_state)
	{
	case MENU:
		//playingmusic = false;
		//channel[1]->isPlaying(&playingmusic);
		//if (!playingmusic)
		//{
		//	result = system->playSound(FMOD_CHANNEL_FREE, sound[6], false, &channel[1]);
		//}
		//keyDown4(buffer, dt);
		break;
	case INIT:
		//if (gameboard.getActive() == 0)
		//{
		//	if (setPiece == 0)
		//	{
		//		pieceType = 0;
		//	}
		//	else if (setPiece == 1)
		//	{
		//		pieceType = 1;
		//	}
		//	else if ((setPiece >= 2) && (setPiece <= 3))
		//	{
		//		pieceType = 2;
		//	}
		//	else if ((setPiece >= 4) && (setPiece <= 6))
		//	{
		//		pieceType = 3;
		//	}
		//	else if ((setPiece >= 7) && (setPiece <= 10))
		//	{
		//		pieceType = 4;
		//	}
		//	else if ((setPiece >= 11) && (setPiece <= 14))
		//	{
		//		pieceType = 5;
		//	}
		//	else if ((setPiece >= 15) && (setPiece <= 18))
		//	{
		//		pieceType = 6;
		//	}
		//	else if ((setPiece >= 19) && (setPiece <= 23))
		//	{
		//		pieceType = 7;
		//	}
		//	else if ((setPiece >= 24) && (setPiece <= 31))
		//	{
		//		pieceType = 8;
		//	}
		//	else if (setPiece == 32)
		//	{
		//		pieceType = 9;
		//	}
		//	else if ((setPiece >= 23) && (setPiece <= 38))
		//	{
		//		pieceType = 10;
		//	}
		//	else if (setPiece == 39)
		//	{
		//		pieceType = 11;
		//	}
		//	else if (setPiece == 40)
		//	{
		//		gameboard.setActive(1);
		//		setPiece = 0;
		//		pieceType = 12;
		//		initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//		the_state = BLANK_BOARD;
		//		return false;
		//	}
		//	else
		//	{
		//		return false;
		//	}
		//}
		//else if (gameboard.getActive() == 1)
		//{
		//	if (setPiece == 0)
		//	{
		//		pieceType = 12;
		//	}
		//	else if (setPiece == 1)
		//	{
		//		pieceType = 13;
		//	}
		//	else if ((setPiece >= 2) && (setPiece <= 3))
		//	{
		//		pieceType = 14;
		//	}
		//	else if ((setPiece >= 4) && (setPiece <= 6))
		//	{
		//		pieceType = 15;
		//	}
		//	else if ((setPiece >= 7) && (setPiece <= 10))
		//	{
		//		pieceType = 16;
		//	}
		//	else if ((setPiece >= 11) && (setPiece <= 14))
		//	{
		//		pieceType = 17;
		//	}
		//	else if ((setPiece >= 15) && (setPiece <= 18))
		//	{
		//		pieceType = 18;
		//	}
		//	else if ((setPiece >= 19) && (setPiece <= 23))
		//	{
		//		pieceType = 19;
		//	}
		//	else if ((setPiece >= 24) && (setPiece <= 31))
		//	{
		//		pieceType = 20;
		//	}
		//	else if (setPiece == 32)
		//	{
		//		pieceType = 21;
		//	}
		//	else if ((setPiece >= 23) && (setPiece <= 38))
		//	{
		//		pieceType = 22;
		//	}
		//	else if (setPiece == 39)
		//	{
		//		pieceType = 23;
		//	}
		//	else if (setPiece == 40)
		//	{
		//		gameboard.setActive(0);
		//		the_state = BLANK_BOARD;
		//		return false;
		//	}
		//	else
		//	{
		//		return false;
		//	}
		//}
		//keyDown2(buffer, g[pieceType], setPiece, initPosition, dt);
		break;
	case PROGRAM:
		playingmusic = false;
		channel->isPlaying(&playingmusic);
		if (!playingmusic)
		{
			result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
		}
		/*updatevalue = keyDown(buffer, gameboard.getPlayer(), dt);
		gameboard.getPlayer()->setYVelocity(gameboard.getPlayer()->getYVelocity() + 0.0002f);		
		gameboard.getPlayer()->setPosition(D3DXVECTOR3(gameboard.getPlayer()->getPosition().x,
										   (gameboard.getPlayer()->getPosition().y + 
										   (gameboard.getPlayer()->getPosition().y * gameboard.getPlayer()->getYVelocity())), 0.0f));
		for (int i = 0; i < gameboard.getSize(0); ++i)
		{
			gameboard.getSprite(0, i)->setPosition(D3DXVECTOR3(gameboard.getSprite(0, i)->getPosition().x - (updatevalue * 7),
														   gameboard.getSprite(0, i)->getPosition().y, 0.0f));
			if (gameboard.getPlayer()->checkForCollision(*gameboard.getSprite(0, i)))
			{
				if (((int)gameboard.getPlayer()->rightside() >= (int)gameboard.getSprite(0, i)->getPosition().x) &&
					((int)gameboard.getPlayer()->getPosition().x <= (int)gameboard.getSprite(0, i)->rightside()))
				{
					gameboard.getPlayer()->setPosition(D3DXVECTOR3((float)oldpositionx, gameboard.getPlayer()->getPosition().y, 0.0f));
					for (int j = 0; j < gameboard.getSize(0); ++j)
					{
						gameboard.getSprite(0, j)->setPosition(D3DXVECTOR3(gameboard.getSprite(0, j)->getPosition().x + (updatevalue * 7),
														   gameboard.getSprite(0, j)->getPosition().y, 0.0f));
					}
					for (int j = 0; j < gameboard.getSize(1); ++j)
					{
						gameboard.getSprite(1, j)->setPosition(D3DXVECTOR3(gameboard.getSprite(1, j)->getPosition().x + (updatevalue * 7),
															   gameboard.getSprite(1, j)->getPosition().y, 0.0f));
						gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(gameboard.getSprite(2, 0)->getPosition().x - (updatevalue * 7),
															   gameboard.getSprite(2, 0)->getPosition().y, 0.0f));
					}
				}
				if (gameboard.getPlayer()->getYVelocity() > 0.0002f)
				{
					if (((int)gameboard.getPlayer()->rightside() > (int)gameboard.getSprite(0, i)->getPosition().x) &&
					((int)gameboard.getPlayer()->getPosition().x < (int)gameboard.getSprite(0, i)->rightside()))
					{
						gameboard.getPlayer()->setPosition(D3DXVECTOR3(gameboard.getPlayer()->getPosition().x, (float)oldpositiony, 0.0f));
						gameboard.getPlayer()->setYVelocity(0.0f);
					}
				}
			}
		}
		for (int i = 0; i < gameboard.getSize(1); ++i)
		{
			gameboard.getSprite(1, i)->setPosition(D3DXVECTOR3(gameboard.getSprite(1, i)->getPosition().x - (updatevalue * 7),
														   gameboard.getSprite(1, i)->getPosition().y, 0.0f));
			if (gameboard.getPlayer()->checkForCollision(*gameboard.getSprite(1, i)))
			{
				if (((int)gameboard.getPlayer()->rightside() >= (int)gameboard.getSprite(1, i)->getPosition().x) &&
					((int)gameboard.getPlayer()->getPosition().x <= (int)gameboard.getSprite(1, i)->rightside()))
				{
					gameboard.getPlayer()->setPosition(D3DXVECTOR3((float)oldpositionx, gameboard.getPlayer()->getPosition().y, 0.0f));
					for (int j = 0; j < gameboard.getSize(0); ++j)
					{
						gameboard.getSprite(0, j)->setPosition(D3DXVECTOR3(gameboard.getSprite(0, j)->getPosition().x + (updatevalue * 7),
														   gameboard.getSprite(0, j)->getPosition().y, 0.0f));
					}
					for (int j = 0; j < gameboard.getSize(1); ++j)
					{
						gameboard.getSprite(1, j)->setPosition(D3DXVECTOR3(gameboard.getSprite(1, j)->getPosition().x + (updatevalue * 7),
														   gameboard.getSprite(1, j)->getPosition().y, 0.0f));
					}
							gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(gameboard.getSprite(2, 0)->getPosition().x + (updatevalue * 7),
														   gameboard.getSprite(2, 0)->getPosition().y, 0.0f));
				}
				if (gameboard.getPlayer()->getYVelocity() > 0.0002f)
				{
					if (((int)gameboard.getPlayer()->rightside() > (int)gameboard.getSprite(1, i)->getPosition().x) &&
					((int)gameboard.getPlayer()->getPosition().x < (int)gameboard.getSprite(1, i)->rightside()))
					{
						gameboard.getPlayer()->setPosition(D3DXVECTOR3(gameboard.getPlayer()->getPosition().x, (float)oldpositiony, 0.0f));
						gameboard.getPlayer()->setYVelocity(0.0f);
					}
				}
			}
		}
		gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(gameboard.getSprite(2, 0)->getPosition().x - (updatevalue * 7),
														   gameboard.getSprite(2, 0)->getPosition().y, 0.0f));
		if (gameboard.getPlayer()->checkForCollision(*gameboard.getSprite(2, 0)))
		{
			if (((int)gameboard.getPlayer()->rightside() >= (int)gameboard.getSprite(2, 0)->getPosition().x) &&
					((int)gameboard.getPlayer()->getPosition().x <= (int)gameboard.getSprite(2, 0)->rightside()))
				{
					MessageBox(NULL, L"You win!", L"", MB_OK);
					gameboard.clearVectors();
					gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground1.txt");
					gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground2.txt");
					gameboard.loadFromFile(m_pD3DDevice, w_pTexture[1], "platform.txt");
					gameboard.getPlayer()->setPosition(D3DXVECTOR3((gameboard.getSprite(0, 0)->getPosition().x + 200), 
																   (gameboard.getSprite(0, 0)->getPosition().y - 50 - 16), 0.0f));
					gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(1300.0f, 300.0f, 0.0f));
			}
		}
		if (gameboard.getPlayer()->getPosition().y > 600.0f)
		{
			MessageBox(NULL, L"You lose!", L"", MB_OK);
			gameboard.clearVectors();
			gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground1.txt");
			gameboard.loadFromFile(m_pD3DDevice, w_pTexture[0], "ground2.txt");
			gameboard.loadFromFile(m_pD3DDevice, w_pTexture[1], "platform.txt");
			gameboard.getPlayer()->setPosition(D3DXVECTOR3((gameboard.getSprite(0, 0)->getPosition().x + 200), 
														   (gameboard.getSprite(0, 0)->getPosition().y - 50 - 16), 0.0f));
			gameboard.getSprite(2, 0)->setPosition(D3DXVECTOR3(1300.0f, 300.0f, 0.0f));
		}*/
		break;
	case CREDITS_SCENE:
		//keyDown5(buffer, dt);
		break;
	case GAME_OVER:
		break;
	case QUIT:
		return true;
		break;
	}
	return false;
	
}


void CDirectXFramework::Render(HWND & hWnd, float & dt)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	rect.right = rect.right - rect.left;
	rect.bottom = rect.bottom - rect.top;
	rect.left = 0;
	rect.top = 0;
	
	if (the_state == MENU)
	{
		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		//	
		//world = calculateMatrix(200, (menuyposition - 32.0f),
		//						m_sprites[3].getScalex(),
		//						m_sprites[3].getScaley(),									
		//						m_sprites[3].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(m_sprites[3].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(32 + 200), 
		//				   (float)(menuyposition), 0),
		//				   &D3DXVECTOR3((float)(200 + 32), 
		//				   (float)(menuyposition + 32), 0), 
		//					D3DCOLOR_ARGB(255, 255, 255, 255));

		//world = calculateMatrix(m_sprites[4].getPosition().x, (m_sprites[4].getPosition().y),
		//						m_sprites[4].getScalex(),
		//						m_sprites[4].getScaley(),									
		//						m_sprites[4].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(m_sprites[4].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(128 + m_sprites[4].getPosition().x), 
		//				   (float)(m_sprites[4].getPosition().y), 0),
		//				   &D3DXVECTOR3((float)(m_sprites[4].getPosition().x + 128), 
		//				   (float)(m_sprites[4].getPosition().y + 32), 0), 
		//					D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
		
		m_pD3DDevice->BeginScene();

		m_pD3DSprite->Begin(NULL);

		RECT displayclip;
		displayclip.top = 250;
		displayclip.left = 300;
		displayclip.bottom = 640;
		displayclip.right = 800;

		//wchar_t buffer[64];
		//
		//swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		//m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//
		//wchar_t buffer2[64];
		//
		//swprintf_s(buffer, 64, L"%s", L"PLAY");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 325;

		//swprintf_s(buffer, 64, L"%s", L"CREDITS SCENE");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 400;

		//swprintf_s(buffer, 64, L"%s", L"QUIT");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		//
		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}
	if (the_state == INIT)
	{
		float numFrames = 0.0f;
		float timeElapsed = 0.0f;
		float mFPS = 0.0f;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

		//for (int i = 0; i < 10; i++)
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		world = calculateMatrix(i * 64, j * 64, m_sprites[0].getScalex(), 
		//			                    m_sprites[0].getScaley(), m_sprites[0].getRotation());
		//		m_pD3DSprite->SetTransform(&world);
		//		m_pD3DSprite->Draw(m_sprites[0].getTexture(), NULL, &D3DXVECTOR3((float)(32 + (i * 64)), (float)(32 + (j * 64)), 0),
		//						   &D3DXVECTOR3((float)((i * 64) + 32), (float)((j * 64) + 32), 0), 
		//					       D3DCOLOR_ARGB(255, 255, 255, 255));
		//	}
		//}
		//for (int i = 0; i < 40; i++)
		//{
		//	if (gameboard.getActive() == 0)
		//	{
		//		if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
		//		{
		//			world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
		//									(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
		//									gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
		//									gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
		//									gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
		//			m_pD3DSprite->SetTransform(&world);
		//			m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
		//							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
		//							   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
		//							   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
		//							   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
		//								D3DCOLOR_ARGB(255, 255, 255, 255));
		//		}
		//	}
		//	else if (gameboard.getActive() == 1)
		//	{
		//		if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
		//		{
		//			world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
		//									(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
		//									gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
		//									gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
		//									gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
		//			m_pD3DSprite->SetTransform(&world);
		//			m_pD3DSprite->Draw(b_sprites[0].getTexture(), NULL, 
		//							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
		//						       (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
		//						       &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
		//						       (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
		//							   D3DCOLOR_ARGB(255, 255, 255, 255));
		//		}
		//	}
		//}
		//for (int i = 0; i < 40; i++)
		//{
		//	if (gameboard.getActive() == 1)
		//	{
		//		if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
		//		{
		//			world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
		//									(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
		//									gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
		//									gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
		//									gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
		//			m_pD3DSprite->SetTransform(&world);
		//			m_pD3DSprite->Draw(gameboard.getPlayer(1)->getGamePiece(i)->getTexture(), NULL, 
		//							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
		//						       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
		//						       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
		//						       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
		//						       D3DCOLOR_ARGB(255, 255, 255, 255));
		//		}
		//	}
		//	else if (gameboard.getActive() == 0)
		//	{	
		//		if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
		//		{
		//			world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
		//									(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
		//									gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
		//									gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
		//									gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
		//			m_pD3DSprite->SetTransform(&world);
		//			m_pD3DSprite->Draw(b_sprites[1].getTexture(), NULL, 
		//							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
		//						       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
		//						       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
		//						       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
		//							   D3DCOLOR_ARGB(255, 255, 255, 255));
		//		}
		//	}
		//}
		//world = calculateMatrix((initPosition.x * 64), 
		//						(initPosition.y * 64), 
		//						g[pieceType].getScalex(),
		//						g[pieceType].getScaley(),
		//						g[pieceType].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(g[pieceType].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
		//				   (float)(32 + (initPosition.y * 64)), 0),
		//				   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
		//				   (float)((initPosition.y * 64) + 32), 0), 
		//				   D3DCOLOR_ARGB(255, 255, 255, 255));
		//world = calculateMatrix((initPosition.x * 64), 
		//						(initPosition.y * 64), 
		//						g[pieceType].getScalex(),
		//						g[pieceType].getScaley(),
		//						g[pieceType].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
		//				   (float)(32 + (initPosition.y * 64)), 0),
		//				   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
		//				   (float)((initPosition.y * 64) + 32), 0), 
		//				   D3DCOLOR_ARGB(255, 255, 255, 255));
		//world = calculateMatrix(640, 0, 
		//						g[pieceType].getScalex() * 2.5,
		//						g[pieceType].getScaley() * 2.5,
		//						g[pieceType].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(g[pieceType].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
		//				   (float)(32 + (initPosition.y * 64)), 0),
		//				   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
		//				   (float)((initPosition.y * 64) + 32), 0), 
		//				   D3DCOLOR_ARGB(255, 255, 255, 255));
		//world = calculateMatrix(640, 0, 
		//						g[pieceType].getScalex() * 2.5,
		//						g[pieceType].getScaley() * 2.5,
		//						g[pieceType].getRotation());
		//m_pD3DSprite->SetTransform(&world);
		//m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
		//				   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
		//				   (float)(32 + (initPosition.y * 64)), 0),
		//				   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
		//				   (float)((initPosition.y * 64) + 32), 0), 
		//				   D3DCOLOR_ARGB(255, 255, 255, 255));

		//numFrames += 1.0f;
		//timeElapsed += dt;

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();

		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(NULL);

		//if (timeElapsed >= 1.0f)
		//{
		//	mFPS = numFrames / dt;
		//	timeElapsed = 0.0f;
		//	numFrames = 0.0f;
		//}

		//wchar_t buffer[64];
		//
		//swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		//m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//
		//RECT displayclip;
	 //	displayclip.top = ((64 * 2) + 30 + 1);
		//displayclip.left = (640 + 0 + 1);
		//displayclip.bottom = ((64 * 2) + 1 + 30 + 64);
		//displayclip.right = 800;

		//wchar_t buffer2[64];

		//swprintf_s(buffer2, 64, L"%hs", g[pieceType].getName());

		//m_classicfont->DrawText(0, buffer2, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
	if (the_state == PROGRAM)
	{
		float numFrames = 0.0f;
		float timeElapsed = 0.0f;
		float mFPS = 0.0f;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(NULL);

		gameboard.draw(m_pD3DDevice, m_pD3DSprite, &world);

		

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();		
		
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
		

	}

	if (the_state == CREDITS_SCENE)
	{

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
			
		m_pD3DDevice->BeginScene();

		m_pD3DSprite->Begin(NULL);

		//RECT displayclip;
		//displayclip.top = 0;
		//displayclip.left = 0;
		//displayclip.bottom = 640;
		//displayclip.right = 800;

		//wchar_t buffer[64];
		//
		//swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		//m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//
		//wchar_t buffer2[64];
		//
		//swprintf_s(buffer, 64, L"%s", L"MADE BY:");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 75;
		//displayclip.left = 75;

		//swprintf_s(buffer, 64, L"%s", L"JAMES SORGE");
		//
		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 150;
		//displayclip.left = 0;

		//swprintf_s(buffer, 64, L"%s", L"CLASS FOR:");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 225;
		//displayclip.left = 75;

		//swprintf_s(buffer, 64, L"%s", L"GSP 361");
		//
		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 300;
		//displayclip.left = 0;

		//swprintf_s(buffer, 64, L"%s", L"PROFESSOR:");

		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		//displayclip.top = 375;
		//displayclip.left = 75;

		//swprintf_s(buffer, 64, L"%s", L"MICHAEL VAGANOV");
		//
		//m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		
		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}

}

void CDirectXFramework::Shutdown()
{
	//*************************************************************************
	// Release COM objects in the opposite order they were created in
	delete [] movepositions;

	system->release();
	
	m_Mouse->Release();

	m_Keyboard->Release();

	m_DInput->Release();
	
	// Sprite
	m_pD3DSprite->Release();
	// Font
	m_pD3DFont->Release();
	// 3DDevice	
	m_pD3DDevice->Release();	
	// 3DObject
	m_pD3DObject->Release();

	CoUninitialize();
	//*************************************************************************

}

D3DXMATRIX & calculateMatrix(int x, int y, float scalex, float scaley, float angle)
{
	D3DXMATRIX scale, rot, trans, world;
	
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rot);
	D3DXMatrixIdentity(&world);
	D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
	D3DXMatrixTranslation(&trans, x, y, 0);
	D3DXMatrixScaling(&scale, scalex, scaley, 0);
	world = rot * scale * trans;
	return world;	
}

float CDirectXFramework::keyDown(BYTE buffer[], Player * p, float dt)
{
	if ((buffer[DIK_UP] & 0x80) && !pressed[DIK_UP])
	{
		if (!pressed[DIK_UP])
		{
			if (p->getPosition().y < 150.0f)
			{
				p->setYVelocity(p->getYVelocity() - 0.0003f);
				pressed[DIK_UP] = true;
			}
			else
			{
				p->setYVelocity(p->getYVelocity() - 0.0003f);
			}
		}
	}
	else
	{
		//press key resetter
		
		if (buffer[DIK_UP] & 0x80)
		{}
		else
		{
			pressed[DIK_UP] = false;
		}
	}
	if (buffer[DIK_RIGHT] & 0x80)
	{
		p->setPosition(D3DXVECTOR3(p->getPosition().x + 0.25f, p->getPosition().y, 0.0f));
		return 0.25f;
	}
	if (buffer[DIK_LEFT] & 0x80)
	{
		p->setPosition(D3DXVECTOR3(p->getPosition().x - 0.25f, p->getPosition().y, 0.0f));
		return -0.25f;
	}
	return 0.0f;
}



//
//void CDirectXFramework::loadFromFile (char * filename)
//{
//using namespace std;
//int Map[1000][1000];
//int loadCounterX =0;
//int loadCounterY =0;
//int mapSizeX;
//int mapSizeY;
//bool once = false;
//
//ifstream openfile (filename);
//	if (openfile.is_open())
//	{
//		while(!openfile.eof())
//		{
//			if(once == false)
//			{
//				openfile >> mapSizeX >> mapSizeY;
//				once = true;
//			}
//			openfile >>Map[loadCounterX][loadCounterY];
//			loadCounterX++;
//			if(loadCounterX >= mapSizeX)
//			{
//				loadCounterX = 0;
//				loadCounterY++;
//			}
//		}// get contents from file 
//	}//is file open
//}//end of loadFromFile


 #include <string>
 #include <fstream>
 #include <Windows.h>


 
// #define DIRECTINPUT_VERSION 0x0800
//@@ -1022,35 +1028,119 @@ float CDirectXFramework::keyDown(BYTE buffer[], Player * p, float dt)

 
 



//BITMAP*Buffer=create_bitmap(800,600);
//bool done = false
//std::vector <std::vector<int>>Map;
//std::vector <BITMAP*> text;

//LoadMap("Map1.txt", Map, texture, done);
//
//while (!done)
//{
//	if(key[KEY_ESC])
//		done =true;
//
//	DrawMap(Buffer, Map);
//
//	blit (Buffer, screen, 0,0,0,0,800,600);
//	clear_bitmap(buffer);
//
//}
//destroy_bitmap(Buffer);
// return 0;

#define BlockSizeX 40
#define BlockSizeY 40

enum LoadState {TEXTURE, MAP};

int state = TEXTURE;

void CDirectXFramework::LoadMap (const char * filename, std::vector <std::vector <int> > &map, std::vector<BITMAP*> &texture,bool &done)
 {
	//bool once = false;
//int loadCounterX =0;
//int loadCounterY =0;
//2D array
//using namespace std;
std::ifstream openfile (filename);
std::string tempLine;
std::vector<int> tempVector;

 	if (openfile.is_open())
 	{
		//openfile >> mapSizeX;
		//openfile >> mapSizeY;
 		while(!openfile.eof())
 		{

			tempVector.clear();
			std::getline(openfile, tempLine);
			std::stringstream str (tempLine);
			if(tempLine.find("[Texture]") != std::string::npos)
			{
			state = LoadState::TEXTURE;
			continue;
			}
			else if (tempLine.find("[Map]") != std::string::npos)
 			{
			state = LoadState::MAP;
			continue;
 			}

			switch(state)
 			{
			case LoadState::TEXTURE:
				if(tempLine.length() > 0)
					texture.push_back(load_bitmap(tempLine.c_str(), NULL));
				break;
			case LoadState::MAP:
				tempLine.erase(tempLine.find_last_not_of(" \n\r\t")+1);
				std::stringstream str (tempLine);
				while(!str.eof())
				{
				std::string s;
				std::getline(str, s, ' ');
				tempVector.push_back(atoi(s.c_str()));
				}
				map.push_back(tempVector);
				break;
	
 			}
 		}// get contents from file 
 	}//is file open
	else
	{
	//message fail to locate file ,filename
	done = true;
	}
}//end of loadFromFile

void CDirectXFramework::DrawMap (BITMAP*Buffer, std::vector <std::vector <int> > map, std::vector <BITMAP*> texture)
{
	//int color= 0;

	for (int i = 0; i < map.size() ; i++)
	{
		for (int j = 0; j < map[i].size() ; j++)
		{
			if (map[i][j] != ' ')
			{
//			draw_sprite(Buffer, texture[map[i][j]], j* BlockSizeX, i * BlockSizeY);
			}
			else
			{
//			rectfill(Buffer, j * BlockSizeX, i * BlockSizeY, j * BlockSizeX + BlockSizeX, i * BlockSizeY + BlockSizeY,makecol(0,148,255));
			}

		}
	}
}







//int Map[100][100]
//LoadMap("Map1.txt" , Map ,done);
//BITMAP*Tiles[2];
//
//Tiles[#] = load_bitmap ("  ", NULL);
//Tiles[1] = load_bitmap ("  ", NULL);
//Tiles[3] = load_bitmap ("  ", NULL);
//
//bool done = false;

