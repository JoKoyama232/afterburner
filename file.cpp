//=============================================================================
//
// ファイル処理 [file.cpp]
// Author : 
//
//=============================================================================

/******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "file.h"
#include "score.h"


/*******************************************************************************
* マクロ定義
*******************************************************************************/



/*******************************************************************************
* 構造体定義
*******************************************************************************/



/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/



/*******************************************************************************
マクロ定義
*******************************************************************************/



/*******************************************************************************
* グローバル変数
*******************************************************************************/
SAVEDATA	save;		// セーブデータ作成場所


/*******************************************************************************
関数名:	void SaveData( void )
引数:	void
戻り値:	void
説明:	セーブデータを作成し、ファイルへ出力する
*******************************************************************************/
void SaveData(void)
{
	{	// プレイヤーデータをセーブする
		PLAYER *player = GetPlayer();

		// プレイヤーの人数分セーブする
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			save.player[i] = player[i];
		}
	}

	{	// エネミーデータをセーブする
		ENEMY *enemy = GetEnemy();

		// エネミーの人数分セーブする
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			save.enemy[i] = enemy[i];
		}
	}


	// スコアデータをセーブする
	save.score = GetScore();


	// セーブデータのチェックサムを求める
	{
		char *adr = (char *)&save;	// デーブデータの先頭アドレスをadrに入れる
		int  sum = 0;				// 計算するチェックサム

		save.sum = 0;				// セーブデータ側のチェックサムを０でクリアしていく

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			if (i % 10 * 3 + i % 7 < 4) {
				sum += adr[i] * 3;
			}
			else {
				sum += adr[i];
			}
		}

		save.sum = sum;
	}



	// SAVEDATA構造体ごと全部をファイルに出力する
	FILE *fp;

	printf("\nセーブ開始・・・");
	fp = fopen("savedata.bin", "wb");			// ファイルをバイナリ書き込みモードでOpenする

	if (fp != NULL)								// ファイルがあれば書き込み、無ければ無視
	{	
		fwrite(&save, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスから指定したバイト数分ファイルへ書き込む
		fclose(fp);								// Openしていたファイルを閉じる
		printf("終了！\n");
	}
	else
	{
		printf("ファイルエラー！\n");
	}

}


/*******************************************************************************
関数名:	void LoadData( void )
引数:	void
戻り値:	void
説明:	セーブデータをファイルから読み込む
*******************************************************************************/
void LoadData(void)
{
	PLAYER *player = GetPlayer();	// プレイヤーのアドレスを取得する
	ENEMY  *enemy  = GetEnemy();	// エネミーのアドレスを取得する

	// ファイルからセーブデータを読み込む
	FILE* fp;

	printf("\nロード開始・・・");
	fp = fopen("savedata.bin", "rb");	// ファイルをバイナリ読み込みモードでOpenする

	if (fp != NULL)						// ファイルがあれば書き込み、無ければ無視
	{
		fread(&save, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスへ指定したバイト数分ファイルから読み込む
		fclose(fp);								// Openしていたファイルを閉じる
		printf("終了！\n");
	}
	else
	{
		printf("ファイルエラー！\n");
	}


	// セーブデータのチェックサムが合っているか調べる
	{
		char *adr = (char *)&save;	// デーブデータの先頭アドレスをadrに入れる
		int  sum = 0;				// 計算するチェックサム
		int  org = save.sum;		// セーブデータ内のチェックサム

		save.sum = 0;				// セーブデータ側のチェックサムを０でクリアしていく

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			if (i % 10 * 3 + i % 7 < 4) {
				sum += adr[i] * 3;
			}
			else {
				sum += adr[i];
			}
		}

		// 元々のチェックサムと再計算したチェックサムが同じか調べている
		if (sum != org)
		{
			// データが改ざんされている！
			return;
		}
	}



	// プレイヤーの人数分、playerワークへ戻す
	{	// プレイヤーデータをロードする
		PLAYER *player = GetPlayer();

		// プレイヤーの人数分ロードする
		for (int i = 0; i < PLAYER_MAX; i++)
		{
			player[i] = save.player[i];
		}
	}

	{	// エネミーデータをロードする
		ENEMY *enemy = GetEnemy();

		// エネミーの人数分ロードする
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			enemy[i] = save.enemy[i];
		}
	}

	// スコアデータをロードする
	SetScore(save.score);


}



