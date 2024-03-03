#include "./vga.h"

VGA::VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM)
{
    uint offsetHsync = pio_add_program(vSync, &vga_hsync_program);
    //uint offsetVsync = pio_add_program(hSync, &vga_vsync_program);
    printf("Hsync loaded%d \n", offsetHsync);
    //printf("Vsync loaded%d \n", offsetVsync);

    // init
    vga_hsync_program_init(hSync, hSyncSM, offsetHsync, HSYNC);
    //vga_vsync_program_init(vSync, vSyncSM, offsetVsync, VSYNC);
    pio_sm_put_blocking(hSync, hSyncSM, 624 / 16);
    //pio_sm_put_blocking(vSync, vSyncSM, 480/2);

    //pio_sm_set_enabled(vSync, vSyncSM, true);
    pio_sm_set_enabled(hSync, hSyncSM, true);
}

VGA::~VGA()
{
}
