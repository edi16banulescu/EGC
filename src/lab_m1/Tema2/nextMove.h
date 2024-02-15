#pragma once
#include <iostream>
#include <random>
#include <map>
#include <string>


namespace m1
{
    enum class MovementState
    {
        GoingForward,
        GoingBackward,
        InPlaceRotationLeft,
        InPlaceRotationRight,
        Aiming
    };
    class NextMove {
        public:
            NextMove();
            ~NextMove();
            int GetRandomNumberInRange(const int minInclusive, const int maxInclusive);

            MovementState GetNextMovementState(const MovementState currentState);
            std::string GetMovementStateName(const MovementState state);
    };
}