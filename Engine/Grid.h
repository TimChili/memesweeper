#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"


class Grid
{
public:
	Grid(Graphics& gfx);
	void GridDraw(Graphics& gfx) const;

private:
	struct Block
	{
		int BombsNear;
		bool IsBomb;
		bool IsRevealed;
		Vei2 loc;
	};
	static constexpr int width = 10;
	static constexpr int height = 10;
	static constexpr int BlockWidthPix = 30;
	static constexpr int BlockHeightPix = 30;
	static const int GridShiftX = (Graphics::ScreenWidth / 2) - (width*BlockWidthPix / 2);// plus half screen width minus board width
	static const int GridShiftY = BlockHeightPix * 2;
	Block Blocks[width*height];
	Color Grey = { 70,70,70 };
};