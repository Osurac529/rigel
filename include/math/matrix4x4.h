#ifndef VAPOR_MATH_MATRIX4X4_H
#define VAPOR_MATH_MATRIX4X4_H

#include "vector4.h"
#include "matrix3x3.h"

namespace vapor
{

namespace math
{

// column major matrix, behaves just like glsl mat4x4
template< typename T >
class matrix4x4
{
public:

  // initialize all the components on the matrix’s diagonal to s,
  // with the remaining components initialized to 0
  explicit matrix4x4( T const& s = T() )
  {
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = s;
  }

  matrix4x4( T const& m00,       T const& m01,       T const& m02 = T(), T const& m03 = T(),  // first column
             T const& m10 = T(), T const& m11 = T(), T const& m12 = T(), T const& m13 = T(),  // second column
             T const& m20 = T(), T const& m21 = T(), T const& m22 = T(), T const& m23 = T(),  // third column
             T const& m30 = T(), T const& m31 = T(), T const& m32 = T(), T const& m33 = T() ) // fourth column
  {
    m[0] = vector4< T >( m00, m01, m02, m03 );
    m[1] = vector4< T >( m10, m11, m12, m13 );
    m[2] = vector4< T >( m20, m21, m22, m23 );
    m[3] = vector4< T >( m30, m31, m32, m33 );
  }

  matrix4x4( vector4< T > const& c0,  // first column
             vector4< T > const& c1,  // second column
             vector4< T > const& c2,  // third column
             vector4< T > const& c3 ) // fourth column    
  {
    m[0] = c0;
    m[1] = c1;
    m[2] = c2;
    m[3] = c3;
  }

  // initializes the upper left 2x2 portion of the matrix with the
  // 2x2 matrix passed as parameter
  explicit matrix4x4( matrix2x2< T > const& mat2x2 )
  {
    m[0] = mat2x2[0];
    m[1] = mat2x2[1];
    m[2] = vector4< T >( T(), T(), 1, T() );
    m[3] = vector4< T >( T(), T(), T(), 1 );
  }

  // initializes the upper left 3x3 portion of the matrix with the
  // 3x3 matrix passed as parameter
  explicit matrix4x4( matrix3x3< T > const& mat3x3 )
  {
    m[0] = mat3x3[0];
    m[1] = mat3x3[1];
    m[2] = mat3x3[2];
    m[3] = vector4< T >( T(), T(), T(), 1 );
  }
  
  //
  // accessors
  //

  vector4< T > const& operator[]( std::size_t const column ) const
  {
    return m[column];
  }

  vector4< T >& operator[]( std::size_t const column )
  {
    return m[column];
  }

  matrix4x4< T >& operator=( matrix2x2< T > const& rhs )
  {
    m[0] = rhs[0];
    m[1] = rhs[1];
    m[2] = vector4< T >( T(), T(), 1, T() );
    m[3] = vector4< T >( T(), T(), T(), 1 );

    return *this;
  }

  matrix4x4< T >& operator=( matrix3x3< T > const& rhs )
  {
    m[0] = rhs[0];
    m[1] = rhs[1];
    m[2] = rhs[2];
    m[3] = vector4< T >( T(), T(), T(), 1 );

    return *this;
  }

  //
  // operations
  //

  matrix4x4< T > const invert() const
  {
    // TODO: finish this

    // step 1. get the matrix of minors (the 2x2 determinants)
    // since this is a 4x4 matrix there are 16 minors, we also
    // get the cofactor matrix in this step by changing the order of
    // subtraction for any row and column indices that sum to an odd
    // number, these are (column, row): 
    //   (1,0) (3,0) (0,1) (2,1) (1,2) (3,2) (0,3) (2,3)
    matrix4x4< T > inv;
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
    m[0] = vector4< T >( 1 );
    m[1] = vector4< T >( 0, 1 );
    m[2] = vector4< T >( 0, 0, 1 );
    m[3] = vector4< T >( 0, 0, 0, 1 );
  }

  // only changes upper left 3x3 part of matrix
  void xrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( 1, 0,    0 );
    m[1] = vector3< T >( 0, cos,  sin );
    m[2] = vector3< T >( 0, -sin, cos );
  }

  // only changes upper left 3x3 part of matrix
  void yrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( cos, 0, -sin );
    m[1] = vector3< T >( 0,   1, 0 );
    m[2] = vector3< T >( sin, 0, cos );
  }

  // only changes upper left 3x3 part of matrix
  void zrotate( T const& radians )
  {
    T const cos( std::cos( radians ) );
    T const sin( std::sin( radians ) );
    m[0] = vector3< T >( cos,  sin, 0 );
    m[1] = vector3< T >( -sin, cos, 0 );
    m[2] = vector3< T >( 0,    0,   1 );
  }

  // rotate about arbitrary axis, only changes upper left 3x3 part of matrix
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

