#include "switch/init.hpp"
#include <switch.h>
#include <cstdio>

namespace nswitch {

void init()
{
  Result nsError = nsInitialize();
  if (R_FAILED(nsError)) {
    return;
  }
  socketInitializeDefault();
  nxlinkConnectToHost(true, false);
  romfsInit();
  printf("init finished\n");
}

void deinit()
{
  romfsExit();
  socketExit();
  nsExit();
}

}
