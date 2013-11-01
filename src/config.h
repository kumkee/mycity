#ifndef GEO_H
#define GEO_H

  #define WHITE_BACKGROUND	false

  #define DEBUG	0

  #define WHITE_ON_BLACK	!WHITE_BACKGROUND

  #define TXTBUFFERSIZE	128

  #define TOT_LENGTH	144
  #define TOT_HEIGHT	168
  #define LEFT_MARGIN	7
  #define TOP_MARGIN	LEFT_MARGIN

  #define city_POS_X	LEFT_MARGIN
  #define city_POS_Y	TOP_MARGIN
  #define city_LENGTH	TOT_LENGTH - LEFT_MARGIN
  #define city_HEIGHT	TOT_HEIGHT*3/4 - TOP_MARGIN
  #define city_GRECT	GRect(city_POS_X, city_POS_Y, city_LENGTH, city_HEIGHT)

  #define city_FONT	fonts_get_system_font(FONT_KEY_GOTHIC_28)

  #if WHITE_ON_BLACK
    #define BACKGROUNDCOLOR	GColorBlack
    #define CONTENTCOLOR	GColorWhite
  #else
    #define BACKGROUNDCOLOR	GColorWhite
    #define CONTENTCOLOR	GColorBlack
  #endif

#endif
