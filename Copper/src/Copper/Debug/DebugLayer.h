#pragma once

#include "Copper/Layer.h"

namespace Copper
{

class DebugLayer : public Layer
{
public:
    DebugLayer();
    ~DebugLayer();
    
    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(Event& event) override;
    void OnUpdate() override;
private:
    float m_Time = 0;
};

}
