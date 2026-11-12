#ifndef VAPOR_MATH_QUATERNION_H
#define VAPOR_MATH_QUATERNION_H

#include "vector4.h"
#include "matrix3x3.h"

namespace vapor
{

namespace math
{

template< typename T >
class quaternion
{
public:

  explicit quaternion( T const& x = T() ) :
    mV( x, x, x ),
    mW( x )
  {}

  quaternion( T const& x, T const& y, T const& z = T(), T const& w = T() ) :
    mV( x, y, z ),
    mW( w )
  {}

  quaternion( vector3< T > const& v, T const& w ) :
    mV( v ),
    mW( w )
  {}

  // converts 3x3 matrix to quaternion, not explicit
  quaternion( matrix3x3< T > const& m )
  {
    mW = T( 0.5 ) * std::sqrt( m[0][0] + m[1][1] + m[2][2] );
    T const ooquadw( T( 1 ) / ( 4 * mW ) );
    mV = vector3< T >( ( m[1][2] - m[2][1] ) * ooquadw,
                       ( m[2][0] - m[0][2] ) * ooquadw,
                       ( m[0][1] - m[1][0] ) * ooquadw );
  }

  //
  // accessors
  //

  T& operator[]( std::size_t index )
  {
    switch ( index )
    {
      case 0:
        return mV.x();

      case 1:
        return mV.y();

      case 2:
        return mV.z();
    }

    return mW;
  }

  T const& operator[]( std::size_t index ) const
  {
    switch ( index )
    {
      case 0:
        return mV.x();

      case 1:
        return mV.y();

      case 2:
        return mV.z();
    }

    return mW;
  }

  T& x()
  {
    return mV.x();
  }

  T const& x() const
  {
    return mV.x();
  }

  T& y()
  {
    return mV.y();
  }

  T const& y() const
  {
    return mV.y();
  }

  T& z()
  {
    return mV.z();
  }

  T const& z() const
  {
    return mV.z();
  }

  T& w()
  {
    return mW;
  }

  T const& w() const
  {
    return mW;
  }

  //
  // operations
  //

  T magnitude() const
  {
    return std::sqrt( norm() );
  }

  T norm() const
  {
    return dot( *this );
  }

  T dot( quaternion< T > const& rhs ) const
  {
    return mV.dot( rhs.mV ) + mW * rhs.mW;
  }

  quaternion< T > const normalize() const
  {
    return *this * ( T( 1 ) / magnitude() );
  }

  quaternion< T > const conjugate() const
  {
    return quaternion< T >( -mV, mW );
  }

  quaternion< T > const invert() const
  {    
    // note: if this quaternion is a unit quaternion (normalized) then the inverse
    // is just the conjugate
    return ( T( 1 ) / norm() ) * conjugate();
  }

  void identity()
  {
    mV = vector3< T >();
    mW = T( 1 );
  }

  // rotate about arbitrary axis
  void rotate( vector3< T > axis, T const& radians )
  {
    axis = axis.normalize();
    T const sina( std::sin( radians * T( 0.5 ) ) );
    T const cosa( std::cos( radians * T( 0.5 ) ) );
    mV.x() = axis.x() * sina;
    mV.y() = axis.y() * sina;
    mV.z() = axis.z() * sina;
    mW = cosa;
  }

  //
  // operators
  //

  // quaternaion-quaternion multiplication
  friend quaternion< T > const operator*( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return quaternion< T >( lhs.mW * rhs.mV + rhs.mW * lhs.mV + lhs.mV.cross( rhs.mV ), 
      lhs.mW * rhs.mW - lhs.mV.dot( rhs.mV ) );
  }

  quaternion< T >& operator*=( quaternion< T > const& rhs )
  {
    return *this = *this * rhs;
  }

  // quaternaion-scalar multiplication
  friend quaternion< T > const operator*( T const& lhs, quaternion< T > const& rhs )
  {
    return quaternion< T >( lhs * rhs.mV, lhs * rhs.mW );
  }

  // quaternaion-scalar multiplication, commutative
  friend quaternion< T > const operator*( quaternion< T > const& lhs, T const& rhs )
  {
    return rhs * lhs;
  }

  quaternion< T >& operator*=( T const& rhs )
  {
    return *this = *this * rhs;
  }

  // quaternaion-vector multiplication
  friend vector4< T > const operator*( vector4< T > const& lhs, quaternion< T > const& rhs )
  {
    // assumes this is a unit quaternion
    quaternion< T > const q( rhs * quaternion< T >( lhs.x(), lhs.y(), lhs.z(), lhs.w() ) * rhs.conjugate() );
    return vector4< T >( q.mV, q.mW );
  }

