#ifndef IRRIGATION_CONTROLLER_H
#define IRRIGATION_CONTROLLER_H

#include "Defines.h"
#include "StateMachine.h"

class IrrigationController
{
public:
    StateMachine mStateMachine;

    IrrigationController();
    ~IrrigationController();
    IrrigationController& getInstance();

    void init();

    void nextEvent(SMEvent smEvent);

private:
    void printStateEventCb(const SMState& newState, const SMEvent& event);

    void smIdleState(void);

    void smStartIrrigation(SMEvent smEvent);
};

#endif // IRRIGATION_CONTROLLER_H
