#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <atomic>

#include "Defines.h"

class StateMachine
{
public:
	using GuardFunction = std::function<bool()>;
    using ActionFunction = std::function<void()>;
    using PrintStateEventCb = typename std::function<void(const SMState&, const SMEvent&)>;

    struct StateMachineTableRow
    {
        SMState currentState;
        SMEvent currentEvent;
        GuardFunction guardFunction;
        SMState newState;
        std::vector<ActionFunction> actionFunctionList;
    };

    using StateMachineList = std::vector<StateMachineTableRow>;

    StateMachine();
    ~StateMachine();

    void setCurrentState(const SMState updateState);

    SMState getCurrentState() const;

	void setStateMachine(const StateMachineList& table,
					     const PrintStateEventCb& cb);

    void setStateMachine(StateMachineList&& table,
                         const PrintStateEventCb& cb);

	void runMachineWithNewEvent(const SMEvent newSmEvent);

private:
    std::atomic<bool> mIsMachineRunning {false};
	SMState mCurrentState = SMState::E_IDLE_STATE;
    StateMachineList mStateMachineTable;
    PrintStateEventCb mPrintCb;

    // Delete move, copy, assign
    StateMachine(const StateMachine&) = delete;
    StateMachine(const StateMachine&&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;
};

#endif // STATE_MACHINE_H
