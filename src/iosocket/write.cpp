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


void IOSocket::write(const char* data, qword_t size) const {

    if(size == 0) return;

    qword_t sent = 0;
    int to_send, n;

    while(sent < size){

        if((size - sent) > chunk_size) to_send = static_cast<int>(chunk_size);
        else to_send = static_cast<int>(size - sent);

        n = ::send(handle, data + sent, to_send, 0);

        if(n > 0) sent += static_cast<qword_t>(n);
        else if(n == 0) throw std::runtime_error("socket: connection closed");
        else throw std::runtime_error(utils::glue("socket: send error: ", utils::last_error()));

    }

}


void IOSocket::writeb(const char* data, qword_t size) const {

    writeo(size);
    write(data, size);

}


void IOSocket::writes(const std::string& text) const {

    writeb(text.data(), text.length());

}


void IOSocket::writes(const char* text) const {

    writeb(text, std::strlen(text));

}


void IOSocket::writed(const data_t& data) const {

    writeb(reinterpret_cast<const char*>(data.data()), data.size());

}