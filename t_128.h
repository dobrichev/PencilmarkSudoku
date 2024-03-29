/*
 * t_128.h
 *
 *  Created on: May 13, 2014
 *      Author: Mladen Dobrichev
 */

//wrapper to 128-bit SIMD x86 instructions

#ifndef T_128_H_INCLUDED

#define T_128_H_INCLUDED

#ifdef   _MSC_VER
	#include <intrin.h>
#else
	#include <immintrin.h>
#endif
#include <limits.h>

#ifdef   _MSC_VER
	#define _popcnt64(a) __popcnt64(a)
	#define _popcnt32(a) __popcnt32(a)
#else
	#define _popcnt64(a) __builtin_popcountll(a)
	#define _popcnt32(a) __builtin_popcount(a)
#endif

#ifndef _MSC_VER
	//assume every compiler but MS is C99 compliant and has inttypes
	#include <inttypes.h>
#else
   //typedef signed __int8     int8_t;
   //typedef signed __int16    int16_t;
   //typedef signed __int32    int32_t;
   typedef unsigned __int8   uint8_t;
   typedef unsigned __int16  uint16_t;
   typedef unsigned __int32  uint32_t;
   //typedef signed __int64       int64_t;
   typedef unsigned __int64     uint64_t;
#endif

typedef union t_128 {
    ////unsigned __int64    m128i_u64[2];
    uint64_t    m128i_u64[2];
    uint8_t     m128i_u8[16];
    uint16_t    m128i_u16[8];
    uint32_t    m128i_u32[4];
	__m128i				m128i_m128i;
    //__int64             m128i_i64[2];
	//__m128d				m128i_m128d;
} t_128;

extern const t_128 bitSet[128];
//extern const t_128 maskLSB[129];
//extern const t_128 mask81;
//extern const t_128 mask108;
//extern const t_128 mask109;

