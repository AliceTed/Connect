#pragma once
/**
* @file DeskDefine.h
* @brief �f�X�N�̋��ʃC���N���[�h
* @author �����T��
* @date 2016/2/8
*/
#include <memory>
#include <vector>
#define MAP_SIZE 6
#define ARRANGE_SIZE 4 //���낦���
#define PIECE_SIZE 2 //���a
class Piece;
using PiecePtr = std::shared_ptr<Piece>;
//�c��̔z��
using Column = std::vector<PiecePtr>;
using Container = std::vector<Column>;