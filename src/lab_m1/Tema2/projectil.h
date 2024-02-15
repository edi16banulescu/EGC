#pragma once
#include <string>
#include "components/simple_scene.h"
#include "components/transform.h"

namespace m1 {
	class Projectil : public gfxc::SimpleScene
	{
	public:
		glm::mat4 modelMatrixProjectil;
		std::string name;
		float translate;
		float livingTime;
		bool hasBeenShot;
		glm::mat4 modelMatrixGun;
		Projectil(std::string name,
			std::unordered_map<std::string, Mesh*>* meshes);
		~Projectil();
	};
}

