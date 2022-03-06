/*
 * t_128.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Mladen Dobrichev
 */

//some 128-bit constants

#include "t_128.h"

const constexpr t_128 bitSet[128] =
{
	{{0x0000000000000001,0x0}}, {{0x0000000000000002,0x0}}, {{0x0000000000000004,0x0}}, {{0x0000000000000008,0x0}},
	{{0x0000000000000010,0x0}}, {{0x0000000000000020,0x0}}, {{0x0000000000000040,0x0}}, {{0x0000000000000080,0x0}},
	{{0x0000000000000100,0x0}}, {{0x0000000000000200,0x0}}, {{0x0000000000000400,0x0}}, {{0x0000000000000800,0x0}},
	{{0x0000000000001000,0x0}}, {{0x0000000000002000,0x0}}, {{0x0000000000004000,0x0}}, {{0x0000000000008000,0x0}},
	{{0x0000000000010000,0x0}}, {{0x0000000000020000,0x0}}, {{0x0000000000040000,0x0}}, {{0x0000000000080000,0x0}},
	{{0x0000000000100000,0x0}}, {{0x0000000000200000,0x0}}, {{0x0000000000400000,0x0}}, {{0x0000000000800000,0x0}},
	{{0x0000000001000000,0x0}}, {{0x0000000002000000,0x0}}, {{0x0000000004000000,0x0}}, {{0x0000000008000000,0x0}},
	{{0x0000000010000000,0x0}}, {{0x0000000020000000,0x0}}, {{0x0000000040000000,0x0}}, {{0x0000000080000000,0x0}},
	{{0x0000000100000000,0x0}}, {{0x0000000200000000,0x0}}, {{0x0000000400000000,0x0}}, {{0x0000000800000000,0x0}},
	{{0x0000001000000000,0x0}}, {{0x0000002000000000,0x0}}, {{0x0000004000000000,0x0}}, {{0x0000008000000000,0x0}},
	{{0x0000010000000000,0x0}}, {{0x0000020000000000,0x0}}, {{0x0000040000000000,0x0}}, {{0x0000080000000000,0x0}},
	{{0x0000100000000000,0x0}}, {{0x0000200000000000,0x0}}, {{0x0000400000000000,0x0}}, {{0x0000800000000000,0x0}},
	{{0x0001000000000000,0x0}}, {{0x0002000000000000,0x0}}, {{0x0004000000000000,0x0}}, {{0x0008000000000000,0x0}},
	{{0x0010000000000000,0x0}}, {{0x0020000000000000,0x0}}, {{0x0040000000000000,0x0}}, {{0x0080000000000000,0x0}},
	{{0x0100000000000000,0x0}}, {{0x0200000000000000,0x0}}, {{0x0400000000000000,0x0}}, {{0x0800000000000000,0x0}},
	{{0x1000000000000000,0x0}}, {{0x2000000000000000,0x0}}, {{0x4000000000000000,0x0}}, {{0x8000000000000000,0x0}},
	{{0x0,0x0000000000000001}}, {{0x0,0x0000000000000002}}, {{0x0,0x0000000000000004}}, {{0x0,0x0000000000000008}},
	{{0x0,0x0000000000000010}}, {{0x0,0x0000000000000020}}, {{0x0,0x0000000000000040}}, {{0x0,0x0000000000000080}},
	{{0x0,0x0000000000000100}}, {{0x0,0x0000000000000200}}, {{0x0,0x0000000000000400}}, {{0x0,0x0000000000000800}},
	{{0x0,0x0000000000001000}}, {{0x0,0x0000000000002000}}, {{0x0,0x0000000000004000}}, {{0x0,0x0000000000008000}},
	{{0x0,0x0000000000010000}}, {{0x0,0x0000000000020000}}, {{0x0,0x0000000000040000}}, {{0x0,0x0000000000080000}},
	{{0x0,0x0000000000100000}}, {{0x0,0x0000000000200000}}, {{0x0,0x0000000000400000}}, {{0x0,0x0000000000800000}},
	{{0x0,0x0000000001000000}}, {{0x0,0x0000000002000000}}, {{0x0,0x0000000004000000}}, {{0x0,0x0000000008000000}},
	{{0x0,0x0000000010000000}}, {{0x0,0x0000000020000000}}, {{0x0,0x0000000040000000}}, {{0x0,0x0000000080000000}},
	{{0x0,0x0000000100000000}}, {{0x0,0x0000000200000000}}, {{0x0,0x0000000400000000}}, {{0x0,0x0000000800000000}},
	{{0x0,0x0000001000000000}}, {{0x0,0x0000002000000000}}, {{0x0,0x0000004000000000}}, {{0x0,0x0000008000000000}},
	{{0x0,0x0000010000000000}}, {{0x0,0x0000020000000000}}, {{0x0,0x0000040000000000}}, {{0x0,0x0000080000000000}},
	{{0x0,0x0000100000000000}}, {{0x0,0x0000200000000000}}, {{0x0,0x0000400000000000}}, {{0x0,0x0000800000000000}},
	{{0x0,0x0001000000000000}}, {{0x0,0x0002000000000000}}, {{0x0,0x0004000000000000}}, {{0x0,0x0008000000000000}},
	{{0x0,0x0010000000000000}}, {{0x0,0x0020000000000000}}, {{0x0,0x0040000000000000}}, {{0x0,0x0080000000000000}},
	{{0x0,0x0100000000000000}}, {{0x0,0x0200000000000000}}, {{0x0,0x0400000000000000}}, {{0x0,0x0800000000000000}},
	{{0x0,0x1000000000000000}}, {{0x0,0x2000000000000000}}, {{0x0,0x4000000000000000}}, {{0x0,0x8000000000000000}}
};

