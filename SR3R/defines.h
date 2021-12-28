#ifndef DEFINES_H
#define DEFINES_H

typedef void(*game_hud_renderer_t)(void);
typedef void(*game_render_set_color_t)(float r, float g, float b, float a);
typedef void(*game_render_string_scale_t)(int sx, int sy, const char* s, float scale, int fontnum, const rl_primitive_state* state);
typedef void(*game_render_rect_t)(float x, float y, float w, float h, const rl_primitive_state* state);
typedef void(*font_get_string_size_t)(int* w, int* h, const char* s, int len, int fontnum, bool fistLineOnly);
typedef void(*game_render_line_t)(float x, float y, float x2, float y2, rl_primitive_state* state);
typedef int(*game_render_screen_width_t)();
typedef int(*game_render_screen_height_t)();
typedef float(*vint_transform_from_doc_height_t)(int x);
typedef int(*vint_transform_from_doc_width_t)(int x);
typedef bool (*human_is_dead_t)(human* const hp);
typedef human* (*find_nearest_human_to_reticule_t)(float* nearest_dist, fl_vector* nearest_ix);
typedef bool (*rl_get_screen_coords_from_world_coords_t)(const fl_vector* world_pos, fl_vector* screen_pos);
typedef vm_vector* (*get_head_pos_t)(human* _this, vm_vector* result, vm_matrix34* head_orient);
typedef vm_vector* (*get_chest_pos_t)(human* _this, vm_vector* result, vm_matrix34* head_orient);
typedef void(*human_set_pos_frame_t)(human* hp, fl_vector* pos);
typedef player* (*player_local_player_t)();
typedef void(*camera_get_xz_orient_t)(vm_vector* fvec, vm_vector* rvec);
typedef bool(*human_parachute_is_open_t)(human* hp);
typedef bool(*human_is_freefalling_t)(human* hp);
typedef bool(*human_is_skydiving_t)(human* hp);
typedef void(*human_adjust_cash_t)(human* _this, const int* amount, int reason);
typedef __int64(*GetNodeId_t)(v_animate* v);
typedef void* (*animlib_get_instanced_model_matrices_t)(int aim, fl_matrix43** matrix);
typedef void(*animlib_get_tag_world_coords_t)(int aim_handle, int tag_index, const vm_vector* base_pos, const vm_matrix34* base_orient, vm_vector* pos, vm_matrix34* orient);
typedef bool(*human_move_is_crouching_t)(human* hp);
typedef bool(*get_tag_world_coords_t)(human* _this, int* tag_index, vm_vector* tag_pos, vm_matrix34* tag_orient, fl_vector* obj_pos, fl_matrix* obj_orient);
typedef int(*animlib_find_bone_by_name_t)(void* rig, const char* name);
typedef bool(*game_is_paused_t)();

extern human_set_pos_frame_t human_set_pos_frame;
extern human_is_skydiving_t human_is_skydiving;
extern human_is_freefalling_t human_is_freefalling;
extern human_parachute_is_open_t human_parachute_is_open;
extern camera_get_xz_orient_t camera_get_xz_orient;
extern player_local_player_t player_local_player;
extern game_hud_renderer_t game_hud_renderer;
extern game_render_set_color_t game_render_set_color;
extern game_render_string_scale_t game_render_string_scale;
extern game_render_rect_t game_render_rect;
extern font_get_string_size_t font_get_string_size;
extern game_render_line_t game_render_line;
extern game_render_screen_width_t game_render_screen_width;
extern game_render_screen_height_t game_render_screen_height;
extern vint_transform_from_doc_height_t vint_transform_from_doc_height;
extern vint_transform_from_doc_width_t vint_transform_from_doc_width;
extern find_nearest_human_to_reticule_t find_nearest_human_to_reticule;
extern rl_get_screen_coords_from_world_coords_t rl_get_screen_coords_from_world_coords;
extern human_is_dead_t human_is_dead;
extern get_head_pos_t get_head_pos;
extern get_chest_pos_t get_chest_pos;
extern human_adjust_cash_t human_adjust_cash;
extern GetNodeId_t GetNodeId;
extern animlib_get_instanced_model_matrices_t animlib_get_instanced_model_matrices;
extern animlib_get_tag_world_coords_t animlib_get_tag_world_coords;
extern human_move_is_crouching_t human_move_is_crouching;
extern get_tag_world_coords_t get_tag_world_coords;
extern animlib_find_bone_by_name_t animlib_find_bone_by_name;
extern game_is_paused_t game_is_paused;



void drawRect(float x, float y, float w, float h, vec4_t color);
void drawLine(fl_vector start, fl_vector end, vec4_t color);
void drawText(const char* text, float x, float y, float scale, vec4_t color);
fl_vector fontStringSize(const char* string, float scale);

fl_vector AnglesToForward(fl_vector origin, vm_vector Angles, float distance);

vm_vector* get_tag_pos(human* _this, vm_vector* result, vm_matrix34* head_orient);
void BoundingBox(float x, float y, float width, float height, const vec4_t color, float thickness);
std::string to_upper(std::string text);

#endif