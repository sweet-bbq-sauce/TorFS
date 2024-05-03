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
#include <torfs/command.hpp>
#include <torfs/address.hpp>

namespace torfs{

    /**
     * @brief TorFS top-level Client object.
     *        Contains methods for connecting to server, logging into, remote filesystem utils, FTP-like transfer and more.
     * 
     */
    class Client{

        public:


            /**
             * @brief Connect to the Server.
             * 
             * @param target 
             * @return true 
             * @return false 
             */
            bool connect(const Address& target);


            /**
             * @brief Connect to the Server.
             * 
             * @param target 
             * @return true 
             * @return false
             */
            bool connect(const char* target);


            Client clone();


            bool close();


            bool logout(){

                request_command(Command::LOGOUT);

                logged = false;
                user = "";
                password = "";

                return true;

            }


            /**
             * @brief Login/switch user.
             * 
             * @param user 
             * @param password 
             * @return true 
             * @return false 
             */
            bool login(std::string user, std::string password);


            /**
             * @brief Get user home directory.
             * 
             * @return path_t home directory
             */
            path_t home();


            /**
             * @brief Get the user current working directory.
             * 
             * @return path_t current working directory
             */
            path_t pwd();


            /**
             * @brief Change working directory.
             * 
             * @param directory 
             * @return true 
             * @return false 
             */
            bool cd(const path_t& directory);


            /**
             * @brief List files in directory.
             * 
             * @param directory 
             * @return std::vector<path_t> 
             */
            std::vector<path_t> ls(const path_t& directory = ".");


            /**
             * @brief Get info about the entry such as size, type and path.
             * 
             * @param entry 
             * @return FileInfo 
             */
            FileInfo info(const path_t& entry);


            /**
             * @brief Get the disk space information.
             * 
             * @return std::filesystem::space_info 
             */
            std::filesystem::space_info space();


            bool touch(const path_t& new_file, qword_t size = 0, byte_t fill = '\0');

            bool mkdir(const path_t& new_directory);

            bool rm(const path_t& to_remove);

            bool rmdir(const path_t& to_remove);

            bool move(const path_t& from, const path_t& to);

            bool copy(const path_t& from, const path_t& to);





        private:

            friend class RemoteFile;

            IOSocket socket;
            std::string remote_version;

            bool logged = false;
            bool connected = false;
            std::string user, password;
            Address host;

            void request_command(word_t command);

    };

}