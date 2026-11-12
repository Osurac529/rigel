#ifndef VAPOR_MATH_VECTOR2_H
#define VAPOR_MATH_VECTOR2_H

#include <cmath>
#include <cstdlib>
#include <ostream>
#include <istream>

namespace vapor
{

namespace math
{

// see this: http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
// for explanation why these are forward declarations
template< typename T > class matrix2x2;
template< typename T > class vector4;
template< typename T > class vector3;
template< typename T > class vector2;
template< typename T > vector2< T > const operator*(
  vector2< T > const& lhs, matrix2x2< T > const& rhs );
template< typename T > vector2< T > const operator*(
  matrix2x2< T > const& lhs, vector2< T > const& rhs );

// behaves just like a glsl vec2
template< typename T >
class vector2
{
public:

  // intializes all components to value
  explicit vector2( T const& value = T() ) :
    mX( value ), mY( value )
  {}

  // intialize at least first 2 components, then rest to all zero optionally
  vector2( T const& x, T const& y ) :
    mX( x ), mY( y )
  {}

  // intialize at least first 2 components
  explicit vector2( vector3< T > const& v );

  // intialize at least first 2 components
  explicit vector2( vector4< T > const& v );

  //
  // accessors
  //

  T const& operator[]( std::size_t const index ) const
  {
    switch ( index )
    {
      case 0:
        return mX;
    }

    return mY;
  }

  T& operator[]( std::size_t const index )
  {
    // reuse const index operator
    return const_cast< T& >(
      static_cast< vector2< T > const& >( *this )[ index ] );
  }

  vector2< T >& operator=( vector3< T > const& rhs );

  vector2< T >& operator=( vector4< T > const& rhs );

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

  T dot( vector2< T > const& v ) const
  {
    return mX * v.mX + mY * v.mY;
  }

  // returns vector in same direction but length is one
  vector2< T > const normalize() const
  {
    return *this * ( 1 / length() );
  }
  
  //
  // operators
  //

  // scalar add
  friend vector2< T > const operator+( vector2< T > const& lhs, T const& rhs )
  {
    return vector2< T >( lhs.mX + rhs, lhs.mY + rhs );
  }

  // scalar add, order swap
  friend vector2< T > const operator+( T const& lhs, vector2< T > const& rhs )
  {
    return rhs + lhs;
  }

  // vector addition
  friend vector2< T > const operator+( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< T >( lhs.mX + rhs.mX, lhs.mY + rhs.mY );
  }

  // negation
  vector2< T > const operator-() const
  {
    return vector2< T >( -mX, -mY );
  }

  // scalar subtract
  friend vector2< T > const operator-( vector2< T > const& lhs, T const& rhs )
  {
    return vector2< T >( lhs.mX - rhs, lhs.mY - rhs );
  }

  // scalar subtract, order swap
  friend vector2< T > const operator-( T const& lhs, vector2< T > const& rhs )
  {
    return vector2< T >( lhs - rhs.mX, lhs - rhs.mY );
  }

  // vector subtraction
  friend vector2< T > const operator-( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< T >( lhs.mX - rhs.mX, lhs.mY - rhs.mY );
  }

  // scalar division, no other order
  friend vector2< T > const operator/( vector2< T > const& lhs, T const& rhs )
  {
    return lhs * ( 1 / rhs );
  }

  // scalar multiplication
  friend vector2< T > const operator*( vector2< T > const& lhs, T const& rhs )
  {
    return vector2< T >( lhs.mX * rhs, lhs.mY * rhs );
  }

  // scalar multiplication, order swap
  friend vector2< T > const operator*( T const& lhs, vector2< T > const& rhs )
  {
    return rhs * lhs;
  }

  // vector multiplication
  friend vector2< T > const operator*( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< T >( lhs.mX * rhs.mX, lhs.mY * rhs.mX );
  }


  // vector-matrix multiplication
  // why is the <> at the end of operator*? see this:
  // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
  friend vector2< T > const operator*<>( vector2< T > const& lhs, matrix2x2< T > const& rhs );

