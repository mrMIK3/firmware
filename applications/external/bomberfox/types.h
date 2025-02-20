#ifndef BOMBER_TYPES_H
#define BOMBER_TYPES_H

#include <stdint.h>
#include <gui/gui.h>
#include <furi_hal.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>
#include <lib/subghz/subghz_tx_rx_worker.h>

#define TAG                     "bomb"
#define LOOP_MESSAGE_TIMEOUT_ms 500
#define DEFAULT_FREQ            433920000
#define RX_TX_BUFFER_SIZE       3
#define MAX_BOMBS               10
#define LEVEL_SIZE              128
#define POWERUP_EXTRABOMB_RATIO 0.1
#define POWERUP_BOMBPOWER_RATIO 0.15

// Graphics
static const uint8_t brick_glyph[] = {0xff, 0x11, 0xff, 0x88, 0xff, 0x11, 0xff, 0x88};
static const uint8_t fox_glyph[] = {0x81, 0xc3, 0xbd, 0x81, 0x99, 0x42, 0x24, 0x18};
static const uint8_t wolf_glyph[] = {0x81, 0xc3, 0xff, 0xff, 0xe7, 0x7e, 0x3c, 0x18};
static const uint8_t bomb_glyph[] = {0x20, 0x10, 0x08, 0x1e, 0x3f, 0x27, 0x37, 0x1e};
static const uint8_t bomb_flash[] = {0x20, 0x10, 0x08, 0x1e, 0x21, 0x21, 0x21, 0x1e};
static const uint8_t bomb_explode[] = {0x30, 0x4b, 0x8d, 0x61, 0x22, 0x91, 0xaa, 0xcc};
static const uint8_t select_glyph[] = {0x01, 0x03, 0x07, 0x0f, 0x07, 0x03, 0x01};
static const uint8_t powerup_extrabomb_glyph[] = {0xff, 0x81, 0xb5, 0xaf, 0xa5, 0xf1, 0x81, 0xff};
static const uint8_t powerup_bombpower_glyph[] = {0xff, 0x81, 0x99, 0xbd, 0xbd, 0x99, 0x81, 0xff};

static const uint8_t fox[] = {
    0x08, 0x00, 0x01, 0x00, 0x14, 0x80, 0x02, 0x00, 0x24, 0x4f, 0x02, 0x00, 0xc4, 0x30, 0x02,
    0x00, 0x04, 0x00, 0x02, 0x00, 0x14, 0x80, 0x02, 0x00, 0x0c, 0x00, 0x03, 0x00, 0xc4, 0x30,
    0x02, 0x00, 0x42, 0x20, 0x04, 0x00, 0xc2, 0x30, 0x04, 0x00, 0x01, 0x06, 0x08, 0x00, 0x06,
    0x00, 0xe6, 0x01, 0x18, 0x80, 0x11, 0x01, 0xe0, 0x70, 0x10, 0x01, 0x20, 0x4f, 0x08, 0x01,
    0x20, 0x40, 0x08, 0x01, 0x10, 0x80, 0x84, 0x00, 0x10, 0x80, 0x84, 0x00, 0x50, 0xa0, 0x42,
    0x00, 0x50, 0xa0, 0x22, 0x00, 0x48, 0x29, 0x11, 0x00, 0x48, 0x29, 0x09, 0x00, 0x48, 0x29,
    0x07, 0x00, 0x48, 0x26, 0x01, 0x00, 0xf0, 0xf9, 0x00, 0x00};
