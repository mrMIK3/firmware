#include "bt_tik.h"
#include <furi_hal_bt.h>
#include <notification/notification_messages.h>
#include <dolphin/dolphin.h>

#define TAG "BtTikApp"



void bt_tik_dialog_callback(DialogExResult result, void* context) {
    furi_assert(context);
    BtTik* app = context;
    if(result == DialogExResultLeft) {
        view_dispatcher_stop(app->view_dispatcher);
    } else if(result == DialogExResultRight) {
        view_dispatcher_switch_to_view(app->view_dispatcher, app->view_id); // Show last view
    }
}

uint32_t bt_tik_exit_confirm_view(void* context) {
    UNUSED(context);
    return BtTikViewExitConfirm;
}

uint32_t bt_tik_exit(void* context) {
    UNUSED(context);
    return VIEW_NONE;
}

void bt_tik_connection_status_changed_callback(BtStatus status, void* context) {
    furi_assert(context);
    BtTik* bt_tik = context;
    bool connected = (status == BtStatusConnected);
    if(connected) {
        notification_internal_message(bt_tik->notifications, &sequence_set_blue_255);
    } else {
        notification_internal_message(bt_tik->notifications, &sequence_reset_blue);
    }
    bt_tik_tiktok_set_connected_status(bt_tik->bt_tik_tiktok, connected);
}

BtTik* bt_tik_app_alloc() {
    BtTik* app = malloc(sizeof(BtTik));

    // Gui
    app->gui = furi_record_open(RECORD_GUI);

    // Bt
    app->bt = furi_record_open(RECORD_BT);

    // Notifications
    app->notifications = furi_record_open(RECORD_NOTIFICATION);

    // View dispatcher
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

    // Dialog view
    app->dialog = dialog_ex_alloc();
    dialog_ex_set_result_callback(app->dialog, bt_tik_dialog_callback);
    dialog_ex_set_context(app->dialog, app);
    dialog_ex_set_left_button_text(app->dialog, "Exit");
    dialog_ex_set_right_button_text(app->dialog, "Stay");
    dialog_ex_set_header(app->dialog, "Close Current App?", 16, 12, AlignLeft, AlignTop);
    view_dispatcher_add_view(
        app->view_dispatcher, BtTikViewExitConfirm, dialog_ex_get_view(app->dialog));

    // TikTok view
    app->bt_tik_tiktok = bt_tik_tiktok_alloc();
    view_set_previous_callback(
        bt_tik_tiktok_get_view(app->bt_tik_tiktok), bt_tik_exit_confirm_view);
    view_dispatcher_add_view(
        app->view_dispatcher, BtTikViewTikTok, bt_tik_tiktok_get_view(app->bt_tik_tiktok));
    // TODO switch to menu after Media is done
    app->view_id = BtTikViewTikTok;
    view_dispatcher_switch_to_view(app->view_dispatcher, app->view_id);

    return app;
}


void bt_tik_app_free(BtTik* app) {
    furi_assert(app);

    // Reset notification
    notification_internal_message(app->notifications, &sequence_reset_blue);

    // Free views
    view_dispatcher_remove_view(app->view_dispatcher, BtTikViewExitConfirm);
    dialog_ex_free(app->dialog);
    view_dispatcher_remove_view(app->view_dispatcher, BtTikViewTikTok);
    bt_tik_tiktok_free(app->bt_tik_tiktok);
    view_dispatcher_free(app->view_dispatcher);

    // Close records
    furi_record_close(RECORD_GUI);
    app->gui = NULL;
    furi_record_close(RECORD_NOTIFICATION);
    app->notifications = NULL;
    furi_record_close(RECORD_BT);
    app->bt = NULL;\

    // Free rest
    free(app);
}

int32_t bt_tik_app(void* p) {
    UNUSED(p);
    // Switch profile to Hid
    BtTik* app = bt_tik_app_alloc();
    bt_set_status_changed_callback(app->bt, bt_tik_connection_status_changed_callback, app);
    // Change profile
    if(!bt_set_profile(app->bt, BtProfileHidKeyboard)) {
        FURI_LOG_E(TAG, "Failed to switch profile");
        bt_tik_app_free(app);
        return -1;
    }
    furi_hal_bt_start_advertising();

    DOLPHIN_DEED(DolphinDeedPluginStart);

    view_dispatcher_run(app->view_dispatcher);

    bt_set_status_changed_callback(app->bt, NULL, NULL);
    // Change back profile to Serial
    bt_set_profile(app->bt, BtProfileSerial);

    bt_tik_app_free(app);

    return 0;
}
