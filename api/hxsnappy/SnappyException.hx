package hxsnappy;

import haxe.PosInfos;
import hxstd.Exception;

/**
 * Exceptions to be thrown when Exceptions from the C FFI need to be wrapped
 * or for any other kind of errors related to Snappy.
 */
class SnappyException extends Exception
{
    /**
     * @{inherit}
     */
    public function new(msg:String = "Uncaught Snappy exception", ?info:PosInfos):Void
    {
        super(msg, info);
    }
}
