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
#include <torfs/iosocket.hpp>
#include <torfs/session.hpp>

namespace torfs{

    /**
     * @brief Server-side commands utils.
     * 
     */
    class Command{

        public:


            /**
             * @brief Standard commands enumerators.
             * 
             */
            enum command_t : word_t{

                NONE = 0x000,

                BYE = 0x100,
                WHOAMI,
                LOGIN,
                HOME,
                LOGOUT,

                PWD = 0x200,
                CD,
                LS,
                INFO,
                SPACE,

                TOUCH,
                MKDIR,
                RM,
                RMDIR,
                MOVE,
                COPY

            };


            /**
             * @brief Command responses.
             * 
             */
            enum class result_t : byte_t {

                OK = 0,
                NOT_FOUND,
                REJECTED,
                DISABLED

            };


            typedef std::function<void(Session&, IOSocket&)> procedure_t;


            /**
             * @brief Add custom server-side command. 
             * 
             * @param id a unique command ID.
             * @param name short command name.
             * @param procedure command procedure.
             */
            static void addCommand(word_t id, std::string name, procedure_t procedure);


            /**
             * @brief Check if given command exists.
             * 
             * @param id 
             * @return true when exists.
             * @return false when not.
             */
            static bool exists(word_t id);


            static std::string get_name(word_t id);


            Command(const Command&) = delete;
            Command& operator=(const Command&) = delete;

        private:

            friend class Session;

            Command(){}

            static std::map<word_t, std::pair<std::string, procedure_t>> commands;
            static std::mutex commands_mutex;

    };

}