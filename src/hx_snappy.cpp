#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <hx/CFFI.h>
#include <snappy-c.h>

#include "hx_snappy.hpp"

extern "C" {

value hxsnappy_compress(value bytes)
{
    const char* data;
    size_t length;
    if (val_is_string(bytes)) { // Neko
        data   = val_string(bytes);
        length = strlen(data);
    } else { // C++
        buffer buf = val_to_buffer(bytes);
        data       = buffer_data(buf);
        length     = buffer_size(buf);
    }

    size_t compressed_length = snappy_max_compressed_length(length);
    char compressed[compressed_length];

    value val;
    snappy_status ret = snappy_compress(data, length, compressed, &compressed_length);
    if (ret == SNAPPY_OK) {
        buffer buf = alloc_buffer(NULL);
        buffer_append_sub(buf, compressed, compressed_length);
        val = buffer_val(buf);
    } else {
        neko_error();
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxsnappy_compress, 1);


value hxsnappy_uncompress(value bytes)
{
    const char* data;
    size_t length;
    if (val_is_string(bytes)) { // Neko
        data   = val_string(bytes);
        length = strlen(data);
    } else { // C++
        buffer buf = val_to_buffer(bytes);
        data       = buffer_data(buf);
        length     = buffer_size(buf);
    }

    size_t uncompressed_length;

    value val;
    snappy_status ret;
    ret = snappy_validate_compressed_buffer(data, length);
    if (ret == SNAPPY_OK) {
        ret = snappy_uncompressed_length(data, length, &uncompressed_length);
        if (ret == SNAPPY_OK) {
            char uncompressed[uncompressed_length];
            ret = snappy_uncompress(data, length, uncompressed, &uncompressed_length);
            if (ret == SNAPPY_OK) {
                buffer buf = alloc_buffer(NULL);
                buffer_append_sub(buf, uncompressed, uncompressed_length);
                val = buffer_val(buf);
            } else {
                neko_error();
                val = alloc_null();
            }
        } else {
            neko_error();
            val = alloc_null();
        }
    } else {
        neko_error();
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxsnappy_uncompress, 1);

} // extern "C"
