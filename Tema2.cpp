#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, -3.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    camera2 = new implemented::Camera();
    camera2->Set(glm::vec3(0, 2, -3.5f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    orthoDelta = 0.1f;
    fov = 70;
    cameraSpeed = 0.2f;
    cameraPos = 0.0f;
    silver = glm::vec3(0.75f, 0.75f, 0.75f);
    mediumOrchid = glm::vec3(0.729f, 0.333f, 0.827f);
    tankSpeed = 7.f;
    totalTankMove = 0.0f;
    totalTankRotate = 0.f;
    numberFriendlyProjectils = 0;
    projectilSpeed = 10.f;
    projectilDelay = 1.f;
    colorHull = glm::vec3(0, 0.2f, 0);
    colorTurret = glm::vec3(1, 0, 0);
    colorGun = glm::vec3(0, 0.4f, 0);
    nextMove = new NextMove();
    changeStateEnemyTank = rand() % 5 + 1;
    numberEnemyProjectils = 0;
    enemyProjectilDelay = 3.f;
    rotateCamera = false;
    timeElapsed = 90.f;
    score = 0;
    gameOver = false;

    colorHullEnemy = glm::vec3(0.5f, 0, 0);
    colorTurretEnemy = glm::vec3(0, 0, 0.5429f);
    colorGunEnemy = glm::vec3(0.777f, 0.082f, 0.519f);
    chocolate = glm::vec3(0.82f, 0.41f, 0.11f);

    float random = rand() % 10;
    building1 = glm::mat4(1);
    building1 = glm::translate(building1, glm::vec3(random, 0, 5));

    random = rand() % 10;
    building2 = glm::mat4(1);
    building2 = glm::translate(building2, glm::vec3(random, 0, -7));

    random = rand() % 10;
    building3 = glm::mat4(1);
    building3 = glm::translate(building3, glm::vec3(random, 0, 5));

    random = rand() % 10;
    building4 = glm::mat4(1);
    building4 = glm::translate(building4, glm::vec3(random, 0, -8));

    random = rand() % 10;
    if (random == 0) {
        random = 2;
    }
    building5 = glm::mat4(1);
    building5 = glm::translate(building5, glm::vec3(random, 0, 0));

    random = rand() % 10;
    if (random == 0) {
        random = 2;
    }
    building6 = glm::mat4(1);
    building6 = glm::translate(building6, glm::vec3(-random, 0, 0));

    random = rand() % 10;
    building7 = glm::mat4(1);
    building7 = glm::translate(building7, glm::vec3(-random, 0, -8));

    random = rand() % 10;
    building8 = glm::mat4(1);
    building8 = glm::translate(building8, glm::vec3(-random, 0, -9));

    random = rand() % 10;
    building9 = glm::mat4(1);
    building9 = glm::translate(building9, glm::vec3(-random, 0, -4));

    random = rand() % 10;
    building10 = glm::mat4(1);
    building10 = glm::translate(building10, glm::vec3(-random, 0, 10));

    sKeyIsPressed = false;


    buildings = { building1, building2, building3, building4, building5, building6, building7, building8, building9, building10 };

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);

    {
        Shader* shader = new Shader("HomeworkShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    myTank = new Tank("me", &meshes);
    {
        Mesh* mesh = new Mesh("plane1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;

        Mesh* mesh2 = new Mesh("plane2");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh2->GetMeshID()] = mesh2;

        Mesh* mesh3 = new Mesh("plane3");
        mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh3->GetMeshID()] = mesh3;

        Mesh* mesh4 = new Mesh("plane4");
        mesh4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh4->GetMeshID()] = mesh4;

        Mesh* mesh5 = new Mesh("plane5");
        mesh5->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh5->GetMeshID()] = mesh5;
    }

    {
        Mesh* mesh = new Mesh("building1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh->GetMeshID()] = mesh;

        Mesh* mesh2 = new Mesh("building2");
        mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh2->GetMeshID()] = mesh2;

        Mesh* mesh3 = new Mesh("building3");
        mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh3->GetMeshID()] = mesh3;

        Mesh* mesh4 = new Mesh("building4");
        mesh4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh4->GetMeshID()] = mesh4;

        Mesh* mesh5 = new Mesh("building5");
        mesh5->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh5->GetMeshID()] = mesh5;

        Mesh* mesh6 = new Mesh("building6");
        mesh6->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh6->GetMeshID()] = mesh6;

        Mesh* mesh7 = new Mesh("building7");
        mesh7->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh7->GetMeshID()] = mesh7;

        Mesh* mesh8 = new Mesh("building8");
        mesh8->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh8->GetMeshID()] = mesh8;

        Mesh* mesh9 = new Mesh("building9");
        mesh9->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh9->GetMeshID()] = mesh9;

        Mesh* mesh10 = new Mesh("building10");
        mesh10->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building.obj");
        meshes[mesh10->GetMeshID()] = mesh10;
    }

    {
        enemyTank1 = new Tank("enemy1", &meshes);
        rotateEnemyTanks(enemyTank1, 3.f);
        moveEnemyTanks(enemyTank1, 7.5f);
        rotateEnemyTanks(enemyTank1, 2.f);
        enemyTank1->mouseAngle = 5.f;

        enemyTank2 = new Tank("enemy2", &meshes);
        rotateEnemyTanks(enemyTank2, 1.8f);
        moveEnemyTanks(enemyTank2, 8.f);
        rotateEnemyTanks(enemyTank2, 2.2f);
        enemyTank2->mouseAngle = 4.f;

        enemyTank3 = new Tank("enemy3", &meshes);
        rotateEnemyTanks(enemyTank3, 1.2f);
        moveEnemyTanks(enemyTank3, 8.f);
        rotateEnemyTanks(enemyTank3, 2.f);
        enemyTank3->mouseAngle = 3.2f;

        enemyTank4 = new Tank("enemy4", &meshes);
        rotateEnemyTanks(enemyTank4, 4.6f);
        moveEnemyTanks(enemyTank4, 6.f);
        rotateEnemyTanks(enemyTank4, 2.f);
        enemyTank4->mouseAngle = 6.6f;

        enemyTank5 = new Tank("enemy5", &meshes);
        rotateEnemyTanks(enemyTank5, -0.2f);
        moveEnemyTanks(enemyTank5, 10.f);
        rotateEnemyTanks(enemyTank5, 2.2f);
        enemyTank5->mouseAngle = 2.f;

        enemyTanks = { enemyTank1, enemyTank2, enemyTank3, enemyTank4, enemyTank5 };
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (timeElapsed > 0) {
        timeElapsed -= deltaTimeSeconds * 2;
        if (myTank->isDead || checkIfYouWon()) {
            camera->Set(glm::vec3(0, 20, -10.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        }
        projectilDelay -= deltaTimeSeconds;
        enemyProjectilDelay -= deltaTimeSeconds;
        RenderTank(myTank, colorHull, colorTurret, colorGun);
        renderPlane(silver);
        renderBuildings(mediumOrchid);
        renderFriendlyProjectils(myTank, deltaTimeSeconds);
        checkCollisionTankWithBuildings(myTank);
        checkCollisionProjectilsWithBuildings();
        for (Tank* enemyTank : enemyTanks) {
            RenderTank(enemyTank, colorHullEnemy, colorTurretEnemy, colorGunEnemy);
        }
        checkCollisionProjectilsWithEnemyTanks();
        checkCollisionTankWithEnemyTanks(myTank);
        moveEnemyTanksRandomly(deltaTimeSeconds);
        attackMyTank(myTank);
        renderEnemyProjectils(deltaTimeSeconds);
        checkCollisionEnemyProjectilsWithMyTank(myTank);
        checkCollisionEnemyProjectilsWithBuildings();
    }
    else {
        score = 0;
        for (Tank* enemyTank : enemyTanks) {
            if (enemyTank->isDead) {
                score++;
			}
		}
        if (!gameOver) {
            if (myTank->isDead) {
                std::cout << "#####################################################"<< std::endl;
				std::cout << "You lost!" << std::endl;
                std::cout << "#####################################################" << std::endl;
			}
            else {
                std::cout << "#####################################################" << std::endl;
                std::cout << "Your score is: " << score << std::endl;
                std::cout << "#####################################################" << std::endl;
			}
        }

        gameOver = true;
    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const float damage)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    GLint loc_object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(loc_object_color, 1, glm::value_ptr(color));

    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint damageLocation = glGetUniformLocation(shader->program, "damage");
    glUniform1f(damageLocation, damage);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (!myTank->isDead) {
        if (window->KeyHold(GLFW_KEY_W)) {
            moveForwardAndBackTank(myTank, deltaTime);
	    }

        if (window->KeyHold(GLFW_KEY_S)) {
            sKeyIsPressed = true;
            moveForwardAndBackTank(myTank, -deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
		    rotateTank(myTank, deltaTime);
	    }

	    if (window->KeyHold(GLFW_KEY_D)) {
            rotateTank(myTank, -deltaTime);
	    }
	}
    
}


void Tema2::OnKeyPress(int key, int mods)
{

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
    if (key == GLFW_KEY_S) {
		sKeyIsPressed = false;
	}
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (rotateCamera)
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
    }

    {
        float sensivityOX = 0.005f;
        rotateGunAndTurret(myTank, -deltaX * sensivityOX);
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (!myTank->isDead) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (projectilDelay <= 0) {
                friendlyProjectils.push_back(new Projectil(numberFriendlyProjectils + "", &meshes));
                numberFriendlyProjectils++;
                projectilDelay = 1.f;
            }
        };

        if (button == 2) {
			rotateCamera = true;
		}
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 2) {
        glm::vec3 position = getPositionFromMatrix(myTank->modelMatrixHull);
        camera->position = camera2->position;
        camera->forward = camera2->forward;
        camera->up = camera2->up;
        camera->right = camera2->right;
        rotateCamera = false;
    }
    
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

template<typename T>
void m1::Tema2::removeFromVector(std::vector<T*>& vector, T* item)
{
    auto it = std::find(vector.begin(), vector.end(), item);
    int index = it - vector.begin();
    vector.erase(vector.begin() + index);
}

void m1::Tema2::RenderTank(Tank* tank, glm::vec3 colorHull, glm::vec3 colorTurret, glm::vec3 colorGun)
{
    RenderMesh(meshes[tank->name + "tracks"], shaders["VertexNormal"], tank->modelMatrixTracks);

    RenderSimpleMesh(meshes[tank->name + "hull"], shaders["HomeworkShader"], tank->modelMatrixHull, colorHull, tank->damage);

    RenderSimpleMesh(meshes[tank->name + "turret"], shaders["HomeworkShader"], tank->modelMatrixTurret, colorTurret, tank->damage);

    RenderSimpleMesh(meshes[tank->name + "gun"], shaders["HomeworkShader"], tank->modelMatrixGun, colorGun, tank->damage);

}

void m1::Tema2::moveForwardAndBackTank(Tank* tank, float deltaTimeSeconds)
{
    tank->translateX = 0;
    tank->translateX += deltaTimeSeconds * tankSpeed;
    glm::mat4 nextModelMatrix = tank->modelMatrixTracks * glm::translate(glm::mat4(1), glm::vec3(0, 0, tank->translateX));
    glm::vec4 newPosition = nextModelMatrix * glm::vec4(0, 0, 0, 1);

    if (newPosition.x > -19.0f && newPosition.x < 19.0f && newPosition.z > -19.0f && newPosition.z < 19.0f) {
        tank->modelMatrixTracks = glm::translate(tank->modelMatrixTracks, glm::vec3(0, 0, tank->translateX));
        tank->modelMatrixHull = glm::translate(tank->modelMatrixHull, glm::vec3(0, 0, tank->translateX));
        glm::mat4 matrixRotatedByMouse = glm::rotate(tank->modelMatrixTracks, tank->mouseAngle, glm::vec3(0, 1, 0));
        tank->modelMatrixGun = matrixRotatedByMouse;
        tank->modelMatrixTurret = matrixRotatedByMouse;
        camera->MoveForward(tank->translateX * cameraSpeed);
        camera2->MoveForward(tank->translateX * cameraSpeed);
        tank->position = newPosition;
    }
}

void m1::Tema2::rotateTank(Tank* tank, float deltaTimeSeconds)
{
    int direction = 0;
    if (deltaTimeSeconds > 0)
		direction = 1;
	else
		direction = -1;

    tank->rotateY = 0;
    tank->rotateY += deltaTimeSeconds * 1.5f;
	tank->modelMatrixTracks = glm::rotate(tank->modelMatrixTracks, tank->rotateY, glm::vec3(0, 1, 0));
	tank->modelMatrixHull = glm::rotate(tank->modelMatrixHull, tank->rotateY, glm::vec3(0, 1, 0));
	camera->RotateThirdPerson_OY(tank->rotateY);
    camera2->RotateThirdPerson_OY(tank->rotateY);
    camera->TranslateRight(tank->rotateY + 0.018f * direction);
    camera2->TranslateRight(tank->rotateY + 0.018f * direction);
}

void m1::Tema2::reinitializeTank(Tank* tank)
{
    tank->modelMatrixTracks = glm::mat4(1);
    tank->modelMatrixHull = glm::mat4(1);
    tank->modelMatrixTurret = glm::mat4(1);
    tank->modelMatrixGun = glm::mat4(1);
    tank->modelMatrixTracks = glm::scale(tank->modelMatrixTracks, glm::vec3(0.2f));
    tank->modelMatrixHull = glm::scale(tank->modelMatrixHull, glm::vec3(0.2f));
    tank->modelMatrixTurret = glm::scale(tank->modelMatrixTurret, glm::vec3(0.2f));
    tank->modelMatrixGun = glm::scale(tank->modelMatrixGun, glm::vec3(0.2f));
}

void m1::Tema2::renderPlane(glm::vec3 color)
{
    RenderSimpleMesh(meshes["plane1"], shaders["HomeworkShader"], glm::mat4(1), color, 1);
    glm::mat4 wall1 = glm::mat4(1);
    wall1 = glm::translate(wall1, glm::vec3(0, 0, 20));
    wall1 = glm::rotate(wall1, RADIANS(90), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["plane2"], shaders["HomeworkShader"], wall1, color, 1);

    glm::mat4 wall2 = glm::mat4(1);
    wall2 = glm::translate(wall2, glm::vec3(0, 0, -20));
    wall2 = glm::rotate(wall2, RADIANS(90), glm::vec3(1, 0, 0));
    RenderSimpleMesh(meshes["plane3"], shaders["HomeworkShader"], wall2, color, 1);


    glm::mat4 wall3 = glm::mat4(1);
    wall3 = glm::translate(wall3, glm::vec3(20, 0, 0));
    wall3 = glm::rotate(wall3, RADIANS(270), glm::vec3(0, 0, 1));
    RenderSimpleMesh(meshes["plane4"], shaders["HomeworkShader"], wall3, color, 1);


    glm::mat4 wall4 = glm::mat4(1);
    wall4 = glm::translate(wall4, glm::vec3(-20, 0, 0));
    wall4 = glm::rotate(wall4, RADIANS(270), glm::vec3(0, 0, 1));
    RenderSimpleMesh(meshes["plane5"], shaders["HomeworkShader"], wall4, color, 1);
}

void m1::Tema2::renderBuildings(glm::vec3 color)
{
	RenderSimpleMesh(meshes["building1"], shaders["HomeworkShader"], building1, color, 1);

	RenderSimpleMesh(meshes["building2"], shaders["HomeworkShader"], building2, color, 1);

	RenderSimpleMesh(meshes["building3"], shaders["HomeworkShader"], building3, color, 1);

	RenderSimpleMesh(meshes["building4"], shaders["HomeworkShader"], building4, color, 1);

	RenderSimpleMesh(meshes["building5"], shaders["HomeworkShader"], building5, color, 1);

    RenderSimpleMesh(meshes["building6"], shaders["HomeworkShader"], building6, color, 1);

    RenderSimpleMesh(meshes["building7"], shaders["HomeworkShader"], building7, color, 1);

    RenderSimpleMesh(meshes["building8"], shaders["HomeworkShader"], building8, color, 1);

    RenderSimpleMesh(meshes["building9"], shaders["HomeworkShader"], building9, color, 1);

    RenderSimpleMesh(meshes["building10"], shaders["HomeworkShader"], building10, color, 1);
}

void m1::Tema2::rotateGunAndTurret(Tank* tank, float mouseX)
{
    if (mouseX != 0) {
        tank->mouseAngle += mouseX;
    }

    tank->modelMatrixGun = glm::rotate(tank->modelMatrixGun, mouseX, glm::vec3(0, 1, 0));
    tank->modelMatrixTurret = glm::rotate(tank->modelMatrixTurret, mouseX, glm::vec3(0, 1, 0));
}

void m1::Tema2::renderFriendlyProjectils(Tank* tank, float deltaTimeSeconds)
{
    for (Projectil* p : friendlyProjectils) {
        if (p->livingTime > 0) {
            p->livingTime -= deltaTimeSeconds;
            if (!p->hasBeenShot) {
                p->modelMatrixGun = tank->modelMatrixGun;
                p->hasBeenShot = true;
            }
            p->modelMatrixProjectil = p->modelMatrixGun;
            p->modelMatrixProjectil = glm::translate(p->modelMatrixProjectil, glm::vec3(0, 2.f, p->translate + 6.f));
            p->translate += deltaTimeSeconds * projectilSpeed;
            RenderSimpleMesh(meshes[p->name + "projectil"], shaders["HomeworkShader"], p->modelMatrixProjectil, chocolate, 1);
        }
        else {
            removeFromVector(friendlyProjectils, p);
        }
	}
}

void m1::Tema2::checkCollisionTankWithBuildings(Tank* tank)
{
	for (const auto& building : buildings) {
		glm::vec3 buildingPosition = getPositionFromMatrix(building);
		glm::vec3 tankPosition = getPositionFromMatrix(tank->modelMatrixTracks);
		if (glm::distance(buildingPosition, tankPosition) < 1.7f) {
            if (sKeyIsPressed)
				moveForwardAndBackTank(tank, 0.1f);
            else {
                moveForwardAndBackTank(tank, -0.1f);
            }
		}
	}
}

glm::vec3 m1::Tema2::getPositionFromMatrix(glm::mat4 matrix)
{
    return glm::vec3(matrix[3]);
}

void m1::Tema2::checkCollisionProjectilsWithBuildings()
{
	for (Projectil* p : friendlyProjectils) {
		for (const auto& building : buildings) {
			glm::vec3 buildingPosition = getPositionFromMatrix(building);
			glm::vec3 projectilPosition = getPositionFromMatrix(p->modelMatrixProjectil);
			if (glm::distance(buildingPosition, projectilPosition) < 1.3f) {
				removeFromVector(friendlyProjectils, p);
			}
		}
	}
}

void m1::Tema2::moveEnemyTanks(Tank* enemyTank, float deltaTimeSeconds)
{
    enemyTank->translateX = 0;
    enemyTank->translateX += deltaTimeSeconds * tankSpeed;
    glm::mat4 nextModelMatrix = enemyTank->modelMatrixTracks * glm::translate(glm::mat4(1), glm::vec3(0, 0, enemyTank->translateX));
    glm::vec4 newPosition = nextModelMatrix * glm::vec4(0, 0, 0, 1);

    if (newPosition.x > -19.0f && newPosition.x < 19.0f && newPosition.z > -19.0f && newPosition.z < 19.0f) {
        enemyTank->modelMatrixTracks = glm::translate(enemyTank->modelMatrixTracks, glm::vec3(0, 0, enemyTank->translateX));
        enemyTank->modelMatrixHull = glm::translate(enemyTank->modelMatrixHull, glm::vec3(0, 0, enemyTank->translateX));
        //glm::mat4 matrixRotated = glm::rotate(enemyTank->modelMatrixTracks, enemyTank->mouseAngle, glm::vec3(0, 1, 0));
        enemyTank->modelMatrixTurret[3].x = enemyTank->modelMatrixTracks[3].x;
        enemyTank->modelMatrixTurret[3].z = enemyTank->modelMatrixTracks[3].z;
        enemyTank->modelMatrixGun[3].x = enemyTank->modelMatrixTracks[3].x;
        enemyTank->modelMatrixGun[3].z = enemyTank->modelMatrixTracks[3].z;
    }
}

void m1::Tema2::rotateEnemyTanks(Tank* enemyTank, float deltaTimeSeconds)
{
    enemyTank->rotateY = 0;
	enemyTank->rotateY += deltaTimeSeconds * 1.5f;
	enemyTank->modelMatrixTracks = glm::rotate(enemyTank->modelMatrixTracks, enemyTank->rotateY, glm::vec3(0, 1, 0));
	enemyTank->modelMatrixHull = glm::rotate(enemyTank->modelMatrixHull, enemyTank->rotateY, glm::vec3(0, 1, 0));
	//enemyTank->modelMatrixTurret = glm::rotate(enemyTank->modelMatrixTurret, enemyTank->rotateY, glm::vec3(0, 1, 0));
	//enemyTank->modelMatrixGun = glm::rotate(enemyTank->modelMatrixGun, enemyTank->rotateY, glm::vec3(0, 1, 0));
}

void m1::Tema2::checkCollisionProjectilsWithEnemyTanks()
{
    for (Projectil* p : friendlyProjectils) {
		    for (Tank* enemyTank : enemyTanks) {
			    glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixHull);
			    glm::vec3 projectilPosition = getPositionFromMatrix(p->modelMatrixProjectil);
			    if (glm::distance(enemyTankPosition, projectilPosition) < 1.f) {
                    if (enemyTank->damage <= 3) {
                        enemyTank->damage += 1;
                    }
                    if (enemyTank->damage >= 4) {
						enemyTank->isDead = true;
					}
                    removeFromVector(friendlyProjectils, p);
			    }
		    }
	    }
}

void m1::Tema2::checkCollisionTankWithEnemyTanks(Tank* tank)
{
    for (Tank* enemyTank : enemyTanks) {
		glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixTracks);
		glm::vec3 tankPosition = getPositionFromMatrix(tank->modelMatrixTracks);
		if (glm::distance(enemyTankPosition, tankPosition) < 1.2f) {
			if (sKeyIsPressed)
				moveForwardAndBackTank(tank, 0.1f);
			else {
				moveForwardAndBackTank(tank, -0.1f);
			}
		}
	}
}

