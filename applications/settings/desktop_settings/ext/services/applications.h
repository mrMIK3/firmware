#pragma once

#include <furi.h>
#include <gui/icon.h>

typedef enum {
    FlipperInternalApplicationFlagDefault = 0,
    FlipperInternalApplicationFlagInsomniaSafe = (1 << 0),
} FlipperInternalApplicationFlag;

typedef struct {
    const FuriThreadCallback app;
    const char* name;
    const char* appid;
    const size_t stack_size;
    const Icon* icon;
    const FlipperInternalApplicationFlag flags;
} FlipperInternalApplication;

/* Apps list
 * Spawned by loader
 */
const FlipperInternalApplication FLIPPER_APPS2[] = {

    {
        .name = "Applications",
    },

    {
        .name = "Bad USB",
        .appid = "/ext/apps/Main/bad_usb.fap",
    },

    {
        .name = "Clock",
        .appid = "/ext/apps/Main/Dab_Timer.fap",
    },

    {
        .name = "GPIO",
        .appid = "/ext/apps/Main/gpio.fap",
    },

    {
        .name = "iButton",
        .appid = "/ext/apps/Main/iButton.fap",
    },

    {
        .name = "Infrared",
        .appid = "/ext/apps/Main/infrared.fap",
    },

    {
        .name = "IR Remote",
        .appid = "/ext/apps/Infrared/IR_Remote.fap",
    },

    {
        .name = "NFC",
    },

    {
        .name = "Sub-GHz",
    },

    {
        .name = "Sub-GHz Playlist",
        .appid = "/ext/apps/Sub-GHz/SubGHz_Playlist.fap",
    },

    {
        .name = "Sub-GHz Remote",
        .appid = "/ext/apps/Sub-GHz/Subghz_Remote_Refactored.fap",
    },

    {
        .name = "U2F",
        .appid = "/ext/apps/Main/u2f.fap",
    },

    {
        .name = "125 kHz RFID",
    }};
const size_t FLIPPER_APPS_COUNT2 = COUNT_OF(FLIPPER_APPS2);
