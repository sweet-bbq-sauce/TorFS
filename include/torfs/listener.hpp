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
#include <torfs/listener.hpp>

namespace torfs{

    class Listener{

        public:

            /**
             * @brief Construct a new Listener object.
             * 
             * @param listener 
             */
            Listener(socket_t listener) : handle(listener) {}


            /**
             * @brief Construct a new Listener object with firewall.
             * 
             * @param listener 
             * @param fw 
             */
            Listener(socket_t listener, FireWall* fw) : handle(listener), firewall(fw) {}


            bool close(){

                int result = closesocket(handle);
                handle = INVALID_SOCKET;
                return result == 0;

            }


            bool operator==(const Listener& compared) const {

                return (handle == compared.handle);

            }


            /**
             * @brief Wait for connections.
             * 
             * @param remote 
             * @return IOSocket 
             */
            IOSocket accept(Address& remote) const;


            /**
             * @brief Wait for connections.
             * 
             * @return IOSocket 
             */
            IOSocket accept() const;


            


        private:

            socket_t handle = INVALID_SOCKET;

            FireWall* firewall = nullptr;

    };

}