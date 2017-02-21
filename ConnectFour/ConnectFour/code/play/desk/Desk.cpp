#include "Desk.h"
#include <cassert>
#include "../IDeskVisitor.h"
#include "../piece/Piece.h"
#include "../../util/IntVector2.h"
#include "../../id/CastID.h"
#include "../Rule.h"
#define ERR_LOCATION IntVector2(-1,-1)
Desk::Desk()
	:m_conatainer()
{
	make_piece();
}

Desk::~Desk()
{
}

bool Desk::isFinish() const
{
	for (const auto& x : m_conatainer)
	{
		for (const auto& y : x)
		{
			if (y->isSameType(COLOR_ID::ACROMIA))
			{
				return false;
			}
		}
	}
	return true;
}

bool Desk::isWin(const Rule & _rule, const IntVector2& _location,CONTROLLER_ID _id) const
{
	return _rule.isWin(m_conatainer,_location,_id);
}

void Desk::accept(IDeskVisitor * _visitor) const
{
	_visitor->visit(m_conatainer);
}

void Desk::placePiece(const IntVector2 & _location, CONTROLLER_ID _id)
{
	assert(MAP_SIZE > _location.x&&MAP_SIZE > _location.y);
	assert(0<= _location.x&&0<=_location.y);
	PiecePtr piece = std::make_shared<Piece>(GSvector3(_location.x*PIECE_SIZE,_location.y*PIECE_SIZE,0),CastID::controllerID2ColorID(_id));
	m_conatainer[_location.x][_location.y].reset();
	m_conatainer[_location.x][_location.y] = piece;
}

IntVector2 Desk::getFreeSpaceColumn(unsigned int _column) const
{
	IntVector2 location(_column,0);
	for (location.y = 0;location.y <MAP_SIZE;location.y++)
	{
		if (isFreeLocation(location))
		{
			return location;
		}
	}
	return ERR_LOCATION;
}

IntVector2 Desk::getFreeMinimalLocation() const
{
	IntVector2 loc;
	for (unsigned int i = 0; i < MAP_SIZE; i++)
	{
		loc =getFreeSpaceColumn(i);
		if (loc != ERR_LOCATION)
		{
			return loc;
		}
	}
	return ERR_LOCATION;
}

bool Desk::isFreeLocation(const IntVector2 & _location) const
{
	if (ERR_LOCATION==_location)return false;
	assert(MAP_SIZE > _location.x&&MAP_SIZE > _location.y);
	assert(0 <= _location.x && 0 <= _location.y);
	return m_conatainer[_location.x][_location.y]->isSameType(COLOR_ID::ACROMIA);
}

void Desk::reset()
{
	m_conatainer.clear();
	make_piece();
}

void Desk::update(float deltaTime)
{
	for (const auto& x : m_conatainer)
	{
		for (const auto& y : x)
		{
			y->update(deltaTime);
		}
	}
}

void Desk::draw(IRenderer * _renderer) const
{
	for (const auto& x:m_conatainer)
	{
		for (const auto& y : x)
		{
			y->draw(_renderer);
		}
	}
}

void Desk::make_piece()
{
	for (unsigned i = 0; i < MAP_SIZE; i++)
	{
		Column column;
		for (unsigned n = 0; n < MAP_SIZE;n++)
		{
			PiecePtr piece = std::make_shared<Piece>(GSvector3(i*PIECE_SIZE, n*PIECE_SIZE, -0.2f),COLOR_ID::ACROMIA);
			column.emplace_back(piece);
		}
		m_conatainer.emplace_back(column);
	}
}

std::vector<IntVector2> Desk::getFreeLoactions() const
{
	std::vector<IntVector2> res;
	for (auto x = 0; x < MAP_SIZE; x++)
	{
		IntVector2 loc = getFreeSpaceColumn(x);
		if (isFreeLocation(loc))
		{
			res.emplace_back(loc);
		}
	}
	return res;
}

void Desk::push_back()
{
	m_list.push_back(m_conatainer);
}

void Desk::pop_back()
{
	assert(!m_list.empty());
	m_conatainer = m_list.back();
	m_list.pop_back();
}

bool Desk::isSamePiece(const IntVector2 & _location, CONTROLLER_ID _id) const
{
	return m_conatainer[_location.x][_location.y]->isSameType(CastID::controllerID2ColorID(_id));
}
