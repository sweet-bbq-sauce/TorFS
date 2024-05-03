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
#include <torfs/utils.hpp>


using namespace torfs;


bool Client::connect(const Address& target){

    try{

        socket = Address::connect(target);

        remote_version = socket.readss();
        socket.writes(utils::version());

        utils::info(utils::glue("Server version: ", remote_version));

    }
    catch(const std::exception& e){

        utils::info(e.what());
        return false;

    }

    connected = true;
    host = target;

    return true;

}


bool Client::connect(const char* target){

    return connect(Address(target));

}


void Client::request_command(word_t command){

    socket.writeo(command);
    switch(socket.reado<Command::result_t>()){

        case Command::result_t::NOT_FOUND: throw std::runtime_error("Command not found."); break;

        case Command::result_t::DISABLED: throw std::runtime_error("Command is disabled."); break;

        case Command::result_t::REJECTED: throw std::runtime_error("Command is rejected."); break;

        case Command::result_t::OK: break;

    }

}


Client Client::clone(){

    Client copy;

    if(connected) copy.connect(host);
    if(logged) copy.login(user, password);
    copy.cd(pwd());

    return copy;

}


bool Client::close(){

    if(!connected) return false;
                
    request_command(Command::BYE);

    connected = false;
    logged = false;

    return socket.close();

}