#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#ifndef _PAINT_H
#define _PAINT_H

#include "../common.h"
#include "../world/map.h"
#include "../interface/colour.h"
#include "../drawing/drawing.h"

typedef struct attached_paint_struct attached_paint_struct;

#pragma pack(push, 1)
/* size 0x12 */
struct attached_paint_struct {
    uint32 image_id;		// 0x00
    union {
        uint32 tertiary_colour;
        // If masked image_id is masked_id
        uint32 colour_image_id;
    };
    uint16 x;		// 0x08
    uint16 y;		// 0x0A
    uint8 flags;    // 0x0C
    uint8 pad_0D;
    attached_paint_struct* next;	//0x0E
};
#ifdef PLATFORM_32BIT
// TODO: drop packing from this when all rendering is done.
assert_struct_size(attached_paint_struct, 0x12);
#endif

typedef struct paint_struct paint_struct;

/* size 0x34 */
struct paint_struct {
	uint32 image_id;		// 0x00
	union {
		uint32 tertiary_colour;	// 0x04
		// If masked image_id is masked_id
		uint32 colour_image_id;	// 0x04
	};
	uint16 bound_box_x;		// 0x08
	uint16 bound_box_y;		// 0x0A
	uint16 bound_box_z; // 0x0C
	uint16 bound_box_z_end; // 0x0E
	uint16 bound_box_x_end; // 0x10
	uint16 bound_box_y_end; // 0x12
	uint16 x;				// 0x14
	uint16 y;				// 0x16
	uint16 var_18;
	uint8 flags;
	uint8 var_1B;
	attached_paint_struct* attached_ps;	//0x1C
	paint_struct* var_20;
	paint_struct* next_quadrant_ps; // 0x24
	uint8 sprite_type;		//0x28
	uint8 var_29;
	uint16 pad_2A;
	uint16 map_x;			// 0x2C
	uint16 map_y;			// 0x2E
	rct_map_element *mapElement; // 0x30 (or sprite pointer)
};
#ifdef PLATFORM_32BIT
// TODO: drop packing from this when all rendering is done.
assert_struct_size(paint_struct, 0x34);
#endif

extern paint_struct * g_ps_F1AD28;
extern attached_paint_struct * g_aps_F1AD2C;

typedef struct paint_string_struct paint_string_struct;

/* size 0x1E */
struct paint_string_struct {
	rct_string_id string_id;		// 0x00
	paint_string_struct *next;		// 0x02
	uint16 x;						// 0x06
	uint16 y;						// 0x08
	uint32 args[4];					// 0x0A
	uint8 *y_offsets;				// 0x1A
};
#ifdef PLATFORM_32BIT
assert_struct_size(paint_string_struct, 0x1e);
#endif
#pragma pack(pop)

typedef struct sprite_bb {
	uint32 sprite_id;
	rct_xyz16 offset;
	rct_xyz16 bb_offset;
	rct_xyz16 bb_size;
} sprite_bb;

enum PAINT_STRUCT_FLAGS {
	PAINT_STRUCT_FLAG_IS_MASKED = (1 << 0)
};

#define gPaintInteractionType		RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8)

/** rct2: 0x00993CC4 */
extern const uint32 construction_markers[];

void painter_setup();

paint_struct * sub_98196C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, sint16 z_offset, uint32 rotation);
paint_struct * sub_98197C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, sint16 z_offset, sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);
paint_struct * sub_98198C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, sint16 z_offset, sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);
paint_struct * sub_98199C(uint32 image_id, sint8 x_offset, sint8 y_offset, sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z, sint16 z_offset, sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z, uint32 rotation);

bool paint_attach_to_previous_attach(uint32 image_id, uint16 x, uint16 y);
bool paint_attach_to_previous_ps(uint32 image_id, uint16 x, uint16 y);
void sub_685EBC(money32 amount, uint16 string_id, sint16 y, sint16 z, sint8 y_offsets[], sint16 offset_x, uint32 rotation);

void viewport_draw_money_effects();
void viewport_paint_setup();

#endif
