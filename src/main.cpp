#include <Arduino.h>
#include "lvgl.h"
#include "TFT_eSPI.h"
#include <Ticker.h>

#include "lvgl_ui/lvgl_ui.h"

bool startCheckAnimation = false;

void screenTransitionTask(lv_task_t * task);
void logoAnimTask(lv_task_t * t_logo_anim);

static uint32_t clock_data = 0;

void setup() {
  Serial.begin(115200);
  build_ui();
  t_logo_anim = lv_task_create(logoAnimTask, 100, LV_TASK_PRIO_MID, &clock_data);

  Serial.println("Serial OK");
}

void loop() {
  lv_task_handler(); /* let the GUI do its work */
  delay(5);
}

void logoAnimTask(lv_task_t * t_logo_anim)
{
  lv_obj_set_hidden(logo_icon_obj, false);
  /*Set the current element of the array*/
  lv_img_set_src(logo_icon_obj, logoImages[logoImagesIndex]);
  /*Go to the next image*/
  logoImagesIndex++;
  if(logoImages[logoImagesIndex] == NULL)
  {
    //lv_obj_set_hidden(logo_icon_obj, true);
    logoImagesIndex = 0;
    lv_task_set_prio(t_logo_anim, LV_TASK_PRIO_OFF);
    startCheckAnimation = false;
  }
}