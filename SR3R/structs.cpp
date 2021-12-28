#include "pch.h"
#include "structs.h"


vec4_t::vec4_t()
{
    this->x = this->y = this->z = this->w = 0;
}

vec4_t::~vec4_t()
{
}

vec4_t::vec4_t(float x, float y, float z, float w)
{
    this->x = (x > 1.0f) ? x / 255.f : x;
    this->y = (y > 1.0f) ? y / 255.f : y;
    this->z = (z > 1.0f) ? z / 255.f : z;
    this->w = (w > 1.0f) ? w / 255.f : w;
}

vec4_t::vec4_t(float vec[4])
{
    this->x = vec[0];
    this->y = vec[1];
    this->z = vec[2];
    this->w = vec[3];
}

vec4_t::operator float* ()
{
    return (float*)&this[0];
}

fl_vector::fl_vector()
{
    this->x = this->y = this->z = 0;
}

fl_vector::~fl_vector()
{
}

fl_vector::fl_vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

fl_vector::fl_vector(float x, float y)
{
    this->x = x;
    this->y = y;
    this->z = 0;
}

fl_vector::fl_vector(float x)
{
    this->x = x;
    this->y = this->z = 0;
}

fl_vector::fl_vector(vm_vector val)
{
    this->x = val.v.m128_f32[0];
    this->y = val.v.m128_f32[1];
    this->z = val.v.m128_f32[2];
}
