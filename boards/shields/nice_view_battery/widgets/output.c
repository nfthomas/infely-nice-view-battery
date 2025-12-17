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
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    lv_layer_t layer;
    canvas_begin(canvas, &layer);

    lv_area_t coords = {
        .x1 = OFFSET_X,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + usb.header.w - 1,
        .y2 = OFFSET_Y + usb.header.h - 1,
    };

    lv_draw_image(&layer, &img_dsc, &coords, &usb);

    canvas_end(canvas, &layer);
}

static void draw_ble_unbonded(lv_obj_t *canvas) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    lv_layer_t layer;
    canvas_begin(canvas, &layer);

    lv_area_t coords = {
        .x1 = OFFSET_X,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + unbound.header.w - 1,
        .y2 = OFFSET_Y + unbound.header.h - 1,
    };

    lv_draw_image(&layer, &img_dsc, &coords, &unbound);

    canvas_end(canvas, &layer);
}
#endif

static void draw_ble_disconnected(lv_obj_t *canvas) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    lv_img_dsc_t *img_ptr =
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
                       &bt_disconnected;
#else
                       &link_disconnected;
#endif

    lv_layer_t layer;
    canvas_begin(canvas, &layer);

    lv_area_t coords = {
        .x1 = OFFSET_X,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + img_ptr->header.w - 1,
        .y2 = OFFSET_Y + img_ptr->header.h - 1,
    };

    lv_draw_image(&layer, &img_dsc, &coords, img_ptr);

    canvas_end(canvas, &layer);
}

static void draw_ble_connected(lv_obj_t *canvas) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    lv_img_dsc_t *img_ptr =
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
                       &bt;
#else
                       &link;
#endif

    lv_layer_t layer;
    canvas_begin(canvas, &layer);

    lv_area_t coords = {
        .x1 = OFFSET_X,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + img_ptr->header.w - 1,
        .y2 = OFFSET_Y + img_ptr->header.h - 1,
    };

    lv_draw_image(&layer, &img_dsc, &coords, img_ptr);

    canvas_end(canvas, &layer);
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
