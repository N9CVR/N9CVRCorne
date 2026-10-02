/*
 * N9CVR split OLED status screen
 * SPDX-License-Identifier: MIT
 *
 * Target: pinned ZMK v0.3 (LVGL 8) and newer, 128x32 SSD1306 displays mounted vertically.
 * Left/central: output, battery, layer, WPM.
 * Right/peripheral: N9CVR in Montserrat plus split-link status.
 */

#include <stddef.h>

#include <lvgl.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zmk/display/status_screen.h>
#include <zmk/display/widgets/battery_status.h>
#include <zmk/display/widgets/layer_status.h>
#include <zmk/display/widgets/output_status.h>
#include <zmk/display/widgets/peripheral_status.h>
#include <zmk/display/widgets/wpm_status.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_BATTERY_STATUS)
static struct zmk_widget_battery_status battery_status_widget;
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
static struct zmk_widget_output_status output_status_widget;
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_LAYER_STATUS)
static struct zmk_widget_layer_status layer_status_widget;
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_WPM_STATUS)
static struct zmk_widget_wpm_status wpm_status_widget;
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS)
static struct zmk_widget_peripheral_status peripheral_status_widget;
#endif

static void set_display_rotation(void) {
#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_CW_LEFT) || \
    IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_CW_RIGHT)
#if LVGL_VERSION_MAJOR >= 9
    lv_display_set_rotation(lv_display_get_default(), LV_DISPLAY_ROTATION_90);
#else
    lv_disp_set_rotation(lv_disp_get_default(), LV_DISP_ROT_90);
#endif
#elif IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_CCW_LEFT) || \
    IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_CCW_RIGHT)
#if LVGL_VERSION_MAJOR >= 9
    lv_display_set_rotation(lv_display_get_default(), LV_DISPLAY_ROTATION_270);
#else
    lv_disp_set_rotation(lv_disp_get_default(), LV_DISP_ROT_270);
#endif
#endif
}

static void style_screen(lv_obj_t *screen) {
    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_text_color(screen, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
}

static void center_widget_at(lv_obj_t *obj, lv_coord_t y) {
    lv_obj_set_width(obj, 32);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, y);
}

static void add_rule(lv_obj_t *screen, lv_coord_t y) {
    lv_obj_t *rule = lv_obj_create(screen);
    lv_obj_set_size(rule, 22, 1);
    lv_obj_set_style_bg_color(rule, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(rule, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(rule, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(rule, 0, LV_PART_MAIN);
    lv_obj_clear_flag(rule, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(rule, LV_ALIGN_TOP_MID, 0, y);
}

#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_RIGHT)
static lv_obj_t *make_label(lv_obj_t *parent, const char *text, const lv_font_t *font) {
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_width(label, 32);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    return label;
}
#endif

#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_LEFT)
static void build_central_portrait(lv_obj_t *screen) {
#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
    zmk_widget_output_status_init(&output_status_widget, screen);
    center_widget_at(zmk_widget_output_status_obj(&output_status_widget), 3);
#endif

    add_rule(screen, 28);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_BATTERY_STATUS)
    zmk_widget_battery_status_init(&battery_status_widget, screen);
    center_widget_at(zmk_widget_battery_status_obj(&battery_status_widget), 34);
#endif

    add_rule(screen, 58);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_LAYER_STATUS)
    zmk_widget_layer_status_init(&layer_status_widget, screen);
    center_widget_at(zmk_widget_layer_status_obj(&layer_status_widget), 64);
#endif

    add_rule(screen, 88);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_WPM_STATUS)
    zmk_widget_wpm_status_init(&wpm_status_widget, screen);
    center_widget_at(zmk_widget_wpm_status_obj(&wpm_status_widget), 95);
#endif
}

static void build_central_landscape(lv_obj_t *screen) {
#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_TOP_LEFT, 1, 1);
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_BATTERY_STATUS)
    zmk_widget_battery_status_init(&battery_status_widget, screen);
    lv_obj_align(zmk_widget_battery_status_obj(&battery_status_widget), LV_ALIGN_TOP_RIGHT, -1, 1);
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_LAYER_STATUS)
    zmk_widget_layer_status_init(&layer_status_widget, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget), LV_ALIGN_BOTTOM_LEFT, 1, -1);
#endif
#if IS_ENABLED(CONFIG_ZMK_WIDGET_WPM_STATUS)
    zmk_widget_wpm_status_init(&wpm_status_widget, screen);
    lv_obj_align(zmk_widget_wpm_status_obj(&wpm_status_widget), LV_ALIGN_BOTTOM_RIGHT, -1, -1);
#endif
}
#endif /* CONFIG_SHIELD_N9CVR_OLED_UI_LEFT */

#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_RIGHT)
static void build_peripheral_portrait(lv_obj_t *screen) {
    lv_obj_t *call = make_label(screen, "N\n9\nC\nV\nR", &lv_font_montserrat_14);
    lv_obj_set_style_text_line_space(call, 1, LV_PART_MAIN);
    lv_obj_align(call, LV_ALIGN_TOP_MID, 0, 2);

    add_rule(screen, 87);

    lv_obj_t *link = make_label(screen, "LINK", &lv_font_montserrat_10);
    lv_obj_align(link, LV_ALIGN_TOP_MID, 0, 91);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS)
    zmk_widget_peripheral_status_init(&peripheral_status_widget, screen);
    center_widget_at(zmk_widget_peripheral_status_obj(&peripheral_status_widget), 106);
#endif
}

static void build_peripheral_landscape(lv_obj_t *screen) {
    lv_obj_t *call = lv_label_create(screen);
    lv_label_set_text(call, "N9CVR");
    lv_obj_set_style_text_font(call, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(call, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(call, LV_ALIGN_LEFT_MID, 4, 0);

#if IS_ENABLED(CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS)
    zmk_widget_peripheral_status_init(&peripheral_status_widget, screen);
    lv_obj_align(zmk_widget_peripheral_status_obj(&peripheral_status_widget), LV_ALIGN_RIGHT_MID, -4, 0);
#endif
}
#endif /* CONFIG_SHIELD_N9CVR_OLED_UI_RIGHT */

lv_obj_t *zmk_display_status_screen(void) {
    set_display_rotation();

    lv_obj_t *screen = lv_obj_create(NULL);
    style_screen(screen);

#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_LANDSCAPE_LEFT) || \
    IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_LANDSCAPE_RIGHT)
#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_RIGHT)
    build_peripheral_landscape(screen);
#else
    build_central_landscape(screen);
#endif
#else
#if IS_ENABLED(CONFIG_SHIELD_N9CVR_OLED_UI_RIGHT)
    build_peripheral_portrait(screen);
#else
    build_central_portrait(screen);
#endif
#endif

    return screen;
}
