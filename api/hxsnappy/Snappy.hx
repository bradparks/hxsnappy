package hxsnappy;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "Snappy (and the whole hxsnappy library) is only supported on C++ and Neko targets."
#end
import haxe.io.Bytes;
import haxe.io.BytesData;
import hxsnappy.SnappyException;

/**
 * Haxe wrapper class around the C FFI implementation wrapping the Snappy compression library.
 */
class Snappy
{
    /**
     * References to the native snappy function implementations loaded through C FFI.
     */
    #if neko
    // initializes the Neko API so alloc_null() etc. becomes valid
    private static var neko_init = {
        var i = Lib.load("snappy","neko_init", 5);
        if (i != null) {
            i(function(s) return new String(s),
              function(len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; },
              null, true, false
            );
            i;
        } else {
            throw new SnappyException("Could not find NekoAPI @ snappy.");
        }
    }
    #end
    private static var hxsnappy_compress:BytesData->Int->BytesData   = Lib.load("snappy", "hxsnappy_compress", 2);
    private static var hxsnappy_uncompress:BytesData->Int->BytesData = Lib.load("snappy", "hxsnappy_uncompress", 2);


    /**
     * Compresses the Bytes.
     *
     * @param Bytes bytes the Bytes to compress
     *
     * @return Bytes
     */
    public static function compress(bytes:Bytes):Bytes
    {
        if (bytes == null || bytes.length == 0) {
            return Bytes.alloc(0);
        }

        try {
            return Bytes.ofData(Snappy.hxsnappy_compress(bytes.getData(), bytes.length));
        } catch (ex:Dynamic) {
            throw new SnappyException(ex);
        }
    }

    /**
     * Uncompresses the Bytes.
     *
     * @param Bytes bytes the Bytes to decompress
     *
     * @return Bytes to original Bytes
     */
    public static function uncompress(bytes:Bytes):Bytes
    {
        if (bytes == null || bytes.length == 0) {
            return Bytes.alloc(0);
        }

        try {
            return Bytes.ofData(Snappy.hxsnappy_uncompress(bytes.getData(), bytes.length));
        } catch (ex:Dynamic) {
            throw new SnappyException(ex);
        }
    }
}
