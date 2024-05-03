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

#include <torfs/iosocket.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


void IOSocket::read(char* data, qword_t size) const {

    if(size == 0) return;

    qword_t received = 0;
    int to_receive, n;

    while(received < size){

        if((size - received) > chunk_size) to_receive = static_cast<int>(chunk_size);
        else to_receive = static_cast<int>(size - received);

        n = ::recv(handle, data + received, to_receive, MSG_WAITALL);

        if(n > 0) received += static_cast<qword_t>(n);
        else if(n == 0) throw std::runtime_error("socket: connection closed");
        else throw std::runtime_error(utils::glue("socket: recv error: ", utils::last_error()));

    }

}


qword_t IOSocket::readl() const {

    return reado<qword_t>();

}


void IOSocket::reads(std::string& text) const {

    qword_t size = readl();

    text.resize(size);

    read(text.data(), size);

}


void IOSocket::readd(data_t& data) const {

    qword_t size = readl();

    data.resize(size);

    read(reinterpret_cast<char*>(data.data()), size);

}


std::string IOSocket::readss() const {

    std::string buffer;

    reads(buffer);

    return buffer;

}