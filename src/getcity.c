#include "getcity.h"
//#include "city_zh.h"

#define LOC_MAG	10000000
#define UPD_FREQ 60	//city update frequency in minute

extern DynTextLayer city_layer;

static int lat, lng;

extern int32_t CITY_HTTP_COOKIE;

static bool located = false;

void request_city()
{
   if(!located) http_location_request();

   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, CITY_HTTP_COOKIE, &body);
   //http_out_get(SERVER_URL, CITY_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
	//DTL_printf(&info_layer, "%s  ", error_msg(result));
	return;
   }

   dict_write_int32(body, CITY_KEY_LATITUDE, lat);
   dict_write_int32(body, CITY_KEY_LONGITUDE, lng);
   // Send it.
   result = http_out_send();
   if(result != HTTP_OK) {
	//DTL_printf(&info_layer, "%s  ", error_msg(result));
	return;
   }
}


void _city_upd(DynTextLayer* self, PebbleTickEvent* evt)
{
   if(self->is_first_update) DTL_printf(self, "%s ", MSG_WAIT);

   located = false;
   request_city();
}


bool _city_upd_cri(PebbleTickEvent* evt)
{
   static int init_min;
   static bool firstcall = true;
   if(firstcall){
	init_min = evt->tick_time->tm_min;
	firstcall = false;
   }

   if(evt->units_changed & MINUTE_UNIT && evt->tick_time->tm_min == init_min)
	return true;
   else
	return false;

}


void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context)
{

   if(cookie != CITY_HTTP_COOKIE) return;

   static char* city_str;//, country_str, prov_str, dist_str;
   static char* country_str;
   static char* prov_str;
   static char* dist_str;

   Tuple* country_str_tuple = dict_find(received, COUNTRY_CODE);
   if(country_str_tuple) {
   	country_str = country_str_tuple->value->cstring;
   }

   Tuple* prov_str_tuple = dict_find(received, PROV_CODE);
   if(prov_str_tuple) {
   	prov_str = prov_str_tuple->value->cstring;
   }

   Tuple* dist_str_tuple = dict_find(received, DIST_CODE);
   if(dist_str_tuple) {
   	dist_str = dist_str_tuple->value->cstring;
   }

   Tuple* city_str_tuple = dict_find(received, CITY_CODE);
   if(city_str_tuple) {
   	city_str = city_str_tuple->value->cstring;
   }

   DTL_printf(&city_layer, "%s\n%s\n%s\n%s", dist_str, city_str, prov_str, country_str);

}


void handle_failed(int32_t cookie, int http_status, void* evt)
{
   DTL_printf(&city_layer, "Failed!");
}


void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   lat = latitude * LOC_MAG;
   lng = longitude * LOC_MAG;
   located = true;
   request_city();
}


void handle_reconnect(void* context)
{
   request_city();
}



