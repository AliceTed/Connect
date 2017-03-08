#pragma once
/**
* @file Desk.h
* @brief コマ管理用
* @author 松尾裕也
* @date 2016/2/8
*/
#include <vector>
#include "DeskDefine.h"
#include "IDeskMediator.h"
class IRenderer;
class Desk:public IDeskMediator
{
public:
	Desk();
	virtual ~Desk()override;
	virtual bool isFinish() const override;
	virtual bool isWin(const Rule & _rule,const IntVector2& _location,CONTROLLER_ID _id)  override;
	virtual void accept(IDeskVisitor * _visitor) const override;
	
	virtual std::vector<IntVector2> getFreeLoactions() const override;
	/**
	* @fn
	* @brief 指定のロケーションにコマを配置する
	*/
	virtual void placePiece(const IntVector2 & _location, CONTROLLER_ID _id) override;
	
	/**
	* @fn
	* @brief 空いてる最小のロケーションを取得
	* @return 空いていない場合ERR_LOCATION　を返す
	*/
	virtual IntVector2 getFreeMinimalLocation()const override;
	/**
	* @fn
	* @brief 指定縦列の空いてるロケーションを取得
	* @param (_column) 指定縦列
	* @return 空いていない場合ERR_LOCATION　を返す
	* @detail 空いている一番下のロケーションを返す
	*/
	IntVector2 getFreeSpaceColumn(unsigned int _column)const;
	/**
	* @fn
	* @brief 指定ロケーションが開いているか
	* @param (_location) 指定ロケーション
	* @return true 空いている ,false 空いていない
	*/
	virtual bool isFreeLocation(const IntVector2& _location)const override;
	void reset();
	void update(float deltaTime);
	void draw(IRenderer* _renderer)const;
	virtual bool isSamePiece(const IntVector2 & _location, CONTROLLER_ID _id) const override;

	virtual void push_back() override;
	virtual void pop_back() override;
private:
	
	void make_piece();
private:
	Container m_conatainer;	
	std::vector<Container> m_list;
};
