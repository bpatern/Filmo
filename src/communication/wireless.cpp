// #include "wireless.h"

// #define MDNS_INSTANCE "Filmo Controller Server"
// #define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
// #define SCRATCH_BUFSIZE (10240)

// typedef struct wireless::rest_server_context;
    

// wireless::wireless() {

// }

// void wireless::initialise_mdns(void) {
//     //initialize mDNS
// mdns_init();
// mdns_hostname_set(CONFIG_EXAMPLE_MDNS_HOSTNAME);
// mdns_instance_name_set(MDNS_INSTANCE);

// mdns_txt_item_t serviceTxtData[] = {
//         {"board", "esp32"},
//         {"path", "/"}
//     };

// mdns_service_add("Filmo Controller", "_http", "_tcp", 80, serviceTxtData, sizeof(serviceTxtData) / sizeof(serviceTxtData[0]));
// }

// void wireless::init_fs() {
//     esp_vfs_spiffs_conf_t conf = {
//         .base_path = CONFIG_EXAMPLE_WEB_MOUNT_POINT,
//         .partition_label = NULL,
//         .max_files = 5,
//         .format_if_mount_failed = false
//     };
//     ret = esp_vfs_spiffs_register(&conf);

//     if (ret != ESP_OK) {
//         if (ret == ESP_FAIL) {
//             ESP_LOGE(TAG, "Failed to mount or format filesystem");
//         } else if (ret == ESP_ERR_NOT_FOUND) {
//             ESP_LOGE(TAG, "Failed to find SPIFFS partition");
//         } else {
//             ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
//         }
//         return ESP_FAIL;
//     }

//     size_t total = 0, used = 0;
//     ret = esp_spiffs_info(NULL, &total, &used);
//     ret = esp_spiffs_info(NULL, &total, &used);
//     if (ret != ESP_OK) {
//         ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
//     } else {
//         ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
//     }
//     return ESP_OK;
// }

// void wireless::init() {
//     nvs_flash_init();
//     esp_netif_init();
//     esp_event_loop_create_default();
//     initialise_mdns();
//     netbiosns_init();
//     netbiosns_set_name("filmo-controller");
//     init_wifi();
//     init_fs();
//     start_rest_server(CONFIG_EXAMPLE_WEB_MOUNT_POINT);
// }

// void wireless::init_wifi() {
//     s_wifi_event_group = xEventGroupCreate();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     esp_wifi_init(&cfg)

//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
//                                                         ESP_EVENT_ANY_ID,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_any_id));
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
//                                                         IP_EVENT_STA_GOT_IP,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_got_ip));

//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = EXAMPLE_ESP_WIFI_SSID,
//             .password = EXAMPLE_ESP_WIFI_PASS,
//             /* Authmode threshold resets to WPA2 as default if password matches WPA2 standards (password len => 8).
//              * If you want to connect the device to deprecated WEP/WPA networks, Please set the threshold value
//              * to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format matching to
//              * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
//              */
//             .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
//             .sae_pwe_h2e = ESP_WIFI_SAE_MODE,
//             .sae_h2e_identifier = EXAMPLE_H2E_IDENTIFIER,
//             },
//     };

//     esp_wifi_set_mode(WIFI_MODE_STA);
//     esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
//     esp_wifi_start();

//     EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
//             WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
//             pdFALSE,
//             pdFALSE,
//             portMAX_DELAY);

//             if (bits & WIFI_CONNECTED_BIT) {
//         ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
//                  EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//     } else if (bits & WIFI_FAIL_BIT) {
//         ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
//                  EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//     } else {
//         ESP_LOGE(TAG, "UNEXPECTED EVENT");
//     }
// }

// void wireless::start_async_server(const char *base_path) {
//         rest_server_context_t *rest_context = calloc(1, sizeof(rest_server_context_t));
//     strlcpy(rest_context->base_path, base_path, sizeof(rest_context->base_path));
//     httpd_handle_t server = NULL;
//     httpd_config_t config = HTTPD_DEFAULT_CONFIG();
//     config.uri_match_fn = httpd_uri_match_wildcard;

//     if (httpd_start(&server, &config) == ESP_OK) {
//         ESP_LOGI(TAG, "Registering URI handlers");
//         register_server_handlers(server);
//         return server;
//     }

//     httpd_uri_t projector_status_uri = {
//         .uri = "/api/projectorstat",
//         .method = HTTP_GET,
//         .handler = projector_status_get_handler,
//         .user_ctx = rest_context
//     };
//     httpd_uri_t getDir = {
//         .uri = "/api/dir",
//         .method = HTTP_POST,
//         .handler = direction_handler,
//         .user_ctx = rest_context
//     };

//     free(rest_context);


// }

//  callbackResponse wireless::direction_handler(httpd_req_t *req) {
// int total_len = req->content_len;
// int cur_len = 0;
// char *buf = ((rest_server_context_t *)(req->user_ctx))->scratch;
// int received = 0;
// while (cur_len < total_len) {
//         received = httpd_req_recv(req, buf + cur_len, total_len);
//         if (received <= 0) {
//             /* Respond with 500 Internal Server Error */
//             httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
//             return failure;
//         }
//         cur_len += received;
//     }
//     buf[total_len] = '\0';
//     cJSON *root = cJSON_Parse(buf);
//     httpd_resp_set_type(req, "application/json");
//     dirTemp = cJSON_GetObjectItem(root, "dir") -> valueint;
//     ESP_LOGI(REST_TAG, "Blinker control: dir = %d", dirTemp);
//     cJSON_Delete(root);
//     httpd_resp_sendstr(req, "Post control value successfully");
//     return success;
// }
//  callbackResponse wireless::projector_status_uri(httpd_req_t *req) {

//     return success;
// }

// callbackResponse wireless::rest_common_get_handler(httpd_req_t *req)
// {char filepath[FILE_PATH_MAX];

//     rest_server_context_t *rest_context = (rest_server_context_t *)req->user_ctx;
//     strlcpy(filepath, rest_context->base_path, sizeof(filepath));
//     if (req->uri[strlen(req->uri) - 1] == '/') {
//         strlcat(filepath, "/index.html", sizeof(filepath));
//     } else {
//         strlcat(filepath, req->uri, sizeof(filepath));
//     }
//     int fd = open(filepath, O_RDONLY, 0);
//     if (fd == -1) {
//         ESP_LOGE(REST_TAG, "Failed to open file : %s", filepath);
//         /* Respond with 500 Internal Server Error */
//         httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file");
//         return failure;
//     }

//     set_content_type_from_file(req, filepath);

//     char *chunk = rest_context->scratch;
//     ssize_t read_bytes;
//     do {
//         /* Read file in chunks into the scratch buffer */
//         read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);
//         if (read_bytes == -1) {
//             ESP_LOGE(REST_TAG, "Failed to read file : %s", filepath);
//         } else if (read_bytes > 0) {
//             /* Send the buffer contents as HTTP response chunk */
//             if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK) {
//                 close(fd);
//                 ESP_LOGE(REST_TAG, "File sending failed!");
//                 /* Abort sending file */
//                 httpd_resp_sendstr_chunk(req, NULL);
//                 /* Respond with 500 Internal Server Error */
//                 httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file");
//                 return failure;
//             }
//         }
//     } while (read_bytes > 0);
//     /* Close file after sending complete */
//     close(fd);
//     ESP_LOGI(REST_TAG, "File sending complete");
//     /* Respond with an empty chunk to signal HTTP response completion */
//     httpd_resp_send_chunk(req, NULL, 0);
//     return success;
// }