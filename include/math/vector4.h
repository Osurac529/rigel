#ifndef VAPOR_MATH_VECTOR4_H
#define VAPOR_MATH_VECTOR4_H

#include "vector3.h"

namespace vapor
{

namespace math
{

// see this: http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
// for explanation why these are forward declarations
template< typename T > class quaternion;
template< typename T > class matrix4x4;
template< typename T > class vector4;
template< typename T > vector4< T > const operator*(
  vector4< T > const& lhs, matrix4x4< T > const& rhs );
template< typename T > vector4< T > const operator*(
  matrix4x4< T > const& lhs, vector4< T > const& rhs );

// behaves just like a glsl vec4
template< typename T >
class vector4
{
public:

  // intializes all components to value
  explicit vector4( T const& value = T() ) :
    mX( value ), mY( value ), mZ( value ), mW( value )
  {}

  // intialize at least first 2 components, then rest to all zero optionally
  vector4( T const& x, T const& y, T const& z = T(), T const& w = T() ) :
    mX( x ), mY( y ), mZ( z ), mW( w )
  {}

  // intializes the first 2 components from a vec2
  explicit vector4( vector2< T > const& v, T const& z = T(), T const& w = T() ) :
    mX( v.x() ), mY( v.y() ), mZ( z ), mW( w )
  {}

  vector4( vector2< T > const& lhs, vector2< T > const& rhs ) :
    mX( lhs.x() ), mY( lhs.y() ), mZ( rhs.x() ), mW( rhs.y() )
  {}

  // intializes the first 3 components from vec3
  explicit vector4( vector3< T > const& v, T const& w = T() ) :
    mX( v.x() ), mY( v.y() ), mZ( v.z() ), mW( w )
  {}

  // intializes the first 3 components from vec3
  vector4( T const& x, vector3< T > const& v ) :
    mX( x ), mY( v.x() ), mZ( v.y() ), mW( v.z() )
  {}

  //
  // accessors
  //

  T const& operator[]( std::size_t const index ) const
  {
    switch ( index )
    {
      case 0:
        return mX;

      case 1:
        return mY;
    
      case 2:
        return mZ;
    }

    return mW;
  }

  T& operator[]( std::size_t const index )
  {
    // reuse const index operator
    return const_cast< T& >(
      static_cast< vector4< T > const& >( *this )[ index ] );
  }

  vector4< T >& operator=( vector3< T > const& rhs )
  {
    mX = rhs.x();
    mY = rhs.y();
    mZ = rhs.z();
    return *this;
  }

  vector4< T >& operator=( vector2< T > const& rhs )
  {
    mX = rhs.x();
    mY = rhs.y();
    return *this;
  }

  T& x()
  {
    return mX;
  }

  T const& x() const
  {
    return mX;
  }

  T& y()
  {
    return mY;
  }

  T const& y() const
  {
    return mY;
  }

  T& z()
  {
    return mZ;
  }

  T const& z() const
  {
    return mZ;
  }

  T& w()
  {
    return mW;
  }

  T const& w() const
  {
    return mW;
  }

  T& r()
  {
    return mX;
  }

  T const& r() const
  {
    return mX;
  }

  T& g()
  {
    return mY;
  }

  T const& g() const
  {
    return mY;
  }

  T& b()
  {
    return mZ;
  }

  T const& b() const
  {
    return mZ;
  }

  T& a()
  {
    return mW;
  }

  T const& a() const
  {
    return mW;
  }

  T& s()
  {
    return mX;
  }

  T const& s() const
  {
    return mX;
  }

  T& t()
  {
    return mY;
  }

  T const& t() const
  {
    return mY;
  }

  T& p()
  {
    return mZ;
  }

  T const& p() const
  {
    return mZ;
  }

  T& q()
  {
    return mW;
  }

  T const& q() const
  {
    return mW;
  }

  //
  // operations
  //

  T length() const
  {
    return std::sqrt( squaredLength() );
  }

  // no square root
  T squaredLength() const
  {
    return dot( *this );
  }

  T dot( vector4< T > const& v ) const
  {
    return mX * v.mX + mY * v.mY + mZ * v.mZ + mW * v.mW;
  }

  // there is no cross for vec4

  // returns vector in same direction but length is one
  vector4< T > const normalize() const
  {
    return *this * ( T( 1 ) / length() );
  }
  
  //
  // operators
  //

  // scalar add
  friend vector4< T > const operator+( vector4< T > const& lhs, T const& rhs )
  {
    return vector4< T >( lhs.mX + rhs, lhs.mY + rhs, lhs.mZ + rhs, lhs.mW + rhs );
  }

  // scalar add, order swap
  friend vector4< T > const operator+( T const& lhs, vector4< T > const& rhs )
  {
    return rhs + lhs;
  }

  vector4< T >& operator+=( T const& rhs )
  {
    mX += rhs;
    mY += rhs;
    mZ += rhs;
    mW += rhs;
    return *this;
  }

