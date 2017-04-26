#include "gba/gba.h"
#include "gba/flash_internal.h"

extern const u16 mxMaxTime[];
extern const struct FlashSetupInfo MX29L010;
extern const struct FlashSetupInfo LE26FV10N1TS;
extern const struct FlashSetupInfo DefaultFlash;

const struct FlashSetupInfo * const sSetupInfos512[] =
{
    (const struct FlashSetupInfo * const)0x08152F88, // 64k SST
    (const struct FlashSetupInfo * const)0x08152FB8, // 64k Macronix
    &DefaultFlash, // repurposed for 64k Panasonic
    &MX29L010,     // 128k Macronix
    &LE26FV10N1TS, // 128k Sanyo
    0              // intentionally 0, indicates end of known flash chips
    // technically there's one more flash chip, the 64k Atmel, but that one has odd
    // characteristics that would need to be handled differently than all other chips,
    // so I've chosen to not support it
};

const struct FlashSetupInfo LE26FV10N1TS =
{
    ProgramFlashByte_MX,
    ProgramFlashSector_MX,
    EraseFlashChip_MX,
    EraseFlashSector_MX,
    WaitForFlashWrite_Common,
    mxMaxTime,
    {
        131072, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              32, // number of sectors
               0  // appears to be unused
        },
        { 3, 1 }, // wait state setup data
        { { 0x62, 0x13 } } // ID
    }
};
