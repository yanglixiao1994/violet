#include "auxiliary.h"
#include "Object.h"
class Scene {
private:
	Object * root;
	list<Material>matls;
public:
	void insertMatl(const Material&matl);
	void loadScene(const string&file);
};
