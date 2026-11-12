#ifndef VAPOR_MATH_MAT_H
#define VAPOR_MATH_MAT_H

#include "matrix4x4.h"
#include "matrix3x3.h"
#include "matrix2x2.h"
#include "operation_tracer.h"

namespace vapor
{

namespace math
{

// The double versions of vectors do not exist in the GLSL language
// they are here for use on the CPU not GPU since GPU does not have
// a 64 bit floating point type.

typedef matrix4x4< FloatOpTracer > mat4x4;
typedef mat4x4 mat4;
typedef matrix4x4< DoubleOpTracer > dmat4x4;
typedef dmat4x4 dmat4;
typedef matrix3x3< FloatOpTracer > mat3x3;
typedef mat3x3 mat3;
typedef matrix3x3< DoubleOpTracer > dmat3x3;
typedef dmat3x3 dmat3;
typedef matrix2x2< FloatOpTracer > mat2x2;
typedef mat2x2 mat2;
typedef matrix2x2< DoubleOpTracer > dmat2x2;
typedef dmat2x2 dmat2;

} // end of namespace math

} // end of namespace vapor

#endif
