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


std::map<word_t, std::pair<std::string, Command::procedure_t>> Command::commands;
std::mutex Command::commands_mutex;





void Command::addCommand(word_t id, std::string name, procedure_t procedure){

    commands_mutex.lock();

    commands[id] = {name, procedure};

    commands_mutex.unlock();

}


bool Command::exists(word_t id){

    //commands_mutex.lock();

    return commands.find(id) != commands.end();

    //commands_mutex.unlock();

}


std::string Command::get_name(word_t id){

    if(!exists(id)) throw std::runtime_error("Command not found.");

    return commands[id].first;

}