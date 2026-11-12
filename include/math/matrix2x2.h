#ifndef VAPOR_MATH_MATRIX2X2_H
#define VAPOR_MATH_MATRIX2X2_H

#include "vector2.h"

namespace vapor
{

namespace math
{

template< typename T > class matrix3x3;
template< typename T > class matrix4x4;

// column major matrix, behaves just like glsl mat2x2
template< typename T >
class matrix2x2
{
public:

  // initialize all the components on the matrix’s diagonal to s,
  // with the remaining components initialized to 0
  explicit matrix2x2( T const& s = T() )
  {
    m[0][0] = m[1][1] = s;
  }

  matrix2x2( T const& m00,       T const& m01,        // first column
             T const& m10 = T(), T const& m11 = T() ) // second column
  {
    m[0] = vector2< T >( m00, m01 );
    m[1] = vector2< T >( m10, m11 );
  }

  matrix2x2( vector2< T > const& c0,  // first column
             vector2< T > const& c1 ) // second column
  {
    m[0] = c0;
    m[1] = c1;
  }

  // defined in matrix3x3.h
  explicit matrix2x2( matrix3x3< T > const& mat3x3 );

  // defined in matrix4x4.h
  explicit matrix2x2( matrix4x4< T > const& mat4x4 );
  
  //
  // accessors
  //

  vector2< T > const& operator[]( std::size_t const column ) const
  {
    return m[column];
  }

  vector2< T >& operator[]( std::size_t const column )
  {
    return m[column];
  }

  // defined in matrix3x3.h
  matrix2x2< T >& operator=( matrix3x3< T > const& rhs );

  // defined in matrix4x4.h
  matrix2x2< T >& operator=( matrix4x4< T > const& rhs );

  //
  // operations
  //
  
  matrix2x2< T > const invert() const
  {
    // step 1. get the matrix of minors (the 2x2 determinants)
    // since this is a 2x2 matrix then the matrix itself is the minors
    matrix2x2< T > inv( *this );

    // step 2. get the cofactor matrix by changing the signs of any
    // element where the row and column number when summed are an odd number   
    inv.m[0][1] = -inv.m[0][1];
    inv.m[1][0] = -inv.m[1][0];
    std::swap( inv.m[0][0], inv.m[1][1] );

    // step 3. get the determinant
    T const det( m[0][0] * m[1][1] - m[1][0] * m[0][1] );

    // a determinant of zero means the matrix cannot be inverted
    if ( T() == det )
    {
      abort();
    }

    // step 4. scale the matrix by the determinant
    inv /= det;

    return inv;
  }

  void identity()
  {
    m[0] = vector2< T >( 1 );
    m[1] = vector2< T >( 0, 1 );
  }

  void rotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector2< T >( cos,  sin );
    m[1] = vector2< T >( -sin, cos );
  }

  matrix2x2< T > const transpose() const
  {
    return matrix2x2< T >( m[0][0], m[1][0],
                           m[0][1], m[1][1] );
  }

  friend matrix2x2< T > const operator+( matrix2x2< T > const& lhs, matrix2x2< T > const& rhs )
  {
    return matrix2x2< T >( lhs.m[0] + rhs.m[0], lhs.m[1] + rhs.m[1] );
  }

  matrix2x2< T >& operator+=( matrix2x2< T > const& rhs )
  {
    m[0] += rhs.m[0];
    m[1] += rhs.m[1];

    return *this;
  }

  friend matrix2x2< T > const operator-( matrix2x2< T > const& lhs, matrix2x2< T > const& rhs )
  {
    return matrix2x2< T >( lhs.m[0] - rhs.m[0], lhs.m[1] - rhs.m[1] );
  }

  matrix2x2< T > const operator-() const
  {
    return matrix2x2< T >( -m[0], -m[1] );
  }

  matrix2x2< T >& operator-=( matrix2x2< T > const& rhs )
  {
    m[0] -= rhs.m[0];
    m[1] -= rhs.m[1];

    return *this;
  }

  friend matrix2x2< T > const operator*( matrix2x2< T > const& lhs, T const& rhs )
  {
    return matrix2x2< T >( lhs.m[0] * rhs, lhs.m[1] * rhs );
  }

  friend matrix2x2< T > const operator*( T const& lhs, matrix2x2< T > const& rhs )
  {
    return rhs * lhs;
  }

  matrix2x2< T >& operator*=( T const& rhs )
  {
    m[0] *= rhs;
    m[1] *= rhs;

    return *this;
  }

  friend matrix2x2< T > const operator*( matrix2x2< T > const& lhs, matrix2x2< T > const& rhs )
  {
    // lhst is lhs transposed
    matrix2x2< T > const lhst( lhs.transpose() );

    return matrix2x2< T >( lhst[0].dot( rhs.m[0] ), lhst[0].dot( rhs.m[1] ),
                           lhst[1].dot( rhs.m[0] ), lhst[1].dot( rhs.m[1] ) );
  }

  matrix2x2< T >& operator*=( matrix2x2< T > const& rhs )
  {
    return *this = *this * rhs;
  }

  friend matrix2x2< T > const operator/( matrix2x2< T > const& lhs, T const& rhs )
  {
    return ( T( 1 ) / rhs ) * lhs;
  }

  matrix2x2< T >& operator/=( T const& rhs )
  {
    return *this = *this / rhs;
  }

private:

  vector2< T > m[2];
};

template< typename T >
vector2< T > const operator*( vector2< T > const& lhs, matrix2x2< T > const& rhs )
{
  return vector2< T >( lhs.dot( rhs[0] ), lhs.dot( rhs[1] ) );
}

template< typename T >
vector2< T > const operator*( matrix2x2< T > const& lhs, vector2< T > const& rhs )
{
  return rhs * lhs.transpose();
}

template< typename T >
vector2< T >& vector2< T >::operator*=( matrix2x2< T > const& rhs )
{
  return *this = *this * rhs;
}

} // end of namespace math

} // end of namespace vapor

#endif
