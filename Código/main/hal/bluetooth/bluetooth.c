/*
 * bluetooth.c
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#include "bluetooth.h"
#include <string.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"

/*****************************************************************************
*							Global Variables
******************************************************************************/
void(*gBluetooth_cb)( char* , int8_t ) = NULL;

/*****************************************************************************
*							Private Functions
******************************************************************************/
static bool get_name_from_eir(uint8_t *eir, uint8_t *name, uint8_t *name_len) 
{
    if (!eir){ return false; }
    
    uint8_t len;
    uint8_t *n = esp_bt_gap_resolve_eir_data(eir, ESP_BT_EIR_TYPE_CMPL_LOCAL_NAME, &len);
    
    if(!n)
    {
		n = esp_bt_gap_resolve_eir_data(eir, ESP_BT_EIR_TYPE_SHORT_LOCAL_NAME, &len);
	} 
	
    if (n) 
    {
		len = len > ESP_BT_GAP_MAX_BDNAME_LEN ? ESP_BT_GAP_MAX_BDNAME_LEN : len;
        memcpy(name, n, len);
        name[len] = '\0';
        if (name_len)
        {
			*name_len = len;
		} 
        return true;
    }
    return false;
}

/* GAP callback for device discovery */
static void bt_gap_cb( esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param ) 
{
    switch (event) 
    {
	    case ESP_BT_GAP_DISC_RES_EVT: 
	    {
	        int8_t rssi = -127;
	        uint8_t name_len = 0;
	        uint8_t name[ESP_BT_GAP_MAX_BDNAME_LEN + 1] = {0};
	
	        for( int i = 0; i < param->disc_res.num_prop; i++ ) 
	        {
	            esp_bt_gap_dev_prop_t *p = param->disc_res.prop + i;
	            switch( p->type )
	            {
					case ESP_BT_GAP_DEV_PROP_RSSI:
						rssi = *(int8_t *)p->val;
					break;
					case ESP_BT_GAP_DEV_PROP_BDNAME:
						 name_len = (p->len > ESP_BT_GAP_MAX_BDNAME_LEN) ? ESP_BT_GAP_MAX_BDNAME_LEN : p->len;
		                memcpy(name, p->val, name_len);
		                name[name_len] = '\0';
					break;
					case ESP_BT_GAP_DEV_PROP_EIR:
						get_name_from_eir(p->val, name, &name_len);
					break;
					default:
					break;
				}
	        }
	        gBluetooth_cb( (char*)name , rssi );
	    break;
	    }
	    case ESP_BT_GAP_DISC_STATE_CHANGED_EVT:
	        if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) 
	        {
	            esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
	        } 
	        else 
	        {
	        }
	    break;
	    default:
	    break;
    }
}

/*****************************************************************************
*							Public Functions
******************************************************************************/
void BLUETOOTH_Init( const char* device_name )
{
    nvs_flash_init();
    esp_bt_controller_mem_release(ESP_BT_MODE_BLE);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    esp_bluedroid_init();
    esp_bluedroid_enable();

    esp_bt_gap_register_callback(bt_gap_cb);
    esp_bt_gap_set_device_name(device_name);
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);

    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
}

void BLUETOOTH_SetCallback( void(*cb)( char * , int8_t ) )
{
	gBluetooth_cb = cb;
}