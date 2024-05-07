#include <iostream>

#include "IrrigationController.h"

int main()
{
    IrrigationController irrigatorController;
    irrigatorController.getInstance().init();

    irrigatorController.getInstance().nextEvent(SMEvent::E_START_IRRIGATION_EV);
}
