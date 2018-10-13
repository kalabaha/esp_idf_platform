#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_spi_flash.h"

/* ===== LOCAL ============================================================== */

static void _print_chip_info(void)
{
    esp_chip_info_t info;
    esp_chip_info(&info);

    printf("\n--------------------------\n");

    printf("   Cores: %d\n", info.cores);
    printf("      RF: Wifi");
    if (info.features & CHIP_FEATURE_BT) {
        printf("/BT");
    }
    if (info.features & CHIP_FEATURE_BLE) {
        printf("/BLE");
    }
    printf("\n");

    printf("Revision: %d\n", info.revision);

    printf("   Flash: %dMB (%s)\n",
        spi_flash_get_chip_size() / (1024 * 1024),
        info.features & CHIP_FEATURE_EMB_FLASH ? "embedded" : "external");

    printf("--------------------------\n\n");
}

/* ===== APP ENTRY POINT ==================================================== */

void app_main()
{
    _print_chip_info();
    printf("Hello world!\n");

    vTaskDelay(pdMS_TO_TICKS(5000));

    esp_restart();
}

/* -------------------------------------------------------------------------- */
