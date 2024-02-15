#include "tank.h"

namespace m1
{
	Tank::Tank(std::string name,
        std::unordered_map<std::string, Mesh*>* meshes)
	{
        this->name = name;
        this->modelMatrixTracks = glm::mat4(1);
        this->modelMatrixHull = glm::mat4(1);
        this->modelMatrixTurret = glm::mat4(1);
        this->modelMatrixGun = glm::mat4(1);
        this->modelMatrixTracks = glm::scale(this->modelMatrixTracks, glm::vec3(0.2f));
        this->modelMatrixHull = glm::scale(this->modelMatrixHull, glm::vec3(0.2f));
        this->modelMatrixTurret = glm::scale(this->modelMatrixTurret, glm::vec3(0.2f));
        this->modelMatrixGun = glm::scale(this->modelMatrixGun, glm::vec3(0.2f));
        this->translateX = 0;
        this->rotateY = 0;
        this->position = glm::vec4(1);
        this->mouseAngle = 0;
        this->damage = 1;
        this->lastMovementState = MovementState::GoingForward;
        this->isDead = false;

        {
            Mesh* mesh1 = new Mesh(name + "tracks");
            mesh1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tracks.obj");
            (*meshes)[mesh1->GetMeshID()] = mesh1;

            Mesh* mesh2 = new Mesh(name + "hull");
            mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "hull.obj");
            (*meshes)[mesh2->GetMeshID()] = mesh2;

            Mesh* mesh3 = new Mesh(name + "turret");
            mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "turret.obj");
            (*meshes)[mesh3->GetMeshID()] = mesh3;

            Mesh* mesh4 = new Mesh(name + "gun");
            mesh4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "gun.obj");
            (*meshes)[mesh4->GetMeshID()] = mesh4;
        }
	}



	Tank::~Tank()
	{
	}

}