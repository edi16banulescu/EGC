#include "projectil.h"

namespace m1 {
	Projectil::Projectil(std::string name,
		std::unordered_map<std::string, Mesh*>* meshes) {

		this->name = name;
		this->modelMatrixProjectil = glm::mat4(1.0f);
		this->translate = 0.f;
		this->livingTime = 5.f;
		this->hasBeenShot = false;
		this->modelMatrixGun = glm::mat4(1.0f);

		Mesh* mesh1 = new Mesh(name + "projectil");
		mesh1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		(*meshes)[mesh1->GetMeshID()] = mesh1;
	}
	Projectil::~Projectil()
	{
	}
}
