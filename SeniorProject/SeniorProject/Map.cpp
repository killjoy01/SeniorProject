#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map()
	:m_map(0), m_height(-1), m_width(-1)
{
}

Map::~Map()
{
	if(m_map)
	{
		for(int i = 0; i < m_height; ++i)
		{
			delete [] m_map[i];
		}
		delete [] m_map;
	}
}

Map::Map(char* a_filename)
{
	load(a_filename);
}

char* Map:: getFileName()
{
	return m_filename;
}

bool Map::load(char* a_filename)
{
	//sets the filename of the map
	this->m_filename = a_filename;
	//init the input file
	std::ifstream file;
	//open the passed file
	file.open(a_filename);

	//load fails if file isnt open
	if(!file.is_open())
		return false;
	//read the height and width from the file
	file >> m_width >> m_height;
	//start up the map
	m_map = create(m_width, m_height);

	int c, row = 0, col = 0;

	//read through the file and make the 
	do{
		c = file.get();
		char x = c;

		if(c != EOF && c != '\n' && c != '\r' && c != '=')
		{
			m_map[row][col] = c;
			col++;
			if(col >= m_width) 
			{
				col = 0;
				row++;
				if(row >= m_height)
					break;
			}

		}

	}while(c != EOF);
	file.close();
	return true;
}

char** Map::create(int a_width, int a_height)
{
	char** a = new char*[a_height];
	for(int i = 0; i < a_height;++i)
		a[i] = new char[a_width];

	return a;
}

void Map::Shutdown(char ** m, const int width, const int height)
{
	if(m_map)
	{
		for(int i = 0; i < height; ++i)
			delete [] m[i];

		delete [] m_map;
	}
	m_map = NULL;

}

void Map::Draw(int a_x, int a_y)
{
	/*pos.m_x = a_x;
	pos.m_y = a_y;

	for(int x = 0; x < m_width; ++x) 
	{
		for(int y = 0; y < m_height; ++y) 
		{
			setCursorXY(a_x+x,a_y+y);
			if(m_map[y][x] != ' ' && m_map[y][x] != '=' )
			{
				std::cout << m_map[y][x];
			}
		}
		std::cout << std::endl;
	}*/
}



void Map::setPos(int a_x, int a_y)
{
	pos.m_x = a_x;
	pos.m_y = a_y;
}

XY Map::getPos()
{
	return pos;
}
int Map::getH()
{
	return m_height;
}

int Map::getW()
{
	return m_width;
}

char** Map::getMap()
{
	return m_map;
}

void Map::set(int a_x, int a_y, char a_symbol)
{
	m_map[a_x][a_y] = a_symbol;
}

char Map::get(int a_x, int a_y) const
{
	return m_map[a_x][a_y];
}

bool Map::collision(Map & m, char willCollide, char collidable)
{
	for(int row = 0; row < m.getH(); ++row)
	{
		for(int col = 0; col < m.getW(); ++col)
		{

			int bcy = row+m.pos.m_y;
			int bcx = m.pos.m_x+col;
			char boardchar = get(bcy,bcx);
			char piecechar = m.get(row, col);

			//if piecechar is overlapping boardchar, 
			//and piecechar and boardchar are the pieces passed, 
			//returns true
			if(boardchar == collidable
				&& piecechar == willCollide)
			{
				return true;
			}
		}
	}
	return false;
}

void Map::flipH(){
	char ** m = create(m_width, m_height);
	for(int row = 0; row < m_height; ++row) {
		for(int col = 0; col < m_width; ++col) {
			m[row][col] = m_map[row][m_width-1-col]; 
		}
	}
	Shutdown(m_map, m_width, m_height);
	m_map = m;
}
void Map::flipV(){
	char ** m = create(m_width, m_height);
	for(int row = 0; row < m_height; ++row) {
		for(int col = 0; col < m_width; ++col) {
			m[row][col] = m_map[m_height-1-row][col]; 
		}
	}
	Shutdown(m_map, m_width, m_height);
	m_map = m;
}

void Map::flipXY(){
	char ** m = create(m_height, m_width);
	for(int row = 0; row < m_width; ++row) {
		for(int col = 0; col < m_height; ++col) {
			m[row][col] = m_map[col][row]; 
		}
	}
	Shutdown(m_map, m_width, m_height);
	int temp = m_width;	m_width = m_height; m_height = temp;
	m_map = m;
}

void Map::rotateRight()
{	
	flipXY();	
	flipH();	
}
void Map::rotateLeft()
{	
	flipXY();	
	flipV();	
}