//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX		(100)		// バレットのMax数
#define BULLET_SPEED	(6.0f)		// バレットの移動スピード


// バレット構造体
struct BULLET
{
	BOOL				use;				// true:使っている  false:未使用
	float				w, h;				// 幅と高さ
	float				progress;			//
	XMFLOAT3			pos;				// バレットの座標
	XMFLOAT3			pos_prev;			//バレットの前座標
	XMFLOAT3			pos_start;			//バレットの前座標
	int					target_ID;			//バレットの前座標
	XMFLOAT3			pos_arc;			//バレットの前座標
	XMFLOAT3			rot;				// バレットの回転量
	XMFLOAT3			move;				// バレットの移動量
	int					countAnim;			// アニメーションカウント
	int					patternAnim;		// アニメーションパターンナンバー
	int					texNo;				// 何番目のテクスチャーを使用するのか

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(XMFLOAT3 pos);


