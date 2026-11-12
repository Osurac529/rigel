#ifndef VAPOR_MATH_QUAT_H
#define VAPOR_MATH_QUAT_H

#include "quaternion.h"
#include "operation_tracer.h"

namespace vapor
{

namespace math
{

typedef quaternion< FloatOpTracer > quat;
typedef quaternion< DoubleOpTracer > dquat;

} // end of namespace math

} // end of namespace vapor

#endif
