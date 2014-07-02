#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE
#include <hx/CFFI.h>
#include <snappy-c.h>

#include "hx_snappy.hpp"

extern "C" {

value hxsnappy_compress(value bytes, value length)
{
    val_check(length, int);

    const size_t data_length = val_int(length);
    const char* data;
    if (val_is_string(bytes)) { // Neko
        data = val_string(bytes);
    } else { // C++
        buffer buf = val_to_buffer(bytes);
        data       = buffer_data(buf);
    }

    size_t compressed_length = snappy_max_compressed_length(data_length);
    char compressed[compressed_length];

    value val;
    if (snappy_compress(data, data_length, compressed, &compressed_length) == SNAPPY_OK) {
        buffer buf = alloc_buffer(NULL);
        buffer_append_sub(buf, compressed, compressed_length);
        val = buffer_val(buf);
    } else {
        neko_error();
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxsnappy_compress, 2);


value hxsnappy_uncompress(value compressed, value compressed_length)
{
    val_check(compressed_length, int);

    const size_t data_length = val_int(compressed_length);
    const char* data;
    if (val_is_string(compressed)) { // Neko
        data = val_string(compressed);
    } else { // C++
        buffer buf = val_to_buffer(compressed);
        data       = buffer_data(buf);
    }

    size_t uncompressed_length;

    value val;
    snappy_status ret;
    ret = snappy_uncompressed_length(data, data_length, &uncompressed_length);
    if (ret == SNAPPY_OK) {
        char uncompressed[uncompressed_length];
        ret = snappy_uncompress(data, data_length, uncompressed, &uncompressed_length);
        if (ret == SNAPPY_OK) {
            buffer buf = alloc_buffer(NULL);
            buffer_append_sub(buf, uncompressed, uncompressed_length);
            val = buffer_val(buf);
        }
    }

    if (ret != SNAPPY_OK) {
        neko_error();
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxsnappy_uncompress, 2);


value hxsnappy_validate(value compressed, value compressed_length)
{
    val_check(compressed_length, int);

    const char* data;
    if (val_is_string(compressed)) { // Neko
        data = val_string(compressed);
    } else { // C++
        buffer buf = val_to_buffer(compressed);
        data       = buffer_data(buf);
    }

    value val;
    if (snappy_validate_compressed_buffer(data, val_int(compressed_length)) == SNAPPY_OK) {
        val = alloc_bool(true);
    } else {
        val = alloc_bool(false);
    }

    return val;
}
DEFINE_PRIM(hxsnappy_validate, 2);

} // extern "C"
