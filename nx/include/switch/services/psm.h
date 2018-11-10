/**
 * @file psm.h
 * @brief PSM service IPC wrapper.
 * @author XorTroll, endrift, and yellows8
 * @copyright libnx Authors
 */
#pragma once
#include "../types.h"

typedef enum {
    ChargerType_None = 0,    ///< No charger
    ChargerType_Charger = 1, ///< Official charger or dock
    ChargerType_Usb = 2      ///< Other USB-C chargers
} ChargerType;

typedef enum {
    PsmBatteryVoltageState_NeedsShutdown = 0,      ///< Power state should transition to shutdown
    PsmBatteryVoltageState_NeedsSleep = 1,         ///< Power state should transition to sleep
    PsmBatteryVoltageState_NoPerformanceBoost = 2, ///< Performance boost modes cannot be entered
    PsmBatteryVoltageState_Normal = 3,             ///< Everything is normal
} PsmBatteryVoltageState;

Result psmInitialize(void);
void psmExit(void);

Result psmGetBatteryChargePercentage(u32 *out);
Result psmGetChargerType(ChargerType *out);
Result psmGetBatteryVoltageState(PsmBatteryVoltageState *out);

/**
 * @brief Wrapper func which handles event setup.
 * @note Uses the actual BindStateChangeEvent cmd internally.
 * @note The event is not signalled on BatteryChargePercentage changes.
 * @param[in] ChargerType Passed to SetChargerTypeChangeEventEnabled.
 * @param[in] PowerSupply Passed to SetPowerSupplyChangeEventEnabled.
 * @param[in] BatteryVoltage Passed to SetBatteryVoltageStateChangeEventEnabled.
 */
Result psmBindStateChangeEvent(bool ChargerType, bool PowerSupply, bool BatteryVoltage);

/// Wait on the Event setup by psmBindStateChangeEvent.
Result psmWaitStateChangeEvent(u64 timeout);

/// Cleanup version of psmBindStateChangeEvent. Called automatically by \ref psmExit and \ref psmBindStateChangeEvent, if already initialized.
Result psmUnbindStateChangeEvent(void);
