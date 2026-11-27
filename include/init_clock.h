#ifndef GUARD_INIT_CLOCK_H
#define GUARD_INIT_CLOCK_H

extern const u8 gText_ClockNotWorkingLc[];

void CB2_InitClockLc(void);
bool32 IsClockAvailableLc(void);
void SetNewGameClockLc(void);

#endif //GUARD_INIT_CLOCK_H
