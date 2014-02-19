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
//#include <allegro.h>

using namespace std;

#define DIRECTINPUT_VERSION 0x0800

bool keyDown(BYTE [], The_Sprite &, float);
bool mouseDown(DIMOUSESTATE2, The_Sprite &, int &);

const long int jumptimeout = 1000;

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


	system->createSound("Airburshed.mp3", FMOD_DEFAULT, 0, &sound);

	gameboard.init();

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"BackImage2.jpg", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &backgroundTexture);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Purple_Blob.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &playerTexture[0]);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Power1NotActive.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &playerTexture[1]);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Power2Active.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &playerTexture[2]);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Power3Active.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &playerTexture[3]);
	
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"basic_block.png", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255, 255), NULL, NULL, &blockTexture);

	gameboard.getLevel(0)->getBackground()->setTexture(backgroundTexture);
	gameboard.getLevel(0)->getBackground()->setWidth(width);
	gameboard.getLevel(0)->getBackground()->setHeight(height);
	gameboard.getLevel(0)->getBackground()->setScalex(2800 / 640);
	gameboard.getLevel(0)->getBackground()->setScaley(1640 / 480);
	gameboard.getLevel(0)->getBackground()->setRotation(0.0f);
	gameboard.getLevel(0)->getBackground()->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	gameboard.getLevel(0)->getBackground()->setRect();

	gameboard.getLevel(0)->getBlock()->setTexture(blockTexture);
	gameboard.getLevel(0)->getBlock()->setWidth(32);
	gameboard.getLevel(0)->getBlock()->setHeight(32);
	gameboard.getLevel(0)->getBlock()->setScalex(1.0f);
	gameboard.getLevel(0)->getBlock()->setScaley(1.0f);
	gameboard.getLevel(0)->getBlock()->setRotation(0.0f);
	//gameboard.getLevel(0)->getBlock()->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	gameboard.getLevel(0)->getBlock()->setRect();

	gameboard.getPlayer()->setTexture(playerTexture[0]);
	gameboard.getPlayer()->setTextureList(playerTexture);
	gameboard.getPlayer()->setWidth(32);
	gameboard.getPlayer()->setHeight(32);
	gameboard.getPlayer()->setScalex(1.0f);
	gameboard.getPlayer()->setScaley(1.0f);
	gameboard.getPlayer()->setRotation(0.0f);
	//gameboard.getPlayer()->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	gameboard.getPlayer()->setRect();

	gameboard.getLevel(0)->init("BASIC_MAP.txt", gameboard.getLevel(0)->getBlock(), gameboard.getPlayer());

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

	elapsed_time = 0;
}

