#pragma once
/**
* @file IRenderer.h
* @brief レンダラー用インターフェイス
* @author 松尾裕也
* @date 2016/3/3
*/
#include <gslib.h>
struct MeshRenderDesc;
struct SpriteRenderDesc;
struct LookAtDesc;
struct StringRenderDesc;
class IRenderer
{
public:
	virtual ~IRenderer() {}
	virtual void begin() = 0;
	//描画終了
	virtual void end() = 0;
	//画面消去
	virtual void clear(const GScolor& _color) = 0;
	//カメラ
	virtual void lookAt(const LookAtDesc& _desc) = 0;
	//描画(コマンドの追加)
	virtual void draw(const MeshRenderDesc& _desc) = 0;
	//スプライト描画
	virtual void draw(const SpriteRenderDesc& _desc) = 0;
	//文字列描画
	virtual void draw(const StringRenderDesc& _desc) = 0;

	//同期を取る
	virtual void sync() = 0;
};