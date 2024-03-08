#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <dialogs/dialogs.h>
#include <gui/modules/dialog_ex.h>
#include <applications.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/popup.h>
#include <lib/toolbox/path.h>
#include <lib/toolbox/value_index.h>
#include <storage/storage.h>
#include <toolbox/stream/file_stream.h>
#include "scenes/cfw_app_scene.h"
#include "dolphin/helpers/dolphin_state.h"
#include "dolphin/dolphin.h"
#include "dolphin/dolphin_i.h"
#include <lib/flipper_format/flipper_format.h>
#include <lib/subghz/subghz_setting.h>
#include <flipper_application/flipper_application.h>
#include <loader/loader.h>
#include <loader/loader_mainmenu.h>
#include <notification/notification_app.h>
#include <power/power_service/power.h>
#include <rgb_backlight.h>
#include <m-array.h>
#include <cfw/cfw.h>
#include <cfw/namespoof.h>
#include "cfw_icons.h"
#include <applications.h>
#include <desktop/desktop_settings.h>
#include "helpers/passport_settings.h"

#define MENU_ICON_MAX_SIZE 14
#define CFW_SUBGHZ_FREQ_BUFFER_SIZE 6

ARRAY_DEF(CharList, char*)

//For the Dolphin Manifest Switcher Menu.
typedef struct ManifestInfo ManifestInfo;
ARRAY_DEF(ManifestFilesArray, ManifestInfo*, M_POD_OPLIST)

static const struct {
    char* name;
    RgbColor color;
} lcd_colors[] = {
{"Orange", {240, 69, 0}},  {"Coral", {255, 127, 80}}, {"Tomato", {255, 99, 71}},
{"Red", {255, 0, 0}},      {"Crimson", {220, 20, 60}}, {"Maroon", {128, 0, 0}},
{"Gold", {255, 215, 0}},   {"Yellow", {255, 150, 0}},  {"Khaki", {240, 230, 140}},
{"Olive", {128, 128, 0}},  {"Chartreuse", {127, 255, 0}}, {"Lime", {0, 255, 0}},
{"Spring Green", {0, 255, 127}}, {"Aqua", {0, 255, 127}}, {"Medium Sea Green", {60, 179, 113}},
{"Green", {0, 128, 0}},    {"Turquoise", {64, 224, 208}}, {"Cyan", {0, 210, 210}},
{"Sky Blue", {135, 206, 235}}, {"Azure", {0, 127, 255}}, {"Steel Blue", {70, 130, 180}},
{"Teal", {0, 128, 128}},   {"Royal Blue", {65, 105, 225}}, {"Blue", {0, 0, 255}},
{"Navy", {0, 0, 128}},     {"Indigo", {75, 0, 130}},   {"Purple", {96, 0, 255}},
{"Orchid", {218, 112, 214}}, {"Fuchsia", {255, 0, 255}}, {"Thistle", {216, 191, 216}},
{"Lavender", {230, 230, 250}}, {"Pink", {255, 0, 127}},   {"Salmon", {250, 128, 114}},
{"Brown", {165, 42, 42}},   {"Sienna", {160, 82, 45}},  {"Silver", {192, 192, 192}},
{"White", {255, 255, 255}}, {"Gainsboro", {220, 220, 220}}, {"Off", {0, 0, 0}},

};

typedef struct {
    Gui* gui;
    DialogsApp* dialogs;
    NotificationApp* notification;
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    VariableItemList* var_item_list;
    Submenu* submenu;
    TextInput* text_input;
    ByteInput* byte_input;
    Popup* popup;
    DialogEx* dialog_ex;

    DesktopSettings desktop;
    PassportSettings passport;

    CharList_t mainmenu_app_names;
    CharList_t mainmenu_app_paths;
    uint8_t mainmenu_app_index;

    CharList_t gamemenu_app_names;
    CharList_t gamemenu_app_paths;
    uint8_t gamemenu_app_index;

    uint8_t start_point_index;
    uint8_t game_start_point_index;

    bool subghz_use_defaults;
    FrequencyList_t subghz_static_freqs;
    uint8_t subghz_static_index;
    FrequencyList_t subghz_hopper_freqs;
    uint8_t subghz_hopper_index;
    char subghz_freq_buffer[CFW_SUBGHZ_FREQ_BUFFER_SIZE];
    bool subghz_extend;
    bool subghz_bypass;
    RgbColor lcd_color;
    char device_name[FURI_HAL_VERSION_ARRAY_NAME_LENGTH];
    FuriString* version_tag;

    bool save_mainmenu_apps;
    bool save_gamemenu_apps;
    bool save_subghz_frequencies;
    bool save_subghz;
    bool save_name;
    bool save_backlight;
    bool save_settings;
    bool require_reboot;
} CfwApp;

typedef enum {
    CfwAppViewVarItemList,
    CfwAppViewSubmenu,
    CfwAppViewTextInput,
    CfwAppViewByteInput,
    CfwAppViewPopup,
    CfwAppViewDialogEx,
} CfwAppView;

bool cfw_app_apply(CfwApp* app);
