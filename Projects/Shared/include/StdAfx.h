#pragma once

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <algorithm>
#include <functional>

#include <vector>
#include <list>
#include <map>
#include <string>


#define Log(str, ...) printf(str, __VA_ARGS__)
#define Warn(str, ...) printf("WARNING: "str, __VA_ARGS__)
#define Error(str, ...) printf("ERROR: "str, __VA_ARGS__)

#include "Util\timer.h"
#include "Util\consolewindow.h"
#include "Util\vectortypes.h"
#include "Util\winkeycodes.h"

#include "Util\Utility.h"