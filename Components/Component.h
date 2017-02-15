#pragma once
#include <functional>
#include <list>

class CComponent
{
public:
    void Call_OnStart()
    {
       if(m_OnStart != nullptr)
            m_OnStart();
    }
    void Call_Update()
    {
       if(m_Update != nullptr)
            m_Update();
    }
    void Call_PostUpdate()
    {
        if(m_PostUpdate != nullptr)
            m_PostUpdate();
    }

    bool HaveUpdate() {return m_Update != nullptr;}
    bool HaveOnStart() {return m_OnStart != nullptr;}
protected:
    std::function<void ()> m_OnStart = nullptr;
    std::function<void ()> m_Update  = nullptr;
    std::function<void ()> m_PostUpdate = nullptr;
};
