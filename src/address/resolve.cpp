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

#include <torfs/address.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


std::string Address::resolve(const std::string& domain, bool prefer_v6){

    addrinfo hints = {0};
    addrinfo *res, *p;
    int status;
    char address[INET6_ADDRSTRLEN];

    hints.ai_family = (prefer_v6 ? AF_INET6 : AF_INET);

    if((status = getaddrinfo(domain.c_str(), nullptr, &hints, &res)) != 0){

        throw std::runtime_error(utils::glue("getaddrinfo error: ", status));

    }

    for(p = res; p != nullptr; p = p->ai_next){

        void *buffer;

        if(p->ai_family == AF_INET){

            sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(p->ai_addr);
            buffer = &(ipv4->sin_addr);

        }
        else{

            sockaddr_in6* ipv6 = reinterpret_cast<sockaddr_in6*>(p->ai_addr);
            buffer = &(ipv6->sin6_addr);

        }

        if(inet_ntop(p->ai_family, buffer, address, sizeof(address)) == nullptr){

            throw std::runtime_error(utils::glue("inet_ntop error: ", errno, "(", strerror(errno), ")"));

        }

        break;

    }

    freeaddrinfo(res);

    utils::info(utils::glue("Resolved \"", domain, "\" to ", address));

    return address;

}