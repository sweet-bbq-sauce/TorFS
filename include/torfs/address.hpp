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

#include <torfs/torfs.hpp>
#include <torfs/iosocket.hpp>
#include <torfs/listener.hpp>
#include <torfs/firewall.hpp>

namespace torfs{

    /**
     * @brief Object for storing and interpret network address. It includes also some static network utils like connect, listen, DNS resolve
     * 
     */
    class Address{


        public:


            /**
             * @brief Address types.
             * 
             */
            enum type_t{

                IPV4,
                IPV6,

                DOMAIN,

                UNKNOWN

            };


            /**
             * @brief Construct a empty (non-valid) Address object.
             * 
             */
            Address(){}


            /**
             * @brief Construct a new Address object.
             * 
             * @param hostname 
             * @param port 
             */
            Address(const std::string& hostname, const port_t& port) : _hostname(hostname), _port(port) {}


            /**
             * @brief Construct a new Address object from "hostname:port".
             * 
             * @param host 
             */
            Address(const std::string& host);


            /**
             * @brief Return hostname.
             * 
             * @return std::string 
             */
            std::string hostname() const;


            /**
             * @brief Return port.
             * 
             * @return port_t 
             */
            port_t port() const;


            /**
             * @brief Return hostname with port.
             * 
             * @return std::string host as "hostname:port"
             */
            std::string host() const;


            /**
             * @brief Check if address is valid.
             * 
             * @return - true when hostname is not empty and port is greater than 0
             * @return - false when hostname is empty or port is 0
             */
            explicit operator bool() const;


            bool operator==(const Address& compared) const;


            /**
             * @brief Return type of the hostname.
             * 
             * @param hostname 
             * @return type_t 
             */
            static type_t type(const std::string& hostname);


            /**
             * @brief Resolve a DNS address.
             * 
             * @param domain 
             * @param prefer_v6
             * @return std::string IPv4 or IPv6 address in human-readable format.
             */
            static std::string resolve(const std::string& domain, bool prefer_v6 = false);


            /**
             * @brief Create new Listener object with firewall.
             * 
             * @param host 
             * @param firewall 
             * @return Listener 
             */
            static Listener listen(const Address& host, FireWall* firewall);


            /**
             * @brief Create new Listener object.
             * 
             * @param host 
             * @return Listener 
             */
            static Listener listen(const Address& host);


            /**
             * @brief Establish connection to host and return client as IOSocket.
             * 
             * @param host 
             * @return IOSocket 
             */
            static IOSocket connect(const Address& host);


            static IOSocket socks5_connect(const Address& proxy, const Address& target, const std::string& login = "", const std::string& password = ""){

                IOSocket sock = Address::connect(proxy);

                sock.writeo<byte_t>(0x05);      // Socks5

                sock.writeo<byte_t>(0x01);      // Number of auth methods
                sock.writeo<byte_t>(0x00);      // No auth

                if(sock.reado<byte_t>() != 0x05) throw std::runtime_error("Wrong server response");
                if(sock.reado<byte_t>() != 0x00) throw std::runtime_error("Auth required");

                sock.writeo<byte_t>(0x05);      // Socks5
                sock.writeo<byte_t>(0x01);      // CONNECT command
                sock.writeo<byte_t>(0x00);      // Reserved
                sock.writeo<byte_t>(0x03);      // Domain resolve

                const std::string& hostname = target.hostname();
                if(hostname.length() > 255) throw std::runtime_error("Hostname is too long");

                sock.writeo<byte_t>(static_cast<byte_t>(hostname.length()));
                sock.write(hostname.data(), hostname.length());

                sock.writeo<port_t>(htons(target.port()));

                if(sock.reado<byte_t>() != 0x05) throw std::runtime_error("Wrong server response");

                if(sock.reado<byte_t>() != 0x00) throw std::runtime_error("Can't connect to target");

                sock.reado<byte_t>();
                for(byte_t i = sock.reado<byte_t>(); i >= 0; i--) sock.reado<byte_t>();
                sock.reado<port_t>();

                return sock;

            }


        private:

            std::string _hostname;
            port_t _port = 0;

    };

}