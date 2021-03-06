/*
Copyright (c) 2015 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef HIP_INCLUDE_HIP_HCC_DETAIL_DRIVER_TYPES_H
#define HIP_INCLUDE_HIP_HCC_DETAIL_DRIVER_TYPES_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef void* hipDeviceptr_t;
typedef enum hipChannelFormatKind {
    hipChannelFormatKindSigned = 0,
    hipChannelFormatKindUnsigned = 1,
    hipChannelFormatKindFloat = 2,
    hipChannelFormatKindNone = 3
}hipChannelFormatKind;

typedef struct hipChannelFormatDesc {
    int x;
    int y;
    int z;
    int w;
    enum hipChannelFormatKind f;
}hipChannelFormatDesc;

#define HIP_TRSF_NORMALIZED_COORDINATES 0x01
#define HIP_TRSF_READ_AS_INTEGER 0x00
#define HIP_TRSA_OVERRIDE_FORMAT 0x01

typedef enum hipArray_Format {
    HIP_AD_FORMAT_UNSIGNED_INT8 = 0x01,
    HIP_AD_FORMAT_UNSIGNED_INT16 = 0x02,
    HIP_AD_FORMAT_UNSIGNED_INT32 = 0x03,
    HIP_AD_FORMAT_SIGNED_INT8 = 0x08,
    HIP_AD_FORMAT_SIGNED_INT16 = 0x09,
    HIP_AD_FORMAT_SIGNED_INT32 = 0x0a,
    HIP_AD_FORMAT_HALF = 0x10,
    HIP_AD_FORMAT_FLOAT = 0x20
}hipArray_Format;

typedef struct HIP_ARRAY_DESCRIPTOR {
    enum hipArray_Format format;
    unsigned int numChannels;
    size_t width;
    size_t height;
    unsigned int flags;
    size_t depth;
}HIP_ARRAY_DESCRIPTOR;

typedef struct hipArray {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int type;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    struct HIP_ARRAY_DESCRIPTOR drvDesc;
    bool isDrv;
    unsigned int textureType;
}hipArray;

typedef struct hip_Memcpy2D {
    size_t height;
    size_t widthInBytes;
    hipArray* dstArray;
    hipDeviceptr_t dstDevice;
    void* dstHost;
    hipMemoryType dstMemoryType;
    size_t dstPitch;
    size_t dstXInBytes;
    size_t dstY;
    hipArray* srcArray;
    hipDeviceptr_t srcDevice;
    const void* srcHost;
    hipMemoryType srcMemoryType;
    size_t srcPitch;
    size_t srcXInBytes;
    size_t srcY;
} hip_Memcpy2D;


typedef struct hipArray* hipArray_t;

typedef const struct hipArray* hipArray_const_t;

// TODO: It needs to be modified since it was just copied from hipArray.
struct hipMipmappedArray {
    void* data;  // FIXME: generalize this
    struct hipChannelFormatDesc desc;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
};

typedef struct hipMipmappedArray* hipMipmappedArray_t;

typedef const struct hipMipmappedArray* hipMipmappedArray_const_t;

/**
 * hip resource types
 */
typedef enum hipResourceType {
    hipResourceTypeArray = 0x00,
    hipResourceTypeMipmappedArray = 0x01,
    hipResourceTypeLinear = 0x02,
    hipResourceTypePitch2D = 0x03
}hipResourceType;

/**
 * hip texture resource view formats
 */
typedef enum hipResourceViewFormat {
    hipResViewFormatNone = 0x00,
    hipResViewFormatUnsignedChar1 = 0x01,
    hipResViewFormatUnsignedChar2 = 0x02,
    hipResViewFormatUnsignedChar4 = 0x03,
    hipResViewFormatSignedChar1 = 0x04,
    hipResViewFormatSignedChar2 = 0x05,
    hipResViewFormatSignedChar4 = 0x06,
    hipResViewFormatUnsignedShort1 = 0x07,
    hipResViewFormatUnsignedShort2 = 0x08,
    hipResViewFormatUnsignedShort4 = 0x09,
    hipResViewFormatSignedShort1 = 0x0a,
    hipResViewFormatSignedShort2 = 0x0b,
    hipResViewFormatSignedShort4 = 0x0c,
    hipResViewFormatUnsignedInt1 = 0x0d,
    hipResViewFormatUnsignedInt2 = 0x0e,
    hipResViewFormatUnsignedInt4 = 0x0f,
    hipResViewFormatSignedInt1 = 0x10,
    hipResViewFormatSignedInt2 = 0x11,
    hipResViewFormatSignedInt4 = 0x12,
    hipResViewFormatHalf1 = 0x13,
    hipResViewFormatHalf2 = 0x14,
    hipResViewFormatHalf4 = 0x15,
    hipResViewFormatFloat1 = 0x16,
    hipResViewFormatFloat2 = 0x17,
    hipResViewFormatFloat4 = 0x18,
    hipResViewFormatUnsignedBlockCompressed1 = 0x19,
    hipResViewFormatUnsignedBlockCompressed2 = 0x1a,
    hipResViewFormatUnsignedBlockCompressed3 = 0x1b,
    hipResViewFormatUnsignedBlockCompressed4 = 0x1c,
    hipResViewFormatSignedBlockCompressed4 = 0x1d,
    hipResViewFormatUnsignedBlockCompressed5 = 0x1e,
    hipResViewFormatSignedBlockCompressed5 = 0x1f,
    hipResViewFormatUnsignedBlockCompressed6H = 0x20,
    hipResViewFormatSignedBlockCompressed6H = 0x21,
    hipResViewFormatUnsignedBlockCompressed7 = 0x22
}hipResourceViewFormat;

