/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/err.h"
#include "lwip/sys.h"


#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include <esp_http_server.h>
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_check.h"
#include "driver/gpio.h"

#define Lock1 GPIO_NUM_4
#define Lock2 GPIO_NUM_2

static const char *TAG = "Webserver";


/*********************** WEBSERVER CODE BIGINS ************************/



/*LOCK 1 CONFIGURATIONS*/


static esp_err_t LOCK1LOBBY_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK1 LOBBY OPENED");
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
}

static const httpd_uri_t lock1lobby = {
    .uri       = "/lock1lobby",
    .method    = HTTP_GET,
    .handler   = LOCK1LOBBY_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\	
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #000000;} /* Black */\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<h2>LOCKER1</h2>\
<p>Click \"UNLOCK\" to unlock the door</p>\
\
<button class=\"button button1\" onclick= \"window.location.href='/lock1'\">Unlock</button>\
<button class=\"button button2\" onclick= \"window.location.href='/'\">Home</button>\
\
</body>\
</html>"
};


static esp_err_t LOCK1_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK1 UNLOCKED");
	gpio_set_level(Lock1, 0);
	vTaskDelay(100);
	gpio_set_level(Lock1, 1);
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
}

static const httpd_uri_t lock1 = {
    .uri       = "/lock1",
    .method    = HTTP_GET,
    .handler   = LOCK1_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\	
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #000000;} /* Black */\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<h2>LOCKER1</h2>\
<p>Click \"UNLOCK\" to unlock the door</p>\
\
<button class=\"button button1\" onclick= \"window.location.href='/lock1'\">Unlock</button>\
<button class=\"button button2\" onclick= \"window.location.href='/'\">Home</button>\
\
</body>\
</html>"
};

/*LOCK 1 CONFIGURATIONS ENDS*/


/*LOCK 2 CONFIGURATIONS*/


static esp_err_t LOCK2LOBBY_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK2 LOBBY OPENED");
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
	
}

static const httpd_uri_t lock2lobby = {
    .uri       = "/lock2lobby",
    .method    = HTTP_GET,
    .handler   = LOCK2LOBBY_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\	
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #008CBA;} /* Blue */\
.button2 {background-color: #000000;} /* Black */\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<h2>LOCKER2</h2>\
<p>Click \"UNLOCK\" to unlock the door</p>\
\
<button class=\"button button1\" onclick= \"window.location.href='/lock2'\">Unlock</button>\
<button class=\"button button2\" onclick= \"window.location.href='/'\">Home</button>\
\
</body>\
</html>"
};


static esp_err_t LOCK2_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK2 UNLOCKED");
	gpio_set_level(Lock2, 0);
	vTaskDelay(100);
	gpio_set_level(Lock2, 1);
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
	
}

static const httpd_uri_t lock2 = {
    .uri       = "/lock2",
    .method    = HTTP_GET,
    .handler   = LOCK2_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\	
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #008CBA;} /* Blue */\
.button2 {background-color: #000000;} /* Black */\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<h2>LOCKER2</h2>\
<p>Click \"UNLOCK\" to unlock the door</p>\
\
<button class=\"button button1\" onclick= \"window.location.href='/lock2'\">Unlock</button>\
<button class=\"button button2\" onclick= \"window.location.href='/'\">Home</button>\
\
</body>\
</html>"
};

/*LOCK 2 CONFIGURATIONS ENDS*/


/*ADMIN CONFIGURATIONS*/

static esp_err_t LOCK1ADMIN_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK1 UNLOCKED BY ADMIN");
	gpio_set_level(Lock1, 0);
	vTaskDelay(100);
	gpio_set_level(Lock1, 1);
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
}


static const httpd_uri_t lock1admin = {
    .uri       = "/lock1admin",
    .method    = HTTP_GET,
    .handler   = LOCK1ADMIN_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #008CBA;} /* Blue */\
.button3 {background-color: #000000;} /* Black */\
\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<p>Please select the Locker you want to access</p>\
<button class=\"button button1\" onclick= \"window.location.href='/lock1admin'\">Locker 1</button>\
<button class=\"button button2\" onclick= \"window.location.href='/lock2admin'\">Locker 2</button>\
<button class=\"button button3\" onclick= \"window.location.href='/'\">Home</button>\
</body>\
</html>"
};


static esp_err_t LOCK2ADMIN_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "LOCK 2UNLOCKED BY ADMIN");
	gpio_set_level(Lock2, 0);
	vTaskDelay(100);
	gpio_set_level(Lock2, 1);
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
}