void m1::Tema2::moveEnemyTanksRandomly(float deltaTimeSeconds)
{
    changeStateEnemyTank -= deltaTimeSeconds;
    if (changeStateEnemyTank > 0) {
        for (Tank* enemyTank : enemyTanks) {
            if (enemyTank->isDead) {
				continue;
			}
            MovementState state = enemyTank->lastMovementState;
            switch (state) {
            case MovementState::GoingForward:
                if (checkCollisionEnemyTankWithBuildings(enemyTank)) {
                    glm::mat4 copyOfTankTracks = enemyTank->modelMatrixTracks;
                    copyOfTankTracks = glm::translate(copyOfTankTracks, glm::vec3(0, 0, 0.1f));
                    glm::vec3 newPosition = getPositionFromMatrix(copyOfTankTracks);
                    for (const auto& building : buildings) {
                        glm::vec3 buildingPosition = getPositionFromMatrix(building);
                        if (glm::distance(newPosition, buildingPosition) < 1.7f) {
                            moveEnemyTanks(enemyTank, -0.1f);
                            break;
                        }
                    }
                    break;
                }
                else if (checkCollisionEnemyTankWithEnemyTanks(enemyTank)) {
                    glm::mat4 copyOfTankTracks = enemyTank->modelMatrixTracks;
                    copyOfTankTracks = glm::translate(copyOfTankTracks, glm::vec3(0, 0, 0.1f));
                    glm::vec3 newPosition = getPositionFromMatrix(copyOfTankTracks);
                    for (Tank* enemyTank2 : enemyTanks) {
                        if (enemyTank == enemyTank2) {
							continue;
						}
                        glm::vec3 enemyTankPosition2 = getPositionFromMatrix(enemyTank2->modelMatrixTracks);
                        if (glm::distance(newPosition, enemyTankPosition2) < 1.2f) {
                            moveEnemyTanks(enemyTank, -0.1f);
                            moveEnemyTanks(enemyTank2, -0.1f);
                        }
                        else {
                            moveEnemyTanks(enemyTank, -0.1f);
                            moveEnemyTanks(enemyTank2, 0.1f);
                        }
                    }
                }
                else {
                    moveEnemyTanks(enemyTank, deltaTimeSeconds);
                    break;
                }
            case MovementState::GoingBackward:
                if (checkCollisionEnemyTankWithBuildings(enemyTank)) {
                    glm::mat4 copyOfTankTracks = enemyTank->modelMatrixTracks;
                    copyOfTankTracks = glm::translate(copyOfTankTracks, glm::vec3(0, 0, -0.1f));
                    glm::vec3 newPosition = getPositionFromMatrix(copyOfTankTracks);
                    for (const auto& building : buildings) {
                        glm::vec3 buildingPosition = getPositionFromMatrix(building);
                        if (glm::distance(newPosition, buildingPosition) < 1.7f) {
                            moveEnemyTanks(enemyTank, 0.1f);
                            break;
                        }
                    }
                    break;
                }
                else if (checkCollisionEnemyTankWithEnemyTanks(enemyTank)) {
                    glm::mat4 copyOfTankTracks = enemyTank->modelMatrixTracks;
                    copyOfTankTracks = glm::translate(copyOfTankTracks, glm::vec3(0, 0, -0.1f));
                    glm::vec3 newPosition = getPositionFromMatrix(copyOfTankTracks);
                    for (Tank* enemyTank2 : enemyTanks) {
                        if (enemyTank == enemyTank2) {
                            continue;
                        }
                        glm::vec3 enemyTankPosition2 = getPositionFromMatrix(enemyTank2->modelMatrixTracks);
                        if (glm::distance(newPosition, enemyTankPosition2) < 1.2f) {
                            moveEnemyTanks(enemyTank, 0.1f);
                            moveEnemyTanks(enemyTank2, 0.1f);
                        }
                        else {
                            moveEnemyTanks(enemyTank, 0.1f);
                            moveEnemyTanks(enemyTank2, -0.1f);
                        }
                    }
                }
                else {
                    moveEnemyTanks(enemyTank, -deltaTimeSeconds);
                    break;
                }
            case MovementState::InPlaceRotationLeft:
                rotateEnemyTanks(enemyTank, deltaTimeSeconds);
                break;
            case MovementState::InPlaceRotationRight:
                rotateEnemyTanks(enemyTank, -deltaTimeSeconds);
                break;
            case MovementState::Aiming:
                float angle = findRotationAngle(enemyTank);
                if (angle != enemyTank->rotateY) {
                    enemyTank->rotateY = angle;
                }
                glm::mat4 copyMatrix = glm::mat4(1);
                copyMatrix = glm::scale(copyMatrix, glm::vec3(0.2f));
                copyMatrix[3].x = enemyTank->modelMatrixTracks[3].x;
                copyMatrix[3].z = enemyTank->modelMatrixTracks[3].z;
                enemyTank->modelMatrixGun = glm::rotate(copyMatrix, enemyTank->rotateY, glm::vec3(0, 1, 0));
                enemyTank->modelMatrixTurret = glm::rotate(copyMatrix, enemyTank->rotateY, glm::vec3(0, 1, 0));
                enemyTank->mouseAngle += angle;
                break;
            }
        }
    }
    else {
        for (Tank* enemyTank : enemyTanks) {
            if (enemyTank->isDead) {
                continue;
            }
            MovementState state = nextMove->GetNextMovementState(enemyTank->lastMovementState);
            enemyTank->lastMovementState = state;
        }
        changeStateEnemyTank = rand() % 5 + 1;
    }
}

