#ifndef DEF_GRASS
#define DEF_GRASS

#include "Object.h"

class Grass : public Object {
public:
	Grass();
	~Grass();
	virtual bool estTraversant();
};

#endif 
