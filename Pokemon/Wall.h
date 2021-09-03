#ifndef DEF_WALL
#define DEF_WALL

#include "Object.h"

class Wall : public Object {
public:
	Wall();
	~Wall();
	virtual bool estTraversant();
};

#endif
