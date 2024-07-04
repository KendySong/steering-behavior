#include "Mode.hpp"

const char* modeString(Mode mode)
{
    switch (mode)
    {
    case Mode::Seek:
        return "Seek";
        break;

    case Mode::Flee:
        return "Flee";
        break;

    case Mode::Pursuit:
        return "Pursuit";
        break;

    case Mode::FlowField:
        return "FlowField";
        break;
    }
}