#ifndef DEF_MAP
#define DEF_MAP

#include "Object.h"
#include <vector>
#include <string>

class Map {
private:
	std::vector<std::vector<Object*>> m_map;
	void loadMap(std::string file);

public:
	Map(std::string file);
	~Map();
	std::vector<std::vector<Object*>> getMap();
};

#endif
