#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK 16384

int compress_file(const char *source, const char *dest) {
    FILE *source_file = fopen(source, "rb");
    FILE *dest_file = fopen(dest, "wb");

    if (!source_file || !dest_file) {
        perror("Error opening files");
        return -1;
    }

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (deflateInit(&stream, Z_BEST_COMPRESSION) != Z_OK) {
        perror("deflateInit failed");
        return -1;
    }

    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    int ret;
    do {
        stream.avail_in = fread(in, 1, CHUNK, source_file);
        if (ferror(source_file)) {
            deflateEnd(&stream);
            fclose(source_file);
            fclose(dest_file);
            return -1;
        }
        stream.next_in = in;

        do {
            stream.avail_out = CHUNK;
            stream.next_out = out;
            ret = deflate(&stream, Z_FINISH);
            if (ret == Z_STREAM_ERROR) {
                deflateEnd(&stream);
                fclose(source_file);
                fclose(dest_file);
                return -1;
            }
            fwrite(out, 1, CHUNK - stream.avail_out, dest_file);
        } while (stream.avail_out == 0);
    } while (ret != Z_STREAM_END);

    deflateEnd(&stream);
    fclose(source_file);
    fclose(dest_file);

    return 0;
}

int decompress_file(const char *source, const char *dest) {
    FILE *source_file = fopen(source, "rb");
    FILE *dest_file = fopen(dest, "wb");

    if (!source_file || !dest_file) {
        perror("Error opening files");
        return -1;
    }

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (inflateInit(&stream) != Z_OK) {
        perror("inflateInit failed");
        return -1;
    }

    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    int ret;
    do {
        stream.avail_in = fread(in, 1, CHUNK, source_file);
        if (ferror(source_file)) {
            inflateEnd(&stream);
            fclose(source_file);
            fclose(dest_file);
            return -1;
        }
        if (stream.avail_in == 0)
            break;
        stream.next_in = in;

        do {
            stream.avail_out = CHUNK;
            stream.next_out = out;
            ret = inflate(&stream, Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR) {
                inflateEnd(&stream);
                fclose(source_file);
                fclose(dest_file);
                return -1;
            }
            fwrite(out, 1, CHUNK - stream.avail_out, dest_file);
        } while (stream.avail_out == 0);
    } while (ret != Z_STREAM_END);

    inflateEnd(&stream);
    fclose(source_file);
    fclose(dest_file);

    return 0;
}

int main() {
    const char *input_file = "BinarySearchR.c";
    const char *compressed_file = "compressed_file.z";
    const char *decompressed_file = "decompressed_file.c";

    // Compress the input file
    if (compress_file(input_file, compressed_file) == 0) {
        printf("File compressed successfully.\n");

        // Decompress the compressed file
        if (decompress_file(compressed_file, decompressed_file) == 0) {
            printf("File decompressed successfully.\n");
        } else {
            printf("Error decompressing file.\n");
        }
    } else {
        printf("Error compressing file.\n");
    }

    return 0;
}
