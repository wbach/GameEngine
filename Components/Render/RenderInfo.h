#pragma once
#include <functional>

struct RenderInfo
{
    std::function<void ()> m_RenderFunction;
};
