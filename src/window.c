#include "window.h"
#include <pebble.h>

static Animation *s_animation_pusheen;
static GBitmap *s_bitmap_pusheen_1;
static GBitmap *s_bitmap_pusheen_2;
static GBitmap *s_bitmap_pusheen_3;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static TextLayer *s_textlayer_time;
static BitmapLayer *s_bitmaplayer_pusheen;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(4, 17, 135, 42));
  text_layer_set_text(s_textlayer_time, "9:41 AM");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_bitmaplayer_pusheen
  s_bitmaplayer_pusheen = bitmap_layer_create(GRect(0, 68, 144, 100));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_pusheen);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_time);
  bitmap_layer_destroy(s_bitmaplayer_pusheen);
}
// END AUTO-GENERATED UI CODE

static void initialize_ui(void) {
  initialise_ui();
    
  s_bitmap_pusheen_1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PUSHEEN_1);
  s_bitmap_pusheen_2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PUSHEEN_2);
  s_bitmap_pusheen_3 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PUSHEEN_3);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  
  animation_destroy(s_animation_pusheen);
  gbitmap_destroy(s_bitmap_pusheen_1);
  gbitmap_destroy(s_bitmap_pusheen_2);
  gbitmap_destroy(s_bitmap_pusheen_3);
}

static char time_buffer[16];
static void update_time_buffer(void) {
  clock_copy_time_string(time_buffer, sizeof(time_buffer)/sizeof(*time_buffer));
  text_layer_set_text(s_textlayer_time, time_buffer);  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time_buffer();
}

static void animation_update(Animation *animation, const uint32_t time_normalized) {
  GBitmap *new_bitmap = NULL;
  switch (time_ms(NULL, NULL) / 250) {
    case 0:
    case 2:
      new_bitmap = s_bitmap_pusheen_1;
      break;
    case 1:
      new_bitmap = s_bitmap_pusheen_2;
      break;
    case 3:
      new_bitmap = s_bitmap_pusheen_3;
      break;
  }
  
  bitmap_layer_set_bitmap(s_bitmaplayer_pusheen, new_bitmap);
}

void show_window(void) {
  initialize_ui();
  update_time_buffer();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  static const AnimationImplementation imp = {
    .update = animation_update,
  };
  
  s_animation_pusheen = animation_create();
  animation_set_curve(s_animation_pusheen, AnimationCurveLinear);
  animation_set_duration(s_animation_pusheen, ANIMATION_DURATION_INFINITE);
  animation_set_implementation(s_animation_pusheen, &imp);
  animation_schedule(s_animation_pusheen);

  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window(void) {
  window_stack_remove(s_window, true);
}
