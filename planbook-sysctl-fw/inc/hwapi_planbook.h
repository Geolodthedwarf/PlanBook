#ifndef HWAPI_PLANBOOK
#define HWAPI_PLANBOOK

#include "sysctl.h"

void hwapi_planbook_init(battery_info_s *binfo);
uint64_t hwapi_set_usb_mode(uint64_t port, uint64_t mode);

#endif
