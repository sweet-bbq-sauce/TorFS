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


void commands_init_user(){


    Command::addCommand(Command::LOGIN, "login", [](Session& session, IOSocket& sock){

        std::string user = sock.readss();
        std::string password = sock.readss();

        bool result = session.login_middleware(user, password, session.root, session.home);

        sock.writeo(result);

        if(result){

            session.logged = true;
            session.user = user;
            session.cwd = session.home;

        }

    });


    Command::addCommand(Command::WHOAMI, "whoami", [](Session& session, IOSocket& sock){

        sock.writes(session.user);

    });


    Command::addCommand(Command::HOME, "home", [](Session& session, IOSocket& sock){

        sock.writes(session.userify(session.home));

    });


    Command::addCommand(Command::HOME, "logout", [](Session& session, IOSocket& sock){

        session.logged = false;
        session.root = "";
        session.home = "";
        session.cwd = "";
        session.user = "";

    });


}