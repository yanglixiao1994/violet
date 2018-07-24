#include "auxiliary.h"
#include "Object.h"
class Scene {
private:
	Object * root;
	list<Material>matls;
	list<Object>objs;
public:
	void insertMatl(const Material&matl);
	void loadScene(const string&file);
};
