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
				Blocks[j*width + i].gridloc = Vei2(i,j);
				Blocks[j*width+i].loc = Vei2(i*BlockWidthPix+GridShiftX,j*BlockHeightPix+GridShiftY);
				Blocks[j*width + i].IsBomb = false;
				Blocks[j*width + i].state = IsHidden;
				Blocks[j*width + i].BombsNear = 0;
				Blocks[j*width + i].c = Grey;
		}
	RemainingBombs = InitialBombs;
	GenerateRandomBombs();
	GenerateNumbers();
}

bool Grid::GridLocIsValid(const int x, const int y)
{
	if (x*y >= 0 && x*y <= width * height)
	{
		if (Blocks[y*width + x].gridloc.x == x && Blocks[y*width + x].gridloc.y == y && Blocks[y*width + x].state == IsHidden)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Grid::GridLocIsValidIsBomb(const int x, const int y)
{
	if (x*y >= 0 && x*y <= width * height)
	{
		if (Blocks[y*width +x].gridloc.x == x && Blocks[y*width + x].gridloc.y == y && Blocks[y*width + x].IsBomb == true)
			return true;
		else
			return false;
	}
	else
		return false;
}


void Grid::GridDraw(Graphics & gfx) const
{
	for (int i = 0; i < width*height; i++)
	{
		gfx.DrawRect(Blocks[i].loc.x, Blocks[i].loc.y, Blocks[i].loc.x + BlockWidthPix - 1, Blocks[i].loc.y + BlockHeightPix - 1, Blocks[i].c);
		if (Blocks[i].IsBomb == false && Blocks[i].state == IsRevealed)
		{
			switch (Blocks[i].BombsNear)
			{
			case 0:
				SpriteCodex::DrawTile0(Blocks[i].loc, gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(Blocks[i].loc, gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(Blocks[i].loc, gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(Blocks[i].loc, gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(Blocks[i].loc, gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(Blocks[i].loc, gfx);
				break; 
			case 6:
				SpriteCodex::DrawTile6(Blocks[i].loc, gfx);
				break; 
			case 7:
				SpriteCodex::DrawTile7(Blocks[i].loc, gfx);
				break;
			case 8:
				SpriteCodex::DrawTile8(Blocks[i].loc, gfx);
				break;
			}
		}
		if (Blocks[i].state == IsMarked)
		{
			SpriteCodex::DrawTileFlag(Blocks[i].loc, gfx);
		}
		if (Blocks[i].IsBomb == true && Blocks[i].state == IsRevealed)
		{
			SpriteCodex::DrawTileBomb(Blocks[i].loc, gfx);
		}
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
				Blocks[x].c = Grey;
				latch = true;
			}
		} while (latch == false);
	}

}

void Grid::GenerateNumbers()
{
	for (int i = 0; i < width*height; i++)
	{
		int x = Blocks[i].gridloc.x;
		int y = Blocks[i].gridloc.y;
		int tally = 0;
		//8 Directions
		if (GridLocIsValidIsBomb(x - 1, y - 1))
			tally++;
		if (GridLocIsValidIsBomb(x, y - 1))
			tally++;
		if (GridLocIsValidIsBomb(x + 1, y - 1))
			tally++;
		if (GridLocIsValidIsBomb(x - 1, y))
			tally++; 
		if (GridLocIsValidIsBomb(x + 1,y))
			tally++;
		if (GridLocIsValidIsBomb(x - 1, y +1))
			tally++;
		if (GridLocIsValidIsBomb(x, y + 1))
			tally++;
		if (GridLocIsValidIsBomb(x + 1, y +1))
			tally++;
		Blocks[i].BombsNear = tally;
	}
}

void Grid::RevealAroundBlank(int x, int y)
{
	//8Directions
	BlankRecall(x - 1, y - 1);
	BlankRecall(x, y - 1);
	BlankRecall(x + 1, y - 1);

	BlankRecall(x - 1, y);
	BlankRecall(x + 1, y);

	BlankRecall(x - 1, y + 1);
	BlankRecall(x, y + 1);
	BlankRecall(x + 1, y + 1);
}

void Grid::BlankRecall(const int tx, const int ty)
{
	if (GridLocIsValid(tx, ty))
	{
		int w = (ty)*width + tx;
		Blocks[w].state = IsRevealed;
		Blocks[w].c = DarkGrey;
		BlankCall(w);
	}
}

void Grid::BlankCall(const int i)
{
	if (Blocks[i].BombsNear == 0 && Blocks[i].IsBomb == false)
	{
		RevealAroundBlank(Blocks[i].gridloc.x, Blocks[i].gridloc.y);
	}
}

void Grid::MouseClickManager(Mouse & mouse)
{
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			int i = ClickLocator(e.GetPosX(), e.GetPosY());
			if (i >= 0 && Blocks[i].state == IsHidden)
			{
				Blocks[i].state = IsRevealed;
				Blocks[i].c = DarkGrey;
				BlankCall(i);
				if (Blocks[i].IsBomb == true)
					Blocks[i].c = cBomb;
			}
		}
		if (e.GetType() == Mouse::Event::Type::RPress)
		{
			int i = ClickLocator(e.GetPosX(), e.GetPosY());

			if (i >= 0 && Blocks[i].state == IsHidden)
			{
				Blocks[i].state = IsMarked;
			}
			else if (i >= 0 && Blocks[i].state == IsMarked)
			{
				Blocks[i].state = IsHidden;
			}
		}
	}
}

int Grid::ClickLocator(const int x, const int y)
{
	bool latch = true;
	for (int i = 0; i < width*height; i++)
	{
		if (x > Blocks[i].loc.x && y > Blocks[i].loc.y &&  x < Blocks[i].loc.x + BlockWidthPix && y < Blocks[i].loc.y + BlockHeightPix)
		{
			return i;
			latch = false;
		}
	}
		if (latch == true)
		{
			return (-1);
		}
}

