/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

// uwu

#include <assert.h>
#include <string.h>

#include "bsp/bsp.h"
#include "hal/hal_gpio.h"
#include "os/os.h"
#include "sysinit/sysinit.h"
#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif
#include <pinetime_lvgl_mynewt/pinetime_lvgl_mynewt.h>

static volatile int g_task1_loops;

extern void pinetime_lvgl_mynewt_init();
extern void pinetime_lvgl_mynewt_test();
extern void pinetime_lvgl_mynewt_render();
extern void init_backlight(void);

/**
 * main
 *
 * The main task for the project. This function initializes packages,
 * and then blinks the BSP LED in a loop.
 *
 * @return int NOTE: this function should never return!
 */
int main(int argc, char **argv) {
  int rc;

#ifdef ARCH_sim
  mcu_sim_parse_args(argc, argv);
#endif

  sysinit();

  init_backlight();

  lv_obj_t *btn =
      lv_btn_create(lv_scr_act(), NULL); //  Add a button the current screen
  lv_obj_t *label = lv_label_create(btn, NULL); //  Add a label to the button
  lv_label_set_text(label, "Mynewt LVGL");      //  Set the label text

  while (1) {
    //  Must tick at least 100 milliseconds to force LVGL to update display
    lv_tick_inc(100);
    //  LVGL will flush our display driver
    lv_task_handler();

    os_time_delay(OS_TICKS_PER_SEC / 2);
  }
  assert(0);

  return rc;
}
