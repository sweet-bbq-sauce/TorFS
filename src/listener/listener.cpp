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

#include <torfs/listener.hpp>
#include <torfs/address.hpp>
#include <torfs/iosocket.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


IOSocket Listener::accept(Address& remote) const {

    sockaddr_storage addr;
    socklen_t sock_len = sizeof(addr);

    socket_t client = ::accept(handle, reinterpret_cast<sockaddr*>(&addr), &sock_len);

    if(client == INVALID_SOCKET) throw std::runtime_error(utils::glue("accept() error: ", utils::last_error()));

    IOSocket sock(client);

    if(addr.ss_family == AF_INET){

        char buffer[INET_ADDRSTRLEN];

        sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(&addr);

        if(inet_ntop(AF_INET, &ipv4->sin_addr, buffer, sizeof(buffer)) == nullptr) throw std::runtime_error("inet_ntop() error");

        remote = Address(buffer, ntohs(ipv4->sin_port));

    }
    else if(addr.ss_family == AF_INET6){

        char buffer[INET6_ADDRSTRLEN];

        sockaddr_in6* ipv6 = reinterpret_cast<sockaddr_in6*>(&addr);

        if(inet_ntop(AF_INET6, &ipv6->sin6_addr, buffer, sizeof(buffer)) == nullptr) throw std::runtime_error("inet_ntop() error");

        remote = Address(buffer, ntohs(ipv6->sin6_port));

    }

    if(firewall != nullptr){

        if(!firewall->test(remote)){

            sock.close();

            return accept(remote);

        }

    }

    utils::info(utils::glue("New connection from: ", remote.host()));

    return sock;

}


IOSocket Listener::accept() const {

    Address null;

    return accept(null);

}