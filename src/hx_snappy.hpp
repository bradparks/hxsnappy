#ifndef __HX_SNAPPY_HPP
#define __HX_SNAPPY_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <hx/CFFI.h>

/*
 * Compresses the string stored behind "str" and
 * returns the compressed version of it.
 *
 * Example:
 *   value str = hxsnappy_compress(buffer_val(buf));
 */
value hxsnappy_compress(value bytes);


/*
 * Decompresses the string stored behind "str" and
 * returns the uncompressed version of it.
 *
 * Example:
 *   value compressed = hxsnappy_compress(...);
 *   value str = hxsnappy_uncompress(compressed);
 */
value hxsnappy_uncompress(value bytes);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_SNAPPY_HPP */
