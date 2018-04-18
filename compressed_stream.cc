// Copyright (c) 2014 The Trident Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is modified from `protobuf-zerocopy-compression':
//   https://github.com/JohannesEbke/protobuf-zerocopy-compression

// Copyright (c) 2013, Johannes Ebke and Peter Waller.  All rights reserved.
// Author: peter.waller@gmail.com (Peter Waller)
// Author: johannes@ebke.org (Johannes Ebke)

#include <trident/compressed_stream.h>

#include <trident/block_wrappers.h>
#include <trident/common.h>
#include <trident/gzip_stream.h>

namespace trident {

AbstractCompressedInputStream * get_compressed_input_stream(
        ZeroCopyInputStream * istream, CompressType type) {
    switch(type) {
        case CompressTypeGzip:
            return new GzipInputStream(istream, GzipInputStream::GZIP);
        case CompressTypeZlib:
            return new GzipInputStream(istream, GzipInputStream::ZLIB);
        case CompressTypeSnappy:
#ifdef HAVE_SNAPPY
            return new SnappyInputStream(istream);
#else
            SCHECK(false);
#endif
        case CompressTypeLZ4:
            return new LZ4InputStream(istream);
        default:
            SCHECK(false);
    }
    return NULL;
}

AbstractCompressedOutputStream * get_compressed_output_stream(
        ZeroCopyOutputStream * ostream, CompressType type, int level) {
    switch (type) {
        case CompressTypeGzip:
            {
                GzipOutputStream::Options o;
                o.format = GzipOutputStream::GZIP;
                o.compression_level = level;
                return new GzipOutputStream(ostream, o);
            }
        case CompressTypeZlib:
            {
                GzipOutputStream::Options o;
                o.format = GzipOutputStream::ZLIB;
                o.compression_level = level;
                return new GzipOutputStream(ostream, o);
            }
        case CompressTypeSnappy:
#ifdef HAVE_SNAPPY
            return new SnappyOutputStream(ostream);
#else
            SCHECK(false);
#endif
        case CompressTypeLZ4:
            return new LZ4OutputStream(ostream);
        default:
            SCHECK(false);
    }
    return NULL;
}


} // namespace trident

/* vim: set ts=4 sw=4 sts=4 tw=100 */