struct bm128 {
	t_128 bitmap128;
	bm128() {}
	bm128(const bm128 &v) {bitmap128.m128i_m128i = v.bitmap128.m128i_m128i;}
	bm128(const __m128i &v) {bitmap128.m128i_m128i = v;}
	bm128(const t_128 &v) {bitmap128.m128i_m128i = v.m128i_m128i;}
	inline bool isSubsetOf(const bm128 &s) const {return 0 != _mm_testc_si128(s.bitmap128.m128i_m128i, bitmap128.m128i_m128i);}
	inline bool operator== (const bm128& r) const {return 0xFFFF == _mm_movemask_epi8(_mm_cmpeq_epi8(bitmap128.m128i_m128i, r.bitmap128.m128i_m128i));}
	//inline bool operator== (const bm128& r) const {return ((*this).isSubsetOf(r) & r.isSubsetOf(*this));}
	//inline bool operator== (const bm128& r) const {return bitmap128.m128i_u64[0] == r.bitmap128.m128i_u64[0] && bitmap128.m128i_u64[1] == r.bitmap128.m128i_u64[1];}
	inline void operator&= (const bm128& r) {bitmap128.m128i_m128i = _mm_and_si128(bitmap128.m128i_m128i, r.bitmap128.m128i_m128i);}
	inline void operator|= (const bm128& r) {bitmap128.m128i_m128i = _mm_or_si128(bitmap128.m128i_m128i, r.bitmap128.m128i_m128i);}
	inline void operator^= (const bm128& r) {bitmap128.m128i_m128i = _mm_xor_si128(bitmap128.m128i_m128i, r.bitmap128.m128i_m128i);}
	inline bool isDisjoint(const bm128& r) const {return 0 != _mm_testz_si128(r.bitmap128.m128i_m128i, bitmap128.m128i_m128i);}
	inline int mask8() const {return _mm_movemask_epi8(bitmap128.m128i_m128i);}
	inline uint64_t toInt64() const {return _mm_cvtsi128_si64(bitmap128.m128i_m128i);}
	//inline uint64_t toInt64() const {return _mm_extract_epi64(bitmap128.m128i_m128i, 0);}
	inline uint64_t toInt64_1() const {return _mm_extract_epi64(bitmap128.m128i_m128i, 1);}
	inline bool operator <(const bm128& r) const {if(toInt64() < r.toInt64()) return true; if(toInt64() > r.toInt64()) return false; return toInt64_1() < r.toInt64_1();}
	inline int lge(const bm128& r) const {int d = toInt64() < r.toInt64() ? -1 : (toInt64() == r.toInt64() ? 0 : 1); return d ? d : toInt64_1() < r.toInt64_1() ? -1 : (toInt64_1() == r.toInt64_1() ? 0 : 1);} // <=> operator
	//inline int toInt32() const {return _mm_cvtsi128_si32(bitmap128.m128i_m128i);}
	inline uint32_t toInt32_2() const {return _mm_extract_epi32(bitmap128.m128i_m128i, 2);}
	inline uint32_t toInt32_3() const {return _mm_extract_epi32(bitmap128.m128i_m128i, 3);}
	inline bool isBitSet(const int theBit) const {return !_mm_testz_si128(this->bitmap128.m128i_m128i, bitSet[theBit].m128i_m128i);}
	inline void setBit(const int theBit) {*this |= bitSet[theBit].m128i_m128i;}
	inline void clearBit(const int theBit) {bitmap128.m128i_m128i = _mm_andnot_si128(bitSet[theBit].m128i_m128i, bitmap128.m128i_m128i);}
	inline void clearBits(const bm128& r) {bitmap128.m128i_m128i = _mm_andnot_si128(r.bitmap128.m128i_m128i, bitmap128.m128i_m128i);}
	inline void clear() {bitmap128.m128i_m128i = _mm_setzero_si128();}
	inline void operator= (const bm128 &rhs) {bitmap128.m128i_m128i = rhs.bitmap128.m128i_m128i;}
	inline void operator= (const void *p) {bitmap128.m128i_m128i = _mm_loadu_si128((const __m128i*)p);}
	//inline bool isZero() const {return _mm_testc_si128(_mm_setzero_si128(), bitmap128.m128i_m128i);}
	inline bool isZero() const {return 0 != _mm_testz_si128(bitmap128.m128i_m128i, bitmap128.m128i_m128i);}
	inline void shl16(const int numBits) {bitmap128.m128i_m128i = _mm_slli_epi16(bitmap128.m128i_m128i, numBits);}
	void toMask81(char* r) const {for(int i = 0; i < 81; i++) r[i] = isBitSet(i) ? '1' : '.';}
	void toMask128(char* r) const {for(int i = 0; i < 128; i++) r[i] = isBitSet(i) ? '1' : '.';}
	inline int popcount_128() const {
//		uint64_t i, j;
//		__m128i xmm = bitmap128.m128i_m128i;
//		i = _mm_cvtsi128_si64(xmm);
//		xmm = _mm_srli_si128(xmm, 8);
//		j = _mm_cvtsi128_si64(xmm);
		return (int)(_popcnt64(this->toInt64()) + _popcnt64(this->toInt64_1()));
	}
	inline int popcount_96() const {
		return (int)(_popcnt64(this->toInt64()) + _popcnt32(this->toInt32_2()));
	}
    //inline unsigned int nonzeroOctets() const {return 0x0000ffff ^ _mm_movemask_epi8(_mm_cmpeq_epi8(bitmap128.m128i_m128i, _mm_setzero_si128()));}
    //inline unsigned int diffOctets(const bm128 &rhs) const {return 0x0000ffff ^ _mm_movemask_epi8(_mm_cmpeq_epi8(bitmap128.m128i_m128i, rhs.bitmap128.m128i_m128i));}
	inline int getFirstBit1Index96() const {
		//lower 64 bits
		{
			uint64_t i = toInt64();
			if(i) {
				return (int)FindLSBIndex64(i);
			}
		}
		//upper 32 bits
		{
//			bm128 xmm;
//			xmm.bitmap128.m128i_m128i = _mm_srli_si128(bitmap128.m128i_m128i, 8);
//			uint32_t i = _mm_cvtsi128_si32(xmm.bitmap128.m128i_m128i);
			uint32_t i = toInt32_2();
			if(i) {
				return 64 + FindLSBIndex32(i);
			}
		}
		return -1;
	}
	inline bool hasMin2Bits() const {
		//exploit the fact that when (x & (x-1)) == 0 then x has 0 or 1 bits set
		return 0 == _mm_testz_si128(bitmap128.m128i_m128i, _mm_add_epi64(bitmap128.m128i_m128i, _mm_cmpeq_epi64(bitmap128.m128i_m128i, bitmap128.m128i_m128i)));
		//static const t_128 minus1 = {0xffffffffffffffff,0xffffffffffffffff}; //pcmpeqw, __m128i _mm_cmpeq_epi8(xmm0, xmm0)
		//return 0 == _mm_testz_si128(bitmap128.m128i_m128i, _mm_add_epi64(bitmap128.m128i_m128i, minus1.m128i_m128i));
	}
    inline static uint64_t FindLSBIndex64(const uint64_t Mask) {
#ifdef   _MSC_VER
        unsigned long res;
        _BitScanForward64(&res, Mask);
        return res;
#else
#if 1
       uint64_t Ret;
        __asm__
        (
            "bsfq %[Mask], %[Ret]"
            :[Ret] "=r" (Ret)
            :[Mask] "mr" (Mask)
        );
        return Ret;
#else
        return __builtin_ctzll(Mask); //some g++ versions split this to two 32-bit operations that work slower
#endif
#endif
    }
    inline static uint32_t FindLSBIndex32(const uint32_t Mask) {
#ifdef   _MSC_VER
    	unsigned long res;
        _BitScanForward(&res, Mask);
        return (uint32_t) res;
#else
        return (uint32_t) __builtin_ctz(Mask);
#endif
    }
};

#endif // T_128_H_INCLUDED
