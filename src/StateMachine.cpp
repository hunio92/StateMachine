#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
    if (mIsMachineRunning)
    {
        std::cout << " deleted while running!" << std::endl;
    }
}

void StateMachine::setCurrentState(const SMState updateState)
{
    mCurrentState = updateState;
}

SMState StateMachine::getCurrentState() const
{
    return mCurrentState;
}

void StateMachine::setStateMachine(const StateMachineList& table,
                                   const PrintStateEventCb& cb)
{
    mStateMachineTable = table;
    mPrintCb = cb;
    mPrintCb(getCurrentState(), SMEvent::E_LAST_EV);
}

void StateMachine::setStateMachine(StateMachineList&& table,
                                   const PrintStateEventCb& cb)
{
    mStateMachineTable = std::move(table);
    mPrintCb = cb;
    mPrintCb(getCurrentState(), SMEvent::E_LAST_EV);
}

void StateMachine::runMachineWithNewEvent(const SMEvent newEvent)
{
    // not authorized to call runMachineWithNewEvent() from guard callbacks!
    bool machineRunning = false;
    if(mIsMachineRunning.compare_exchange_strong(machineRunning, true))
    {
        machineRunning = true;
        bool transitionFound = false;
        for(const StateMachineTableRow &entry : mStateMachineTable)
        {
            if((entry.currentEvent == newEvent) &&
                (entry.currentState == mCurrentState) &&
                // let user use nullptr for guard function
                ((entry.guardFunction == nullptr) ||
                (entry.guardFunction && entry.guardFunction()))
            )
            {
                SMState newState = entry.newState;
                // notify user for new state and event that trigger the change
                mPrintCb(newState, newEvent);

                // change state
                mCurrentState = newState;

                // execute action callbacks
                const auto& callbacksSize = entry.actionFunctionList.size();
                for(size_t i = 0; i < callbacksSize; ++i)
                {
                    if (i == (callbacksSize - 1))
                    {
                        // allow for action to trigger new event or delete machine with last callback
                        // from now on no StateMachine variables are used
                        mIsMachineRunning.store(false);
                        machineRunning = false;
                    }
                    if(entry.actionFunctionList[i])
                    {
                        entry.actionFunctionList[i]();
                    }
                }
                transitionFound = true;
                break;
            }
        }

        if(!transitionFound)
        {
            std::cout << "transition not found. event: " << static_cast<int>(newEvent)
                      << "current state: " << static_cast<int>(mCurrentState) << std::endl;
        }

        if (machineRunning)
        {
            mIsMachineRunning.store(false);
        }
    }
    else
    {
        std::cout << "event called recursively!" << std::endl;
    }
}
