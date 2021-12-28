#ifndef STRUCTS_H
#define STRUCTS_H

#define M_PI		3.14159265358979323846f	// matches value in gcc v2 math.h


struct vec4_t
{
    float x, y, z, w;

    vec4_t();
    ~vec4_t();
    vec4_t(float x, float y, float z, float w);
    vec4_t(float vec[4]);

    operator float* ();
};

enum human_cash_adjustment_reason : __int32
{
    HUMAN_CASH_ADJUSTMENT_ACTIVITY_REWARD = 0x0,
    HUMAN_CASH_ADJUSTMENT_CASH_INSTEAD_OF_RESEPECT = 0x1,
    HUMAN_CASH_ADJUSTMENT_CASH_PICKUP = 0x2,
    HUMAN_CASH_ADJUSTMENT_CHEATS = 0x3,
    HUMAN_CASH_ADJUSTMENT_CRIB_STASH = 0x4,
    HUMAN_CASH_ADJUSTMENT_DIVERSION_REWARD = 0x5,
    HUMAN_CASH_ADJUSTMENT_MISSION_REWARD = 0x6,
    HUMAN_CASH_ADJUSTMENT_PICKPOCKET = 0x7,
    HUMAN_CASH_ADJUSTMENT_UNLOCKABLE_LUMP_SUM = 0x8,
    HUMAN_CASH_ADJUSTMENT_HOMIE_DEATH = 0x9,
    HUMAN_CASH_ADJUSTMENT_PLAYER_DEATH = 0xA,
    HUMAN_CASH_ADJUSTMENT_PURCHASE = 0xB,
    HUMAN_CASH_ADJUSTMENT_DEBUG = 0xC,
    HUMAN_CASH_ADJUSTMENT_SCRIPTED = 0xD,
    NUM_HUMAN_CASH_ADJUSTMENT_REASONS = 0xE,
};

struct ctg_object_flags
{
    unsigned __int8 flagged_list_state;
    __int8 preserve_handle : 1;
    __int8 destruction_started : 1;
    __int8 destroyed : 1;
    __int8 active : 1;
    __int8 stub : 1;
};

struct object_handle
{
    unsigned __int64 m_data;
};

struct ctg_object 
{
    object_handle handle;
    object_handle parent;
    const char* obj_name;
    ctg_object* children;
    ctg_object* child_next;
    ctg_object* child_prev;
    ctg_object* flagged_next;
    ctg_object* flagged_prev;
    unsigned __int16 all_index;
    ctg_object_flags ctg_flags;
    unsigned __int8 m_derived_type;
};
struct v_mempool_base {};

enum gender_types : __int8
{
    GENDER_TYPE_MALE = 0x0,
    GENDER_TYPE_FEMALE = 0x1,
    NUM_GENDER_TYPES = 0x2,
    GENDER_TYPE_INVALID = 0x3,
};

struct rl_primitive_state
{
    unsigned int value;


    static rl_primitive_state* Singleton()
    {
        return ((rl_primitive_state*)(ResolveImport() + 0x12064D8));
    }
};


union __m128
{
    float m128_f32[4];
    unsigned __int64 m128_u64[2];
    char m128_i8[16];
    __int16 m128_i16[8];
    int m128_i32[4];
    __int64 m128_i64[2];
    unsigned __int8 m128_u8[16];
    unsigned __int16 m128_u16[8];
    unsigned int m128_u32[4];
};
struct vm_vector
{
    __m128 v;
};

struct vm_float
{
    __m128 v;
};

struct fl_vector
{
    float x;
    float y;
    float z;

    fl_vector();
    ~fl_vector();

    fl_vector(float x, float y, float z);
    fl_vector(float x, float y);
    fl_vector(float x);
    fl_vector(vm_vector val);

};
struct fl_matrix
{
    fl_vector rvec;
    fl_vector uvec;
    fl_vector fvec;
};


struct fl_matrix43
{
    fl_matrix m_rotation;
    fl_vector m_translation;
};

struct vm_matrix34
{
    vm_vector rows[3];
};

template<typename T>
struct base_array
{
    T* elt;
    int array_size;
    int num;
};

struct ctg_world
{
    char _0x00[0x8];
    ctg_object* m_current_flagged_object;
    unsigned __int8 m_current_flagged_mode;
    char level_name[65];
    unsigned __int8 m_num_game_types;
    volatile int m_thread_id;
    int m_max_world_objects;
    v_mempool_base* m_scratch_mempool;
    base_array<ctg_object*> m_all_objects;
    base_array<unsigned short> m_object_type_buckets[255];

    static ctg_world*& s_out_world()
    {
        return (*(ctg_world**)(ResolveImport() + 0x294C9B8));
    }
};


struct checksum_stri
{
    unsigned int checksum;
};

struct anim_bone
{
    char* name;
    fl_vector inv_translation;
    fl_vector rel_bone_translation;
    int parent_index;
    int vid;
};

struct anim_tag
{
    char* name;
    fl_matrix43 transformation;
    int parent_index;
    int vid;
};

struct anim_rig
{
    char name[32];
    unsigned int flags;
    int num_bones;
    int num_common_bones;
    int num_virtual_bones;
    int num_tags;
    unsigned int* bone_name_chksums;
    anim_bone* bones;
    anim_tag* tags;
    unsigned __int64 data_size;
    unsigned int uid;
    unsigned __int8* original_buffer;
};

