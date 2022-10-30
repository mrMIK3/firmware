#pragma once

#include <gui/view.h>

typedef struct BtTikTikTok BtTikTikTok;

BtTikTikTok* bt_tik_tiktok_alloc();

void bt_tik_tiktok_free(BtTikTikTok* bt_tik_tiktok);

View* bt_tik_tiktok_get_view(BtTikTikTok* bt_tik_tiktok);

void bt_tik_tiktok_set_connected_status(BtTikTikTok* bt_tik_tiktok, bool connected);