//const t_128 maskLSB[129] =
//{
//	{0,0},
//	{0x00000001,0}, {0x00000003,0}, {0x00000007,0}, {0x0000000F,0},
//	{0x0000001F,0}, {0x0000003F,0}, {0x0000007F,0}, {0x000000FF,0},
//	{0x000001FF,0}, {0x000003FF,0}, {0x000007FF,0}, {0x00000FFF,0},
//	{0x00001FFF,0}, {0x00003FFF,0}, {0x00007FFF,0}, {0x0000FFFF,0},
//	{0x0001FFFF,0}, {0x0003FFFF,0}, {0x0007FFFF,0}, {0x000FFFFF,0},
//	{0x001FFFFF,0}, {0x003FFFFF,0}, {0x007FFFFF,0}, {0x00FFFFFF,0},
//	{0x01FFFFFF,0}, {0x03FFFFFF,0}, {0x07FFFFFF,0}, {0x0FFFFFFF,0},
//	{0x1FFFFFFF,0}, {0x3FFFFFFF,0}, {0x7FFFFFFF,0}, {0xFFFFFFFF,0},
//	{0x00000001FFFFFFFF,0}, {0x00000003FFFFFFFF,0}, {0x00000007FFFFFFFF,0}, {0x0000000FFFFFFFFF,0},
//	{0x0000001FFFFFFFFF,0}, {0x0000003FFFFFFFFF,0}, {0x0000007FFFFFFFFF,0}, {0x000000FFFFFFFFFF,0},
//	{0x000001FFFFFFFFFF,0}, {0x000003FFFFFFFFFF,0}, {0x000007FFFFFFFFFF,0}, {0x00000FFFFFFFFFFF,0},
//	{0x00001FFFFFFFFFFF,0}, {0x00003FFFFFFFFFFF,0}, {0x00007FFFFFFFFFFF,0}, {0x0000FFFFFFFFFFFF,0},
//	{0x0001FFFFFFFFFFFF,0}, {0x0003FFFFFFFFFFFF,0}, {0x0007FFFFFFFFFFFF,0}, {0x000FFFFFFFFFFFFF,0},
//	{0x001FFFFFFFFFFFFF,0}, {0x003FFFFFFFFFFFFF,0}, {0x007FFFFFFFFFFFFF,0}, {0x00FFFFFFFFFFFFFF,0},
//	{0x01FFFFFFFFFFFFFF,0}, {0x03FFFFFFFFFFFFFF,0}, {0x07FFFFFFFFFFFFFF,0}, {0x0FFFFFFFFFFFFFFF,0},
//	{0x1FFFFFFFFFFFFFFF,0}, {0x3FFFFFFFFFFFFFFF,0}, {0x7FFFFFFFFFFFFFFF,0}, {0xFFFFFFFFFFFFFFFF,0},
//	{0xFFFFFFFFFFFFFFFF,0x00000001}, {0xFFFFFFFFFFFFFFFF,0x00000003}, {0xFFFFFFFFFFFFFFFF,0x00000007}, {0xFFFFFFFFFFFFFFFF,0x0000000F},
//	{0xFFFFFFFFFFFFFFFF,0x0000001F}, {0xFFFFFFFFFFFFFFFF,0x0000003F}, {0xFFFFFFFFFFFFFFFF,0x0000007F}, {0xFFFFFFFFFFFFFFFF,0x000000FF},
//	{0xFFFFFFFFFFFFFFFF,0x000001FF}, {0xFFFFFFFFFFFFFFFF,0x000003FF}, {0xFFFFFFFFFFFFFFFF,0x000007FF}, {0xFFFFFFFFFFFFFFFF,0x00000FFF},
//	{0xFFFFFFFFFFFFFFFF,0x00001FFF}, {0xFFFFFFFFFFFFFFFF,0x00003FFF}, {0xFFFFFFFFFFFFFFFF,0x00007FFF}, {0xFFFFFFFFFFFFFFFF,0x0000FFFF},
//	{0xFFFFFFFFFFFFFFFF,0x0001FFFF}, {0xFFFFFFFFFFFFFFFF,0x0003FFFF}, {0xFFFFFFFFFFFFFFFF,0x0007FFFF}, {0xFFFFFFFFFFFFFFFF,0x000FFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x001FFFFF}, {0xFFFFFFFFFFFFFFFF,0x003FFFFF}, {0xFFFFFFFFFFFFFFFF,0x007FFFFF}, {0xFFFFFFFFFFFFFFFF,0x00FFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x01FFFFFF}, {0xFFFFFFFFFFFFFFFF,0x03FFFFFF}, {0xFFFFFFFFFFFFFFFF,0x07FFFFFF}, {0xFFFFFFFFFFFFFFFF,0x0FFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFF},
//	{0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x3FFFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF}, {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF},
//};

////only first 81 bits set
//const t_128 mask81 = {0xFFFFFFFFFFFFFFFF,0x0001FFFF};
//
////only first 81 + 27 = 108 bits set
//const t_128 mask108 = {0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFF};

//only first 81 + 27 + 1 = 109 bits set
//const t_128 mask109 = {0xFFFFFFFFFFFFFFFF,0x1FFFFFFFFFFF};
