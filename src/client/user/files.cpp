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


FileInfo Client::info(const path_t& entry){

    request_command(Command::INFO);

    socket.writes(entry.string());

    if(!socket.reado<bool>()) throw std::runtime_error("Wrong entry");

    return {
        socket.readss(),
        socket.reado<qword_t>(),
        socket.reado<std::filesystem::file_type>()
    };

}


bool Client::mkdir(const path_t& new_directory){

    request_command(Command::MKDIR);

    socket.writes(new_directory.string());

    return socket.reado<bool>();

}


bool Client::rm(const path_t& to_remove){

    request_command(Command::RM);

    socket.writes(to_remove.string());

    return socket.reado<bool>();

}


bool Client::rmdir(const path_t& to_remove){

    request_command(Command::RMDIR);

    socket.writes(to_remove.string());

    return socket.reado<bool>();

}


bool Client::move(const path_t& from, const path_t& to){

    request_command(Command::MOVE);

    socket.writes(from.string());
    socket.writes(to.string());

    return socket.reado<bool>();

}


bool Client::copy(const path_t& from, const path_t& to){

    request_command(Command::COPY);

    socket.writes(from.string());
    socket.writes(to.string());

    return socket.reado<bool>();

}