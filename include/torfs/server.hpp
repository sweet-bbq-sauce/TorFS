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
#include <torfs/address.hpp>
#include <torfs/command.hpp>
#include <torfs/session.hpp>

namespace torfs{

    /**
     * @brief TorFS top-level server object. Receives commands from Client and executes them.
     * 
     */
    class Server{

        public:

            Server();

            typedef std::function<bool(std::string user, std::string password, path_t& root, path_t& home)> login_middleware_t;
            typedef std::function<Command::result_t(word_t cmd, std::string user, bool logged)> command_middleware_t;


            /**
             * @brief Set the middleware for user login.
             * 
             * @param middleware login middleware.
             */
            void set_login_middleware(login_middleware_t middleware);


            /**
             * @brief Set the middleware for command execute.
             * 
             * @param middleware command middleware.
             */
            void set_command_middleware(command_middleware_t middleware);


            /**
             * @brief Add listener on the given host.
             * 
             * @param host 
             * @return true 
             * @return false 
             */
            bool listen(Address host);


            /**
             * @brief Wait for server end.
             * 
             */
            void wait();


        private:

            friend class Session;

            std::string remote_version;
            bool running = false;
            std::vector<std::thread> listeners;
            std::map<Session*, std::thread> sessions;

            login_middleware_t login_middleware;
            command_middleware_t command_middleware;

            void listen_loop(Listener& listener);

    };

}