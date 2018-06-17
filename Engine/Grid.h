#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>
#include "Mouse.h"


class Grid
{
public:
	Grid(Graphics& gfx);
	bool GridLocIsValid(const int x, const int y);
	bool GridLocIsValidIsBomb(const int x,const int y);
	void GenerateRandomBombs();
	void GenerateNumbers();
	void RevealAroundBlank(const int x, const int y);
	void BlankRecall(const int x, const int y);
	void BlankCall(const int i);
	void MouseClickManager(Mouse&  mouse); 
	int ClickLocator(const int x, const int y);  
	void g();

	void GridDraw(Graphics& gfx) const;
	

private:
	//Block Stuff
	enum rbClick { IsHidden, IsRevealed, IsMarked, IsQuestioned };
	struct Block
	{
		int BombsNear;
		bool IsBomb;
		rbClick state;
		Vei2 gridloc;
		Vei2 loc;
		Color c;
	};
	static constexpr int width = 12;
	static constexpr int height = 12;
	static constexpr int BlockWidthPix = 30;
	static constexpr int BlockHeightPix = 30;
	static const int GridShiftX = (Graphics::ScreenWidth / 2) - (width*BlockWidthPix / 2);// plus half screen width minus board width
	static const int GridShiftY = BlockHeightPix * 2;
	Block Blocks[width*height];
	Color Grey = { 70,70,70 };
	Color DarkGrey = { 120,120,120 };
	Color cBomb = { 255,0,0 };
	Color Greenish = { 25,200,25 };
	
	
	//Bomb Stuff
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> DistBomb;
	static constexpr int InitialBombs = 20;
	int RemainingBombs;

};