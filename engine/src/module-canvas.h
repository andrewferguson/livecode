/* Copyright (C) 2003-2014 Runtime Revolution Ltd.
 
 This file is part of LiveCode.
 
 LiveCode is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License v3 as published by the Free
 Software Foundation.
 
 LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.
 
 You should have received a copy of the GNU General Public License
 along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef _MODULE_CANVAS_H_
#define _MODULE_CANVAS_H_

#include <foundation.h>
#include <graphics.h>

////////////////////////////////////////////////////////////////////////////////

// TODO - move to MCImageRep wrapper library

struct MCGImageFrame
{
	MCGImageRef image;
	
	MCGFloat x_scale;
	MCGFloat y_scale;
};

// An MCImageBitmap is a non-premultiplied ARGB image, as decoded from the storage format
struct MCImageBitmap
{
	uint32_t width;
	uint32_t height;
	uint32_t stride;
	uint32_t *data;
	
	bool has_transparency;
	bool has_alpha;
};

class MCImageRep;

MCImageRep *MCImageRepRetain(MCImageRep *p_image_rep);
void MCImageRepRelease(MCImageRep *p_image_rep);
bool MCImageRepCreateWithPath(MCStringRef p_path, MCImageRep *&r_image_rep);
bool MCImageRepCreateWithData(MCDataRef p_data, MCImageRep *&r_image_rep);
bool MCImageRepCreateWithPixels(MCDataRef p_pixels, uint32_t p_width, uint32_t p_height, MCGPixelFormat p_format, bool p_premultiplied, MCImageRep *&r_image_rep);
bool MCImageRepGetGeometry(MCImageRep *p_image_rep, uint32_t &r_width, uint32_t &r_height);
bool MCImageRepGetFrameDuration(MCImageRep *p_image_rep, uint32_t p_frame, uint32_t &r_duration);

bool MCImageRepLock(MCImageRep *p_image_rep, uint32_t p_index, MCGFloat p_density, MCGImageFrame &r_frame);
void MCImageRepUnlock(MCImageRep *p_image_rep, uint32_t p_index, MCGImageFrame &p_frame);

bool MCImageRepLockRaster(MCImageRep *p_image_rep, uint32_t p_index, MCGFloat p_density, MCImageBitmap *&r_raster);
void MCImageRepUnlockRaster(MCImageRep *p_image_rep, uint32_t p_index, MCImageBitmap *p_raster);

//////////

bool MCImageRepGetTransformed(MCImageRep *p_image_rep, const MCGAffineTransform &p_transform, const MCGSize *p_output_size, MCGImageFilter p_resize_quality, MCImageRep *&r_transformed);

////////////////////////////////////////////////////////////////////////////////

// TODO - move to foundation library ?
template <class T>
struct MCCArray
{
	T *data;
	uint32_t length;
};

////////////////////////////////////////////////////////////////////////////////

// Module initialization
bool MCCanvasModuleInitialize();
void MCCanvasModuleFinalize();

void MCCanvasPush(MCGContextRef gcontext);
void MCCanvasPop(void);

////////////////////////////////////////////////////////////////////////////////
// Type Definitions

extern "C"
{

typedef MCGFloat MCCanvasFloat;

typedef struct __MCCanvasRectangle *MCCanvasRectangleRef;
typedef struct __MCCanvasPoint *MCCanvasPointRef;
typedef struct __MCCanvasColor *MCCanvasColorRef;
typedef struct __MCCanvasTransform *MCCanvasTransformRef;
typedef struct __MCCanvasImage *MCCanvasImageRef;
typedef struct __MCCanvasPaint *MCCanvasPaintRef;
typedef struct __MCCanvasSolidPaint *MCCanvasSolidPaintRef;
typedef struct __MCCanvasPattern *MCCanvasPatternRef;
typedef struct __MCCanvasGradient *MCCanvasGradientRef;
typedef struct __MCCanvasGradientStop *MCCanvasGradientStopRef;
typedef struct __MCCanvasPath *MCCanvasPathRef;
typedef struct __MCCanvasEffect *MCCanvasEffectRef;
typedef struct __MCCanvas *MCCanvasRef;

extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasRectangleTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasPointTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasColorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasTransformTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasImageTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasPaintTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasSolidPaintTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasPatternTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasGradientTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasGradientStopTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasPathTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasEffectTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasTypeInfo;

// Constant refs
extern MCCanvasTransformRef kMCCanvasIdentityTransform;

extern MCCanvasColorRef kMCCanvasColorBlack;

////////////////////////////////////////////////////////////////////////////////
// Canvas Errors

extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasRectangleListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasPointListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasColorListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasScaleListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasTranslationListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasSkewListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasRadiiListFormatErrorTypeInfo;
extern MC_DLLEXPORT MCTypeInfoRef kMCCanvasImageSizeListFormatErrorTypeInfo;


}

////////////////////////////////////////////////////////////////////////////////

bool MCCanvasRectangleCreateWithMCGRectangle(const MCGRectangle &p_rect, MCCanvasRectangleRef &r_rectangle);
void MCCanvasRectangleGetMCGRectangle(MCCanvasRectangleRef p_rectangle, MCGRectangle &r_rect);

bool MCCanvasPointCreateWithMCGPoint(const MCGPoint &p_point, MCCanvasPointRef &r_point);
void MCCanvasPointGetMCGPoint(MCCanvasPointRef p_point, MCGPoint &r_point);

bool MCCanvasColorCreateWithRGBA(MCCanvasFloat red, MCCanvasFloat green, MCCanvasFloat blue, MCCanvasFloat alpha, MCCanvasColorRef &r_color);

bool MCCanvasTransformCreateWithMCGAffineTransform(const MCGAffineTransform &p_transform, MCCanvasTransformRef &r_transform);
void MCCanvasTransformGetMCGAffineTransform(MCCanvasTransformRef p_transform, MCGAffineTransform &r_transform);

bool MCCanvasImageCreateWithImageRep(MCImageRep *p_rep, MCCanvasImageRef &r_image);
MCImageRep *MCCanvasImageGetImageRep(MCCanvasImageRef p_image);

bool MCCanvasSolidPaintCreateWithColor(MCCanvasColorRef p_color, MCCanvasSolidPaintRef &r_paint);
bool MCCanvasPatternCreateWithImage(MCCanvasImageRef p_image, MCCanvasTransformRef p_transform, MCCanvasPatternRef &r_pattern);
bool MCCanvasGradientStopCreate(MCCanvasFloat p_offset, MCCanvasColorRef p_color, MCCanvasGradientStopRef &r_stop);
bool MCCanvasGradientCreateWithRamp(integer_t p_type, MCProperListRef p_ramp, MCCanvasGradientRef &r_gradient);

bool MCCanvasPathCreateWithMCGPath(MCGPathRef p_path, MCCanvasPathRef &r_path);
MCGPathRef MCCanvasPathGetMCGPath(MCCanvasPathRef p_path);

bool MCCanvasEffectCreateWithPropertyArray(integer_t p_type, MCArrayRef p_properties, MCCanvasEffectRef &r_effect);


extern "C" MC_DLLEXPORT bool MCCanvasCreate(MCGContextRef p_context, MCCanvasRef &r_canvas);

////////////////////////////////////////////////////////////////////////////////

// Rectangle

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasRectangleMakeWithLTRB(MCCanvasFloat p_left, MCCanvasFloat p_top, MCCanvasFloat p_right, MCCanvasFloat p_bottom, MCCanvasRectangleRef &r_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleMakeWithList(MCProperListRef p_list, MCCanvasRectangleRef &r_point);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetLeft(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_left);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetLeft(MCCanvasFloat p_left, MCCanvasRectangleRef &x_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetTop(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_top);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetTop(MCCanvasFloat p_top, MCCanvasRectangleRef &x_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetRight(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_right);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetRight(MCCanvasFloat p_right, MCCanvasRectangleRef &x_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetBottom(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_bottom);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetBottom(MCCanvasFloat p_bottom, MCCanvasRectangleRef &x_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetWidth(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_width);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetWidth(MCCanvasFloat p_width, MCCanvasRectangleRef &x_rect);
extern "C" MC_DLLEXPORT void MCCanvasRectangleGetHeight(MCCanvasRectangleRef p_rect, MCCanvasFloat &r_height);
extern "C" MC_DLLEXPORT void MCCanvasRectangleSetHeight(MCCanvasFloat p_height, MCCanvasRectangleRef &x_rect);

//////////

// Point

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasPointMake(MCCanvasFloat p_x, MCCanvasFloat p_y, MCCanvasPointRef &r_point);
extern "C" MC_DLLEXPORT void MCCanvasPointMakeWithList(MCProperListRef p_list, MCCanvasPointRef &r_list);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasPointGetX(MCCanvasPointRef p_point, MCCanvasFloat &r_x);
extern "C" MC_DLLEXPORT void MCCanvasPointSetX(MCCanvasFloat p_x, MCCanvasPointRef &x_point);
extern "C" MC_DLLEXPORT void MCCanvasPointGetY(MCCanvasPointRef p_point, MCCanvasFloat &r_y);
extern "C" MC_DLLEXPORT void MCCanvasPointSetY(MCCanvasFloat p_y, MCCanvasPointRef &x_point);

//////////

// Color

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasColorMakeRGBA(MCCanvasFloat p_red, MCCanvasFloat p_green, MCCanvasFloat p_blue, MCCanvasFloat p_alpha, MCCanvasColorRef &r_color);
extern "C" MC_DLLEXPORT void MCCanvasColorMakeWithList(MCProperListRef p_list, MCCanvasColorRef &r_color);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasColorGetRed(MCCanvasColorRef p_color, MCCanvasFloat &r_red);
extern "C" MC_DLLEXPORT void MCCanvasColorSetRed(MCCanvasFloat p_red, MCCanvasColorRef &x_color);
extern "C" MC_DLLEXPORT void MCCanvasColorGetGreen(MCCanvasColorRef p_color, MCCanvasFloat &r_green);
extern "C" MC_DLLEXPORT void MCCanvasColorSetGreen(MCCanvasFloat p_green, MCCanvasColorRef &x_color);
extern "C" MC_DLLEXPORT void MCCanvasColorGetBlue(MCCanvasColorRef p_color, MCCanvasFloat &r_blue);
extern "C" MC_DLLEXPORT void MCCanvasColorSetBlue(MCCanvasFloat p_blue, MCCanvasColorRef &x_color);
extern "C" MC_DLLEXPORT void MCCanvasColorGetAlpha(MCCanvasColorRef p_color, MCCanvasFloat &r_alpha);
extern "C" MC_DLLEXPORT void MCCanvasColorSetAlpha(MCCanvasFloat p_alpha, MCCanvasColorRef &x_color);

//////////

// Transform

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeIdentity(MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeScale(MCCanvasFloat p_xscale, MCCanvasFloat p_yscale, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeScaleWithList(MCProperListRef p_list, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeRotation(MCCanvasFloat p_angle, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeTranslation(MCCanvasFloat p_x, MCCanvasFloat p_y, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeTranslationWithList(MCProperListRef p_list, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeSkew(MCCanvasFloat p_x, MCCanvasFloat p_y, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeSkewWithList(MCProperListRef p_list, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformMakeWithMatrixValues(MCCanvasFloat p_a, MCCanvasFloat p_b, MCCanvasFloat p_c, MCCanvasFloat p_d, MCCanvasFloat p_tx, MCCanvasFloat p_ty, MCCanvasTransformRef &r_transform);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasTransformGetMatrix(MCCanvasTransformRef p_transform, MCArrayRef &r_matrix);
extern "C" MC_DLLEXPORT void MCCanvasTransformSetMatrix(MCArrayRef p_matrix, MCCanvasTransformRef &x_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformGetInverse(MCCanvasTransformRef p_transform, MCCanvasTransformRef &r_transform);
// T = Tscale * Trotate * Tskew * Ttranslate
extern "C" MC_DLLEXPORT void MCCanvasTransformGetScale(MCCanvasTransformRef p_transform, MCCanvasPointRef &r_scale);
extern "C" MC_DLLEXPORT void MCCanvasTransformSetScale(MCCanvasPointRef p_scale, MCCanvasTransformRef &x_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformGetRotation(MCCanvasTransformRef p_transform, MCCanvasFloat &r_rotation);
extern "C" MC_DLLEXPORT void MCCanvasTransformSetRotation(MCCanvasFloat p_rotation, MCCanvasTransformRef &x_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformGetSkew(MCCanvasTransformRef p_transform, MCCanvasPointRef &r_skew);
extern "C" MC_DLLEXPORT void MCCanvasTransformSetSkew(MCCanvasPointRef p_skew, MCCanvasTransformRef &x_transform);
extern "C" MC_DLLEXPORT void MCCanvasTransformGetTranslation(MCCanvasTransformRef p_transform, MCCanvasPointRef &r_translation);
extern "C" MC_DLLEXPORT void MCCanvasTransformSetTranslation(MCCanvasPointRef p_translation, MCCanvasTransformRef &x_transform);

// Operations
extern "C" MC_DLLEXPORT void MCCanvasTransformConcat(MCCanvasTransformRef &x_transform_a, MCCanvasTransformRef p_transform_b);
extern "C" MC_DLLEXPORT void MCCanvasTransformScale(MCCanvasTransformRef &x_transform, MCCanvasFloat p_x_scale, MCCanvasFloat p_y_scale);
extern "C" MC_DLLEXPORT void MCCanvasTransformScaleWithList(MCCanvasTransformRef &x_transform, MCProperListRef p_list);
extern "C" MC_DLLEXPORT void MCCanvasTransformRotate(MCCanvasTransformRef &x_transform, MCCanvasFloat p_rotation);
extern "C" MC_DLLEXPORT void MCCanvasTransformTranslate(MCCanvasTransformRef &x_transform, MCCanvasFloat p_dx, MCCanvasFloat p_dy);
extern "C" MC_DLLEXPORT void MCCanvasTransformTranslateWithList(MCCanvasTransformRef &x_transform, MCProperListRef p_list);
extern "C" MC_DLLEXPORT void MCCanvasTransformSkew(MCCanvasTransformRef &x_transform, MCCanvasFloat p_x_skew, MCCanvasFloat p_y_skew);
extern "C" MC_DLLEXPORT void MCCanvasTransformSkewWithList(MCCanvasTransformRef &x_transform, MCProperListRef p_list);

//////////

// Image

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasImageMakeWithPath(MCStringRef p_path, MCCanvasImageRef &x_image);
extern "C" MC_DLLEXPORT void MCCanvasImageMakeWithData(MCDataRef p_data, MCCanvasImageRef &x_image);
extern "C" MC_DLLEXPORT void MCCanvasImageMakeWithPixels(integer_t p_width, integer_t p_height, MCDataRef p_pixels, MCCanvasImageRef &x_image);
extern "C" MC_DLLEXPORT void MCCanvasImageMakeWithPixelsWithSizeAsList(MCProperListRef p_size, MCDataRef p_pixels, MCCanvasImageRef &x_image);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasImageGetWidth(MCCanvasImageRef p_image, uint32_t &r_width);
extern "C" MC_DLLEXPORT void MCCanvasImageGetHeight(MCCanvasImageRef p_image, uint32_t &r_height);
extern "C" MC_DLLEXPORT void MCCanvasImageGetPixels(MCCanvasImageRef p_image, MCDataRef &r_pixels);
// TODO - Add support for image metadata
//void MCCanvasImageGetMetadata(const MCCanvasImage &p_image, MCArrayRef &r_metadata);

// TODO - Implement image operations
//void MCCanvasImageTransform(MCCanvasImage &x_image, const MCCanvasTransform &p_transform);
//void MCCanvasImageScale(MCCanvasImage &x_image, MCCanvasFloat p_x_scale, MCCanvasFloat p_y_scale);
//void MCCanvasImageRotate(MCCanvasImage &x_image, MCCanvasFloat p_angle);
//void MCCanvasImageCrop(MCCanvasImage &x_image, const MCCanvasRectangle &p_rect);

//////////

// Solid Paint

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasSolidPaintMakeWithColor(MCCanvasColorRef p_color, MCCanvasSolidPaintRef &r_paint);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasSolidPaintGetColor(MCCanvasSolidPaintRef p_paint, MCCanvasColorRef &r_color);
extern "C" MC_DLLEXPORT void MCCanvasSolidPaintSetColor(MCCanvasColorRef p_color, MCCanvasSolidPaintRef &x_paint);

//////////

// Pattern

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithImage(MCCanvasImageRef p_image, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithTransformedImage(MCCanvasImageRef p_image, MCCanvasTransformRef p_transform, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithScaledImage(MCCanvasImageRef p_image, MCCanvasFloat p_xscale, MCCanvasFloat p_yscale, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithImageScaledWithList(MCCanvasImageRef p_image, MCProperListRef p_list, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithRotatedImage(MCCanvasImageRef p_image, MCCanvasFloat p_angle, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithTranslatedImage(MCCanvasImageRef p_image, MCCanvasFloat p_x, MCCanvasFloat p_y, MCCanvasPatternRef &r_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternMakeWithImageTranslatedWithList(MCCanvasImageRef p_image, MCProperListRef p_list, MCCanvasPatternRef &r_pattern);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasPatternGetImage(MCCanvasPatternRef p_pattern, MCCanvasImageRef &r_image);
extern "C" MC_DLLEXPORT void MCCanvasPatternSetImage(MCCanvasImageRef p_image, MCCanvasPatternRef &x_pattern);
extern "C" MC_DLLEXPORT void MCCanvasPatternGetTransform(MCCanvasPatternRef p_pattern, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasPatternSetTransform(MCCanvasTransformRef p_transform, MCCanvasPatternRef &x_pattern);

// Operations
extern "C" MC_DLLEXPORT void MCCanvasPatternTransform(MCCanvasPatternRef &x_pattern, MCCanvasTransformRef p_transform);
extern "C" MC_DLLEXPORT void MCCanvasPatternScale(MCCanvasPatternRef &x_pattern, MCCanvasFloat p_xscale, MCCanvasFloat p_yscale);
extern "C" MC_DLLEXPORT void MCCanvasPatternScaleWithList(MCCanvasPatternRef &x_pattern, MCProperListRef p_scale);
extern "C" MC_DLLEXPORT void MCCanvasPatternRotate(MCCanvasPatternRef &x_pattern, MCCanvasFloat p_angle);
extern "C" MC_DLLEXPORT void MCCanvasPatternTranslate(MCCanvasPatternRef &x_pattern, MCCanvasFloat p_x, MCCanvasFloat p_y);
extern "C" MC_DLLEXPORT void MCCanvasPatternTranslateWithList(MCCanvasPatternRef &x_pattern, MCProperListRef p_translation);
// TODO - add skew?"

//////////

// Gradient Stop

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasGradientStopMake(MCCanvasFloat p_offset, MCCanvasColorRef p_color, MCCanvasGradientStopRef &r_stop);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasGradientStopGetOffset(MCCanvasGradientStopRef p_stop, MCCanvasFloat &r_offset);
extern "C" MC_DLLEXPORT void MCCanvasGradientStopSetOffset(MCCanvasFloat p_offset, MCCanvasGradientStopRef &x_stop);
extern "C" MC_DLLEXPORT void MCCanvasGradientStopGetColor(MCCanvasGradientStopRef p_stop, MCCanvasColorRef &r_color);
extern "C" MC_DLLEXPORT void MCCanvasGradientStopSetColor(MCCanvasColorRef p_color, MCCanvasGradientStopRef &x_stop);

// Gradient

extern "C" MC_DLLEXPORT void MCCanvasGradientEvaluateType(integer_t p_type, integer_t& r_type);

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasGradientMakeWithRamp(integer_t p_type, MCProperListRef p_ramp, MCCanvasGradientRef &r_gradient);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasGradientGetRamp(MCCanvasGradientRef p_gradient, MCProperListRef &r_ramp);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetRamp(MCProperListRef p_ramp, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetTypeAsString(MCCanvasGradientRef p_gradient, MCStringRef &r_string);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetTypeAsString(MCStringRef p_string, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetRepeat(MCCanvasGradientRef p_gradient, integer_t &r_repeat);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetRepeat(integer_t p_repeat, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetWrap(MCCanvasGradientRef p_gradient, bool &r_wrap);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetWrap(bool p_wrap, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetMirror(MCCanvasGradientRef p_gradient, bool &r_mirror);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetMirror(bool p_mirror, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetFrom(MCCanvasGradientRef p_gradient, MCCanvasPointRef &r_from);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetFrom(MCCanvasPointRef p_from, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetTo(MCCanvasGradientRef p_gradient, MCCanvasPointRef &r_to);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetTo(MCCanvasPointRef p_to, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetVia(MCCanvasGradientRef p_gradient, MCCanvasPointRef &r_via);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetVia(MCCanvasPointRef p_via, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientGetTransform(MCCanvasGradientRef p_gradient, MCCanvasTransformRef &r_transform);
extern "C" MC_DLLEXPORT void MCCanvasGradientSetTransform(MCCanvasTransformRef p_transform, MCCanvasGradientRef &x_gradient);

// Operators
extern "C" MC_DLLEXPORT void MCCanvasGradientAddStop(MCCanvasGradientStopRef p_stop, MCCanvasGradientRef &x_gradient);
extern "C" MC_DLLEXPORT void MCCanvasGradientTransform(MCCanvasGradientRef &x_gradient, MCCanvasTransformRef p_transform);
extern "C" MC_DLLEXPORT void MCCanvasGradientScale(MCCanvasGradientRef &x_gradient, MCCanvasFloat p_xscale, MCCanvasFloat p_yscale);
extern "C" MC_DLLEXPORT void MCCanvasGradientScaleWithList(MCCanvasGradientRef &x_gradient, MCProperListRef p_scale);
extern "C" MC_DLLEXPORT void MCCanvasGradientRotate(MCCanvasGradientRef &x_gradient, MCCanvasFloat p_angle);
extern "C" MC_DLLEXPORT void MCCanvasGradientTranslate(MCCanvasGradientRef &x_gradient, MCCanvasFloat p_x, MCCanvasFloat p_y);
extern "C" MC_DLLEXPORT void MCCanvasGradientTranslateWithList(MCCanvasGradientRef &x_gradient, MCProperListRef p_translation);

//////////

// Path

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithInstructionsAsString(MCStringRef p_instructions, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithRectangle(MCCanvasRectangleRef p_rect, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithRoundedRectangle(MCCanvasRectangleRef p_rect, MCCanvasFloat p_radius, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithRoundedRectangleWithRadii(MCCanvasRectangleRef p_rect, MCCanvasFloat p_x_radius, MCCanvasFloat p_y_radius, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithRoundedRectangleWithRadiiAsList(MCCanvasRectangleRef p_rect, MCProperListRef p_radii, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithRectangle(MCCanvasRectangleRef p_rect, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithEllipse(MCCanvasPointRef p_center, MCCanvasFloat p_radius_x, MCCanvasFloat p_radius_y, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithEllipseWithRadiiAsList(MCCanvasPointRef p_center, MCProperListRef p_radii, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithCircle(MCCanvasPointRef p_center, MCCanvasFloat p_radius, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithLine(MCCanvasPointRef p_start, MCCanvasPointRef p_end, MCCanvasPathRef &r_path);
extern "C" MC_DLLEXPORT void MCCanvasPathMakeWithPoints(bool p_close, MCProperListRef p_points, MCCanvasPathRef &r_path);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasPathGetSubpaths(integer_t p_start, integer_t p_end, MCCanvasPathRef p_path, MCCanvasPathRef &r_subpaths);
extern "C" MC_DLLEXPORT void MCCanvasPathGetSubpath(integer_t p_index, MCCanvasPathRef p_path, MCCanvasPathRef &r_subpaths);
extern "C" MC_DLLEXPORT void MCCanvasPathGetBoundingBox(MCCanvasPathRef p_path, MCCanvasRectangleRef &r_bounds);
extern "C" MC_DLLEXPORT void MCCanvasPathGetInstructionsAsString(MCCanvasPathRef p_path, MCStringRef &r_instruction_string);

// Operations
extern "C" MC_DLLEXPORT void MCCanvasPathTransform(MCCanvasPathRef &x_path, MCCanvasTransformRef p_transform);
extern "C" MC_DLLEXPORT void MCCanvasPathScale(MCCanvasPathRef &x_path, MCCanvasFloat p_xscale, MCCanvasFloat p_yscale);
extern "C" MC_DLLEXPORT void MCCanvasPathScaleWithList(MCCanvasPathRef &x_path, MCProperListRef p_scale);
extern "C" MC_DLLEXPORT void MCCanvasPathRotate(MCCanvasPathRef &x_path, MCCanvasFloat p_angle);
extern "C" MC_DLLEXPORT void MCCanvasPathTranslate(MCCanvasPathRef &x_path, MCCanvasFloat p_x, MCCanvasFloat p_y);
extern "C" MC_DLLEXPORT void MCCanvasPathTranslateWithList(MCCanvasPathRef &x_path, MCProperListRef p_translation);
extern "C" MC_DLLEXPORT void MCCanvasPathAddPath(MCCanvasPathRef p_source, MCCanvasPathRef &x_dest);
extern "C" MC_DLLEXPORT void MCCanvasPathMoveTo(MCCanvasPointRef p_point, MCCanvasPathRef &x_path);
extern "C" MC_DLLEXPORT void MCCanvasPathLineTo(MCCanvasPointRef p_point, MCCanvasPathRef &x_path);
extern "C" MC_DLLEXPORT void MCCanvasPathCurveThroughPoint(MCCanvasPointRef p_through, MCCanvasPointRef p_to, MCCanvasPathRef &x_path);
extern "C" MC_DLLEXPORT void MCCanvasPathCurveThroughPoints(MCCanvasPointRef p_through_a, MCCanvasPointRef p_through_b, MCCanvasPointRef p_to, MCCanvasPathRef &x_path);
extern "C" MC_DLLEXPORT void MCCanvasPathClosePath(MCCanvasPathRef &x_path);

//////////

// Effect

extern "C" MC_DLLEXPORT void MCCanvasEffectEvaluateType(integer_t p_type, integer_t &r_type);

// Constructors
extern "C" MC_DLLEXPORT void MCCanvasEffectMakeWithPropertyArray(integer_t p_type, MCArrayRef p_properties, MCCanvasEffectRef &r_effect);

// Properties
extern "C" MC_DLLEXPORT void MCCanvasEffectGetTypeAsString(MCCanvasEffectRef p_effect, MCStringRef &r_type);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetColor(MCCanvasEffectRef p_effect, MCCanvasColorRef &r_color);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetColor(MCCanvasColorRef p_color, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetBlendModeAsString(MCCanvasEffectRef p_effect, MCStringRef &r_blend_mode);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetBlendModeAsString(MCStringRef p_blend_mode, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetOpacity(MCCanvasEffectRef p_effect, MCCanvasFloat &r_opacity);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetOpacity(MCCanvasFloat p_opacity, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetSize(MCCanvasEffectRef p_effect, MCCanvasFloat &r_size);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetSize(MCCanvasFloat p_size, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetSpread(MCCanvasEffectRef p_effect, MCCanvasFloat &r_spread);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetSpread(MCCanvasFloat p_spread, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetDistance(MCCanvasEffectRef p_effect, MCCanvasFloat &r_distance);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetDistance(MCCanvasFloat p_distance, MCCanvasEffectRef &x_effect);
extern "C" MC_DLLEXPORT void MCCanvasEffectGetAngle(MCCanvasEffectRef p_effect, MCCanvasFloat &r_angle);
extern "C" MC_DLLEXPORT void MCCanvasEffectSetAngle(MCCanvasFloat p_angle, MCCanvasEffectRef &x_effect);

//////////

// Canvas

// Properties
extern "C" MC_DLLEXPORT void MCCanvasGetPaint(MCCanvasRef p_canvas, MCCanvasPaintRef &r_paint);
extern "C" MC_DLLEXPORT void MCCanvasSetPaint(MCCanvasPaintRef p_paint, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetFillRuleAsString(MCCanvasRef p_canvas, MCStringRef &r_string);
extern "C" MC_DLLEXPORT void MCCanvasSetFillRuleAsString(MCStringRef p_string, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetAntialias(MCCanvasRef p_canvas, bool &r_antialias);
extern "C" MC_DLLEXPORT void MCCanvasSetAntialias(bool p_antialias, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetOpacity(MCCanvasRef p_canvas, MCCanvasFloat &r_opacity);
extern "C" MC_DLLEXPORT void MCCanvasSetOpacity(MCCanvasFloat p_opacity, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetBlendModeAsString(MCCanvasRef p_canvas, MCStringRef &r_blend_mode);
extern "C" MC_DLLEXPORT void MCCanvasSetBlendModeAsString(MCStringRef p_blend_mode, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetStippled(MCCanvasRef p_canvas, bool &r_stippled);
extern "C" MC_DLLEXPORT void MCCanvasSetStippled(bool p_stippled, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasGetImageResizeQualityAsString(MCCanvasRef p_canvas, MCStringRef &r_quality);
extern "C" MC_DLLEXPORT void MCCanvasSetImageResizeQualityAsString(MCStringRef p_quality, MCCanvasRef p_canvas);

// Operations
extern "C" MC_DLLEXPORT void MCCanvasTransform(MCCanvasRef p_canvas, MCCanvasTransformRef p_transform);
extern "C" MC_DLLEXPORT void MCCanvasScale(MCCanvasRef p_canvas, MCCanvasFloat p_scale_x, MCCanvasFloat p_scale_y);
extern "C" MC_DLLEXPORT void MCCanvasScaleWithList(MCCanvasRef p_canvas, MCProperListRef p_scale);
extern "C" MC_DLLEXPORT void MCCanvasRotate(MCCanvasRef p_canvas, MCCanvasFloat p_angle);
extern "C" MC_DLLEXPORT void MCCanvasTranslate(MCCanvasRef p_canvas, MCCanvasFloat p_x, MCCanvasFloat p_y);
extern "C" MC_DLLEXPORT void MCCanvasTranslateWithList(MCCanvasRef p_canvas, MCProperListRef p_translation);
extern "C" MC_DLLEXPORT void MCCanvasSaveState(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasRestore(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasBeginLayer(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasBeginLayerWithEffect(MCCanvasEffectRef p_effect, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasEndLayer(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasFill(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasFillPath(MCCanvasPathRef p_path, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasStroke(MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasStrokePath(MCCanvasPathRef p_path, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasClipToRect(MCCanvasRectangleRef p_rect, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasAddPath(MCCanvasPathRef p_path, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasDrawRectOfImage(MCCanvasRectangleRef p_src_rect, MCCanvasImageRef p_image, MCCanvasRectangleRef p_dst_rect, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasMoveTo(MCCanvasPointRef p_point, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasLineTo(MCCanvasPointRef p_point, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasCurveThroughPoint(MCCanvasPointRef p_through, MCCanvasPointRef p_to, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasCurveThroughPoints(MCCanvasPointRef p_through_a, MCCanvasPointRef p_through_b, MCCanvasPointRef p_to, MCCanvasRef p_canvas);
extern "C" MC_DLLEXPORT void MCCanvasClosePath(MCCanvasRef p_canvas);

////////////////////////////////////////////////////////////////////////////////

#endif//_MODULE_CANVAS_H_
