#ifndef VAPOR_MATH_MATRIX3X3_H
#define VAPOR_MATH_MATRIX3X3_H

#include "vector3.h"
#include "matrix2x2.h"

namespace vapor
{

namespace math
{

template< typename T > class quaternion;

// column major matrix, behaves just like glsl mat3x3
template< typename T >
class matrix3x3
{
public:

  // initialize all the components on the matrix’s diagonal to s,
  // with the remaining components initialized to 0
  explicit matrix3x3( T const& s = T() )
  {
    m[0][0] = m[1][1] = m[2][2] = s;
  }

  matrix3x3( T const& m00,       T const& m01,       T const& m02 = T(),  // first column
             T const& m10 = T(), T const& m11 = T(), T const& m12 = T(),  // second column
             T const& m20 = T(), T const& m21 = T(), T const& m22 = T() ) // third column
  {
    m[0] = vector3< T >( m00, m01, m02 );
    m[1] = vector3< T >( m10, m11, m12 );
    m[2] = vector3< T >( m20, m21, m22 );
  }

  matrix3x3( vector3< T > const& c0,  // first column
             vector3< T > const& c1,  // second column
             vector3< T > const& c2 ) // third column
  {
    m[0] = c0;
    m[1] = c1;
    m[2] = c2;
  }

  // defined in matrix4x4.h
  explicit matrix3x3( matrix4x4< T > const& mat4x4 );

  explicit matrix3x3( matrix2x2< T > const& mat2x2 )
  {
    m[0] = mat2x2[0];
    m[1] = mat2x2[1];
    m[2] = vector3< T >( 0, 0, 1 );
  }
  
  // converts a quaternion to 3x3 matrix, not explicit
  // defined in quaternion.h
  matrix3x3( quaternion< T > const& q );

  //
  // accessors
  //

  vector3< T > const& operator[]( std::size_t const column ) const
  {
    return m[column];
  }

  vector3< T >& operator[]( std::size_t const column )
  {
    return m[column];
  }

  // defined in matrix4x4
  matrix3x3< T >& operator=( matrix4x4< T > const& rhs );

  matrix3x3< T >& operator=( matrix2x2< T > const& rhs )
  {
    m[0] = rhs[0];
    m[1] = rhs[1];
    m[2] = vector3< T >( T(), T(), 1 );

    return *this;
  }

  //
  // operations
  //

  matrix3x3< T > const invert() const
  {
    // step 1. get the matrix of minors (the 2x2 determinants)
    // since this is a 3x3 matrix there are 9 minors, we also
    // get the cofactor matrix in this step by changing the order of
    // subtraction for any row and column indices that sum to an odd
    // number, these are (column, row): (1,0) (0,1) (1,2) (2,1)
    matrix3x3< T > inv;
    inv.m[0][0] = m[1][1] * m[2][2] - m[2][1] * m[1][2];
    inv.m[0][1] = m[2][0] * m[1][2] - m[1][0] * m[2][2];
    inv.m[0][2] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
    inv.m[1][0] = m[2][1] * m[0][2] - m[0][1] * m[2][2];
    inv.m[1][1] = m[0][0] * m[2][2] - m[2][0] * m[0][2];
    inv.m[1][2] = m[2][0] * m[0][1] - m[0][0] * m[2][1];
    inv.m[2][0] = m[0][1] * m[1][2] - m[1][1] * m[0][2];
    inv.m[2][1] = m[1][0] * m[0][2] - m[0][0] * m[1][2];
    inv.m[2][2] = m[0][0] * m[1][1] - m[1][0] * m[0][1];

    // step 2. get the determinant by taking any row or column from the
    // cofactor matrix and dot it with the same row or column in the
    // original matrix, we will use the first column
    T const det( m[0].dot( inv.m[0] ) );

    // a determinant of zero means the matrix cannot be inverted
    if ( T() == det )
    {
      abort();
    }

    // step 3. get the adjoint matrix which is the transpose of the cofactor matrix
    inv = inv.transpose();
    
    // step 4. scale the matrix by the determinant
    inv /= det;

    return inv;
  }

  void identity()
  {
    m[0] = vector3< T >( 1 );
    m[1] = vector3< T >( 0, 1 );
    m[2] = vector3< T >( 0, 0, 1 );
  }

  void xrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( 1, 0,    0 );
    m[1] = vector3< T >( 0, cos,  sin );
    m[2] = vector3< T >( 0, -sin, cos );
  }

  void yrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( cos, 0, -sin );
    m[1] = vector3< T >( 0,   1, 0 );
    m[2] = vector3< T >( sin, 0, cos );
  }

