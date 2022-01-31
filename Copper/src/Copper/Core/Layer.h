#pragma once

#include "Copper/Event/Event.h"
#include "Timestep.h"

namespace Copper
{

class Layer
{
public:
    Layer(const std::string& name)
        : m_DebugName(name) {};
    virtual ~Layer() {}
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnEvent(Event& event) {}
    virtual void OnUpdate(Timestep ts) {}
    virtual void OnImGuiUpdate() {}

    inline const std::string& GetName() const { return m_DebugName; }
private:
    std::string m_DebugName;
};

}
