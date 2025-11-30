//pin_select.h
#include"types.h"

#ifndef PIN_SELECT_H
#define PIN_SELECT_H

// Pin Function Selection Constants
// 0 ? Function 1, 1 ? Function 2, 2 ? Function 3, 3 ? Function 4
#define PIN_FUNC1 0
#define PIN_FUNC2 1
#define PIN_FUNC3 2
#define PIN_FUNC4 3

void CfgPortPinFun(u32,u32,u32);  // Function Prototype
#endif  //PIN_SELECT_H
