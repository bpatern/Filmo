// #pragma once
// #ifndef wireless_h
// #define wireless_h

// #include "control.h"
// #include "comm.h"
// #include "filmo.h"
// #include "esp_vfs_semihost.h"
// #include "esp_vfs_fat.h"
// #include "esp_spiffs.h"
// #include "sdmmc_cmd.h"
// #include "nvs_flash.h"
// #include "esp_netif.h"
// #include "esp_event.h"
// #include "esp_log.h"
// #include "mdns.h"
// #include "lwip/apps/netbiosns.h"
// #include "protocol_examples_common.h"
// #include <string.h>
// #include <fcntl.h>
// #include "esp_http_server.h"
// #include "esp_chip_info.h"
// #include "esp_random.h"
// #include "esp_log.h"
// #include "esp_vfs.h"
// #include "cJSON.h"

// #define MDNS_INSTANCE "esp home web server"


// class wireless : public remoteControl {
//     public:
//     typedef struct rest_server_context {
//         char base_path[ESP_VFS_PATH_MAX + 1];
//         char scratch[SCRATCH_BUFSIZE];
//     } rest_server_context_t;

//     enum callbackResponse {
//         success,
//         fail
//     };
//     static const char *TAG = "example";
//     void start_async_server(const char *base_path);
//     callbackResponse projector_status_uri(httpd_req_t *req);
//     callbackResponse direction_handler(httpd_req_t *req);
//     callbackResponse rest_common_get_handler(httpd_req_t *req);
//     wireless();
//     void init();
//     void initialise_mdns(void);
//     void init_fs();
//     void init_wifi();
//     void start_async_server(const char *base_path);
    
//     private:

// }

// #endif