  // vector addition
  friend vector4< T > const operator+( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< T >( lhs.mX + rhs.mX, lhs.mY + rhs.mY, lhs.mZ + rhs.mZ, lhs.mW + rhs.mW );
  }

  vector4< T >& operator+=( vector4< T > const& rhs )
  {
    mX += rhs.mX;
    mY += rhs.mY;
    mZ += rhs.mZ;
    mW += rhs.mW;
    return *this;
  }

  // negation
  vector4< T > const operator-() const
  {
    return vector4< T >( -mX, -mY, -mZ, -mW );
  }

  // scalar subtract
  friend vector4< T > const operator-( vector4< T > const& lhs, T const& rhs )
  {
    return vector4< T >( lhs.mX - rhs, lhs.mY - rhs, lhs.mZ - rhs, lhs.mW - rhs );
  }

  // scalar subtract, order swap
  friend vector4< T > const operator-( T const& lhs, vector4< T > const& rhs )
  {
    return vector4< T >( lhs - rhs.mX, lhs - rhs.mY, lhs - rhs.mZ, lhs - rhs.mW );
  }

  vector4< T >& operator-=( T const& rhs )
  {
    mX -= rhs;
    mY -= rhs;
    mZ -= rhs;
    mW -= rhs;
    return *this;
  }

  // vector subtraction
  friend vector4< T > const operator-( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< T >( lhs.mX - rhs.mX, lhs.mY - rhs.mY, lhs.mZ - rhs.mZ, lhs.mW - rhs.mW );
  }

  vector4< T >& operator-=( vector4< T > const& rhs )
  {
    mX -= rhs.mX;
    mY -= rhs.mY;
    mZ -= rhs.mZ;
    mW -= rhs.mW;
    return *this;
  }

  // scalar division, no other order
  friend vector4< T > const operator/( vector4< T > const& lhs, T const& rhs )
  {
    return lhs * ( 1 / rhs );
  }

  vector4< T >& operator/=( T const& rhs )
  {
    T const oos( 1 / rhs );
    mX *= oos;
    mY *= oos;
    mZ *= oos;
    mW *= oos;
    return *this;
  }

  // scalar multiplication
  friend vector4< T > const operator*( vector4< T > const& lhs, T const& rhs )
  {
    return vector4< T >( lhs.mX * rhs, lhs.mY * rhs, lhs.mZ * rhs, lhs.mW * rhs );
  }

  // scalar multiplication, order swap
  friend vector4< T > const operator*( T const& lhs, vector4< T > const& rhs )
  {
    return rhs * lhs;
  }

  vector4< T >& operator*=( T const& rhs )
  {
    mX *= rhs;
    mY *= rhs;
    mZ *= rhs;
    mW *= rhs;
    return *this;
  }

  // vector multiplication
  friend vector4< T > const operator*( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< T >( lhs.mX * rhs.mX, lhs.mY * rhs.mY, lhs.mZ * rhs.mZ, lhs.mW * rhs.mW );
  }

  vector4< T >& operator*=( vector4< T > const& rhs )
  {
    mX *= rhs.mX;
    mY *= rhs.mY;
    mZ *= rhs.mZ;
    mW *= rhs.mW;
    return *this;
  }

  // vector-matrix multiplication, defined in matrix4x4.h
  // why is the <> at the end of operator*? see this:
  // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
  friend vector4< T > const operator*<>( vector4< T > const& lhs, matrix4x4< T > const& rhs );

  // vector-matrix multiplication, defined in matrix4x4.h
  // why is the <> at the end of operator*? see this:
  // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
  friend vector4< T > const operator*<>( matrix4x4< T > const& lhs, vector4< T > const& rhs );

  // vector-matrix multiplication, defined in matrix4x4.h  
  vector4< T >& operator*=( matrix4x4< T > const& rhs );

  // vector-quaternion multiplication, defined in quaternion.h  
  vector4< T >& operator*=( quaternion< T > const& rhs );

  //
  // comparison operators
  //

  friend vector4< bool > const operator<( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX < rhs.mX, lhs.mY < rhs.mY, lhs.mZ < rhs.mZ, lhs.mW < rhs.mW );
  }

  friend vector4< bool > const operator<=( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX <= rhs.mX, lhs.mY <= rhs.mY, lhs.mZ <= rhs.mZ, lhs.mW <= rhs.mW );
  }

