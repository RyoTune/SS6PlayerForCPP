﻿/**
	SS6Player for CPP(C++/ssbp2)
	Platform: OpenGL(GLFW+GLEW)

	Copyright(C) Web Technology Corp.
	All rights reserved.
*/
/* ========================================================================== */
/* MEMO:                                                                      */
/* 特殊な部位で、恐らく各プラットフォームのmain.cppあたりからしか呼ばれない部 */
/* 位です。                                                                   */
/* SS6Playerで使用しているプラットフォーム用の定型処理関数を実装しています。  */
/* ※基本的には定型になるはずなのですが、プラットフォーム毎で内部実装や引数が */
/*   専用になる場合があるため、Platform部分に積んでいます。                   */
/* ========================================================================== */
#pragma once

/* -------------------------------------------------------------------------- */
/*                                                 Includes / Compile-Options */
/* -------------------------------------------------------------------------- */
#include "ss6player_types.h"

namespace SpriteStudio6	{
/* -------------------------------------------------------------------------- */
/*                                                Defines (Value-Type Macros) */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                            Classes / Structures / Typedefs */
/* -------------------------------------------------------------------------- */
/* MEMO: 本構造体の内容はプラットフォーム依存します。 */
struct	SettingSystem
{
	/* ----------------------------------------------- Classes, Structs,Interfaces & Typedefs */

	/* ----------------------------------------------- Enums & Constants */
	enum Constant	{
		MAX_LENGTH_PATH = 2048,						/* 基準パスの最大長 */
	};

	enum ValueDefault	{
		/* レンダラ関係 */
		/* MEMO: LIMIT_BUFFER_CHUNKGPU_DELAYDELETEは遅延解放を行うためのGPUメモリの */
		/*       「1回の遅延解放処理でバッファリングできる個数」を示しています。    */
		/*       - Buffer::GPUSingleならバッファを1つ                               */
		/*       - Buffer::GPUMultiならバッファを2つ                                */
		/*       持つ勘定になります。                                               */
		/*       SpriteStudio6::EntityないしはSpriteStudio6::EntityEffectは、内部で */
		/*       Buffer::GPUMultiを14個（PrimitiveBufferで使用している頂点データ +  */
		/*       シェーダ定数）持っていますので、1アニメーションオブジェクト毎で    */
		/*       28個（30個弱）のGPUメモリを使用しています。                        */
		/*       描画～描画の間に解放されるエンティティの数を保証できる分の値にする */
		/*       ことを推奨します。                                                 */
		/*       ※描画バッファを持っているのは、各アニメーションオブジェクトの最親 */
		/*         のエンティティだけなので、子エンティティの分は考慮しないで大丈夫 */
		/*         です（子エンティティは親エンティティの描画オブジェクトを共用して */
		/*         います）。                                                       */
		LIMIT_BUFFER_CHUNKGPU_DELAYDELETE = 1024,	/* 遅延解放用バッファ数 */
	};

	/* ----------------------------------------------- Variables */
	char FilePathBase[Constant::MAX_LENGTH_PATH];	/* ファイル: 基準パス（文字エンコード: UTF-8） */
	int RendererLimitBufferChunkDelayDelete;		/* レンダラ: GPUバッファ遅延解放用バッファリング個数 */

	/* ----------------------------------------------- Functions */
	/* ********************************************************* */
	//! コンストラクタ
	/*!
	@param	なし

	@retval	なし
	*/
	SettingSystem(void)
	{
		memset(FilePathBase, 0x00, sizeof(FilePathBase));	/* クリア方法として今風ではないのだが…… */

		RendererLimitBufferChunkDelayDelete = ValueDefault::LIMIT_BUFFER_CHUNKGPU_DELAYDELETE;
	}

	/* ********************************************************* */
	//! デストラクタ
	/*!
	@param	なし

	@retval	なし
	*/
	~SettingSystem(void)
	{
	}
};

/* -------------------------------------------------------------------------- */
/*                                                                  Variables */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                    Inline-Functions / Function-Type Macros */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                                        Function Prototypes */
/* -------------------------------------------------------------------------- */
/* ********************************************************* */
//! プラットフォーム実装基部の起動
/*!
@param	setting
	システム設定

@retval	関数値
	true == 成功
	false == 失敗

SS6Playerの足回り実装の起動を行います。
SS6Playerの実際の処理を行う前に行ってください。
プラットフォームのライブラリ群の初期起動後に、一度だけ呼び出し
	てください。

settingは本関数の終了後は実体を確保しておく必要はありません
	（単にシステムの設定を引き渡すための情報体です）。
※settingの内容はプラットフォーム依存します。
*/
extern bool SystemBootUp(const SettingSystem& setting);

/* ********************************************************* */
//! プラットフォーム実装基部の終了
/*!
@param	なし

@retval	なし

SS6Playerの足回り実装部を終了します。
プラットフォームのライブラリ群の終了前に、一度だけ呼び出して
	ください。
*/
extern void SystemShutDown(void);

/* ********************************************************* */
//! メインスレッドの定常処理開始
/*!
@param	なし

@retval	なし

メインスレッドの定常処理の開始時に呼び出してください。
*/
extern void SystemProcessMainPre(void);

/* ********************************************************* */
//! メインスレッドの定常処理終了
/*!
@param	なし

@retval	なし

メインスレッドの定常処理の終了寸前に呼び出してください。
*/
extern void SystemProcessMainPost(void);

/* ********************************************************* */
//! 描画スレッドの処理開始
/*!
@param	なし

@retval	なし

描画（描画コマンドリスト作成）スレッドの処理開始時に呼び出し
	てください。
*/
extern void SystemProcessRenderPre(void);

/* ********************************************************* */
//! 描画スレッドの処理終了
/*!
@param	なし

@retval	なし

描画（描画コマンドリスト作成）スレッドの処理終了時に呼び出し
	てください。
※ここでスワップチェインの更新を処理しています。
*/
extern void SystemProcessRenderPost(void);
}	/* SpriteStudio6 */
