#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/font.h"

#define OFFSET_X 29
#define OFFSET_Y 37

LV_IMG_DECLARE(bolt);
LV_IMG_DECLARE(battery);
LV_IMG_DECLARE(battery_mask);

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);
    lv_draw_label_dsc_t outline_dsc;
    init_label_dsc(&outline_dsc, LVGL_BACKGROUND, &font, LV_TEXT_ALIGN_CENTER);
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &font, LV_TEXT_ALIGN_CENTER);

    lv_layer_t layer;
    canvas_begin(canvas, &layer);

    lv_area_t coords = {
        .x1 = 0,
        .y1 = 0,
        .x2 = 0 + battery.header.w - 1,
        .y2 = 0 + battery.header.h - 1,
    };

    lv_draw_image(&layer, &img_dsc, &coords, &battery);

    canvas_end(canvas, &layer);

    lv_layer_t layer_rect;
    canvas_begin(canvas, &layer_rect);

    lv_area_t coords_rect = {
        .x1 = 4,
        .y1 = 4,
        .x2 = 4 + 54 * state->battery / 100 - 1,
        .y2 = 4 + 23 - 1,
    };

    lv_draw_rect(&layer_rect, &rect_dsc, &coords_rect);

    canvas_end(canvas, &layer_rect);

    lv_layer_t layer_mask;
    canvas_begin(canvas, &layer_mask);

    lv_area_t coords_mask = {
        .x1 = 2,
        .y1 = 2,
        .x2 = 2 + battery_mask.header.w - 1,
        .y2 = 2 + battery_mask.header.h - 1,
    };

    lv_draw_image(&layer_mask, &img_dsc, &coords_mask, &battery_mask);

    canvas_end(canvas, &layer_mask);

    char text[10] = {};
    sprintf(text, "%i%%", state->battery);

    const int y = 9;
    const int w = 62;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) {
                lv_layer_t layer_outline;
                canvas_begin(canvas, &layer_outline);

                lv_area_t coords_outline = {
                    .x1 = dx,
                    .y1 = y + dy,
                    .x2 = dx + w - 1,
                    .y2 = y + dy + outline_dsc.font->line_height - 1,
                };

                lv_draw_label(&layer_outline, &outline_dsc, &coords_outline, text, NULL);

                canvas_end(canvas, &layer_outline);
            }
        }
    }

    lv_layer_t layer_text;
    canvas_begin(canvas, &layer_text);

    lv_area_t coords_text = {
        .x1 = 0,
        .y1 = y,
        .x2 = 0 + w - 1,
        .y2 = y + label_dsc.font->line_height - 1,
    };

    lv_draw_label(&layer_text, &label_dsc, &coords_text, text, NULL);

    canvas_end(canvas, &layer_text);

    if (state->charging) {
        lv_layer_t layer_bolt;
        canvas_begin(canvas, &layer_bolt);

        lv_area_t coords_bolt = {
            .x1 = OFFSET_X,
            .y1 = OFFSET_Y,
            .x2 = OFFSET_X + bolt.header.w - 1,
            .y2 = OFFSET_Y + bolt.header.h - 1,
        };

        lv_draw_image(&layer_bolt, &img_dsc, &coords_bolt, &bolt);

        canvas_end(canvas, &layer_bolt);
    }
}
