#include "Grid.h"

Grid::Grid(Graphics & gfx)
	:
	rng(rd()),
	DistBomb(0,width*height-1)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
				//  y*width+x = k
				// (x-k)/width = y
				// -(y*width-k) = x
				Blocks[j*width+i].loc = Vei2(i*BlockWidthPix+GridShiftX,j*BlockHeightPix+GridShiftY);
				Blocks[j*width + i].IsBomb = false;
				Blocks[j*width + i].IsRevealed = false;
				Blocks[j*width + i].BombsNear = 0;
				Blocks[j*width + i].c = Grey;
		}
	RemainingBombs = InitialBombs;
	GenerateRandomBombs();

}

void Grid::GridDraw(Graphics & gfx) const
{
	for (int i = 0; i < width*height; i++)
	{
		gfx.DrawRect(Blocks[i].loc.x, Blocks[i].loc.y, Blocks[i].loc.x +BlockWidthPix - 1, Blocks[i].loc.y + BlockHeightPix - 1, Blocks[i].c);
	}
}

void Grid::GenerateRandomBombs()
{
	for (int i = 0; i < InitialBombs; i++)
	{
		bool latch = false;
		do
		{
			int x = DistBomb(rng);
			if (!Blocks[x].IsBomb)
			{
				Blocks[x].IsBomb = true;
				Blocks[x].c = cBomb;
				latch = true;
			}
		} while (latch == false);
	}

}

