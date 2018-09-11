#include "time.h"

// Backlight blinking
static uint32_t timer;
static bool blinking = false;
static int blink_seq = 0;
static int blink_effects[][100] = {
    [0] = {
        9,   // number of steps
        0,   // current step
        200, // interval
        1, 2, 3, 3, 3, 2, 2, 1, 1 // levels
    },
    [1] = {
        2,   // number of steps
        0,   // current step
        100, // interval
        0, 3 // levels
    },
    [2] = {
        9,   // number of steps
        0,   // current step
        200, // interval
        0, 3, 0, 0, 3, 0, 0, 0, 3 // levels
    },
    [3] = {
        6,   // number of steps
        0,   // current step
        100, // interval
        3, 2, 3, 1, 3, 0 // levels
    }
};

// Enable blinking
void enable_blinking(void)
{
    blinking = true;
    timer = timer_read32();
}

// Disable blinking
void disable_blinking(void)
{
    blinking = false;
    backlight_level(BACKLIGHT_LEVELS); // it could be 0, depends on circuit.
}

// Add to function matrix_scan_user()
void blink_backlight(void)
{
    if (!blinking) return;

    uint32_t now = timer_read32();
    if (now - timer > blink_effects[blink_seq][2])
    {
        timer = now;
        backlight_level(blink_effects[blink_seq][blink_effects[blink_seq][1]++ + 3]);
        blink_effects[blink_seq][1] %= blink_effects[blink_seq][0];
    }
}

// Move to next blinking effect
void blink_next(void)
{
    blink_seq++;
    blink_seq %= sizeof (blink_effects) / sizeof(blink_effects[0]);
}
