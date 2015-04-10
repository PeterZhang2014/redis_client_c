/* Copyright (C) 2015/02/05 , Genvision
 * File Name   : basic_types.h
 * Description : In order to enhance the portability of code, to redefine the basic data types of C language
 * Verision    : 1.0
 * Date        : Feb 5, 2015
 * Author      : Peter Zhang
 * Email       : zfy31415926.love@163.com OR zhangfy@genvision.cn
 */

#ifndef __BASIC_TYPES_H__
#define __BASIC_TYPES_H__
typedef unsigned char 			u8;
typedef signed char        		s8;
typedef unsigned short     		u16;
typedef signed short       		s16;
typedef unsigned int       		u32;
typedef signed int         		s32;
typedef unsigned long long 		u64;
typedef signed long long   		s64;

typedef unsigned char 			__u8;
typedef signed char        		__s8;
typedef unsigned short     		__u16;
typedef signed short       		__s16;
typedef unsigned int       		__u32;
typedef signed int         		__s32;
typedef unsigned long long 		__u64;
typedef signed long long   		__s64;

typedef unsigned char 			BASIC_BOOL;
enum basic_bool_value{
	BASIC_FALSE = 0,
	BASIC_TRUE = 1,
};
#endif/*the end of 'ifdef __BASIC_TYPES_H__'*/
