#ifndef VAPOR_MATH_OPERATION_TRACER_H
#define VAPOR_MATH_OPERATION_TRACER_H

#include <istream>
#include <ostream>

namespace vapor
{

namespace math
{

template< typename T >
class operation_tracer
{
public:

  operation_tracer()
  {
    ++nullConstructorCount;
  }

  operation_tracer( T const& x ):
    mX( x )
  {
    ++constructorCount;
  }

  operator T() const
  {
    return mX;
  }

  operation_tracer< T >& operator=( operation_tracer< T > const& rhs )
  {  
    ++assignmentCount;
    mX = rhs.mX;
    return *this;
  }

  operation_tracer< T >& operator=( T const& rhs )
  {
    ++assignmentCount;
    mX = rhs;
    return *this;
  }

  friend operation_tracer< T > const operator*( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++mulCount;
    return operation_tracer< T >( lhs.mX * rhs.mX );
  }

  operation_tracer< T >& operator*=( operation_tracer< T > const& rhs )
  {
    ++mulCount;
    mX *= rhs.mX;
    return *this;
  }

  friend operation_tracer< T > const operator/( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++divCount;
    return operation_tracer< T >( lhs.mX / rhs.mX );
  }

  operation_tracer< T >& operator/=( operation_tracer< T > const& rhs )
  {
    ++divCount;
    mX /= rhs.mX;
    return *this;
  }

  friend operation_tracer< T > const operator+( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++addCount;
    return operation_tracer< T >( lhs.mX + rhs.mX );
  }

  operation_tracer< T >& operator+=( operation_tracer< T > const& rhs )
  {
    ++addCount;
    mX += rhs.mX;
    return *this;
  }

  friend operation_tracer< T > const operator-( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++subCount;
    return operation_tracer< T >( lhs.mX - rhs.mX );
  }

  operation_tracer< T >& operator-=( operation_tracer< T > const& rhs )
  {
    ++subCount;
    mX -= rhs.mX;
    return *this;
  }

  operation_tracer< T > const operator-()
  {
    ++negCount;
    return operation_tracer< T >( -mX );
  }

  friend std::ostream& operator<<( std::ostream& lhs, operation_tracer< T > const& rhs )
  {
    return lhs << rhs.mX;
  }

  friend std::istream& operator>>( std::istream& lhs, operation_tracer< T >& rhs )
  {
    return lhs >> rhs.mX;
  }

  static void clear()
  {
    nullConstructorCount =
    constructorCount =
    assignmentCount =
    mulCount =
    divCount =
    addCount =
    subCount =
    negCount = 0;
  }

  static void print( std::ostream& out )
  {
#ifdef OPERATION_TRACING
    out << "nullConstructorCount: " << nullConstructorCount << std::endl
      << "constructorCount: " << constructorCount << std::endl
      << "assignmentCount: " << assignmentCount << std::endl
      << "mulCount: " << mulCount << std::endl
      << "divCount: " << divCount << std::endl
      << "addCount: " << addCount << std::endl
      << "subCount: " << subCount << std::endl
      << "negCount: " << negCount << std::endl
      << "lessThanCount: " << lessThanCount << std::endl
      << "lessThanEqualCount: " << lessThanEqualCount << std::endl
      << "greaterThanCount: " << greaterThanCount << std::endl
      << "greaterThanEqualCount: " << greaterThanEqualCount << std::endl
      << "equalCount: " << equalCount << std::endl
      << "notEqualCount: " << notEqualCount << std::endl;
#else
    out << "Operation tracing disabled" << std::endl;
#endif
  }

  friend bool const operator<( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++lessThanCount;
    return lhs.mX < rhs.mX;
  }

  friend bool const operator<=( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++lessThanEqualCount;
    return lhs.mX <= rhs.mX;
  }

  friend bool const operator>( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++greaterThanCount;
    return lhs.mX > rhs.mX;
  }

  friend bool const operator>=( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++greaterThanEqualCount;
    return lhs.mX >= rhs.mX;
  }

  friend bool const operator==( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++equalCount;
    return lhs.mX == rhs.mX;
  }

  friend bool const operator!=( operation_tracer< T > const& lhs, operation_tracer< T > const& rhs )
  {
    ++notEqualCount;
    return lhs.mX != rhs.mX;
  }

private:

  static unsigned long nullConstructorCount;
  static unsigned long constructorCount;
  static unsigned long assignmentCount;
  static unsigned long mulCount;
  static unsigned long divCount;
  static unsigned long addCount;
  static unsigned long subCount;
  static unsigned long negCount;
  static unsigned long lessThanCount;
  static unsigned long lessThanEqualCount;
  static unsigned long greaterThanCount;
  static unsigned long greaterThanEqualCount;
  static unsigned long equalCount;
  static unsigned long notEqualCount;

  T mX;
};

template< typename T >
unsigned long operation_tracer< T >::nullConstructorCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::constructorCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::assignmentCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::mulCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::divCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::addCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::subCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::negCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::lessThanCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::lessThanEqualCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::greaterThanCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::greaterThanEqualCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::equalCount( 0 );
template< typename T >
unsigned long operation_tracer< T >::notEqualCount( 0 );

#ifdef OPERATION_TRACING
typedef operation_tracer< float > FloatOpTracer;
typedef operation_tracer< double > DoubleOpTracer;
typedef operation_tracer< int > IntOpTracer;
#else
typedef float FloatOpTracer;
typedef double DoubleOpTracer;
typedef int IntOpTracer;
#endif

} // end namespace math

} // end namespace vapor

#endif
