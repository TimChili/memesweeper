#include "Grid.h"

Grid::Grid(Graphics & gfx)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
				Blocks[j*width+i].loc = Vei2(i*BlockWidthPix+GridShiftX,j*BlockHeightPix+GridShiftY);
				Blocks[j*width + i].IsBomb = false;
				Blocks[j*width + i].IsRevealed = false;
				Blocks[j*width + i].BombsNear = 0;
		}

	//  y*width+x = k
	// (x-k)/width = y
	// -(y*width-k) = x
}

void Grid::GridDraw(Graphics & gfx) const
{
	for (int i = 0; i < width*height; i++)
	{
		gfx.DrawRect(Blocks[i].loc.x, Blocks[i].loc.y, Blocks[i].loc.x +BlockWidthPix - 1, Blocks[i].loc.y + BlockHeightPix - 1, Grey);
	}
}
