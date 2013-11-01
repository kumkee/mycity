#ifndef CITY_H
#define CITY_H

#include "DynTextLayer.h"
#include "http.h"

#define CITY_KEY_LATITUDE 1
#define CITY_KEY_LONGITUDE 2
#define SERVER_URL "http://pbwcity.duapp.com/"
#define COUNTRY_CODE	1
#define PROV_CODE	2
#define CITY_CODE	3
#define DIST_CODE	4

#define MSG_WAIT "Please Wait..."

void _city_upd(DynTextLayer*, PebbleTickEvent*);
bool _city_upd_cri(PebbleTickEvent*);
void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context);
void handle_failed(int32_t cookie, int http_status, void* context);
void handle_location(float latitude, float longitude, float altitude, float accuracy, void* context);
void handle_reconnect(void* context);
//void request_city();

#endif
