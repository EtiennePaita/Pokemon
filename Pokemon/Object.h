#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Elements.h"

/*
	Classe abstraite
*/
class Object {
protected:
	Elements type;

public:
	Object(Elements e);
	~Object();

	Elements getType() const;
	virtual bool estTraversant()=0; // methode virtuelle pure (abstraite)
};

#endif
