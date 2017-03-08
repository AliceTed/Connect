#pragma once
/**
* @file Desk.h
* @brief �R�}�Ǘ��p
* @author �����T��
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
	* @brief �w��̃��P�[�V�����ɃR�}��z�u����
	*/
	virtual void placePiece(const IntVector2 & _location, CONTROLLER_ID _id) override;
	
	/**
	* @fn
	* @brief �󂢂Ă�ŏ��̃��P�[�V�������擾
	* @return �󂢂Ă��Ȃ��ꍇERR_LOCATION�@��Ԃ�
	*/
	virtual IntVector2 getFreeMinimalLocation()const override;
	/**
	* @fn
	* @brief �w��c��̋󂢂Ă郍�P�[�V�������擾
	* @param (_column) �w��c��
	* @return �󂢂Ă��Ȃ��ꍇERR_LOCATION�@��Ԃ�
	* @detail �󂢂Ă����ԉ��̃��P�[�V������Ԃ�
	*/
	IntVector2 getFreeSpaceColumn(unsigned int _column)const;
	/**
	* @fn
	* @brief �w�胍�P�[�V�������J���Ă��邩
	* @param (_location) �w�胍�P�[�V����
	* @return true �󂢂Ă��� ,false �󂢂Ă��Ȃ�
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
