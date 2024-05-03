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

#include <torfs/utils.hpp>
#include <torfs/command.hpp>


namespace torfs{


Command::result_t default_command_middleware(word_t cmd, std::string user, bool logged){

    if(cmd == Command::LOGIN) return Command::result_t::OK;

    if(!logged) return Command::result_t::REJECTED;
    else{

        utils::info(utils::glue("User \"", user, "\" requested command ", cmd, " (", Command::get_name(cmd), ")"));

        return Command::result_t::OK;

    }

}


bool default_login_middleware(std::string user, std::string password, path_t& root, path_t& home){

    root = std::getenv("HOME");
    home = root;

    utils::info(utils::glue("User: ", user, "  Root: ", root, "  Home: ", home));

    return true;

}

};