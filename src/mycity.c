#include "headers.h"

#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0x4E, 0x99, 0xAD }
PBL_APP_INFO(MY_UUID,
             "mycity", "kumkee",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

DynTextLayer city_layer;

int32_t CITY_HTTP_COOKIE;

void handle_init(AppContextRef ctx) {

  window_init(&window, "mycity");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, BACKGROUNDCOLOR);

  DTL_init(&city_layer, &window.layer, city_GRECT, city_FONT, _city_upd, _city_upd_cri);

  srand(time(NULL));
  int32_t HTTP_APP_ID = RAND_MAX/2 - rand(); 
  CITY_HTTP_COOKIE = RAND_MAX/2 - rand();
  
  http_set_app_id(HTTP_APP_ID);
  HTTPCallbacks httpcallbacks = {
    .success = handle_success,
    .failure = handle_failed,
    .location = handle_location,
    .reconnect = handle_reconnect
  };
  http_register_callbacks(httpcallbacks, ctx);
}


void handle_tick(AppContextRef ctx, PebbleTickEvent *evt)
{
   city_layer.update(&city_layer, evt);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    },
    .messaging_info = {
      .buffer_sizes = {
          .inbound = 124,
          .outbound = 256
      }
    }
  };
  app_event_loop(params, &handlers);
}
