#include <zephyr/kernel.h>
#include "profile.h"

#define OFFSET_X 0
#define OFFSET_Y 15

LV_IMG_DECLARE(profile);
LV_IMG_DECLARE(profile_active);

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    for (int i = 0; i < 5; i++) {
        lv_img_dsc_t *img_ptr = i == state->active_profile_index ? &profile_active : &profile;
        
        lv_layer_t layer;
        canvas_begin(canvas, &layer);

        lv_area_t coords = {
            .x1 = OFFSET_X + (i * 14),
            .y1 = OFFSET_Y,
            .x2 = OFFSET_X + (i * 14) + img_ptr->header.w - 1,
            .y2 = OFFSET_Y + img_ptr->header.h - 1,
        };

        lv_draw_image(&layer, &img_dsc, &coords, img_ptr);

        canvas_end(canvas, &layer);
    }
}
