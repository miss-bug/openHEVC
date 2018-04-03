/*
 * HEVC video decoder
 *
 * Copyright (C) 2012 - 2013 Guillaume Martres
 * Copyright (C) 2013 - 2014 Pierre-Edouard Lepere
 *
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_X86_HEVCDSP_H
#define AVCODEC_X86_HEVCDSP_H

#include <stddef.h>
#include <stdint.h>

#include "libavcodec/hevcdec.h"
#include "config.h"

#define PEL_LINK(dst, idx1, idx2, idx3, name, D, opt) \
dst[idx1][idx2][idx3] = ff_hevc_put_hevc_ ## name ## _ ## D ## _##opt; \
dst ## _bi[idx1][idx2][idx3] = ff_hevc_put_hevc_bi_ ## name ## _ ## D ## _##opt; \
dst ## _uni[idx1][idx2][idx3] = ff_hevc_put_hevc_uni_ ## name ## _ ## D ## _##opt; \
dst ## _uni_w[idx1][idx2][idx3] = ff_hevc_put_hevc_uni_w_ ## name ## _ ## D ## _##opt; \
dst ## _bi_w[idx1][idx2][idx3] = ff_hevc_put_hevc_bi_w_ ## name ## _ ## D ## _##opt

#if CONFIG_OH_OPTIM
#define OH_PEL_LINK(dst, idx1, idx2, idx3, name, D, opt) \
dst[idx1][idx2][idx3] = ohhevc_put_hevc_ ## name ## _ ## D ## _##opt; \
dst ## _bi[idx1][idx2][idx3] = ohhevc_put_hevc_bi_ ## name ## _ ## D ## _##opt; \
dst ## _uni[idx1][idx2][idx3] = ohhevc_put_hevc_uni_ ## name ## _ ## D ## _##opt; \
dst ## _uni_w[idx1][idx2][idx3] = ohhevc_put_hevc_uni_w_ ## name ## _ ## D ## _##opt; \
dst ## _bi_w[idx1][idx2][idx3] = ohhevc_put_hevc_bi_w_ ## name ## _ ## D ## _##opt
#endif

#define PEL_PROTOTYPE(name, D, opt) \
void ff_hevc_put_hevc_ ## name ## _ ## D ## _##opt(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width); \
void ff_hevc_put_hevc_bi_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width); \
void ff_hevc_put_hevc_uni_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my, int width); \
void ff_hevc_put_hevc_uni_w_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int height, int denom, int wx, int ox, intptr_t mx, intptr_t my, int width); \
void ff_hevc_put_hevc_bi_w_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, int denom, int wx0, int wx1, int ox0, int ox1, intptr_t mx, intptr_t my, int width)

#if CONFIG_OH_OPTIM
#define OH_PEL_PROTOTYPE(name, D, opt) \
void ohhevc_put_hevc_ ## name ## _ ## D ## _##opt(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width); \
void ohhevc_put_hevc_bi_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width); \
void ohhevc_put_hevc_uni_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my, int width); \
void ohhevc_put_hevc_uni_w_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int height, int denom, int wx, int ox, intptr_t mx, intptr_t my, int width); \
void ohhevc_put_hevc_bi_w_ ## name ## _ ## D ## _##opt(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, int denom, int wx0, int wx1, int ox0, int ox1, intptr_t mx, intptr_t my, int width)
#endif
///////////////////////////////////////////////////////////////////////////////
//IDCT functions
///////////////////////////////////////////////////////////////////////////////
void ohhevc_transform_skip_8_sse(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);

void ohhevc_transform_4x4_luma_8_sse2(int16_t *coeffs);
void ohhevc_transform_4x4_luma_10_sse2(int16_t *coeffs);
void ohhevc_transform_4x4_luma_12_sse2(int16_t *coeffs);

#define OH_IDCT_FUNC(s, b) void ohhevc_transform_ ## s ## x ## s ##_## b ##_sse2\
            (int16_t *coeffs, int col_limit);

OH_IDCT_FUNC(4, 8)
OH_IDCT_FUNC(4, 10)
OH_IDCT_FUNC(4, 12)
OH_IDCT_FUNC(8, 8)
OH_IDCT_FUNC(8, 10)
OH_IDCT_FUNC(8, 12)
OH_IDCT_FUNC(16, 8)
OH_IDCT_FUNC(16, 10)
OH_IDCT_FUNC(16, 12)
OH_IDCT_FUNC(32, 8)
OH_IDCT_FUNC(32, 10)
OH_IDCT_FUNC(32, 12)

#define TRANSFORM_ADD_FUNC_MMXEXT(s, b) void ff_hevc_transform_add ## s ## _ ## b ##_mmxext\
		(uint8_t *dst, int16_t *coeffs, ptrdiff_t stride);
#define TRANSFORM_ADD_FUNC_SSE2(s, b) void ff_hevc_transform_add ## s ## _ ## b ##_sse2\
		(uint8_t *dst, int16_t *coeffs, ptrdiff_t stride);
#define TRANSFORM_ADD_FUNC_AVX(s, b) void ff_hevc_transform_add ## s ## _ ## b ##_avx\
		(uint8_t *dst, int16_t *coeffs, ptrdiff_t stride);
#define TRANSFORM_ADD_FUNC_AVX2(s, b) void ff_hevc_transform_add ## s ## _ ## b ##_avx2\
		(uint8_t *dst, int16_t *coeffs, ptrdiff_t stride);

TRANSFORM_ADD_FUNC_MMXEXT(4,8)
TRANSFORM_ADD_FUNC_SSE2(8,8)
TRANSFORM_ADD_FUNC_SSE2(16,8)
TRANSFORM_ADD_FUNC_SSE2(32,8)

TRANSFORM_ADD_FUNC_AVX(8,8)
TRANSFORM_ADD_FUNC_AVX(16,8)
TRANSFORM_ADD_FUNC_AVX(32,8)

TRANSFORM_ADD_FUNC_MMXEXT(4,10)
TRANSFORM_ADD_FUNC_SSE2(8,10)
TRANSFORM_ADD_FUNC_SSE2(16,10)
TRANSFORM_ADD_FUNC_SSE2(32,10)

TRANSFORM_ADD_FUNC_AVX(8,10)
TRANSFORM_ADD_FUNC_AVX(16,10)
TRANSFORM_ADD_FUNC_AVX(32,10)

TRANSFORM_ADD_FUNC_AVX2(32,8)

TRANSFORM_ADD_FUNC_AVX2(16,10)
TRANSFORM_ADD_FUNC_AVX2(32,10)

#define OH_TRANSFORM_ADD_FUNC_SSE2(s, b) void ohhevc_transform_ ## s ## x ## s ##_add_## b ##_sse2\
		(uint8_t *dst, int16_t *coeffs, ptrdiff_t stride);

OH_TRANSFORM_ADD_FUNC_SSE2(4,8)
OH_TRANSFORM_ADD_FUNC_SSE2(8,8)
OH_TRANSFORM_ADD_FUNC_SSE2(16,8)
OH_TRANSFORM_ADD_FUNC_SSE2(32,8)

OH_TRANSFORM_ADD_FUNC_SSE2(4,10)
OH_TRANSFORM_ADD_FUNC_SSE2(8,10)
OH_TRANSFORM_ADD_FUNC_SSE2(16,10)
OH_TRANSFORM_ADD_FUNC_SSE2(32,10)

OH_TRANSFORM_ADD_FUNC_SSE2(4,12)
OH_TRANSFORM_ADD_FUNC_SSE2(8,12)
OH_TRANSFORM_ADD_FUNC_SSE2(16,12)
OH_TRANSFORM_ADD_FUNC_SSE2(32,12)

void ohhevc_transform_4x4_add_8_sse4(uint8_t *dst, int16_t *_coeffs, ptrdiff_t _stride);
void ohhevc_transform_8x8_add_8_sse4(uint8_t *dst, int16_t *_coeffs, ptrdiff_t _stride);
void ohhevc_transform_16x16_add_8_sse4(uint8_t *dst, int16_t *_coeffs, ptrdiff_t _stride);
void ohhevc_transform_32x32_add_8_sse4(uint8_t *dst, int16_t *_coeffs, ptrdiff_t _stride);

///////////////////////////////////////////////////////////////////////////////
// MC functions
///////////////////////////////////////////////////////////////////////////////
#define EPEL_PROTOTYPES(fname, bitd, opt) \
        PEL_PROTOTYPE(fname##4,  bitd, opt); \
        PEL_PROTOTYPE(fname##6,  bitd, opt); \
        PEL_PROTOTYPE(fname##8,  bitd, opt); \
        PEL_PROTOTYPE(fname##12, bitd, opt); \
        PEL_PROTOTYPE(fname##16, bitd, opt); \
        PEL_PROTOTYPE(fname##24, bitd, opt); \
        PEL_PROTOTYPE(fname##32, bitd, opt); \
        PEL_PROTOTYPE(fname##48, bitd, opt); \
        PEL_PROTOTYPE(fname##64, bitd, opt)

#define QPEL_PROTOTYPES(fname, bitd, opt) \
        PEL_PROTOTYPE(fname##4,  bitd, opt); \
        PEL_PROTOTYPE(fname##8,  bitd, opt); \
        PEL_PROTOTYPE(fname##12, bitd, opt); \
        PEL_PROTOTYPE(fname##16, bitd, opt); \
        PEL_PROTOTYPE(fname##24, bitd, opt); \
        PEL_PROTOTYPE(fname##32, bitd, opt); \
        PEL_PROTOTYPE(fname##48, bitd, opt); \
        PEL_PROTOTYPE(fname##64, bitd, opt)

#define OH_EPEL_PROTOTYPES(fname, bitd, opt) \
        OH_PEL_PROTOTYPE(fname##4,  bitd, opt); \
        OH_PEL_PROTOTYPE(fname##6,  bitd, opt); \
        OH_PEL_PROTOTYPE(fname##8,  bitd, opt); \
        OH_PEL_PROTOTYPE(fname##12, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##16, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##24, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##32, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##48, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##64, bitd, opt)

#define OH_QPEL_PROTOTYPES(fname, bitd, opt) \
        OH_PEL_PROTOTYPE(fname##4,  bitd, opt); \
        OH_PEL_PROTOTYPE(fname##8,  bitd, opt); \
        OH_PEL_PROTOTYPE(fname##12, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##16, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##24, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##32, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##48, bitd, opt); \
        OH_PEL_PROTOTYPE(fname##64, bitd, opt)


#define WEIGHTING_PROTOTYPE(width, bitd, opt) \
void ff_hevc_put_hevc_uni_w##width##_##bitd##_##opt(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, int height, int denom,  int _wx, int _ox); \
void ff_hevc_put_hevc_bi_w##width##_##bitd##_##opt(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, int16_t *_src2, int height, int denom,  int _wx0,  int _wx1, int _ox0, int _ox1)

#define WEIGHTING_PROTOTYPES(bitd, opt) \
        WEIGHTING_PROTOTYPE(2, bitd, opt); \
        WEIGHTING_PROTOTYPE(4, bitd, opt); \
        WEIGHTING_PROTOTYPE(6, bitd, opt); \
        WEIGHTING_PROTOTYPE(8, bitd, opt); \
        WEIGHTING_PROTOTYPE(12, bitd, opt); \
        WEIGHTING_PROTOTYPE(16, bitd, opt); \
        WEIGHTING_PROTOTYPE(24, bitd, opt); \
        WEIGHTING_PROTOTYPE(32, bitd, opt); \
        WEIGHTING_PROTOTYPE(48, bitd, opt); \
        WEIGHTING_PROTOTYPE(64, bitd, opt)


///////////////////////////////////////////////////////////////////////////////
// QPEL_PIXELS EPEL_PIXELS
///////////////////////////////////////////////////////////////////////////////
EPEL_PROTOTYPES(pel_pixels ,  8, sse4);
EPEL_PROTOTYPES(pel_pixels , 10, sse4);
EPEL_PROTOTYPES(pel_pixels , 12, sse4);

void ff_hevc_put_hevc_pel_pixels16_8_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels24_8_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels32_8_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels48_8_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels64_8_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);

void ff_hevc_put_hevc_pel_pixels16_10_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels24_10_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels32_10_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels48_10_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_pel_pixels64_10_avx2(int16_t *dst, uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);



void ff_hevc_put_hevc_uni_pel_pixels32_8_avx2(uint8_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_uni_pel_pixels48_8_avx2(uint8_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_uni_pel_pixels64_8_avx2(uint8_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);
void ff_hevc_put_hevc_uni_pel_pixels96_8_avx2(uint8_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width); //used for 10bit
void ff_hevc_put_hevc_uni_pel_pixels128_8_avx2(uint8_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int height, intptr_t mx, intptr_t my,int width);//used for 10bit


void ff_hevc_put_hevc_bi_pel_pixels16_8_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels24_8_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels32_8_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels48_8_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels64_8_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);

void ff_hevc_put_hevc_bi_pel_pixels16_10_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels24_10_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels32_10_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels48_10_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);
void ff_hevc_put_hevc_bi_pel_pixels64_10_avx2(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride, int16_t *src2, int height, intptr_t mx, intptr_t my, int width);

///////////////////////////////////////////////////////////////////////////////
// EPEL
///////////////////////////////////////////////////////////////////////////////
EPEL_PROTOTYPES(epel_h ,  8, sse4);
EPEL_PROTOTYPES(epel_h , 10, sse4);
EPEL_PROTOTYPES(epel_h , 12, sse4);

EPEL_PROTOTYPES(epel_v ,  8, sse4);
EPEL_PROTOTYPES(epel_v , 10, sse4);
EPEL_PROTOTYPES(epel_v , 12, sse4);

EPEL_PROTOTYPES(epel_hv ,  8, sse4);
EPEL_PROTOTYPES(epel_hv , 10, sse4);
EPEL_PROTOTYPES(epel_hv , 12, sse4);

#if CONFIG_OH_OPTIM
OH_EPEL_PROTOTYPES(epel_h ,  8, sse);
OH_EPEL_PROTOTYPES(epel_h , 10, sse);
OH_EPEL_PROTOTYPES(epel_h , 12, sse);

OH_EPEL_PROTOTYPES(epel_v ,  8, sse);
OH_EPEL_PROTOTYPES(epel_v , 10, sse);
OH_EPEL_PROTOTYPES(epel_v , 12, sse);

OH_EPEL_PROTOTYPES(epel_hv ,  8, sse);
OH_EPEL_PROTOTYPES(epel_hv , 10, sse);
OH_EPEL_PROTOTYPES(epel_hv , 12, sse);

OH_EPEL_PROTOTYPES(pel_pixels ,  8, sse);
OH_EPEL_PROTOTYPES(pel_pixels , 10, sse);
OH_EPEL_PROTOTYPES(pel_pixels , 12, sse);
#endif

PEL_PROTOTYPE(epel_h16, 8, avx2);
PEL_PROTOTYPE(epel_h24, 8, avx2);
PEL_PROTOTYPE(epel_h32, 8, avx2);
PEL_PROTOTYPE(epel_h48, 8, avx2);
PEL_PROTOTYPE(epel_h64, 8, avx2);

PEL_PROTOTYPE(epel_h16,10, avx2);
PEL_PROTOTYPE(epel_h24,10, avx2);
PEL_PROTOTYPE(epel_h32,10, avx2);
PEL_PROTOTYPE(epel_h48,10, avx2);
PEL_PROTOTYPE(epel_h64,10, avx2);

PEL_PROTOTYPE(epel_v16, 8, avx2);
PEL_PROTOTYPE(epel_v24, 8, avx2);
PEL_PROTOTYPE(epel_v32, 8, avx2);
PEL_PROTOTYPE(epel_v48, 8, avx2);
PEL_PROTOTYPE(epel_v64, 8, avx2);

PEL_PROTOTYPE(epel_v16,10, avx2);
PEL_PROTOTYPE(epel_v24,10, avx2);
PEL_PROTOTYPE(epel_v32,10, avx2);
PEL_PROTOTYPE(epel_v48,10, avx2);
PEL_PROTOTYPE(epel_v64,10, avx2);

PEL_PROTOTYPE(epel_hv16, 8, avx2);
PEL_PROTOTYPE(epel_hv24, 8, avx2);
PEL_PROTOTYPE(epel_hv32, 8, avx2);
PEL_PROTOTYPE(epel_hv48, 8, avx2);
PEL_PROTOTYPE(epel_hv64, 8, avx2);

PEL_PROTOTYPE(epel_hv16,10, avx2);
PEL_PROTOTYPE(epel_hv24,10, avx2);
PEL_PROTOTYPE(epel_hv32,10, avx2);
PEL_PROTOTYPE(epel_hv48,10, avx2);
PEL_PROTOTYPE(epel_hv64,10, avx2);

///////////////////////////////////////////////////////////////////////////////
// QPEL
///////////////////////////////////////////////////////////////////////////////
QPEL_PROTOTYPES(qpel_h ,  8, sse4);
QPEL_PROTOTYPES(qpel_h , 10, sse4);
QPEL_PROTOTYPES(qpel_h , 12, sse4);

QPEL_PROTOTYPES(qpel_v,  8, sse4);
QPEL_PROTOTYPES(qpel_v, 10, sse4);
QPEL_PROTOTYPES(qpel_v, 12, sse4);

QPEL_PROTOTYPES(qpel_hv,  8, sse4);
QPEL_PROTOTYPES(qpel_hv, 10, sse4);
QPEL_PROTOTYPES(qpel_hv, 12, sse4);

#if CONFIG_OH_OPTIM
OH_QPEL_PROTOTYPES(qpel_h ,  8, sse);
OH_QPEL_PROTOTYPES(qpel_h , 10, sse);
OH_QPEL_PROTOTYPES(qpel_h , 12, sse);

OH_QPEL_PROTOTYPES(qpel_v,  8, sse);
OH_QPEL_PROTOTYPES(qpel_v, 10, sse);
OH_QPEL_PROTOTYPES(qpel_v, 12, sse);

OH_QPEL_PROTOTYPES(qpel_hv,  8, sse);
OH_QPEL_PROTOTYPES(qpel_hv, 10, sse);
OH_QPEL_PROTOTYPES(qpel_hv, 12, sse);
#endif
PEL_PROTOTYPE(qpel_h16, 8, avx2);
PEL_PROTOTYPE(qpel_h24, 8, avx2);
PEL_PROTOTYPE(qpel_h32, 8, avx2);
PEL_PROTOTYPE(qpel_h48, 8, avx2);
PEL_PROTOTYPE(qpel_h64, 8, avx2);

PEL_PROTOTYPE(qpel_h16,10, avx2);
PEL_PROTOTYPE(qpel_h24,10, avx2);
PEL_PROTOTYPE(qpel_h32,10, avx2);
PEL_PROTOTYPE(qpel_h48,10, avx2);
PEL_PROTOTYPE(qpel_h64,10, avx2);

PEL_PROTOTYPE(qpel_v16, 8, avx2);
PEL_PROTOTYPE(qpel_v24, 8, avx2);
PEL_PROTOTYPE(qpel_v32, 8, avx2);
PEL_PROTOTYPE(qpel_v48, 8, avx2);
PEL_PROTOTYPE(qpel_v64, 8, avx2);

PEL_PROTOTYPE(qpel_v16,10, avx2);
PEL_PROTOTYPE(qpel_v24,10, avx2);
PEL_PROTOTYPE(qpel_v32,10, avx2);
PEL_PROTOTYPE(qpel_v48,10, avx2);
PEL_PROTOTYPE(qpel_v64,10, avx2);

PEL_PROTOTYPE(qpel_hv16, 8, avx2);
PEL_PROTOTYPE(qpel_hv24, 8, avx2);
PEL_PROTOTYPE(qpel_hv32, 8, avx2);
PEL_PROTOTYPE(qpel_hv48, 8, avx2);
PEL_PROTOTYPE(qpel_hv64, 8, avx2);

PEL_PROTOTYPE(qpel_hv16,10, avx2);
PEL_PROTOTYPE(qpel_hv24,10, avx2);
PEL_PROTOTYPE(qpel_hv32,10, avx2);
PEL_PROTOTYPE(qpel_hv48,10, avx2);
PEL_PROTOTYPE(qpel_hv64,10, avx2);

WEIGHTING_PROTOTYPES(8, sse4);
WEIGHTING_PROTOTYPES(10, sse4);
WEIGHTING_PROTOTYPES(12, sse4);

///////////////////////////////////////////////////////////////////////////////
// SAO functions
///////////////////////////////////////////////////////////////////////////////
//#ifndef OPTI_ASM
void ohhevc_sao_edge_filter_8_sse(uint8_t *_dst, uint8_t *_src,
                                  ptrdiff_t stride_dst, ptrdiff_t stride_src,
                                  SAOParams *sao,
                                  int width, int height,
                                  int c_idx);
//#endif
void ohhevc_sao_edge_filter_10_sse(uint8_t *_dst, uint8_t *_src,
                                  ptrdiff_t stride_dst, ptrdiff_t stride_src,
                                  SAOParams *sao,
                                  int width, int height,
                                  int c_idx);
void ohhevc_sao_edge_filter_12_sse(uint8_t *_dst, uint8_t *_src,
                                  ptrdiff_t stride_dst, ptrdiff_t stride_src,
                                  SAOParams *sao,
                                  int width, int height,
                                  int c_idx);
//#ifndef OPTI_ASM
void ohhevc_sao_band_filter_0_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride_dst, ptrdiff_t _stride_src,
                                     struct SAOParams *sao, int *borders, int width, int height, int c_idx);
//#endif
void ohhevc_sao_band_filter_0_10_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride_dst, ptrdiff_t _stride_src,
                                      struct SAOParams *sao, int *borders, int width, int height, int c_idx);
void ohhevc_sao_band_filter_0_12_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride_dst, ptrdiff_t _stride_src,
                                      struct SAOParams *sao, int *borders, int width, int height, int c_idx);

//#ifdef SVC_EXTENSION

    void ohevc_upsample_filter_block_luma_h_all_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
            int x_EL, int x_BL, int block_w, int block_h, int widthEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_h_all_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
                int x_EL, int x_BL, int block_w, int block_h, int widthEL,
                const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_luma_v_all_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_v_all_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

    void ohevc_upsample_filter_block_luma_h_x2_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
            int x_EL, int x_BL, int block_w, int block_h, int widthEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_h_x2_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
                int x_EL, int x_BL, int block_w, int block_h, int widthEL,
                const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_luma_v_x2_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_v_x2_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

    void ohevc_upsample_filter_block_luma_h_x1_5_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
            int x_EL, int x_BL, int block_w, int block_h, int widthEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_h_x1_5_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
                int x_EL, int x_BL, int block_w, int block_h, int widthEL,
                const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_luma_v_x1_5_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_cr_v_x1_5_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

    void ohevc_upsample_filter_block_luma_h_8_8_sse( int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
            int x_EL, int x_BL, int block_w, int block_h, int widthEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
    void ohevc_upsample_filter_block_luma_v_8_8_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
            int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
   void ohevc_upsample_filter_block_cr_h_8_8_sse( int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
            int x_EL, int x_BL, int block_w, int block_h, int widthEL,
            const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
   void ohevc_upsample_filter_block_cr_v_8_8_sse(uint8_t *dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t _srcstride,
           int y_BL, int x_EL, int y_EL, int block_w, int block_h, int widthEL, int heightEL,
           const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_luma_h_x2_sse_16(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t srcstride,
               int x_EL, int x_BL, int width, int height, int widthEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_cr_h_x2_sse_16(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
               int x_EL, int x_BL, int block_w, int block_h, int widthEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_luma_v_x2_sse_16(uint8_t *_dst, ptrdiff_t _dststride, int16_t *_src, ptrdiff_t srcstride,
               int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_cr_v_x2_sse_16(uint8_t *_dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t srcstride,
           int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
           const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_luma_h_x1_5_sse_16(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t srcstride,
               int x_EL, int x_BL, int width, int height, int widthEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_cr_h_x1_5_sse_16(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride,
               int x_EL, int x_BL, int block_w, int block_h, int widthEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_luma_v_x1_5_sse_16(uint8_t *_dst, ptrdiff_t _dststride, int16_t *_src, ptrdiff_t srcstride,
               int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
               const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

   void ohevc_upsample_filter_block_cr_v_x1_5_sse_16(uint8_t *_dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t srcstride,
           int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
           const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

//   void emt_idst_VII_4x4_v_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_v_avx2_9 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_v_avx2_10 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_v_avx2_12(int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);

//   void emt_idst_VII_4x4_h_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_h_avx2_9 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_h_avx2_10 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_VII_4x4_h_avx2_12(int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);

//   void emt_idct_VIII_4x4_v_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_v_avx2_9 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_v_avx2_10 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_v_avx2_12(int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);

//   void emt_idct_VIII_4x4_h_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_h_avx2_9 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_h_avx2_10 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_VIII_4x4_h_avx2_12(int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
   //   void ohevc_upsample_filter_block_cr_v_x2_sse_16(uint8_t *_dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t srcstride,
//           int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
//           const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);

//   void ohevc_upsample_filter_block_cr_v_x2_sse_16(uint8_t *_dst, ptrdiff_t dststride, int16_t *_src, ptrdiff_t srcstride,
//           int y_BL, int x_EL, int y_EL, int width, int height, int widthEL, int heightEL,
//           const struct HEVCWindow *Enhscal, struct UpsamplInf *up_info);
//   void emt_idct_V_4x4_v_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_V_4x4_h_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_II_4x4_v_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idct_II_4x4_h_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);

//   void emt_idst_I_4x4_v_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);
//   void emt_idst_I_4x4_h_avx2_8 (int16_t *x, int16_t *block, int log2_transform_range, const int clip_min, const int clip_max);

#define EMT_DECL_V_DST_4x4(num,optim,depth)\
void emt_idct_##num##_4x4_0_0_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DST_8x8(y,num,optim,depth)\
void emt_idct_##num##_8x8_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_8x8_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DST_16x16(y,num,optim,depth)\
void emt_idct_##num##_16x16_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_2_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_3_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DST_32x32(y,num,optim,depth)\
void emt_idct_##num##_32x32_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_2_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_3_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_4_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_5_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_6_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_32x32_7_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\

#define EMT_DECL_V_DCT_4x4(num,optim,depth)\
void emt_idct_##num##_4x4_0_0_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DCT_8x8(y,num,optim,depth)\
void emt_idct_##num##_8x8_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_8x8_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DCT_16x16(y,num,optim,depth)\
void emt_idct_##num##_16x16_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_2_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_3_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_V_DCT_32x32(y,num,optim,depth)\
    void emt_idct_##num##_32x32_0_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_1_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_2_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_3_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_4_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_5_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_6_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_7_##y##_v_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\

#define EMT_DECL_H_DCT_4x4(num,optim,depth)\
void emt_idct_##num##_4x4_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DCT_8x8(num,optim,depth)\
void emt_idct_##num##_8x8_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_8x8_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DCT_16x16(num,optim,depth)\
void emt_idct_##num##_16x16_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_2_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_3_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DCT_32x32(num,optim,depth)\
    void emt_idct_##num##_32x32_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_2_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_3_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_4_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_5_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_6_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_7_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\

#define EMT_DECL_H_DST_4x4(num,optim,depth)\
void emt_idct_##num##_4x4_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DST_8x8(num,optim,depth)\
void emt_idct_##num##_8x8_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_8x8_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DST_16x16(num,optim,depth)\
void emt_idct_##num##_16x16_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_2_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
void emt_idct_##num##_16x16_3_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\


#define EMT_DECL_H_DST_32x32(num,optim,depth)\
    void emt_idct_##num##_32x32_0_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_1_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_2_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_3_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_4_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_5_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_6_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\
    void emt_idct_##num##_32x32_7_h_##optim##_##depth(int16_t *restrict src, int16_t *restrict dst);\

#define DCT_EMT_DECL_V_32x32(num,optim,depth)\
    EMT_DECL_V_DCT_32x32(0,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(1,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(2,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(3,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(4,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(5,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(6,num,optim,depth)\
    EMT_DECL_V_DCT_32x32(7,num,optim,depth)\


#define DCT_EMT_DECL_V_16x16(num,optim,depth)\
    EMT_DECL_V_DCT_16x16(0,num,optim,depth)\
    EMT_DECL_V_DCT_16x16(1,num,optim,depth)\
    EMT_DECL_V_DCT_16x16(2,num,optim,depth)\
    EMT_DECL_V_DCT_16x16(3,num,optim,depth)\

#define DCT_EMT_DECL_V_8x8(num,optim,depth)\
    EMT_DECL_V_DCT_8x8(0,num,optim,depth)\
    EMT_DECL_V_DCT_8x8(1,num,optim,depth)\

#define DCT_EMT_DECL_V_4x4(num,optim,depth)\
EMT_DECL_V_DCT_4x4(num,optim,depth)\

#define DST_EMT_DECL_V_32x32(num,optim,depth)\
    EMT_DECL_V_DST_32x32(0,num,optim,depth)\
    EMT_DECL_V_DST_32x32(1,num,optim,depth)\
    EMT_DECL_V_DST_32x32(2,num,optim,depth)\
    EMT_DECL_V_DST_32x32(3,num,optim,depth)\
    EMT_DECL_V_DST_32x32(4,num,optim,depth)\
    EMT_DECL_V_DST_32x32(5,num,optim,depth)\
    EMT_DECL_V_DST_32x32(6,num,optim,depth)\
    EMT_DECL_V_DST_32x32(7,num,optim,depth)\


#define DST_EMT_DECL_V_16x16(num,optim,depth)\
    EMT_DECL_V_DST_16x16(0,num,optim,depth)\
    EMT_DECL_V_DST_16x16(1,num,optim,depth)\
    EMT_DECL_V_DST_16x16(2,num,optim,depth)\
    EMT_DECL_V_DST_16x16(3,num,optim,depth)\

#define DST_EMT_DECL_V_8x8(num,optim,depth)\
    EMT_DECL_V_DST_8x8(0,num,optim,depth)\
    EMT_DECL_V_DST_8x8(1,num,optim,depth)\

#define DST_EMT_DECL_V_4x4(num,optim,depth)\
EMT_DECL_V_DST_4x4(num,optim,depth)\

#define DECL_DCT(num,optim,depth)\
    DCT_EMT_DECL_V_32x32(num,optim,depth)\
    DCT_EMT_DECL_V_16x16(num,optim,depth)\
    DCT_EMT_DECL_V_8x8(num,optim,depth)\
    DCT_EMT_DECL_V_4x4(num,optim,depth)\
    EMT_DECL_H_DCT_32x32(num,optim,depth)\
    EMT_DECL_H_DCT_16x16(num,optim,depth)\
    EMT_DECL_H_DCT_8x8(num,optim,depth)\
    EMT_DECL_H_DCT_4x4(num,optim,depth)\

#define DECL_DST(num,optim,depth)\
    DST_EMT_DECL_V_32x32(num,optim,depth)\
    DST_EMT_DECL_V_16x16(num,optim,depth)\
    DST_EMT_DECL_V_8x8(num,optim,depth)\
    DST_EMT_DECL_V_4x4(num,optim,depth)\
    EMT_DECL_H_DST_32x32(num,optim,depth)\
    EMT_DECL_H_DST_16x16(num,optim,depth)\
    EMT_DECL_H_DST_8x8(num,optim,depth)\
    EMT_DECL_H_DST_4x4(num,optim,depth)\

   DECL_DCT(II,avx2,8);

   DECL_DCT(V,avx2,8);

   DECL_DCT(VIII,avx2,8);

   DECL_DST(I,avx2,8);

   DECL_DST(VII,avx2,8);

   DECL_DCT(II,avx2,10);

   DECL_DCT(V,avx2,10);

   DECL_DCT(VIII,avx2,10);

   DECL_DST(I,avx2,10);

   DECL_DST(VII,avx2,10);
   /*
#define EMT_DECL_V(num,size,optim,depth,h)\
    void emt_idct_##num##_##size##_##h##_0_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_1_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_2_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_3_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_4_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_5_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_6_v_##optim##_##depth(int16_t *x, int16_t *block);\
       void emt_idct_##num##_##size##_##h##_7_v_##optim##_##depth(int16_t *x, int16_t *block);\



#define DECL_AMT_IDCT(num,size,optim,depth)\
EMT_DECL_V(num,size,optim,depth,0)\
    EMT_DECL_V(num,size,optim,depth,1)\
    EMT_DECL_V(num,size,optim,depth,2)\
    EMT_DECL_V(num,size,optim,depth,3)\
    EMT_DECL_V(num,size,optim,depth,4)\
    EMT_DECL_V(num,size,optim,depth,5)\
    EMT_DECL_V(num,size,optim,depth,6)\
    EMT_DECL_V(num,size,optim,depth,7)\
void emt_idct_##num##_##size##_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_0_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_1_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_2_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_3_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_4_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_5_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_6_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_7_h_##optim##_##depth(int16_t *x, int16_t *block);\

#define DECL_AMT_IDST(num,size,optim,depth)\
void emt_idct_##num##_##size##_v_##optim##_##depth(int16_t *x, int16_t *block);\
void emt_idct_##num##_##size##_h_##optim##_##depth(int16_t *x, int16_t *block);\
    EMT_DECL_V(num,size,optim,depth,0)\
        EMT_DECL_V(num,size,optim,depth,1)\
        EMT_DECL_V(num,size,optim,depth,2)\
        EMT_DECL_V(num,size,optim,depth,3)\
        EMT_DECL_V(num,size,optim,depth,4)\
        EMT_DECL_V(num,size,optim,depth,5)\
        EMT_DECL_V(num,size,optim,depth,6)\
        EMT_DECL_V(num,size,optim,depth,7)\
    void emt_idct_##num##_##size##_0_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_1_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_2_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_3_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_4_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_5_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_6_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_7_h_##optim##_##depth(int16_t *x, int16_t *block);\

#define DECL_AMT_IDCT2(num,size,optim,depth)\
void emt_idct_##num##_##size##_v_##optim##_##depth(int16_t *x, int16_t *block);\
void emt_idct_##num##_##size##_h_##optim##_##depth(int16_t *x, int16_t *block);\
    EMT_DECL_V(num,size,optim,depth,0)\
        EMT_DECL_V(num,size,optim,depth,1)\
        EMT_DECL_V(num,size,optim,depth,2)\
        EMT_DECL_V(num,size,optim,depth,3)\
        EMT_DECL_V(num,size,optim,depth,4)\
        EMT_DECL_V(num,size,optim,depth,5)\
        EMT_DECL_V(num,size,optim,depth,6)\
        EMT_DECL_V(num,size,optim,depth,7)\
    void emt_idct_##num##_##size##_0_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_1_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_2_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_3_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_4_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_5_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_6_h_##optim##_##depth(int16_t *x, int16_t *block);\
    void emt_idct_##num##_##size##_7_h_##optim##_##depth(int16_t *x, int16_t *block);\


   DECL_AMT_IDCT(  II,4x4,avx2,8)
   DECL_AMT_IDCT(   V,4x4,avx2,8)
   DECL_AMT_IDCT(VIII,4x4,avx2,8)
   DECL_AMT_IDST( VII,4x4,avx2,8)
   DECL_AMT_IDST(   I,4x4,avx2,8)

   DECL_AMT_IDCT2(VIII,8x8,avx2,8)
   DECL_AMT_IDCT2( VII,8x8,avx2,8)
   DECL_AMT_IDCT2(   I,8x8,avx2,8)
   DECL_AMT_IDCT2(   V,8x8,avx2,8)
   DECL_AMT_IDCT2(  II,8x8,avx2,8)

   DECL_AMT_IDCT2(  II,16x16,avx2,8)
   DECL_AMT_IDCT2(   V,16x16,avx2,8)
   DECL_AMT_IDCT2(VIII,16x16,avx2,8)
   DECL_AMT_IDCT2(   I,16x16,avx2,8)
   DECL_AMT_IDCT2( VII,16x16,avx2,8)

   DECL_AMT_IDCT2(  II,32x32,avx2,8)
   DECL_AMT_IDCT2(   V,32x32,avx2,8)
   DECL_AMT_IDCT2(VIII,32x32,avx2,8)
   DECL_AMT_IDCT2(   I,32x32,avx2,8)
   DECL_AMT_IDCT2( VII,32x32,avx2,8)

   DECL_AMT_IDCT(  II,4x4,avx2,10)
   DECL_AMT_IDCT(   V,4x4,avx2,10)
   DECL_AMT_IDCT(VIII,4x4,avx2,10)
   DECL_AMT_IDST( VII,4x4,avx2,10)
   DECL_AMT_IDST(   I,4x4,avx2,10)

   DECL_AMT_IDCT2(VIII,8x8,avx2,10)
   DECL_AMT_IDCT2( VII,8x8,avx2,10)
   DECL_AMT_IDCT2(   I,8x8,avx2,10)
   DECL_AMT_IDCT2(   V,8x8,avx2,10)
   DECL_AMT_IDCT2(  II,8x8,avx2,10)

   DECL_AMT_IDCT2(  II,16x16,avx2,10)
   DECL_AMT_IDCT2(   V,16x16,avx2,10)
   DECL_AMT_IDCT2(VIII,16x16,avx2,10)
   DECL_AMT_IDCT2(   I,16x16,avx2,10)
   DECL_AMT_IDCT2( VII,16x16,avx2,10)

   DECL_AMT_IDCT2(  II,32x32,avx2,10)
   DECL_AMT_IDCT2(   V,32x32,avx2,10)
   DECL_AMT_IDCT2(VIII,32x32,avx2,10)
   DECL_AMT_IDCT2(   I,32x32,avx2,10)
   DECL_AMT_IDCT2( VII,32x32,avx2,10)
*/
//#endif
   //void oh_tr_add_8x8_10_avx2  (int16_t * /*restrict*/ dst, int16_t * /*restrict*/ src, int stride);
   //void oh_tr_add_16x16_10_avx2(int16_t * /*restrict*/ dst, int16_t * /*restrict*/ src, int stride);
   //void oh_tr_add_32x32_10_avx2(int16_t * /*restrict*/ dst, int16_t * /*restrict*/ src, int stride);
   void hevc_emt_avx2_c(HEVCContext *s,HEVCLocalContext *lc, HEVCTransformContext *tr_ctx, int16_t *tmp, int h, int v,int size);
   void hevc_emt_avx2_luma(HEVCContext *s,HEVCLocalContext *lc, HEVCTransformContext *tr_ctx, int16_t *tmp, int h, int v,int size);

#endif // AVCODEC_X86_HEVCDSP_H
