#include "nextMove.h"

namespace m1
{
    NextMove::NextMove()
    {
    }
    NextMove::~NextMove()
    {
    }

    int NextMove::GetRandomNumberInRange(const int minInclusive, const int maxInclusive)
    {
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());

        std::uniform_int_distribution<int> uniformDist(minInclusive, maxInclusive);

        return uniformDist(randomEngine);
    }

    MovementState NextMove::GetNextMovementState(const MovementState currentState)
    {
        int randomChange = GetRandomNumberInRange(0, 1);
        MovementState nextState = currentState;

        switch (currentState)
        {
        case MovementState::GoingForward:
        case MovementState::GoingBackward:
            nextState = (randomChange == 1)
                ? MovementState::InPlaceRotationLeft
                : MovementState::InPlaceRotationRight;
            break;

        case MovementState::InPlaceRotationLeft:
        case MovementState::InPlaceRotationRight:
            nextState = (randomChange == 1)
                ? MovementState::GoingForward
                : MovementState::GoingBackward;
            break;
        case MovementState::Aiming:
			nextState = (randomChange == 1)
				? MovementState::GoingForward
				: MovementState::GoingBackward;
			break;

        default:
            break;
        }

        return nextState;
    }


    std::string NextMove::GetMovementStateName(const MovementState state)
    {
        static const std::map<MovementState, std::string> kStateNames
        {
            { MovementState::GoingForward, "GoingForward" },
            { MovementState::GoingBackward, "GoingBackward" },
            { MovementState::InPlaceRotationLeft, "InPlaceRotationLeft" },
            { MovementState::InPlaceRotationRight, "InPlaceRotationRight" },
        };

        std::string s = "";

        if (kStateNames.find(state) != kStateNames.end())
        {
            s = kStateNames.at(state);
        }

        return s;
    }
}