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

#include <torfs/session.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


void Session::session_loop(){

    while(true){

        try{

            word_t command;

            try{

                command = sock.reado<word_t>();

            }
            catch(const std::exception& e){

                break;

            }

            if(command == Command::BYE){

                sock.writeo(Command::result_t::OK);
                break;

            }

            if(!Command::exists(command)){

                sock.writeo(Command::result_t::NOT_FOUND);

                break;

            }
            else{

                Command::result_t result = parent->command_middleware(command, user, logged);

                sock.writeo(result);

                if(result == Command::result_t::OK) Command::commands[command].second(*this, sock);

            }

        }
        catch(const std::exception& e){

            utils::info(e.what());
                        
            break;

        }

    }

    sock.close();

}