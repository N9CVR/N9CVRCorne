# SPDX-License-Identifier: MIT

if(CONFIG_SHIELD_N9CVR_OLED_UI_CW OR
   CONFIG_SHIELD_N9CVR_OLED_UI_CCW OR
   CONFIG_SHIELD_N9CVR_OLED_UI_LANDSCAPE)
  target_sources(app PRIVATE custom_status_screen.c)
endif()