  // quaternaion-vector multiplication, commutative
  friend vector4< T > const operator*( quaternion< T > const& lhs, vector4< T > const& rhs )
  {
    return rhs * lhs;
  }

  // quaternaion-quaternion addition
  friend quaternion< T > const operator+( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return quaternion< T >( lhs.mV + rhs.mV, lhs.mW + rhs.mW );
  }

  quaternion< T >& operator+=( T const& rhs )
  {
    return *this = *this + rhs;
  }

  // quaternaion-quaternion subtraction
  friend quaternion< T > const operator-( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return quaternion< T >( lhs.mV - rhs.mV, lhs.mW - rhs.mW );
  }

  quaternion< T >& operator-=( T const& rhs )
  {
    return *this = *this - rhs;
  }

  // quaternaion-scalar division
  friend quaternion< T > const operator/( quaternion< T > const& lhs, T const& rhs )
  {
    return ( 1 / rhs ) * lhs;
  }

  quaternion< T >& operator/=( T const& rhs )
  {
    return *this = *this / rhs;
  }

  // quaternion negation
  quaternion< T > const operator-()
  {
    return quaternion< T >( -mV, -mW );
  }

  //
  // comparison operators
  //

  friend vector4< bool > const operator<( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX < rhs.mX, lhs.mY < rhs.mY, lhs.mZ < rhs.mZ, lhs.mW < rhs.mW );
  }

  friend vector4< bool > const operator<=( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX <= rhs.mX, lhs.mY <= rhs.mY, lhs.mZ <= rhs.mZ, lhs.mW <= rhs.mW );
  }

  friend vector4< bool > const operator>( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX > rhs.mX, lhs.mY > rhs.mY, lhs.mZ > rhs.mZ, lhs.mW > rhs.mW );
  }

  friend vector4< bool > const operator>=( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX >= rhs.mX, lhs.mY >= rhs.mY, lhs.mZ >= rhs.mZ, lhs.mW >= rhs.mW );
  }

  friend vector4< bool > const operator==( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX == rhs.mX, lhs.mY == rhs.mY, lhs.mZ == rhs.mZ, lhs.mW == rhs.mW );
  }

  friend vector4< bool > const operator!=( quaternion< T > const& lhs, quaternion< T > const& rhs )
  {
    return vector4< bool >( lhs.mX != rhs.mX, lhs.mY != rhs.mY, lhs.mZ != rhs.mZ, lhs.mW != rhs.mW );
  }

  //
  // stream operators
  //

  friend std::ostream& operator<<( std::ostream& out, quaternion< T > const& q )
  {
    return out << q.mV << ' ' << q.mW;
  }

  friend std::istream& operator>>( std::istream& in, quaternion< T >& q )
  {
    return in >> q.mV >> q.mW;
  }

private:

  vector3< T > mV;
  T mW;
};

// t must be between 0 and 1 inclusively
template< typename T >
quaternion< T > const slerp( quaternion< T > const& lhs, quaternion< T > const& rhs, T const& t )
{
  T const theta( std::acos( lhs.dot( rhs ) ) );
  T const oosint( T( 1 ) / T( std::sin( theta ) ) );
  return ( T( std::sin( theta * ( T( 1 ) - t ) ) ) * oosint * lhs ) + 
         ( T( std::sin( theta * t ) ) * oosint * rhs );
}

template< typename T >
matrix3x3< T >::matrix3x3( quaternion< T > const& q )
{
  // if we know the quaternion is a unit quaternion then s = 2.
  T const s( T( 2 ) / q.norm() );
  T const xy( q.x() * q.y() );
  T const xz( q.x() * q.z() );
  T const yz( q.y() * q.z() );
  T const wx( q.w() * q.x() );
  T const wy( q.w() * q.y() );
  T const wz( q.w() * q.z() );
  T const xsq( q.x() * q.x() );
  T const ysq( q.y() * q.y() );
  T const zsq( q.z() * q.z() );

  m[0] = vector3< T >( T( 1 ) - s * ( ysq + zsq ), s * ( xy + wz ), s * ( xz - wy ) );
  m[1] = vector3< T >( s * ( xy - wz ), T( 1 ) - s * ( xsq + zsq ), s * ( yz + wx ) );
  m[2] = vector3< T >( s * ( xz + wy ), s * ( yz - wx ), T( 1 ) - s * ( xsq + ysq ) );
}

template< typename T >
vector4< T >& vector4< T >::operator*=( quaternion< T > const& rhs )
{
  return *this = *this * rhs;
}

} // end of namespace math

} // end of namespace vapor

#endif