  void zrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( cos,  sin, 0 );
    m[1] = vector3< T >( -sin, cos, 0 );
    m[2] = vector3< T >( 0,    0,   1 );
  }

  // rotate about arbitrary axis
  void rotate( vector3< T > const& axis, T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    T const omcos( T( 1 ) - cos );
    T const xsq( axis.x() * axis.x() );
    T const ysq( axis.y() * axis.y() );
    T const zsq( axis.z() * axis.z() );
    T const xy( axis.x() * axis.y() );
    T const xz( axis.x() * axis.z() );
    T const yz( axis.y() * axis.z() );
    T const zsin( axis.z() * sin );
    T const ysin( axis.y() * sin );
    T const xsin( axis.x() * sin );

    m[0] = vector3< T >( xsq + ( T( 1 ) - xsq ) * cos,
                         xy * omcos + zsin,
                         xz * omcos - ysin );
    m[1] = vector3< T >( xy * omcos - zsin,
                         ysq + ( T( 1 ) - ysq ) * cos,
                         yz * omcos + xsin );
    m[2] = vector3< T >( xz * omcos + ysin,
                         yz * omcos - xsin,
                         zsq + ( T( 1 ) - zsq ) * cos );
  }

  matrix3x3< T > const transpose() const
  {
    return matrix3x3< T >( m[0][0], m[1][0], m[2][0],
                           m[0][1], m[1][1], m[2][1],
                           m[0][2], m[1][2], m[2][2] );
  }

  friend matrix3x3< T > const operator+( matrix3x3< T > const& lhs, matrix3x3< T > const& rhs )
  {
    return matrix3x3< T >( lhs.m[0] + rhs.m[0], lhs.m[1] + rhs.m[1], lhs.m[2] + rhs.m[2] );
  }

  matrix3x3< T >& operator+=( matrix3x3< T > const& rhs )
  {
    m[0] += rhs.m[0];
    m[1] += rhs.m[1];
    m[2] += rhs.m[2];

    return *this;
  }

  friend matrix3x3< T > const operator-( matrix3x3< T > const& lhs, matrix3x3< T > const& rhs )
  {
    return matrix3x3< T >( lhs.m[0] - rhs.m[0], lhs.m[1] - rhs.m[1], lhs.m[2] - rhs.m[2] );
  }

  matrix3x3< T > const operator-() const
  {
    return matrix3x3< T >( -m[0], -m[1], -m[2] );
  }

  matrix3x3< T >& operator-=( matrix3x3< T > const& rhs )
  {
    m[0] -= rhs.m[0];
    m[1] -= rhs.m[1];
    m[2] -= rhs.m[2];

    return *this;
  }

  friend matrix3x3< T > const operator*( matrix3x3< T > const& lhs, T const& rhs )
  {
    return matrix3x3< T >( lhs.m[0] * rhs, lhs.m[1] * rhs, lhs.m[2] * rhs );
  }

  friend matrix3x3< T > const operator*( T const& lhs, matrix3x3< T > const& rhs )
  {
    return rhs * lhs;
  }

  matrix3x3< T >& operator*=( T const& rhs )
  {
    m[0] *= rhs;
    m[1] *= rhs;
    m[2] *= rhs;

    return *this;
  }

  friend matrix3x3< T > const operator*( matrix3x3< T > const& lhs, matrix3x3< T > const& rhs )
  {
    // lhst is lhs transposed
    matrix3x3< T > const lhst( lhs.transpose() );

    return matrix3x3< T >( lhst[0].dot( rhs.m[0] ), lhst[0].dot( rhs.m[1] ), lhst[0].dot( rhs.m[2] ),
                           lhst[1].dot( rhs.m[0] ), lhst[1].dot( rhs.m[1] ), lhst[1].dot( rhs.m[2] ),
                           lhst[2].dot( rhs.m[0] ), lhst[2].dot( rhs.m[1] ), lhst[2].dot( rhs.m[2] ) );
  }

  matrix3x3< T >& operator*=( matrix3x3< T > const& rhs )
  {
    return *this = *this * rhs;
  }

  friend matrix3x3< T > const operator/( matrix3x3< T > const& lhs, T const& rhs )
  {
    return ( T( 1 ) / rhs ) * lhs;
  }

  matrix3x3< T >& operator/=( T const& rhs )
  {
    return *this = *this * ( T( 1 ) / rhs );
  }

private:

  vector3< T > m[3];
};

template< typename T >
vector3< T > const operator*( vector3< T > const& lhs, matrix3x3< T > const& rhs )
{
  return vector3< T >( lhs.dot( rhs[0] ), lhs.dot( rhs[1] ), lhs.dot( rhs[2] ) );
}

template< typename T >
vector3< T > const operator*( matrix3x3< T > const& lhs, vector3< T > const& rhs )
{
  return rhs * lhs.transpose();
}

template< typename T >
vector3< T >& vector3< T >::operator*=( matrix3x3< T > const& rhs )
{
  return *this = *this * rhs;
}

template< typename T >
matrix2x2< T >::matrix2x2( matrix3x3< T > const& mat3x3 )
{
  m[0] = mat3x3[0];
  m[1] = mat3x3[1];
}

template< typename T >
matrix2x2< T >& matrix2x2< T >::operator=( matrix3x3< T > const& rhs )
{
  m[0] = rhs[0];
  m[1] = rhs[1];

  return *this;
}

} // end of namespace math

} // end of namespace vapor

#endif
