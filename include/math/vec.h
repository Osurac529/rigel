#ifndef VAPOR_MATH_VEC_H
#define VAPOR_MATH_VEC_H

#include "vector4.h"
#include "operation_tracer.h"

namespace vapor
{

namespace math
{

// The double versions of vectors do not exist in the GLSL language
// they are here for use on the CPU not GPU since GPU does not have
// a 64 bit floating point type.

typedef vector2< FloatOpTracer > vec2;
typedef vector2< DoubleOpTracer > dvec2;
typedef vector2< IntOpTracer > ivec2;

typedef vector3< FloatOpTracer > vec3;
typedef vector3< DoubleOpTracer > dvec3;
typedef vector3< IntOpTracer > ivec3;

typedef vector4< FloatOpTracer > vec4;
typedef vector4< DoubleOpTracer > dvec4;
typedef vector4< IntOpTracer > ivec4;

// bools do not track operations
typedef vector2< bool > bvec2;
typedef vector3< bool > bvec3;
typedef vector4< bool > bvec4;

} // end of namespace math

} // end of namespace vapor

#endif
