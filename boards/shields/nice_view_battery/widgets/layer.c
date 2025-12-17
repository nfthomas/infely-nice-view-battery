#include <zephyr/kernel.h>
#include "layer.h"
#include "../assets/font.h"

#define OFFSET_X 0
#define OFFSET_Y 0

LV_IMG_DECLARE(layer);

void draw_layer_status(lv_obj_t *canvas, const struct status_state *state) {
    if (state->layer_label == NULL || state->layer_label[0] == '\0') {
        return;
    }

    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_BACKGROUND, &font, LV_TEXT_ALIGN_CENTER);

    char text[10] = {};
    strcpy(text, state->layer_label);
    to_uppercase(text);

    lv_layer_t layer_img;
    canvas_begin(canvas, &layer_img);

    lv_area_t coords_img = {
        .x1 = OFFSET_X,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + layer.header.w - 1,
        .y2 = OFFSET_Y + layer.header.h - 1,
    };

    lv_draw_image(&layer_img, &img_dsc, &coords_img, &layer);

    canvas_end(canvas, &layer_img);

    lv_layer_t layer_text;
    canvas_begin(canvas, &layer_text);

    lv_area_t coords_text = {
        .x1 = OFFSET_X + 2,
        .y1 = OFFSET_Y,
        .x2 = OFFSET_X + 2 + 64 - 1,
        .y2 = OFFSET_Y + label_dsc.font->line_height - 1,
    };

    lv_draw_label(&layer_text, &label_dsc, &coords_text, text, NULL);

    canvas_end(canvas, &layer_text);
}
