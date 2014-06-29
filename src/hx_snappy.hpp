#ifndef __HX_SNAPPY_HPP
#define __HX_SNAPPY_HPP

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Compresses the string stored behind "str" and
 * returns the compressed version of it.
 *
 * Example:
 *   value str = hxsnappy_compress(buffer_val(buf), buffer_size(buf));
 */
value hxsnappy_compress(value bytes, value length);


/*
 * Decompresses the string stored behind "str" and
 * returns the uncompressed version of it.
 *
 * Example:
 *   value compressed = hxsnappy_compress(...);
 *   value str = hxsnappy_uncompress(compressed, compressed_length);
 */
value hxsnappy_uncompress(value compressed, value compressed_length);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_SNAPPY_HPP */
