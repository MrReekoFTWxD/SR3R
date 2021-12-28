#include "pch.h"
#include "defines.h"

game_hud_renderer_t game_hud_renderer = game_hud_renderer_t(ResolveImport() + 0x3863B0);
game_render_set_color_t game_render_set_color = game_render_set_color_t(ResolveImport() + 0x170690);
game_render_string_scale_t game_render_string_scale = game_render_string_scale_t(ResolveImport() + 0x170730);
game_render_screen_width_t game_render_screen_width = game_render_screen_width_t(ResolveImport() + 0x175340);
game_render_screen_height_t game_render_screen_height = game_render_screen_height_t(ResolveImport() + 0x175330);
vint_transform_from_doc_height_t vint_transform_from_doc_height = vint_transform_from_doc_height_t(ResolveImport() + 0x85B9D0);
vint_transform_from_doc_width_t vint_transform_from_doc_width = vint_transform_from_doc_width_t(ResolveImport() + 0x85BA20);
game_render_rect_t game_render_rect = game_render_rect_t(ResolveImport() + 0x170430);
font_get_string_size_t font_get_string_size = font_get_string_size_t(ResolveImport() + 0x8A2730);
find_nearest_human_to_reticule_t find_nearest_human_to_reticule = find_nearest_human_to_reticule_t(ResolveImport() + 0x382260);
get_chest_pos_t get_chest_pos = get_chest_pos_t(ResolveImport() + 0x4CF3A0);
rl_get_screen_coords_from_world_coords_t rl_get_screen_coords_from_world_coords = rl_get_screen_coords_from_world_coords_t(ResolveImport() + 0x8F6780);
human_is_dead_t human_is_dead = human_is_dead_t(ResolveImport() + 0x500450);
game_render_line_t game_render_line = game_render_line_t(ResolveImport() + 0x170330);
get_head_pos_t get_head_pos = get_head_pos_t(ResolveImport() + 0x4CF600);
human_set_pos_frame_t human_set_pos_frame = human_set_pos_frame_t(ResolveImport() + 0x4D5340);
human_is_skydiving_t human_is_skydiving = human_is_skydiving_t(ResolveImport() + 0x53E410);
human_is_freefalling_t human_is_freefalling = human_is_freefalling_t(ResolveImport() + 0x524C50);
human_parachute_is_open_t human_parachute_is_open = human_parachute_is_open_t(ResolveImport() + 0x525190);
camera_get_xz_orient_t camera_get_xz_orient = camera_get_xz_orient_t(ResolveImport() + 0xE2BC0);
player_local_player_t player_local_player = player_local_player_t(ResolveImport() + 0x576790);
human_adjust_cash_t human_adjust_cash = human_adjust_cash_t(ResolveImport() + 0x4CD860);
GetNodeId_t GetNodeId = GetNodeId_t(ResolveImport() + 0x7D05A0);
animlib_get_instanced_model_matrices_t animlib_get_instanced_model_matrices = animlib_get_instanced_model_matrices_t(ResolveImport() + 0x7DBB70);
animlib_get_tag_world_coords_t animlib_get_tag_world_coords = animlib_get_tag_world_coords_t(ResolveImport() + 0x7DBE30);
human_move_is_crouching_t human_move_is_crouching = human_move_is_crouching_t(ResolveImport() + 0x5176B0);
get_tag_world_coords_t get_tag_world_coords = get_tag_world_coords_t(ResolveImport() + 0x4D0020);
animlib_find_bone_by_name_t animlib_find_bone_by_name = animlib_find_bone_by_name_t(ResolveImport() + 0x7DB1F0);
game_is_paused_t game_is_paused = game_is_paused_t(ResolveImport() + 0x2E2730);



void drawRect(float x, float y, float w, float h, vec4_t color)
{
    game_render_set_color(color[0], color[1], color[2], color[3]);
    game_render_rect(x, y, w, h, rl_primitive_state::Singleton());
}

void drawLine(fl_vector start, fl_vector end, vec4_t color)
{
    game_render_set_color(color[0], color[1], color[2], color[3]);
    game_render_line(start.x, start.y, end.x, end.y, rl_primitive_state::Singleton());
}

void drawText(const char* text, float x, float y, float scale, vec4_t color)
{
    game_render_set_color(color[0], color[1], color[2], color[3]);
    game_render_string_scale(x, y, text, scale, 1, rl_primitive_state::Singleton());
}

fl_vector fontStringSize(const char* string, float scale)
{
    int fontWidth = 0;
    int fontHeight = 0;
    font_get_string_size(&fontWidth, &fontHeight, string, strlen(string), 1, false);

    return fl_vector(fontWidth, fontHeight);
}

//Based off Quake works good enough for this game might redo later
fl_vector AnglesToForward(fl_vector origin, vm_vector Angles, float distance)
{
    float angle, sr, sp, sy, cr, cp, cy, PiDiv;
    PiDiv = ((float)M_PI / 180);
    angle = Angles.v.m128_f32[1] * PiDiv;
    sy = (float)sinf(angle);
    cy = (float)cosf(angle);
    angle = Angles.v.m128_f32[0] * PiDiv;
    sp = sinf(angle);
    cp = (float)cosf(angle);
    angle = Angles.v.m128_f32[1] * PiDiv;
    sr = (float)sinf(angle);
    cr = (float)cosf(angle);
    fl_vector Final = { (cp * cy * distance) + origin.x, (cp * sy * distance) + origin.y, (-sp * distance) + origin.z };
    return Final;
}

//Currently crashes but not everytime, need to look into animlib_get_tag_world_coords more when I have time
vm_vector* get_tag_pos(human* _this, vm_vector* result, vm_matrix34* head_orient)
{
    vm_vector basePos;

    int bone = _this->char_info->left_hip_bone_index;
        if (get_tag_world_coords(_this, &bone, result, 0, &_this->m_pos, &_this->m_orient))
            return result;


        animlib_get_tag_world_coords(GetNodeId(_this->char_inst->vp), animlib_find_bone_by_name(_this->char_info->character_rig, "spine"), &basePos, head_orient, result, 0);

    return result;
}

void BoundingBox(float x, float y, float width, float height, const vec4_t color, float thickness)
{
    drawRect(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
    drawRect(x - thickness, y + height, width + (thickness * 2), thickness, color);  // Bottom
    drawRect(x - thickness, y - thickness, thickness, height + thickness, color);    // Left
    drawRect(x + width, y - thickness, thickness, height + (thickness * 2), color);    // Right
}