static const httpd_uri_t lock2admin = {
    .uri       = "/lock2admin",
    .method    = HTTP_GET,
    .handler   = LOCK2ADMIN_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #008CBA;} /* Blue */\
.button3 {background-color: #000000;} /* Black */\
\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<p>Please select the Locker you want to access</p>\
<button class=\"button button1\" onclick= \"window.location.href='/lock1admin'\">Locker 1</button>\
<button class=\"button button2\" onclick= \"window.location.href='/lock2admin'\">Locker 2</button>\
<button class=\"button button3\" onclick= \"window.location.href='/'\">Home</button>\
</body>\
</html>"
};


static esp_err_t ADMIN_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "Admin page opened");
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
	
}

static const httpd_uri_t admin = {
    .uri       = "/admin",
    .method    = HTTP_GET,
    .handler   = ADMIN_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #008CBA;} /* Blue */\
.button3 {background-color: #000000;} /* Black */\
\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<p>Please select the Locker you want to access</p>\
<button class=\"button button1\" onclick= \"window.location.href='/lock1admin'\">Locker 1</button>\
<button class=\"button button2\" onclick= \"window.location.href='/lock2admin'\">Locker 2</button>\
<button class=\"button button3\" onclick= \"window.location.href='/'\">Home</button>\
</body>\
</html>"
};

/*ADMIN CONFIGURATIONS ENDS*/

/*ROOT PAGE CONFIGURATIONS*/
static esp_err_t ROOT_handler(httpd_req_t *req)
{
    esp_err_t error;
	ESP_LOGI(TAG, "Root page opened");
	const char *response = (const char *) req->user_ctx;
	error = httpd_resp_send(req, response, strlen(response));
	if (error != ESP_OK)
	{
		ESP_LOGI(TAG, "Error %d while sending Response", error);
	}
	else ESP_LOGI(TAG, "Response sent Successfully");
	return error;
	
}

static const httpd_uri_t root = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = ROOT_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "<!DOCTYPE html>\
<html>\
<head>\
<style>\
.button {\
  border: none;\
  color: white;\
  padding: 15px 32px;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  font-size: 16px;\
  margin: 4px 2px;\
  cursor: pointer;\
}\
\
.button1 {background-color: #04AA6D;} /* Green */\
.button2 {background-color: #008CBA;} /* Blue */\
.button3 {background-color: #000000;} /* Black */\
\
</style>\
</head>\
<body>\
\
<h1>SBU SmartLock Network</h1>\
<p>Please select the Locker you want to access</p>\
<button class=\"button button1\" onclick= \"window.location.href='/lock1lobby'\">Locker 1</button>\
<button class=\"button button2\" onclick= \"window.location.href='/lock2lobby'\">Locker 2</button>\
<button class=\"button button3\" onclick= \"window.location.href='/admin'\">ADMIN</button>\
</body>\
</html>"
};


/*ROOT PAGE CONFIGURATIONS ENDS*/


esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
     /* For any other URI send 404 and close socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}


static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
#if CONFIG_IDF_TARGET_LINUX
    // server will be started.
    config.server_port = 8001;
#endif // !CONFIG_IDF_TARGET_LINUX
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &lock1lobby);
        httpd_register_uri_handler(server, &lock1);
        httpd_register_uri_handler(server, &lock2lobby);
        httpd_register_uri_handler(server, &lock2);
        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &admin);
        httpd_register_uri_handler(server, &lock1admin);
        httpd_register_uri_handler(server, &lock2admin);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

static esp_err_t stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    return httpd_stop(server);
}

static void disconnect_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        if (stop_webserver(*server) == ESP_OK) {
            *server = NULL;
        } else {
            ESP_LOGE(TAG, "Failed to stop http server");
        }
    }
}

static void connect_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}
/********************WEB SERVER CODE ENDS*********************/

static void configure_locks (void)
{
	gpio_reset_pin (Lock1);
	
	gpio_set_direction (Lock1, GPIO_MODE_OUTPUT);
	
	gpio_set_level (Lock1, 1);
	
	gpio_reset_pin (Lock2);
	
	gpio_set_direction (Lock2, GPIO_MODE_OUTPUT);
	
	gpio_set_level (Lock2, 1);
	
	
}


/* The examples use WiFi configuration that you can set via project configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_WIFI_CHANNEL   CONFIG_ESP_WIFI_CHANNEL
#define EXAMPLE_MAX_STA_CONN       CONFIG_ESP_MAX_STA_CONN


static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d, reason=%d",
                 MAC2STR(event->mac), event->aid, event->reason);
    }
}

void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
#ifdef CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT
            .authmode = WIFI_AUTH_WPA3_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
#else /* CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT */
            .authmode = WIFI_AUTH_WPA2_PSK,
#endif
            .pmf_cfg = {
                    .required = true,
            },
        },
    };
    if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
}

void app_main(void)
{
	
	configure_locks();
	
	static httpd_handle_t server = NULL;
	
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
    
    ESP_ERROR_CHECK(esp_netif_init());
    
        ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
}
