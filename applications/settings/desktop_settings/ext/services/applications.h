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
    const char* link;
} FlipperInternalApplication;

/* Apps list
 * Spawned by loader
 */
const FlipperInternalApplication FLIPPER_APPS2[] = {

    {
        .name = "Clock",
    },

    {
        .name = "Applications",
    },

    {
        .name = "Sub-GHz",
    },

    {
        .name = "Sub-GHz Remote",
    },

    {
        .name = "Sub-GHz Playlist",
    },

    {
        .name = "125 kHz RFID",
    },

    {
        .name = "NFC",
    },

    {
        .name = "Infrared",
    },

    {
        .name = "IR Remote",
    },

    {
        .name = "GPIO",
    },

    {
        .name = "iButton",
    },

    {
        .name = "Bad USB",
    },

    {
        .name = "U2F",
    }};
const size_t FLIPPER_APPS_COUNT2 = COUNT_OF(FLIPPER_APPS2);
