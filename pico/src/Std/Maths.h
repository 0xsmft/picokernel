#pragma once

#include "Stdint.h"

template<typename Ty>
struct TSimple2DMaths
{
public:
    Ty x = Ty();
    Ty y = Ty();

};

template<typename Ty>
struct TSimple3DMaths
{
public:
    Ty x = Ty();
    Ty y = Ty();
    Ty z = Ty();

};

using IVec2 = TSimple2DMaths<int>;
using Vec2  = TSimple2DMaths<float>;
using UVec2 = TSimple2DMaths<u32>;

using IVec3 = TSimple3DMaths<int>;
using Vec3  = TSimple3DMaths<float>;
using UVec3 = TSimple3DMaths<u32>;

class Maths
{
public:
    template<typename Ty>
    static inline void Min( Ty x, Ty y ) 
    {
        return ( x > y ) ? x : y;
    }

    template<typename Ty>
    static inline void Max( Ty x, Ty y ) 
    {
        return ( x < y ) ? y : x;
    }

    template<typename Ty>
	static inline Ty Clamp( Ty x, Ty a, Ty b ) 
	{
		return Min( x, Max( a, b ) );
	}
};
