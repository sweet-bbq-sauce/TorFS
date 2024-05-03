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

#include <torfs/server.hpp>
#include <torfs/address.hpp>
#include <torfs/listener.hpp>
#include <torfs/utils.hpp>


using namespace torfs;


Server::Server(){

    extern Command::result_t default_command_middleware(word_t, std::string, bool);
    extern bool default_login_middleware(std::string, std::string, path_t&, path_t&);

    command_middleware = default_command_middleware;
    login_middleware = default_login_middleware;

}


void Server::set_login_middleware(login_middleware_t middleware){

    login_middleware = middleware;

}


void Server::set_command_middleware(command_middleware_t middleware){

    command_middleware = middleware;

}


bool Server::listen(Address host){

    try{

        Listener listener = Address::listen(host);

        std::thread thread = std::thread([this, &listener](){ this->listen_loop(listener); });

        listeners.push_back(std::move(thread));

    }
    catch(const std::exception& e){

        utils::info(e.what());
        
        return false;

    }

    return true;

}


void Server::wait(){

    for(auto& listener : listeners){

        if(listener.joinable()) listener.join();

    }

}


void Server::listen_loop(Listener& listener){

    running = true;

    while(running){

        IOSocket client = listener.accept();

        client.writes(utils::version());
        remote_version = client.readss();

        utils::info(utils::glue("Client version: ", remote_version));

        Session* session = new Session(client, this, command_middleware, login_middleware);
        sessions[session] = std::thread([session](){ session->session_loop(); });

    }

    listener.close();

}