#ifndef DEF_TALLGRASS
#define DEF_TALLGRASS

#include "Object.h"

class TallGrass : public Object {
public:
	TallGrass();
	~TallGrass();
	virtual bool estTraversant();
	bool estUtilisee();
	void estDessus();
	void pasDessus();
private:
	bool utilisee;
};

#endif
