#pragma once
#include <string>

enum class Mode
{
    Seek      = 0,
    Flee      = 1,
    Pursuit   = 2,
    FlowField = 3,

    Count     = 4
};

const char* modeString(Mode mode);