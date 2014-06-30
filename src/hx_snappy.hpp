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


/*
 * Validates that the compressed bytes can be uncompressed.
 *
 * This check is about 4x faster than uncompress itself.
 *
 * Example:
 *   value compressed = hxsnappy_compress(...);
 *   value valid = hxsnappy_validate(compressed, buffer_size(val_to_buffer(compressed)))
 *   ...
 *   if (val_bool(valid)) {
 *     // uncompress
 *   }
 */
value hxsnappy_validate(value compressed, value compressed_length);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_SNAPPY_HPP */