bool m1::Tema2::checkCollisionEnemyTankWithBuildings(Tank* enemyTank)
{
	glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixTracks);
    if (!enemyTank->isDead) {
        for (const auto& building : buildings) {
		    glm::vec3 buildingPosition = getPositionFromMatrix(building);
            if (glm::distance(enemyTankPosition, buildingPosition) < 1.7f) {
			    return true;
		    }
	    }
    }

    return false;
}

bool m1::Tema2::checkCollisionEnemyTankWithEnemyTanks(Tank* enemyTank)
{
    glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixTracks);
    if (!enemyTank->isDead) {
        for (Tank* enemyTank2 : enemyTanks) {
            if (enemyTank == enemyTank2) {
                continue;
            }
			glm::vec3 enemyTankPosition2 = getPositionFromMatrix(enemyTank2->modelMatrixTracks);
            if (glm::distance(enemyTankPosition2, enemyTankPosition) < 1.2f) {
				return true;
			}
        }
    }
    return false;
}

void m1::Tema2::attackMyTank(Tank* tank)
{
    for (Tank* enemyTank : enemyTanks) {
        if (enemyTank->isDead) {
			continue;
		}
        glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixTracks);
        glm::vec3 tankPosition = getPositionFromMatrix(tank->modelMatrixTracks);
        if (glm::distance(enemyTankPosition, tankPosition) < 5.f) {
            enemyTank->lastMovementState = MovementState::Aiming;

            if (enemyProjectilDelay <= 0) {
                Projectil* p = new Projectil(numberEnemyProjectils + "enemy", &meshes);
                p->modelMatrixGun = enemyTank->modelMatrixGun;
                p->hasBeenShot = true;
				enemyProjectils.push_back(p);
				numberEnemyProjectils++;
				enemyProjectilDelay = 3.f;
			}
		}
    }
}

