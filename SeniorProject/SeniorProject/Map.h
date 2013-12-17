#pragma once
//#include "cli.h"

struct XY
{
	int m_x,m_y;
	XY():m_x(0),m_y(0){}
	XY(int a_x, int a_y):m_x(a_x),m_y(a_y){}
};
class Map
{
private:
	char** m_map;															//2D array of the map
	int m_height;															//map height
	int m_width;															//map width
	char* m_filename;														//holds the name of the file that has the map
	XY pos;																	//where the map is drawn
public:

	Map();																	//cotr							
	Map(char * a_filename);													//@param loads the file passed
	~Map();																	//dcotr

	void Draw(int a_x, int a_y);											//draws the map	
	bool load(char* a_filename);											//loads a map from a text file
	void Shutdown(char ** m, const int width, const int height);			//releases the memory for the map			

	char* getFileName();													//getter: filename										
	XY getPos();															//getter:pos
	int getH();																//getter:m_height
	int getW();																//getter:m_width
	char get(int a_x, int a_y) const ;										//returns m_map[a_x,a_y]
	char** getMap();														//getter:m_map


	void setPos(int a_x, int a_y);											//setter:pos
	void set(int a_x, int a_y, char a_symbol);								//m_map[a_x][a_y] = a_symbol
	bool collision(Map & m, char myChar, char collidable);					//checks map m to see if myChar is where collidable is on this->m_map
	void rotateLeft();														//rotates left
	void rotateRight();														//rotates right
private:	
	static char** create(int a_height, int a_width);						//dynamically makes a new array 													
	void flipH();															//flips the map horizontally
	void flipV();															//flips the map vertically
	void flipXY();															//flips the map about the x/y axis
};