#ifndef LVGL_UI_H_INCLUDED
#define LVGL_UI_H_INCLUDED

#include "lvgl.h"
#include "TFT_eSPI.h"
#include <Ticker.h>

#define LVGL_TICK_PERIOD 20

void build_ui();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void logoAnimTask(lv_task_t * t_logo_anim);

TFT_eSPI tft = TFT_eSPI();
Ticker tick;

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
static lv_style_t menuMainStyle;

LV_IMG_DECLARE(logo1);
LV_IMG_DECLARE(logo2);
LV_IMG_DECLARE(logo3);
LV_IMG_DECLARE(logo4);
LV_IMG_DECLARE(logo5);
LV_IMG_DECLARE(logo6);
LV_IMG_DECLARE(logo7);

lv_img_dsc_t const * logoImages[] = {
    &logo1,
    &logo2,
    &logo3,
    &logo4,
    &logo5,
    &logo6,
    &logo7,
    NULL
};
static uint8_t logoImagesIndex = 0;

lv_task_t * t_logo_anim;

lv_obj_t * menu_main;
lv_obj_t * logo_icon_obj;


static void lv_tick_handler(void)
{
  lv_tick_inc(LVGL_TICK_PERIOD);
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void build_ui()
{
  lv_init();

  tft.init();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 240;
  disp_drv.ver_res = 135;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  tft.setSwapBytes(true);

  menu_main = lv_obj_create(NULL, NULL);

  lv_style_init(&menuMainStyle);
  lv_style_set_radius(&menuMainStyle, LV_STATE_DEFAULT, 5);
  lv_style_set_bg_color(&menuMainStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);

  lv_obj_add_style(menu_main, LV_OBJ_PART_MAIN, &menuMainStyle);

  //------------------- LOGO IMAGES--------------------------
  logo_icon_obj = lv_img_create(menu_main, NULL);
  lv_obj_align(logo_icon_obj, NULL, LV_ALIGN_IN_LEFT_MID, 25, -5);
  lv_img_set_src(logo_icon_obj, &logo1);

  lv_obj_set_hidden(logo_icon_obj, true);

  //---------------------------------------------------------

  lv_scr_load(menu_main);

  tick.attach_ms(LVGL_TICK_PERIOD, lv_tick_handler);
}

#endif