  friend vector4< bool > const operator>( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX > rhs.mX, lhs.mY > rhs.mY, lhs.mZ > rhs.mZ, lhs.mW > rhs.mW );
  }

  friend vector4< bool > const operator>=( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX >= rhs.mX, lhs.mY >= rhs.mY, lhs.mZ >= rhs.mZ, lhs.mW >= rhs.mW );
  }

  friend vector4< bool > const operator==( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX == rhs.mX, lhs.mY == rhs.mY, lhs.mZ == rhs.mZ, lhs.mW == rhs.mW );
  }

  friend vector4< bool > const operator!=( vector4< T > const& lhs, vector4< T > const& rhs )
  {
    return vector4< bool >( lhs.mX != rhs.mX, lhs.mY != rhs.mY, lhs.mZ != rhs.mZ, lhs.mW != rhs.mW );
  }

  //
  // stream operators
  //

  friend std::ostream& operator<<( std::ostream& out, vector4< T > const& rhs )
  {
    return out << rhs.mX << ' ' << rhs.mY << ' ' << rhs.mZ << ' ' << rhs.mW;
  }

  friend std::istream& operator>>( std::istream& in, vector4< T >& rhs )
  {
    return in >> rhs.mX >> rhs.mY >> rhs.mZ >> rhs.mW;
  }
  
private:

  T mX;
  T mY;
  T mZ;
  T mW;
};

//
// glsl non object type functions
//

template< typename T >
T length( vector4< T > const& v )
{
  return v.length();
}

template< typename T >
T distance( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return length( lhs - rhs );
}

template< typename T >
T dot( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs.dot( rhs );
}

// Returns vector in same direction as v, with length of one
template< typename T >
vector4< T > const normalize( vector4< T > const& v )
{
  return v.normalize();
}

template< typename T >
vector4< T > const faceforward( vector4< T > const& N,
                                vector4< T > const& I,
                                vector4< T > const& Nref )
{
  if ( 0 > dot( Nref, I ) )
  {
    return N;
  }

  return –N;
}

// For the incident vector I and surface orientation N,
// returns the reflection direction:
// I – 2 * dot(N, I) * N
// N must already be normalized in order to achieve the
// desired result.
template< typename T >
vector4< T > const reflect( vector4< T > const& I, vector4< T > const& N )
{
  return I – 2 * dot( N, I ) * N;
}

// For the incident vector I and surface normal N, and the
// ratio of indices of refraction eta, return the refraction
// vector.
// The input parameters for the incident vector I and the
// surface normal N must already be normalized to get the
// desired results.
template< typename T >
vector4< T > const refract( vector4< T > const& I, vector4< T > const& N, T eta )
{
  T const k( 1 - eta * eta * ( 1 - dot( N, I ) * dot( N, I ) ) );

  if ( 0 > k  )
  {
    return vector4< T >( 0 );
  }

  return eta * I - ( eta * dot( N, I ) + std::sqrt( k ) ) * N;
}

// Returns the component-wise compare of lhs < rhs.
template< typename T >
vector4< bool > const lessThan( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs < rhs;
}

// Returns the component-wise compare of lhs <= rhs.
template< typename T >
vector4< bool > const lessThanEqual( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs <= rhs;
}

// Returns the component-wise compare of lhs > rhs.
template< typename T >
vector4< bool > const greaterThan( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs > rhs;
}

// Returns the component-wise compare of lhs > rhs.
template< typename T >
vector4< bool > const greaterThanEqual( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs >= rhs;
}

// Returns the component-wise compare of lhs == rhs.
template< typename T >
vector4< bool > const equal( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs == rhs;
}

// Returns the component-wise compare of lhs == rhs.
vector4< bool > const equal( vector4< bool > const lhs, vector4< bool > const rhs )
{
  return lhs == rhs;
}

// Returns the component-wise compare of lhs != rhs.
template< typename T >
vector4< bool > const notEqual( vector4< T > const& lhs, vector4< T > const& rhs )
{
  return lhs != rhs;
}

// Returns the component-wise compare of lhs != rhs.
vector4< bool > const notEqual( vector4< bool > const lhs, vector4< bool > const rhs )
{
  return lhs != rhs;
}

// Returns true if any component of v is true.
bool any( vector4< bool > const& v )
{
  return v.x() || v.y() || v.z() || v.w();
}

// Returns true only if all components of v are true.
bool all( vector4< bool > const& v ) 
{
  return v.x() && v.y() && v.z() && v.w();
}

// Returns the component-wise logical complement of v.
vector4< bool > const not( vector4< bool > const& v )
{
  return vector4< bool >( !v.x(), !v.y(), !v.z(), !v.w() );
}

template< typename T >
vector3< T >::vector3( vector4< T > const& v ) :
  mX( v.x() ), mY( v.y() ), mZ( v.z() )
{}

template< typename T >
vector3< T >& vector3< T >::operator=( vector4< T > const& v )
{
  mX = v.x();
  mY = v.y();
  mZ = v.z();

  return *this;
}

template< typename T >
vector2< T >::vector2( vector4< T > const& v ) :
  mX( v.x() ), mY( v.y() )
{}

template< typename T >
vector2< T >& vector2< T >::operator=( vector4< T > const& rhs )
{
  mX = rhs.x();
  mY = rhs.y();

  return *this;
}

} // end namespace math

} // end namespace vapor

#endif
