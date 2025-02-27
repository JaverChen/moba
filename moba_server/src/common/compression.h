#pragma once
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/array.hpp>

class ZlibCompressor {
public:
    static std::vector<char> Compress(const std::vector<char>& input) {
        namespace io = boost::iostreams;

        io::zlib_params params;
        params.level = io::zlib::best_compression;
        
        std::vector<char> output;
        io::filtering_ostreambuf out;
        out.push(io::zlib_compressor(params));
        out.push(io::back_inserter(output));
        
        io::basic_array_source<char> src(input.data(), input.size());
        io::copy(src, out);
        return output;
    }

    static std::vector<char> Decompress(const std::vector<char>& input) {
        namespace io = boost::iostreams;
        
        std::vector<char> output;
        io::filtering_istreambuf in;
        in.push(io::zlib_decompressor());
        in.push(io::basic_array_source<char>(input.data(), input.size()));
        
        io::copy(in, io::back_inserter(output));
        return output;
    }
};