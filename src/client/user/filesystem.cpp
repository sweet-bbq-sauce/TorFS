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

#include <torfs/client.hpp>


using namespace torfs;


std::filesystem::space_info Client::space(){

    request_command(Command::SPACE);

    return socket.reado<std::filesystem::space_info>();

}


path_t Client::pwd(){

    request_command(Command::PWD);

    return path_t(socket.readss());

}


bool Client::cd(const path_t& directory){

    request_command(Command::CD);

    socket.writes(directory.string());

    return socket.reado<bool>();

}


std::vector<path_t> Client::ls(const path_t& directory){

    request_command(Command::LS);

    socket.writes(directory.string());

    if(!socket.reado<bool>()) throw std::runtime_error("Wrong directory");

        std::vector<path_t> entries;

        for(qword_t i = socket.reado<qword_t>(); i > 0; i--) entries.push_back(socket.readss());

        return entries;

}

bool Client::touch(const path_t& new_file, qword_t size, byte_t fill){

    request_command(Command::TOUCH);

    socket.writes(new_file.string());
    socket.writeo(size);
    socket.writeo(fill);

    return socket.reado<bool>();

}

