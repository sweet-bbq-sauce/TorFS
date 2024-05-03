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

#include <torfs/command.hpp>


using namespace torfs;


void commands_init_files(){


    Command::addCommand(Command::INFO, "info", [](Session& session, IOSocket& sock){

        path_t path(session.resolve(sock.readss()));

        if(!std::filesystem::exists(path)){

            sock.writeo(false);
            return;

        }

        sock.writeo(true);

        std::filesystem::directory_entry entry(path);

        sock.writes(session.userify(path));     // Path
        sock.writeo(entry.is_regular_file() ? static_cast<qword_t>(entry.file_size()) : 0);    // Size
        sock.writeo(entry.status().type());  // File type

    });


}