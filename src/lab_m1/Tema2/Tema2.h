#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "tank.h"
#include "projectil.h"
#include "nextMove.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const float damage);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderTank(Tank* tank, glm::vec3 colorHull, glm::vec3 colorTurret, glm::vec3 colorGun);
        void moveForwardAndBackTank(Tank* tank, float deltaTimeSeconds);
        void rotateTank(Tank* tank, float deltaTimeSeconds);
        void reinitializeTank(Tank* tank);
        void renderPlane(glm::vec3 color);
        void renderBuildings(glm::vec3 color);
        void rotateGunAndTurret(Tank* tank, float mouseX);
        void renderFriendlyProjectils(Tank* tank, float deltaTimeSeconds);
        template <typename T>
        void removeFromVector(std::vector<T*>& vector, T* item);
        void checkCollisionTankWithBuildings(Tank* tank);
        glm::vec3 getPositionFromMatrix(glm::mat4 matrix);
        void checkCollisionProjectilsWithBuildings();
        void moveEnemyTanks(Tank* enemyTank, float deltaTimeSeconds);
        void rotateEnemyTanks(Tank* enemyTank, float deltaTimeSeconds);
        void checkCollisionProjectilsWithEnemyTanks();
        void checkCollisionTankWithEnemyTanks(Tank* tank);
        void moveEnemyTanksRandomly(float deltaTimeSeconds);
        bool checkCollisionEnemyTankWithBuildings(Tank* enemyTank);
        bool checkCollisionEnemyTankWithEnemyTanks(Tank* enemyTank);
        void attackMyTank(Tank* tank);
        void renderEnemyProjectils(float deltaTimeSeconds);
        void checkCollisionEnemyProjectilsWithMyTank(Tank* tank);
        void checkCollisionEnemyProjectilsWithBuildings();
        bool checkIfYouWon();
        float findRotationAngle(Tank* enemyTank);

     protected:
        implemented::Camera *camera;
        implemented::Camera* camera2;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        Tank* myTank;
        float cameraPos;
        bool sKeyIsPressed;
        int score;
        bool gameOver;

        float orthoDelta;
        float fov;
        float cameraSpeed;
        float timeElapsed;
        glm::vec3 silver;
        glm::vec3 mediumOrchid;
        float tankSpeed;
        float totalTankMove;
        float totalTankRotate;
        std::vector<Projectil* > friendlyProjectils;
        std::vector<Projectil* > enemyProjectils;
        int numberFriendlyProjectils;
        float projectilSpeed;
        float projectilDelay;
        float enemyProjectilDelay;
        NextMove* nextMove;
        float changeStateEnemyTank;
        int numberEnemyProjectils;
        bool rotateCamera;
        bool youWon;

        std::vector<glm::mat4> buildings;
        glm::mat4 building1;
        glm::mat4 building2;
        glm::mat4 building3;
        glm::mat4 building4;
        glm::mat4 building5;
        glm::mat4 building6;
        glm::mat4 building7;
        glm::mat4 building8;
        glm::mat4 building9;
        glm::mat4 building10;
        Tank* enemyTank1;
        Tank* enemyTank2;
        Tank* enemyTank3;
        Tank* enemyTank4;
        Tank* enemyTank5;
        std::vector<Tank*> enemyTanks;
        glm::vec3 colorHull;
        glm::vec3 colorTurret;
        glm::vec3 colorGun;
        glm::vec3 colorHullEnemy;
        glm::vec3 colorTurretEnemy;
        glm::vec3 colorGunEnemy;
        glm::vec3 chocolate;
    };
}   // namespace m1
