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

namespace torfs{

    /**
     * @brief IOSocket is object for streaming data.
     * 
     */
    class IOSocket{

        public:


            /**
             * @brief Construct a empty (non-valid) IOSocket object.
             * 
             */
            IOSocket() {}


            /**
             * @brief Construct a new IOSocket object.
             * 
             * @param socket 
             */
            IOSocket(socket_t socket) : handle(socket) {}


            /**
             * @brief Close connection.
             * 
             * @return true 
             * @return false 
             */
            bool close() const;


            /**
             * @brief Set socket option.
             * 
             * @tparam T 
             * @param level 
             * @param name 
             * @param value 
             * @return true 
             * @return false 
             */
            template<typename T>
            bool set_option(int level, int name, const T& value) const {

                return setsockopt(handle, level, name, reinterpret_cast<const char*>(&value), sizeof(value)) == 0;

            }


            /**
             * @brief Get the option object
             * 
             * @tparam T 
             * @param level 
             * @param name 
             * @param value 
             * @return true 
             * @return false 
             */
            template<typename T>
            bool get_option(int level, int name, T& value) const {

                return getsockopt(handle, level, name, reinterpret_cast<char*>(&value), sizeof(value)) == 0;

            }


            /**
             * @brief Send raw data
             * 
             * @param data 
             * @param size 
             */
            void write(const char* data, qword_t size) const;


            /**
             * @brief Send plain data object or primitive types.
             * 
             * @tparam T The type of the object to send.
             * @param object The object to send.
             * @warning This method is intended for use with plain data objects (PDO) and primitive types only.
             *          It does not support pointers or complex data structures.
             */
            template<typename T>
            void writeo(const T& object) const {

                write(reinterpret_cast<const char*>(&object), sizeof(object));

            }


            /**
             * @brief Send data with length frame on begin. Used by writes() and writed().
             * 
             * @param data 
             * @param size 
             */
            void writeb(const char* data, qword_t size) const;


            /**
             * @brief Send string.
             * 
             * @param text 
             */
            void writes(const std::string& text) const;
            void writes(const char* text) const;


            /**
             * @brief Send data blob.
             * 
             * @param data 
             */
            void writed(const data_t& data) const;


            /**
             * @brief Receive data.
             * 
             * @param data 
             * @param size 
             */
            void read(char* data, qword_t size) const;


            /**
             * @brief Receive simple data.
             * 
             * @tparam T 
             * @return T 
             */
            template<typename T>
            T reado() const {

                T object;
                read(reinterpret_cast<char*>(&object), sizeof(object));
                return object;

            }


            /**
             * @brief Receive length frame.
             * 
             * @return qword_t 
             */
            qword_t readl() const;


            /**
             * @brief Receive string.
             * 
             * @param text 
             */
            void reads(std::string& text) const;


            /**
             * @brief Receive blob.
             * 
             * @param data 
             */
            void readd(data_t& data) const;


            /**
             * @brief Receive simple string.
             * 
             * @return std::string 
             */
            std::string readss() const;


            /**
             * @brief Check is socket valid
             * 
             * @return true 
             * @return false 
             */
            explicit operator bool() const;


            static const qword_t chunk_size = TORFS_CHUNK_SIZE;

        private:

            socket_t handle = INVALID_SOCKET;

    };

}