#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>
#include <functional>

enum class SMState //: std::uint32_t
{
    E_IDLE_STATE = 0,
    E_IRRIGATION_STATE,
    E_CANCEL_EV,
    E_LAST_STATE
};

enum class SMEvent // : uint32_t
{
    E_EMPTY_EV = 0,
    E_START_IRRIGATION_EV,
    E_STOP_IRRIGATION_EV,
    E_FM_CANCEL_EV,
    E_LAST_EV
};

inline std::ostream &operator<<(std::ostream &out, const SMState &in)
{
      switch (in)
    {
        case SMState::E_IDLE_STATE:
            out << "E_IDLE_STATE";
            break;
        case SMState::E_IRRIGATION_STATE:
            out << "E_IRRIGATION_STATE";
            break;
        case SMState::E_CANCEL_EV:
            out << "E_CANCEL_EV";
            break;
        case SMState::E_LAST_STATE:
            out << "E_LAST_STATE";
            break;
        default:
            out << "Invalid Irrigation State: " << (uint32_t)in;
            break;
    }

    return out;
}

inline std::ostream &operator<<(std::ostream &out, const SMEvent &in)
{
      switch (in)
    {
        case SMEvent::E_EMPTY_EV:
            out << "E_EMPTY_EV";
            break;
        case SMEvent::E_START_IRRIGATION_EV:
            out << "E_START_IRRIGATION_EV";
            break;
        case SMEvent::E_STOP_IRRIGATION_EV:
            out << "E_STOP_IRRIGATION_EV";
            break;
        case SMEvent::E_FM_CANCEL_EV:
            out << "E_FM_CANCEL_EV";
            break;
        case SMEvent::E_LAST_EV:
            out << "E_LAST_EV";
            break;
        default:
            out << "Invalid Irrigation Event: " << (uint32_t)in;
            break;
    }

    return out;
}

#endif // DEFINES_H
