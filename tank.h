#pragma once
#include <string>
#include "components/simple_scene.h"
#include "components/transform.h"
#include "nextMove.h"

namespace m1 {
	class Tank : public gfxc::SimpleScene
	{
	public:
		std::string name;
		glm::mat4 modelMatrixTracks;
		glm::mat4 modelMatrixHull;
		glm::mat4 modelMatrixTurret;
		glm::mat4 modelMatrixGun;
		float translateX;
		float rotateY;
		glm::vec4 position;
		float mouseAngle;
		float damage;
		MovementState lastMovementState;
		bool isDead;
		Tank(std::string name,
			std::unordered_map<std::string, Mesh*>* meshes);
		~Tank();
	};
}