/**
 * HIP resource descriptor
 */
typedef struct hipResourceDesc {
    enum hipResourceType resType;

    union {
        struct {
            hipArray_t array;
        } array;
        struct {
            hipMipmappedArray_t mipmap;
        } mipmap;
        struct {
            void* devPtr;
            struct hipChannelFormatDesc desc;
            size_t sizeInBytes;
        } linear;
        struct {
            void* devPtr;
            struct hipChannelFormatDesc desc;
            size_t width;
            size_t height;
            size_t pitchInBytes;
        } pitch2D;
    } res;
}hipResourceDesc;

/**
 * hip resource view descriptor
 */
struct hipResourceViewDesc {
    enum hipResourceViewFormat format;
    size_t width;
    size_t height;
    size_t depth;
    unsigned int firstMipmapLevel;
    unsigned int lastMipmapLevel;
    unsigned int firstLayer;
    unsigned int lastLayer;
};

/**
 * Memory copy types
 *
 */
typedef enum hipMemcpyKind {
    hipMemcpyHostToHost = 0,      ///< Host-to-Host Copy
    hipMemcpyHostToDevice = 1,    ///< Host-to-Device Copy
    hipMemcpyDeviceToHost = 2,    ///< Device-to-Host Copy
    hipMemcpyDeviceToDevice = 3,  ///< Device-to-Device Copy
    hipMemcpyDefault =
        4  ///< Runtime will automatically determine copy-kind based on virtual addresses.
} hipMemcpyKind;

typedef struct hipPitchedPtr {
    void* ptr;
    size_t pitch;
    size_t xsize;
    size_t ysize;
}hipPitchedPtr;

typedef struct hipExtent {
    size_t width;  // Width in elements when referring to array memory, in bytes when referring to
                   // linear memory
    size_t height;
    size_t depth;
}hipExtent;

typedef struct hipPos {
    size_t x;
    size_t y;
    size_t z;
}hipPos;

typedef struct hipMemcpy3DParms {
    hipArray_t srcArray;
    struct hipPos srcPos;
    struct hipPitchedPtr srcPtr;

    hipArray_t dstArray;
    struct hipPos dstPos;
    struct hipPitchedPtr dstPtr;

    struct hipExtent extent;
    enum hipMemcpyKind kind;

    size_t Depth;
    size_t Height;
    size_t WidthInBytes;
    hipDeviceptr_t dstDevice;
    size_t dstHeight;
    void* dstHost;
    size_t dstLOD;
    hipMemoryType dstMemoryType;
    size_t dstPitch;
    size_t dstXInBytes;
    size_t dstY;
    size_t dstZ;
    void* reserved0;
    void* reserved1;
    hipDeviceptr_t srcDevice;
    size_t srcHeight;
    const void* srcHost;
    size_t srcLOD;
    hipMemoryType srcMemoryType;
    size_t srcPitch;
    size_t srcXInBytes;
    size_t srcY;
    size_t srcZ;
}hipMemcpy3DParms;

static __inline__ struct hipPitchedPtr make_hipPitchedPtr(void* d, size_t p, size_t xsz,
                                                          size_t ysz) {
    struct hipPitchedPtr s;

    s.ptr = d;
    s.pitch = p;
    s.xsize = xsz;
    s.ysize = ysz;

    return s;
}

static __inline__ struct hipPos make_hipPos(size_t x, size_t y, size_t z) {
    struct hipPos p;

    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

static __inline__ struct hipExtent make_hipExtent(size_t w, size_t h, size_t d) {
    struct hipExtent e;

    e.width = w;
    e.height = h;
    e.depth = d;

    return e;
}

#endif