struct character_info
{
    character_info* equivalency_next; 
    character_info* equivalency_prev; 
    const char* name;
    checksum_stri name_cs; 
    const char* model_name; 
    const char* morph_name;
    const char* csim_name; 
    const char* anim_set_name;
    const char* rig_name;
    anim_rig* character_rig;
    unsigned int m_default_personas[12];
    int num_associated_char_presets;
    void** associated_char_presets;
    int num_heads;
    void* heads;
    int num_general_props;
    void* general_props;
    float base_height;
    float default_height_scale;
    float height_scale_variation;
    float base_height_offset;
    float hit_sphere_size;
    float lod_distances[4];
    int gang_rank;
    gender_types gang_gender;
    char root_bone_index;
    char lower_spine_bone_index;
    char upper_spine_bone_index;
    char pelvis_bone_index;
    char head_bone_index;
    char neck_bone_index;
    char eye_l_bone_index;
    char eye_r_bone_index;
    char left_hip_bone_index;
    char left_knee_bone_index;
    char right_hip_bone_index;
    char right_knee_bone_index;
    char left_foot_bone_index;
    char left_toe_bone_index;
    char right_foot_bone_index;
    char right_toe_bone_index;
    char left_shoulder_bone_index;
    char left_elbow_bone_index;
    char right_shoulder_bone_index;
    char right_elbow_bone_index;
    char left_hand_bone_index;
    char right_hand_bone_index;
    char m_camera_root_offset_bone_index;
    char m_camera_animated_bone_index;
    char m_camera_fov_bone_index;
    char m_camera_dof_bone_index;
    __int16 left_equip_tag_index;
    __int16 right_equip_tag_index;
    __int16 left_forearm_equip_tag_index;
    __int16 right_forearm_equip_tag_index;
    __int16 human_shield_tag_index;
    __int16 human_shield_unarmed_tag_index;
    __int16 left_ik_node_bone_index;
    __int16 right_ik_node_bone_index;
    __int16 flame_breath_tag_index;
    void* left_hand_item;
    void* high_res_material;
    void* high_res_material_body;
    void* original_material_map_body;
    unsigned __int64 srid;
    unsigned __int64 high_res_srid;
    unsigned __int64 cin_res_srid;
    unsigned __int64 loaded_srid;

    unsigned __int32 initialized : 1;
    unsigned __int32 player_character : 1;
    unsigned __int32 high_res_texture_requested : 1;
    unsigned __int32 high_res_texture_loaded : 1;
    unsigned __int32 high_res_texture_request_unload : 1;
    unsigned __int32 debug_loaded : 1;
    unsigned __int32 heroic : 1;
};
struct v_animate {};
struct character_instance
{
    char _0x00[0x20];
    v_animate* vp;
    int aim_handle;
};
struct human
{
    char _0x00[0x60];
    fl_vector m_pos; 
    fl_matrix m_orient;
    char _0x78[0x7C];

    int hprocessing_flags; 
    char _0x110[0x18];
    character_info* char_info; 
    char _0x130[0xD68];
    character_instance* char_inst;
};

struct player : human
{

};

struct aa_dist_info
{
    vm_float m_near_dist;
    float m_fade_in_rate;
    float m_fade_out_rate;
    float m_capsule_inner_multiplier;
    float m_capsule_outer_multiplier;
    bool m_use_cylinder;
};

struct aa_steer_info
{
    float m_steer_x;
    float m_steer_y;
    float m_max_steer_x;
    float m_max_steer_y;
    aa_dist_info m_dist_info;
};

struct aa_slow_info
{
    float m_slow_mult_x;
    float m_slow_mult_y;
    aa_dist_info m_dist_info;
};

struct aa_info
{
    char m_name[32];
    aa_steer_info m_steer_info;
    aa_slow_info m_slow_info;
};

enum cheat_ped_type_override : __int32
{
    CHEAT_PED_TYPE_NONE = 0x0,
    CHEAT_PED_TYPE_ZOMBIE = 0x1,
    CHEAT_PED_TYPE_MASCOT = 0x2,
    CHEAT_PED_TYPE_PIMPS_AND_HOS = 0x3,
};

struct cheat_flags
{
    unsigned __int32 pratfalls : 1;
    unsigned __int32 super_throw : 1;
    unsigned __int32 vehicle_infinite_mass : 1;
    unsigned __int32 vehicle_no_damage : 1;
    unsigned __int32 vehicle_smash : 1;
    unsigned __int32 wrath_of_god : 1;
    unsigned __int32 evil_cars : 1;
    unsigned __int32 evil_cars_2 : 1;
    unsigned __int32 unlimited_ammo : 1;
    unsigned __int32 infinite_sprint : 1;
    unsigned __int32 raining_peds : 1;
    unsigned __int32 ped_war : 1;
    unsigned __int32 drunk_peds : 1;
    unsigned __int32 super_saints : 1;
    unsigned __int32 unlimited_clip : 1;
    unsigned __int32 elevator_to_heaven : 1;
    unsigned __int32 god_mode : 1;
    unsigned __int32 hide_hud : 1;
    unsigned __int32 bloody_mess : 1;
    unsigned __int32 golden_gun : 1;
};

struct cheat_effects
{
    cheat_flags flags;
    float beer_muscles_boost;
    float explosion_boost;
    float human_scale;
    float player_scale[2];
    float jump_height_multiplier;
    fl_vector throw_velocity;
    cheat_ped_type_override ped_type_override;

    static cheat_effects* Singleton()
    {
        return ((cheat_effects*)(ResolveImport() + 0x15FCAD8));
    }
};

#endif