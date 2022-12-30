/* Copyright (c) Kuba Szczodrzyński 2022-06-04. */

#include "LibreTuyaCompat.h"

#if LT_HAS_FREERTOS
BaseType_t xTaskCreateUniversal(
	TaskFunction_t pxTaskCode,
	const char *const pcName,
	const uint32_t usStackDepth,
	void *const pvParameters,
	UBaseType_t uxPriority,
	TaskHandle_t *const pxCreatedTask,
	const BaseType_t xCoreID
) {
	// #ifndef CONFIG_FREERTOS_UNICORE
	// 	if (xCoreID >= 0 && xCoreID < 2) {
	// 		return xTaskCreatePinnedToCore(
	// 			pxTaskCode,
	// 			pcName,
	// 			usStackDepth,
	// 			pvParameters,
	// 			uxPriority,
	// 			pxCreatedTask,
	// 			xCoreID
	// 		);
	// 	} else {
	// #endif
	return xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
	// #ifndef CONFIG_FREERTOS_UNICORE
	// 	}
	// #endif
}
#endif
