#ifndef PCH_H
#define PCH_H

#include "framework.h"

#pragma comment(lib, "detours.lib")

#pragma warning( disable : 4244 ) //Disable int to float warning
#pragma warning( disable : 4267 ) //Disable size_t to int warning
#pragma warning( disable : 4305 ) //Disable double to float warning

#include "utils.h"
#include "structs.h"
#include "defines.h"
#include "esp.h"
#include "ui.h"
#include "menu.h"

#endif //PCH_H
