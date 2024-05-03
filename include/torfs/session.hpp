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

#pragma once

#include <torfs/torfs.hpp>
#include <torfs/server.hpp>
#include <torfs/iosocket.hpp>
#include <torfs/utils.hpp>

namespace torfs{

    /**
     * @brief Session object. Stores actual Client session.
     * 
     */
    class Session{

        public:

            path_t root, home, cwd;

            Server* parent;

            IOSocket sock;

            std::string user;

            bool logged = false;

            std::fstream current_file;

            Server::command_middleware_t& command_middleware;
            Server::login_middleware_t& login_middleware;

            bool accesible(path_t path){

                return path.lexically_relative(root).empty() == false;

            }

            path_t resolve(std::string path){

                switch(path.front()){

                    case '/': return root/path.substr(1);
                    case '~': return home/path.substr(2);
                    //case '.': return cwd/path.substr(2);

                    default: return cwd/path;

                }

            }

            std::string userify(path_t path){

                std::string buffer = path.lexically_relative(root).generic_string();

                if(buffer == ".") return "/";

                else return utils::glue('/', buffer);

            }
            

        private:

            friend class Server;

            Session(

                IOSocket socket,
                Server* server,
                Server::command_middleware_t cmd_middleware,
                Server::login_middleware_t log_middleware
                
            ) : 
                
                sock(socket),
                parent(server),
                command_middleware(cmd_middleware),
                login_middleware(log_middleware)
                
            {}

            void session_loop();

    };

}