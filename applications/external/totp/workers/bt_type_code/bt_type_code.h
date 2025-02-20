#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <furi/core/mutex.h>
#include "../../types/automation_kb_layout.h"

#define TOTP_BT_KEYS_STORAGE_PATH EXT_PATH("apps_data/authenticator/.bt_hid.keys")

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t TotpBtTypeCodeWorkerEvent;

typedef struct TotpBtTypeCodeWorkerContext TotpBtTypeCodeWorkerContext;

/**
 * @brief Bluetooth token input automation worker events
 */
enum TotpBtTypeCodeWorkerEvents {
    /**
     * @brief Reserved, should not be used anywhere
     */
    TotpBtTypeCodeWorkerEventReserved = 0b00,

    /**
     * @brief Stop worker
     */
    TotpBtTypeCodeWorkerEventStop = 0b01,

    /**
     * @brief Trigger token input automation
     */
    TotpBtTypeCodeWorkerEventType = 0b10
};

/**
 * @brief Initializes bluetooth token input automation worker
 * @param mac_xor value to be used to XOR BT MAC address to make it unique
 * @param profile_index profile index to be used
 * @return worker context
 */
TotpBtTypeCodeWorkerContext*
    totp_bt_type_code_worker_init(uint16_t mac_xor, uint8_t profile_index);

/**
 * @brief Disposes bluetooth token input automation worker and releases all the allocated resources
 * @param context worker context
 */
void totp_bt_type_code_worker_free(TotpBtTypeCodeWorkerContext* context);

/**
 * @brief Starts bluetooth token input automation worker
 * @param context worker context
 * @param code_buffer code buffer to be used to automate
 * @param code_buffer_size code buffer size
 * @param code_buffer_sync code buffer synchronization primitive
 * @param keyboard_layout keyboard layout to be used
 * @param initial_delay initial delay before starting automation
 */
void totp_bt_type_code_worker_start(
    TotpBtTypeCodeWorkerContext* context,
    char* code_buffer,
    uint8_t code_buffer_size,
    FuriMutex* code_buffer_sync,
    AutomationKeyboardLayout keyboard_layout,
    uint16_t initial_delay);

/**
 * @brief Stops bluetooth token input automation worker
 * @param context worker context
 */
void totp_bt_type_code_worker_stop(TotpBtTypeCodeWorkerContext* context);

/**
 * @brief Notifies bluetooth token input automation worker with a given event
 * @param context worker context
 * @param event event to notify worker with
 * @param flags event flags
 */
void totp_bt_type_code_worker_notify(
    TotpBtTypeCodeWorkerContext* context,
    TotpBtTypeCodeWorkerEvent event,
    uint8_t flags);

/**
 * @brief Gets information whether Bluetooth is advertising now or not
 * @param context worker context
 * @return \c true if Bluetooth is advertising now; \c false otherwise
 */
bool totp_bt_type_code_worker_is_advertising(const TotpBtTypeCodeWorkerContext* context);

#ifdef __cplusplus
}
#endif
