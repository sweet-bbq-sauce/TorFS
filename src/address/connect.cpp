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


IOSocket Address::connect(const Address& host){

    // We are operating on a copy of the address because we will be editing it
    Address temp = host;

    // Get the hostname type
    Address::type_t type = Address::type(temp.hostname());
    if(type == UNKNOWN) throw std::runtime_error("unknown address family");

    // If hostname is of type DOMAIN, we resolve it
    if(type == DOMAIN){

        temp = Address(Address::resolve(temp.hostname()), temp.port());

        type = Address::type(temp.hostname());

    }

    // Create TCP socket
    socket_t sock = socket((type == IPV4) ? AF_INET : AF_INET6, SOCK_STREAM, 0);

    sockaddr_storage addr = {0};
    socklen_t sock_len;

    // IPv4 procedure
    if(type == IPV4){

        sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(&addr);

        ipv4->sin_family = AF_INET;
        ipv4->sin_port = htons(host.port());
                                    
        if(inet_pton(AF_INET, temp.hostname().c_str(), &ipv4->sin_addr) != 1) throw std::runtime_error("inet_pton() error");

        sock_len = sizeof(sockaddr_in);
    
    }

    // IPv6 procedure
    else if(type == IPV6){

        sockaddr_in6* ipv6 = reinterpret_cast<sockaddr_in6*>(&addr);

        ipv6->sin6_family = AF_INET6;
        ipv6->sin6_port = htons(host.port());
                                    
        if(inet_pton(AF_INET6, temp.hostname().c_str(), &ipv6->sin6_addr) != 1) throw std::runtime_error("inet_pton() error");

        sock_len = sizeof(sockaddr_in6);

    }
    else{

        throw std::runtime_error("unknown address family");

    }

    // Connect to remote
    if(::connect(sock, reinterpret_cast<sockaddr*>(&addr), sock_len) != 0) throw std::runtime_error("connect() error");

    // Dump debug info
    utils::info(utils::glue("Connected: ", temp.host()));

    // Return socket as new IOSocket object
    return IOSocket(sock);

}