bool CDirectXFramework::Update(float & dt)
{
	updatevalue = 0x0;
	bool playingmusic = false;
	long evCode;
	LONG_PTR eventParam1, eventParam2;
	m_Keyboard->Acquire();
	m_Mouse->Acquire();
	m_Keyboard->GetDeviceState(sizeof(buffer), (void **)&buffer);
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void **)&m_MouseState);

	Object * o = NULL;
	int statememory;
	switch(the_state)
	{
	case MENU:
		playingmusic = false;
		channel->isPlaying(&playingmusic);
		if (!playingmusic)
		{
			result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
		}
		updatevalue = keyDown2(buffer, gameboard.getPlayer(), dt);
		//menu.updateState(updatevalue, dt);
		break;
	case INIT:

		break;
	case PROGRAM:
		playingmusic = false;
		channel->isPlaying(&playingmusic);
		if (!playingmusic)
		{
			result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
		}
		updatevalue = keyDown(buffer, gameboard.getPlayer(), dt);
	
		statememory = gameboard.getPlayer()->UpdateState(updatevalue, dt);

		//statememory = gameboard.checkForCollision();

		if (statememory == 1)
		{
			pressed[DIK_UP] = false;
			pressed[DIK_W] = false;
			elapsed_time = 0;
		}
		if (statememory == 3)
		{
			if (buffer[DIK_UP] & 0x80)
			{
				MessageBox(NULL, L"You win!", L"", MB_OK);
				gameboard.clearVectors();
			}
		}
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

		//menu.draw(m_pD3DDevice, m_pD3DSprite, &world);

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

		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();

		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(NULL);

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

unsigned int CDirectXFramework::keyDown(BYTE buffer[], Player * p, float dt)
{
	unsigned int updatevalue = 0x0;
	if ((buffer[DIK_RETURN] & 0x80) && !pressed[DIK_RETURN])
	{
		if (!pressed[DIK_RETURN])
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_RETURN] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_RETURN] & 0x80)
		{}
		else
		{
			pressed[DIK_RETURN] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_SPACE] & 0x80) && !pressed[DIK_SPACE])
	{
		if (!pressed[DIK_SPACE])
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_SPACE] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_SPACE] & 0x80)
		{}
		else
		{
			pressed[DIK_SPACE] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_3] & 0x80) && !pressed[DIK_3]) || ((buffer[DIK_0] & 0x80) && !pressed[DIK_0]))
	{
		if ((!pressed[DIK_3]) || (!pressed[DIK_0]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_3] = true;
			pressed[DIK_0] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_3] & 0x80)
		{}
		else
		{
			pressed[DIK_3] = false;
		}
		if (buffer[DIK_0] & 0x80)
		{}
		else
		{
			pressed[DIK_0] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_2] & 0x80) && !pressed[DIK_2]) || ((buffer[DIK_9] & 0x80) && !pressed[DIK_9]))
	{
		if ((!pressed[DIK_2]) || (!pressed[DIK_9]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_2] = true;
			pressed[DIK_9] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_2] & 0x80)
		{}
		else
		{
			pressed[DIK_2] = false;
		}
		if (buffer[DIK_9] & 0x80)
		{}
		else
		{
			pressed[DIK_9] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_1] & 0x80) && !pressed[DIK_1]) || ((buffer[DIK_8] & 0x80) && !pressed[DIK_8]))
	{
		if ((!pressed[DIK_1]) || (!pressed[DIK_8]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_1] = true;
			pressed[DIK_8] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_1] & 0x80)
		{}
		else
		{
			pressed[DIK_1] = false;
		}
		if (buffer[DIK_8] & 0x80)
		{}
		else
		{
			pressed[DIK_8] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_DOWN] & 0x80) && !pressed[DIK_DOWN]) || ((buffer[DIK_S] & 0x80) && !pressed[DIK_S]))
	{
		if ((!pressed[DIK_DOWN]) || (!pressed[DIK_S]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_DOWN] = true;
			pressed[DIK_S] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_DOWN] & 0x80)
		{}
		else
		{
			pressed[DIK_DOWN] = false;
		}
		if (buffer[DIK_S] & 0x80)
		{}
		else
		{
			pressed[DIK_S] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_UP] & 0x80) && !pressed[DIK_UP]) || ((buffer[DIK_W] & 0x80) && !pressed[DIK_W]))
	{
		if (!pressed[DIK_UP] || !pressed[DIK_W])
		{
			if (elapsed_time > jumptimeout)
			{
				updatevalue = updatevalue | 0x1;
				pressed[DIK_UP] = true;
				pressed[DIK_W] = true;
				elapsed_time += (long int)dt;
			}
			else
			{
				updatevalue = updatevalue | 0x1;
				elapsed_time += (long int)dt;
			}
		}
	}
	else
	{
		//press key resetter
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_RIGHT] & 0x80) || buffer[DIK_S] & 0x80)
	{
		updatevalue = updatevalue | 0x1;
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_LEFT] & 0x80) || buffer[DIK_A] & 0x80)
	{
		updatevalue = updatevalue | 0x1;
	}	
	
	return updatevalue;
}

unsigned int CDirectXFramework::keyDown2(BYTE buffer[], Player * p, float dt)
{
	unsigned int updatevalue = 0x0;
	if ((buffer[DIK_RETURN] & 0x80) && !pressed[DIK_RETURN])
	{
		if (!pressed[DIK_RETURN])
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_RETURN] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_RETURN] & 0x80)
		{}
		else
		{
			pressed[DIK_RETURN] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_SPACE] & 0x80) && !pressed[DIK_SPACE])
	{
		if (!pressed[DIK_SPACE])
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_SPACE] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_SPACE] & 0x80)
		{}
		else
		{
			pressed[DIK_SPACE] = false;
		}
	}
	updatevalue = updatevalue << 1;
	updatevalue = updatevalue << 1;
	updatevalue = updatevalue << 1;
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_DOWN] & 0x80) && !pressed[DIK_DOWN]) || ((buffer[DIK_S] & 0x80) && !pressed[DIK_S]))
	{
		if ((!pressed[DIK_DOWN]) || (!pressed[DIK_W]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_DOWN] = true;
			pressed[DIK_S] = true;
		}
	}
	else
	{
		//press key resetter

		if (buffer[DIK_DOWN] & 0x80)
		{}
		else
		{
			pressed[DIK_DOWN] = false;
		}
		if (buffer[DIK_S] & 0x80)
		{}
		else
		{
			pressed[DIK_S] = false;
		}
	}
	updatevalue = updatevalue << 1;
	if (((buffer[DIK_UP] & 0x80) && !pressed[DIK_UP]) || ((buffer[DIK_W] & 0x80) && !pressed[DIK_W]))
	{
		if ((!pressed[DIK_UP]) || (!pressed[DIK_W]))
		{
			updatevalue = updatevalue | 0x1;
			pressed[DIK_UP] = true;
			pressed[DIK_W] = true;
		}
		else
		{
			updatevalue = updatevalue | 0x1;
		}
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_RIGHT] & 0x80) && buffer[DIK_A] & 0x80)
	{
		updatevalue = updatevalue | 0x1;
	}
	updatevalue = updatevalue << 1;
	if ((buffer[DIK_LEFT] & 0x80) && buffer[DIK_D] & 0x80)
	{
		updatevalue = updatevalue | 0x1;
	}	
	
	return updatevalue;
}

std::vector <std::vector<int>>Map;
std::vector <BITMAP*> text;



#define BlockSizeX 40
#define BlockSizeY 40

enum LoadState {TEXTURE, MAP};

int state = TEXTURE;
