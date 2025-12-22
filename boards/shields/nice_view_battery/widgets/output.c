#include <zephyr/kernel.h>
#include "output.h"
#include "../assets/font.h"

#define OFFSET_X 0
#define OFFSET_Y 0

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    LV_IMG_DECLARE(bt);
    LV_IMG_DECLARE(bt_disconnected);
    LV_IMG_DECLARE(unbound);
    LV_IMG_DECLARE(usb);
#else
    LV_IMG_DECLARE(link);
    LV_IMG_DECLARE(link_disconnected);
#endif

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
static void draw_usb_connected(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);
    lv_canvas_draw_rect(canvas, OFFSET_X, OFFSET_Y + 27, 68, 13, &rect_dsc);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    img_dsc.zoom = (13 << 8) / 22;

    lv_canvas_draw_img(canvas, OFFSET_X + 27, OFFSET_Y + 27, &usb, &img_dsc);
}

static void draw_ble_unbonded(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_BACKGROUND);
    lv_canvas_draw_rect(canvas, OFFSET_X, OFFSET_Y + 27, 68, 13, &rect_dsc);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    img_dsc.zoom = (13 << 8) / 22;

    lv_canvas_draw_img(canvas, OFFSET_X + 27, OFFSET_Y + 27, &unbound, &img_dsc);
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_BACKGROUND);
    lv_canvas_draw_rect(canvas, OFFSET_X, OFFSET_Y + 27, 68, 13, &rect_dsc);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    img_dsc.zoom = (13 << 8) / 22;

    lv_canvas_draw_img(canvas, OFFSET_X + 27, OFFSET_Y + 27,
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
                        &bt_disconnected,
#else
                        &link_disconnected,
#endif
                        &img_dsc);
}

static void draw_ble_connected(lv_obj_t *canvas) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);
    lv_canvas_draw_rect(canvas, OFFSET_X, OFFSET_Y + 27, 68, 13, &rect_dsc);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    img_dsc.zoom = (13 << 8) / 22;

    lv_canvas_draw_img(canvas, OFFSET_X + 27, OFFSET_Y + 27,
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
                        &bt,
#else
                        &link,
#endif
                        &img_dsc);
}

void draw_output_status(lv_obj_t *canvas, const struct status_state *state) {
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    switch (state->selected_endpoint.transport) {
    case ZMK_TRANSPORT_USB:
        draw_usb_connected(canvas);
        break;

    case ZMK_TRANSPORT_BLE:
        if (state->active_profile_bonded) {
            if (state->active_profile_connected) {
                draw_ble_connected(canvas);
            } else {
                draw_ble_disconnected(canvas);
            }
        } else {
            draw_ble_unbonded(canvas);
        }
        break;
    }
#else
    if (state->connected) {
        draw_ble_connected(canvas);
    } else {
        draw_ble_disconnected(canvas);
    }
#endif
}
