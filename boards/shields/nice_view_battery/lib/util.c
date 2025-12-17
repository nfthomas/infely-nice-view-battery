#include <zephyr/kernel.h>
#include "util.h"
#include <ctype.h>

void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[], const int size) {
    static lv_color_t cbuf_tmp[CANVAS_SIZE * CANVAS_SIZE];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));

    lv_image_dsc_t img;
    img.data = (void *)cbuf_tmp;
    img.header.cf = LV_COLOR_FORMAT_NATIVE;
    img.header.w = size;
    img.header.h = size;

    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    img_dsc.angle = 900;                /* 90° */
    img_dsc.zoom  = LV_ZOOM_NONE;
    img_dsc.pivot.x = size / 2;
    img_dsc.pivot.y = size / 2;

    lv_area_t coords = {
        .x1 = 0,
        .y1 = 0,
        .x2 = size - 1,
        .y2 = size - 1,
    };

    lv_draw_img(&layer, &img_dsc, &coords, &img);

    lv_canvas_finish_layer(canvas, &layer);
}

void draw_background(lv_obj_t *canvas, const int size) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_BACKGROUND);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_area_t coords = {
        .x1 = 0,
        .y1 = 0,
        .x2 = size - 1,
        .y2 = size - 1,
    };

    lv_draw_rect(&layer, &rect_dsc, &coords);

    lv_canvas_finish_layer(canvas, &layer);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font,
                    lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
}

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}
