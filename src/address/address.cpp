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


Address::Address(const std::string& host){

    _hostname = host.substr(0, host.find(':'));
    _port = static_cast<port_t>(std::stoul(host.substr(host.find(':') + 1)));

}


std::string Address::hostname() const {

    return _hostname;

}


port_t Address::port() const {

    return _port;

}


std::string Address::host() const {

    return utils::glue(_hostname, ':', _port);

}


Address::operator bool() const {

    return !_hostname.empty() && _port != 0;

}


bool Address::operator==(const Address& compared) const {

    return (_hostname == compared._hostname) && (_port == compared._port);

}


Address::type_t Address::type(const std::string& hostname){

    static const std::regex ipv4_regex("^([0-9]{1,3}\\.){3}[0-9]{1,3}$");
    static const std::regex ipv6_regex("^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$");
    static const std::regex domain_regex("^([a-zA-Z0-9-]+\\.){0,}[a-zA-Z0-9-]{1,}\\.[a-zA-Z]{2,}$");

    if(std::regex_match(hostname, ipv4_regex)) return type_t::IPV4;
    else if(std::regex_match(hostname, ipv6_regex)) return type_t::IPV6;
    //else if(std::regex_match(hostname, domain_regex)) return type_t::DOMAIN;
    else return type_t::DOMAIN;

}