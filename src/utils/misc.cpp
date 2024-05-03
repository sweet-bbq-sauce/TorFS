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

#include <torfs/torfs.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


bool utils::debug = false;


timestamp_t utils::timestamp(timestamp_t since){

    using namespace std::chrono;

    auto now = time_point_cast<microseconds>(system_clock::now());

    return now.time_since_epoch().count() - since;

}


std::string utils::version(){

    return TORFS_VERSION;

}

extern void commands_init_files();
extern void commands_init_filesystem();
extern void commands_init_user();

bool utils::initialize(bool winsock, bool libssl){

    #ifdef _WIN32

        if(winsock){

            WSADATA wsa;
            if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;

            utils::info(utils::glue("Initialized Winsock2 (", (int)LOBYTE(wsa.wVersion), ".", (int)HIBYTE(wsa.wVersion), ")"));

        }

    #endif

    if(libssl){

        SSL_library_init();
        SSL_load_error_strings();

        if(ERR_get_error() != 0) return false;

        utils::info(utils::glue("Initialized OpenSSL (", OPENSSL_VERSION_STR, ")"));

    }

    commands_init_files();
    commands_init_filesystem();
    commands_init_user();
    
    utils::info(utils::glue("Initialized TorFS (", utils::version(), ")"));

    return true;

}


void utils::info(std::string message){

    if(utils::debug) std::cout << message << std::endl;

}


std::string utils::last_error(){

    #ifdef _WIN32

        std::string text;
        int code = WSAGetLastError();
        LPSTR buffer = nullptr;

        DWORD result = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,

            nullptr,
            code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&buffer),
            0,
            nullptr
                
        );

        if(result == 0) text = "Unknown error";
        else{

            text = buffer;
            LocalFree(buffer);

        }

        return text;

    #else

        return std::strerror(errno);

    #endif

}


std::string utils::fixed(qword_t bytes, bool by_1024){

    if(bytes == 0) return "0 B";

    const static std::vector<std::string> decimal = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    const static std::vector<std::string> binary = {"B", "kiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"};

    const long double base = by_1024 ? 1024.0L : 1000.0L;
    const auto& current = by_1024 ? binary : decimal;

    long double bytes_d = static_cast<long double>(bytes);

    int power = 0;

    while(bytes_d >= base){

        bytes_d /= base;

        power++;

    }

    std::ostringstream oss;
    oss << std::fixed << ((power == 0) ? std::setprecision(0) : std::setprecision(2)) << bytes_d;

    return utils::glue(oss.str(), " ", current[power]);

}