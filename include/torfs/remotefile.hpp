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
#include <torfs/client.hpp>

namespace torfs{

    class RemoteFile{

        public:

            bool close();

            void write(const char* data, qword_t size);
            void write(const std::string& text);
            void write(const data_t& data);

            void read(char* data, qword_t size);

            qword_t gcount();

            void seekg(std::streampos pos, std::ios::seekdir dir = std::ios::cur);
            std::streampos tellg();

            void seekp(std::streampos pos, std::ios::seekdir dir = std::ios::cur);
            std::streampos tellp();

            bool eof();

        private:

            RemoteFile(qword_t file_descriptor, Client new_client) : descriptor(file_descriptor), client(new_client) {}

            qword_t descriptor;
            Client client;

    };

}