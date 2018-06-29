#include <switch.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>


void error(const char *error)
{
    printf("[eXhop:Error] %s", error);
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
}

int main()
{
    gfxInitDefault();
    nsInitialize();
    fsInitialize();
    consoleInit(NULL);
    printf("\n");
	u64 tid = 0x0100069000078000;
    printf("Press A to download the Retail Interactive Display Menu");
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
            Result res = nsBeginInstallApplication(tid, 0, FsStorageId_SdCard);
            if(R_SUCCEEDED(res))
            {
                printf("Retail Interactive Display Menu download started, check it in Home Menu!\n");
            }
            else error("Failure starting Retail Interactive Display Menu download.");
        }
    }
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    nsExit();
    fsExit();
    gfxExit();
}