  matrix4x4< T > const transpose() const
  {
    return matrix4x4< T >( m[0][0], m[1][0], m[2][0], m[3][0], 
                           m[0][1], m[1][1], m[2][1], m[3][1], 
                           m[0][2], m[1][2], m[2][2], m[3][2], 
                           m[0][3], m[1][3], m[2][3], m[3][3] );
  }

  friend matrix4x4< T > const operator+( matrix4x4< T > const& lhs, matrix4x4< T > const& rhs )
  {
    return matrix4x4< T >( lhs.m[0] + rhs.m[0], lhs.m[1] + rhs.m[1], lhs.m[2] + rhs.m[2], lhs.m[3] + rhs.m[3] );
  }

  matrix4x4< T >& operator+=( matrix4x4< T > const& rhs )
  {
    m[0] += rhs.m[0];
    m[1] += rhs.m[1];
    m[2] += rhs.m[2];
    m[3] += rhs.m[3];

    return *this;
  }

  friend matrix4x4< T > const operator-( matrix4x4< T > const& lhs, matrix4x4< T > const& rhs )
  {
    return matrix4x4< T >( lhs.m[0] - rhs.m[0], lhs.m[1] - rhs.m[1], lhs.m[2] - rhs.m[2], lhs.m[3] - rhs.m[3] );
  }

  matrix4x4< T > const operator-() const
  {
    return matrix4x4< T >( -m[0], -m[1], -m[2], -m[3] );
  }

  matrix4x4< T >& operator-=( matrix4x4< T > const& rhs )
  {
    m[0] -= rhs.m[0];
    m[1] -= rhs.m[1];
    m[2] -= rhs.m[2];
    m[3] -= rhs.m[3];

    return *this;
  }

  friend matrix4x4< T > const operator*( matrix4x4< T > const& lhs, T const& rhs )
  {
    return matrix4x4< T >( lhs.m[0] * rhs, lhs.m[1] * rhs, lhs.m[2] * rhs, lhs.m[3] * rhs );
  }

  friend matrix4x4< T > const operator*( T const& lhs, matrix4x4< T > const& rhs )
  {
    return rhs * lhs;
  }

  matrix4x4< T >& operator*=( T const& rhs )
  {
    m[0] *= rhs;
    m[1] *= rhs;
    m[2] *= rhs;
    m[3] *= rhs;

    return *this;
  }

  friend matrix4x4< T > const operator*( matrix4x4< T > const& lhs, matrix4x4< T > const& rhs )
  {
    // lhst is lhs transposed
    matrix4x4< T > const lhst( lhs.transpose() );

    return matrix4x4< T >( lhst[0].dot( rhs.m[0] ), lhst[0].dot( rhs.m[1] ), lhst[0].dot( rhs.m[2] ), lhst[0].dot( rhs.m[3] ),
                           lhst[1].dot( rhs.m[0] ), lhst[1].dot( rhs.m[1] ), lhst[1].dot( rhs.m[2] ), lhst[1].dot( rhs.m[3] ),
                           lhst[2].dot( rhs.m[0] ), lhst[2].dot( rhs.m[1] ), lhst[2].dot( rhs.m[2] ), lhst[2].dot( rhs.m[3] ),
                           lhst[3].dot( rhs.m[0] ), lhst[3].dot( rhs.m[1] ), lhst[3].dot( rhs.m[2] ), lhst[3].dot( rhs.m[3] ) );
  }

  matrix4x4< T >& operator*=( matrix4x4< T > const& rhs )
  {
    *this = *this * rhs;
    return *this;
  }

private:

  vector4< T > m[4];
};

template< typename T >
vector4< T > const operator*( vector4< T > const& lhs, matrix4x4< T > const& rhs )
{
  return vector4< T >( lhs.dot( rhs[0] ), lhs.dot( rhs[1] ), lhs.dot( rhs[2] ), lhs.dot( rhs[3] ) );
}

template< typename T >
vector4< T > const operator*( matrix4x4< T > const& lhs, vector4< T > const& rhs )
{
  return rhs * lhs.transpose();
}

template< typename T >
vector4< T >& vector4< T >::operator*=( matrix4x4< T > const& rhs )
{
  return *this = *this * rhs;
}

template< typename T >
matrix2x2< T >::matrix2x2( matrix4x4< T > const& mat4x4 )
{
  m[0] = mat4x4[0];
  m[1] = mat4x4[1];
}

template< typename T >
matrix2x2< T >& matrix2x2< T >::operator=( matrix4x4< T > const& rhs )
{
  m[0] = rhs[0];
  m[1] = rhs[1];

  return *this;
}

template< typename T >
matrix3x3< T >::matrix3x3( matrix4x4< T > const& mat4x4 )
{
  m[0] = mat4x4[0];
  m[1] = mat4x4[1];
  m[2] = mat4x4[2];
}

template< typename T >
matrix3x3< T >& matrix3x3< T >::operator=( matrix4x4< T > const& rhs )
{
  m[0] = rhs[0];
  m[1] = rhs[1];
  m[2] = rhs[2];

  return *this;
}

} // end of namespace math

} // end of namespace vapor

#endif
