#pragma once
/**
* @file Renderer.h
* @brief マルチスレッドレンダラー
* @author 松尾裕也
* @date 2016/3/2
*/
//ActiveObjectパターン

#include "IRenderer.h"
#include "DisplayList.h"
#include "../thread/CriticalSection.h"

class Renderer:public IRenderer
{
public:
	Renderer();
	//描画開始
	virtual void begin()override;
	//描画終了
	virtual void end()override;
	//画面消去
	virtual void clear(const GScolor& _color)override;
	//カメラ
	virtual void lookAt(const LookAtDesc& _desc)override;
	//描画(コマンドの追加)
	virtual void draw(const MeshRenderDesc& _desc)override;
	//スプライト描画
	virtual void draw(const SpriteRenderDesc& _desc)override;
	//文字列描画
	virtual void draw(const StringRenderDesc& _desc)override;

	//スフィアシェーダ描画
	virtual void draw(const SphereShaderDesc & _desc) override;
	//スカイボックス描画
	virtual void draw(const SkyBoxRenderDesc & _desc) override;

	//同期を取る
	virtual void sync()override;
	//ディスプレイリストの描画
	void render();
private:
	//現在のディスプレイリストを取得
	int currentDisplayList()const;
	//レンダリングを行うディプレイリストを取得
	int renderDisplayList()const;
	//スワップ
	void swapDisplayList();
	//待機 (trueで待機)
	void wait(const bool& _isWait)const;

	template<class Command,class Desc>
	void drawTemplate(const Desc& _desc)
	{
		CommandPtr command = std::make_unique<Command>(_desc);
		m_displayList[currentDisplayList()].add(command);
	}
private:
	//ディスプレイ(ダブルバッファように２つ)
	std::vector<DisplayList> m_displayList;
	//DisplayList m_displayList[2];
	//現在のディスプレイリスト
	int m_currentDisplay;
	//現在描画中か？
	bool m_isRendering;
	//コマンド設定中か？
	bool m_isAddCommand;
	//同期中か？
	bool m_isSync;
	//クリティカルセクション
	CriticalSection m_lock;
};