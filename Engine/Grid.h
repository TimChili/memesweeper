#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>


class Grid
{
public:
	Grid(Graphics& gfx);
	bool GridLocIsValidIsBomb(const int x,const int y);
	void GenerateRandomBombs();
	void GenerateNumbers();
	void GridDraw(Graphics& gfx) const;


private:
	//Block Stuff
	struct Block
	{
		int BombsNear;
		bool IsBomb;
		enum rbClick {IsUnmarked, IsMarked, IsFlagged};
		bool IsRevealed;
		Vei2 gridloc;
		Vei2 loc;
		Color c;
	};
	static constexpr int width = 10;
	static constexpr int height = 10;
	static constexpr int BlockWidthPix = 30;
	static constexpr int BlockHeightPix = 30;
	static const int GridShiftX = (Graphics::ScreenWidth / 2) - (width*BlockWidthPix / 2);// plus half screen width minus board width
	static const int GridShiftY = BlockHeightPix * 2;
	Block Blocks[width*height];
	Color Grey = { 70,70,70 };
	Color cBomb = { 255,0,0 };
	
	
	//Bomb Stuff
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> DistBomb;
	static constexpr int InitialBombs = 20;
	int RemainingBombs;

};