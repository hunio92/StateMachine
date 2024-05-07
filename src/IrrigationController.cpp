#include <functional>

#include "IrrigationController.h"
#include "StateMachine.h"

IrrigationController::IrrigationController()
{
}

IrrigationController::~IrrigationController()
{

}

IrrigationController& IrrigationController::getInstance()
{
    static IrrigationController irrigationController;
    return irrigationController;
}



void IrrigationController::init()
{
    StateMachine::StateMachineList stateMachineTransitionTable =
    {
    /* Entry State                                 Event                                        Guard Function      New State                                      Action function(s) */
    /********** IDLE STATE *********/
    {SMState::E_IDLE_STATE,                        SMEvent::E_START_IRRIGATION_EV,              nullptr,            SMState::E_IRRIGATION_STATE,                 {std::bind(&IrrigationController::smStartIrrigation, this, SMEvent::E_START_IRRIGATION_EV)}},

    /********** IRRIGATION STATE *********/
    // {SMState::E_IRRIGATION_STATE,                  SMEvent::E_STOP_IRRIGATION_EV,            nullptr,            SMState::E_IDLE_STATE,                       {std::bind(&IrrigationController::smIdleState, this)}},
    };

    mStateMachine.setStateMachine(stateMachineTransitionTable, [=] (SMState state, SMEvent event) { IrrigationController::printStateEventCb(state, event); });

    mStateMachine.setCurrentState(SMState::E_IDLE_STATE);
}

void IrrigationController::printStateEventCb(const SMState& newSmState, const SMEvent& smEvent)
{
    std::cout << "[StateMachine] <Transition>: ["
                << mStateMachine.getCurrentState() << "]"
                << " -> " << smEvent << " -> [" << newSmState << "]" << std::endl;
}

void IrrigationController::nextEvent(SMEvent smEvent)
{
    std::cout << "[StateMachine] <PostingEvent>: " << smEvent << std::endl;

    mStateMachine.runMachineWithNewEvent(smEvent);
}

void IrrigationController::smIdleState(void)
{
    std::cout << "Idle State" << std::endl;
};

void IrrigationController::smStartIrrigation(SMEvent smEvent)
{
    std::cout << "Start Irrigation State" << std::endl;

    if (SMEvent::E_START_IRRIGATION_EV == smEvent)
    {
        std::cout << "Irrigate" << std::endl;
    }
};