  // vector-matrix multiplication
  // why is the <> at the end of operator*? see this:
  // http://www.parashift.com/c++-faq-lite/templates.html#faq-35.16
  friend vector2< T > const operator*<>( matrix2x2< T > const& lhs, vector2< T > const& rhs );

  // vector-matrix multiplication  
  vector2< T >& operator*=( matrix2x2< T > const& rhs );

  //
  // comparison operators
  //

  friend vector2< bool > const operator<( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX < rhs.mX, lhs.mY < rhs.mY );
  }

  friend vector2< bool > const operator<=( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX <= rhs.mX, lhs.mY <= rhs.mY );
  }

  friend vector2< bool > const operator>( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX > rhs.mX, lhs.mY > rhs.mY );
  }

  friend vector2< bool > const operator>=( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX >= rhs.mX, lhs.mY >= rhs.mY );
  }

  friend vector2< bool > const operator==( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX == rhs.mX, lhs.mY == rhs.mY );
  }

  friend vector2< bool > const operator!=( vector2< T > const& lhs, vector2< T > const& rhs )
  {
    return vector2< bool >( lhs.mX != rhs.mX, lhs.mY != rhs.mY );
  }

  //
  // stream operators
  //

  friend std::ostream& operator<<( std::ostream& out, vector2< T > const& rhs )
  {
    return out << rhs.mX << ' ' << rhs.mY;
  }

  friend std::istream& operator>>( std::istream& in, vector2< T >& rhs )
  {
    return in >> rhs.mX >> rhs.mY;
  }
  
private:

  T mX;
  T mY;
};

//
// glsl non object type functions
//

template< typename T >
T length( vector2< T > const& v )
{
  return v.length();
}

template< typename T >
T distance( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return length( lhs - rhs );
}

template< typename T >
T dot( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs.dot( rhs );
}

// Returns vector in same direction as v, with length of one
template< typename T >
vector2< T > const normalize( vector2< T > const& v )
{
  return v.normalize();
}

template< typename T >
vector2< T > const faceforward( vector2< T > const& N,
                                vector2< T > const& I,
                                vector2< T > const& Nref )
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
vector2< T > const reflect( vector2< T > const& I, vector2< T > const& N )
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
vector2< T > const refract( vector2< T > const& I, vector2< T > const& N, T eta )
{
  T const k( 1 - eta * eta * ( 1 - dot( N, I ) * dot( N, I ) ) );

  if ( 0 > k  )
  {
    return vector2< T >( 0 );
  }

  return eta * I - ( eta * dot( N, I ) + std::sqrt( k ) ) * N;
}

// Returns the component-wise compare of lhs < rhs.
template< typename T >
vector2< bool > const lessThan( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs < rhs;
}

// Returns the component-wise compare of lhs <= rhs.
template< typename T >
vector2< bool > const lessThanEqual( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs <= rhs;
}

// Returns the component-wise compare of lhs > rhs.
template< typename T >
vector2< bool > const greaterThan( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs > rhs;
}

// Returns the component-wise compare of lhs > rhs.
template< typename T >
vector2< bool > const greaterThanEqual( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs >= rhs;
}

// Returns the component-wise compare of lhs == rhs.
template< typename T >
vector2< bool > const equal( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs == rhs;
}

// Returns the component-wise compare of lhs == rhs.
vector2< bool > const equal( vector2< bool > const lhs, vector2< bool > const rhs )
{
  return lhs == rhs;
}

// Returns the component-wise compare of lhs != rhs.
template< typename T >
vector2< bool > const notEqual( vector2< T > const& lhs, vector2< T > const& rhs )
{
  return lhs != rhs;
}

// Returns the component-wise compare of lhs != rhs.
vector2< bool > const notEqual( vector2< bool > const lhs, vector2< bool > const rhs )
{
  return lhs != rhs;
}

// Returns true if any component of v is true.
bool any( vector2< bool > const& v )
{
  return v.x() || v.y();
}

// Returns true only if all components of v are true.
bool all( vector2< bool > const& v ) 
{
  return v.x() && v.y();
}

// Returns the component-wise logical complement of v.
vector2< bool > const not( vector2< bool > const& v )
{
  return vector2< bool >( !v.x(), !v.y() );
}

} // end namespace math

} // end namespace vapor

#endif
