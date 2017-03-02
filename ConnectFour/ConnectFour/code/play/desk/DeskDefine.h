#pragma once
/**
* @file DeskDefine.h
* @brief デスクの共通インクルード
* @author 松尾裕也
* @date 2016/2/8
*/
#include <memory>
#include <vector>
#define MAP_SIZE 6
#define ARRANGE_SIZE 4 //そろえる個数
#define PIECE_SIZE 2 //直径
class Piece;
using PiecePtr = std::shared_ptr<Piece>;
//縦列の配列
using Column = std::vector<PiecePtr>;
using Container = std::vector<Column>;