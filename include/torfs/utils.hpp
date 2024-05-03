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

namespace torfs{

    namespace utils{


        /**
         * @brief Debug flag. If true TorFS will print some info messages. Default is false.
         * 
         */
        extern bool debug;


        /**
         * @brief Concat all arguments to std::string.
         * 
         * @tparam Args 
         * @param args 
         * @return std::string 
         */
        template<typename... Args>
        std::string glue(const Args&... args){
            std::ostringstream ss;
            ((ss << args), ...);
            return ss.str();
        }


        std::string last_error();


        /**
         * @brief Get current timestamp in microseconds
         * 
         * @param since Count time from this timestamp
         * @return timestamp_t 
         */
        timestamp_t timestamp(timestamp_t since = 0);


        /**
         * @brief Initialize TorFS and other modules
         * 
         * @param winsock 
         * @param libssl 
         * @return true 
         * @return false 
         */
        bool initialize(bool winsock = true, bool libssl = true);


        /**
         * @brief Return TorFS version string
         * 
         * @return std::string 
         */
        std::string version();


        /**
         * @brief Print some info. It prints nothing when utils::debug is false.
         * 
         * @param message 
         */
        void info(std::string message);


        std::string fixed(qword_t bytes, bool by_1024 = false);


    };

}