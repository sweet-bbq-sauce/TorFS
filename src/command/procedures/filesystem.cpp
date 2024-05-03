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


void commands_init_filesystem(){


    Command::addCommand(Command::PWD, "pwd", [](Session& session, IOSocket& sock){

        sock.writes(session.userify(session.cwd));

    });


    Command::addCommand(Command::CD, "cd", [](Session& session, IOSocket& sock){

        path_t requested(session.resolve(sock.readss()));

        if(!session.accesible(requested)){

            sock.writeo(false);
            return;

        }

        if(std::filesystem::exists(requested) && std::filesystem::is_directory(requested)){

            session.cwd = requested;
            sock.writeo(true);

        }
        else sock.writeo(false);

    });


    Command::addCommand(Command::LS, "ls", [](Session& session, IOSocket& sock){

        path_t directory(session.resolve(sock.readss()));

        if(!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)){

            sock.writeo(false);
            return;

        }

        sock.writeo(true);

        std::vector<std::string> entries;

        for(const auto& entry : std::filesystem::directory_iterator(directory)) entries.push_back(entry.path().filename().string());

        sock.writeo<qword_t>(entries.size());

        for(const auto& entry : entries) sock.writes(entry);

    });


    Command::addCommand(Command::SPACE, "space", [](Session& session, IOSocket& sock){

        sock.writeo(std::filesystem::space(session.root));

    });


    Command::addCommand(Command::TOUCH, "touch", [](Session& session, IOSocket& sock){

        path_t path = session.resolve(sock.readss());
        qword_t size = sock.reado<qword_t>();
        byte_t fill = sock.reado<byte_t>();

        if(!session.accesible(path)){

            sock.writeo(false);
            return;

        }

        std::ofstream file(path);

        if(file.bad()){

            sock.writeo(false);
            return;

        }

        for(qword_t i = 0; i < size; i++) file.write(reinterpret_cast<const char*>(&fill), sizeof(fill));

        file.close();

        sock.writeo(true);

    });


    Command::addCommand(Command::MKDIR, "mkdir", [](Session& session, IOSocket& sock){

        path_t path = session.resolve(sock.readss());

        if(!session.accesible(path)){

            sock.writeo(false);
            return;

        }

        sock.writeo(std::filesystem::create_directory(path));

    });


    Command::addCommand(Command::RM, "rm", [](Session& session, IOSocket& sock){

        path_t path = session.resolve(sock.readss());

        if(!session.accesible(path) || !std::filesystem::exists(path)){

            sock.writeo(false);
            return;

        }

        sock.writeo(std::filesystem::remove(path));

    });


    Command::addCommand(Command::RMDIR, "rmdir", [](Session& session, IOSocket& sock){

        path_t path = session.resolve(sock.readss());

        if(!session.accesible(path) || !std::filesystem::exists(path) || !std::filesystem::is_directory(path)){

            sock.writeo(false);
            return;

        }

        sock.writeo(std::filesystem::remove(path));

    });


    Command::addCommand(Command::COPY, "copy", [](Session& session, IOSocket& sock){

        path_t from = session.resolve(sock.readss());
        path_t to = session.resolve(sock.readss());

        if(!session.accesible(from) || !std::filesystem::exists(from)){

            sock.writeo(false);
            return;

        }

        if(!session.accesible(to)){

            sock.writeo(false);
            return;

        }

        sock.writeo(std::filesystem::copy_file(from, to, std::filesystem::copy_options::update_existing));

    });


    Command::addCommand(Command::MOVE, "move", [](Session& session, IOSocket& sock){

        path_t from = session.resolve(sock.readss());
        path_t to = session.resolve(sock.readss());

        if(!session.accesible(from) || !std::filesystem::exists(from)){

            sock.writeo(false);
            return;

        }

        if(!session.accesible(to)){

            sock.writeo(false);
            return;

        }

        std::filesystem::rename(from, to);

        sock.writeo(true);

    });


}