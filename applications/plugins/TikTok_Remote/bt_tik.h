#pragma once

#include <furi.h>
#include <bt/bt_service/bt.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <notification/notification.h>

#include <gui/modules/dialog_ex.h>
#include "views/bt_tik_tiktok.h"

typedef struct {
    Bt* bt;
    Gui* gui;
    NotificationApp* notifications;
    ViewDispatcher* view_dispatcher;
    DialogEx* dialog;
    BtTikTikTok* bt_tik_tiktok;
    uint32_t view_id;
} BtTik;

typedef enum {
    BtTikViewTikTok,
    BtTikViewExitConfirm,
} BtTikView;
