package hxsnappy.tests;

import haxe.io.Bytes;
import hxsnappy.Snappy;

/**
 * TestSuite for the hxsnappy.Snappy class.
 */
class TestSnappy extends haxe.unit.TestCase
{
    /**
     *
     */
    public function testCompress():Void
    {
        try {
            Snappy.compress(Bytes.ofString("Hello World"));
            assertTrue(true);
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }

    /**
     *
     */
    public function testCompressEmptyBytes():Void
    {
        try {
            Snappy.compress(Bytes.alloc(0));
            assertTrue(true);
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }

    /**
     *
     */
    public function testCompressNull():Void
    {
        try {
            Snappy.compress(null);
            assertTrue(true);
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }

    /**
     *
     * Attn: This test depends on 'Snappy.compress()' - make sure it works before looking
     * for errors in uncompress method.
     */
    public function testUncompress():Void
    {
        try {
            var input:Bytes        = Bytes.ofString("Hello World");
            var compressed:Bytes   = Snappy.compress(input);
            var uncompressed:Bytes = Snappy.uncompress(compressed);
            assertEquals(input.toString(), uncompressed.toString());
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }

    /**
     *
     */
    public function testUncompressEmptyBytes():Void
    {
        try {
            Snappy.uncompress(Bytes.alloc(0));
            assertTrue(true);
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }

    /**
     *
     */
    public function testUncompressNull():Void
    {
        try {
            Snappy.uncompress(null);
            assertTrue(true);
        } catch (ex:Dynamic) {
            assertTrue(false);
        }
    }
}
