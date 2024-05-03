/*
    MIT License

    Copyright (c) 2024 Wiktor Sołtys (sweet-bbq-sauce)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

#pragma once


#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>


#include <cstring>
#include <cstdint>


#ifdef _WIN32

    #include <ws2tcpip.h>
    #include <winsock2.h>

#else

    #include <netinet/tcp.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define SOCKET int
    #define INVALID_SOCKET ((SOCKET)(-1))
    #define closesocket ::close

#endif


#include <openssl/tls1.h>
#include <openssl/ssl3.h>
#include <openssl/evp.h>
#include <openssl/err.h>


#define TORFS_LIBMAGIC


#ifdef TORFS_LIBMAGIC

    #include <magic.h>

#endif


#ifndef TORFS_VERSION

    #define TORFS_VERSION "null"

#endif


#ifndef TORFS_CHUNK_SIZE

    #define TORFS_CHUNK_SIZE 65536

#endif


#if TORFS_CHUNK_SIZE > INT_MAX

    #error "TORFS_CHUNK_SIZE can't be bigger than INT_MAX (2147483647 bytes)"

#endif


namespace torfs{


    // Core types
    typedef uint8_t byte_t;
    typedef uint16_t word_t;
    typedef uint32_t dword_t;
    typedef uint64_t qword_t;


    // Data types
    typedef qword_t timestamp_t;    // Unix timestamp in microseconds
    typedef std::vector<byte_t> data_t;     // Data array
    typedef std::filesystem::path path_t;   // Filesystem path


    // Net types
    typedef word_t port_t;
    typedef SOCKET socket_t;


    /*class Magic{

        public:

            struct magicinfo_t{

                std::string description, encoding, mime;

            };

            static bool operator()();

            static bool init();

            static bool load();
            static bool load(const char* data, qword_t size);
            static bool load(path_t database);

            static magicinfo_t analize(const char* data, qword_t size);
            static magicinfo_t analize(path_t entry);

            Magic(const Magic&) = delete;
            Magic& operator=(const Magic&) = delete;

        private:

            Magic(){}

    };*/


    struct FileInfo{

            path_t path;
            qword_t size;
            std::filesystem::file_type type;

            std::string filename() const {

                return path.filename().string();

            }

    };

};