static const uint8_t wolf[] = {
    0x08, 0x00, 0x01, 0x00, 0x14, 0x80, 0x02, 0x00, 0x24, 0x4f, 0x02, 0x00, 0xc2, 0x30, 0x04,
    0x00, 0x02, 0x00, 0x04, 0x00, 0x12, 0x80, 0x04, 0x00, 0x0a, 0x00, 0x05, 0x00, 0x44, 0x20,
    0x02, 0x00, 0x82, 0x10, 0x04, 0x00, 0xc2, 0x30, 0x04, 0x00, 0x01, 0x00, 0x08, 0x00, 0x06,
    0x06, 0xe6, 0x01, 0x18, 0x80, 0x11, 0x01, 0xe0, 0x70, 0x10, 0x01, 0x20, 0x4f, 0x08, 0x01,
    0x20, 0x40, 0x08, 0x01, 0x10, 0x80, 0x84, 0x00, 0x10, 0x80, 0x84, 0x00, 0x50, 0xa0, 0x42,
    0x00, 0x50, 0xa0, 0x22, 0x00, 0x48, 0x29, 0x11, 0x00, 0x48, 0x29, 0x09, 0x00, 0x48, 0x29,
    0x07, 0x00, 0x48, 0x26, 0x01, 0x00, 0xf0, 0xf9, 0x00, 0x00};

// A level is basically a 2D array of blocks of one of the following types
typedef enum BlockType {
    BlockType_Empty = 0,
    BlockType_Brick = 1,
    BlockType_Bomb = 2,
    BlockType_Fox = 3,
    BlockType_Wolf = 4,
    BlockType_PuExtraBomb = 5,
    BlockType_PuBombStrength = 6,
    BlockType_PuExtraBomb_Hidden = 7,
    BlockType_PuBombStrength_Hidden = 8
} BlockType;

// Possible states a bomb can be in
typedef enum BombState {
    BombState_None = 0, // Bomb not planted yet
    BombState_Planted = 1, // Bomb has been planted
    BombState_Hot = 2, // Bomb is about to be detonated
    BombState_Explode = 3 // Bomb has exploded
} BombState;

typedef struct {
    uint8_t x;
    uint8_t y;
} Point;

// Represents a bomb. Keeps track of its state and when it was planted.
typedef struct {
    uint8_t x;
    uint8_t y;
    uint32_t planted;
    BombState state;
} Bomb;

typedef struct {
    uint8_t x;
    uint8_t y;
    Bomb bombs[MAX_BOMBS]; // Array of bombs
    uint8_t bomb_power; // Number of blocks a bomb will destroy
    uint8_t bomb_ix; // Index of currently held bomb
    uint8_t bomb_count; // How many bombs the player can use
} Player;

// Application mode. Rendering and input handlers rely on this to know what to render, or how to handle input.
typedef enum {
    BomberAppMode_Uninitialised,
    BomberAppMode_LevelSelect,
    BomberAppMode_PlayerSelect,
    BomberAppMode_Waiting,
    BomberAppMode_Ready,
    BomberAppMode_Playing,
    BomberAppMode_Finished,
    BomberAppMode_GameOver,
    BomberAppMode_Error,
    BomberAppMode_Quit
} BomberAppMode;

typedef enum {
    RxMode_Command,
    RxMode_LevelData
} RxMode;

// Event types for message queue
typedef enum {
    BomberEventType_Input,
    BomberEventType_Tick,
    BomberEventType_SubGhz,
    BomberEventType_HaveLevelData
} BomberEventType;

typedef struct {
    BomberEventType type;
    InputEvent input;
    size_t subGhzIncomingSize;
} BomberEvent;

typedef enum {
    WhoDied_None,
    WhoDied_Fox,
    WhoDied_Wolf
} WhoDied;

typedef struct {
    FuriMessageQueue* queue; // Message queue
    FuriMutex* data_mutex; // Mutex
    ViewPort* view_port; // Viewport
    Gui* gui; // GUI
    NotificationApp* notification;
    FuriTimer* timer;
    BomberAppMode mode;
    uint8_t* level; // Pointer to the current level array
    bool running;
    Player fox; // Position of the fox
    Player wolf; // Position of the wolf
    bool isPlayerTwo;
    uint8_t selectedLevel;

    WhoDied dead;

    // for Sub-GHz
    uint32_t frequency;
    SubGhzTxRxWorker* subghz_worker;
    const SubGhzDevice* subghz_device;
    volatile uint32_t last_time_rx_data;
    uint8_t rx_buffer[RX_TX_BUFFER_SIZE];
    uint8_t tx_buffer[RX_TX_BUFFER_SIZE];
    uint8_t levelData[128];
    RxMode rxMode;
} BomberAppState;

#endif