void m1::Tema2::renderEnemyProjectils(float deltaTimeSeconds)
{
    for (Projectil* p : enemyProjectils) {
        if (p->livingTime > 0) {
            p->livingTime -= deltaTimeSeconds;
            p->modelMatrixProjectil = p->modelMatrixGun;
            p->modelMatrixProjectil = glm::translate(p->modelMatrixProjectil, glm::vec3(0, 2.f, p->translate + 6.f));
            p->translate += deltaTimeSeconds * projectilSpeed;
            RenderSimpleMesh(meshes[p->name + "projectil"], shaders["HomeworkShader"], p->modelMatrixProjectil, glm::vec3(0, 0, 0), 1);
        }
        else {
            removeFromVector(enemyProjectils, p);
        }
    }
}

void m1::Tema2::checkCollisionEnemyProjectilsWithMyTank(Tank* tank)
{
    for (Projectil* p : enemyProjectils) {
		glm::vec3 projectilPosition = getPositionFromMatrix(p->modelMatrixProjectil);
		glm::vec3 tankPosition = getPositionFromMatrix(tank->modelMatrixHull);
        if (glm::distance(projectilPosition, tankPosition) < 1.2f) {
            if (tank->damage <= 3) {
				tank->damage += 1;
			}
            if (tank->damage >= 4) {
				tank->isDead = true;
			}
			removeFromVector(enemyProjectils, p);
		}
	}
}

void m1::Tema2::checkCollisionEnemyProjectilsWithBuildings()
{
    for (Projectil* p : enemyProjectils) {
        for (const auto& building : buildings) {
			glm::vec3 buildingPosition = getPositionFromMatrix(building);
			glm::vec3 projectilPosition = getPositionFromMatrix(p->modelMatrixProjectil);
            if (glm::distance(buildingPosition, projectilPosition) < 1.3f) {
				removeFromVector(enemyProjectils, p);
			}
		}
	}
}

bool m1::Tema2::checkIfYouWon()
{
    for (Tank* enemyTank : enemyTanks) {
        if (!enemyTank->isDead) {
			return false;
		}
	}

    return true;
}

float m1::Tema2::findRotationAngle(Tank* enemyTank)
{
    glm::vec3 enemyTankPosition = getPositionFromMatrix(enemyTank->modelMatrixTracks);
    glm::vec3 myPosition = getPositionFromMatrix(myTank->modelMatrixTracks);
    glm::vec3 angle = enemyTankPosition - myPosition;
    float ourAngle = atan2(angle.x, angle.z) + RADIANS(180);
    return ourAngle;
}



