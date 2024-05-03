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

namespace torfs{

    class FireWall{

        public:

            enum action { ALLOW, REJECT };

            typedef std::vector<std::pair<Address, action>> rules_table;


            /**
             * @brief Construct a new Fire Wall object.
             * 
             * @param default_action action when host is not in the table.
             */
            FireWall(action default_action) : _action(default_action) {}


            /**
             * @brief Construct a new Fire Wall object with predefined rules.
             * 
             * @param default_action action when host is not in the table.
             */
            FireWall(action default_action, const rules_table& default_rules) : _action(default_action), rules(default_rules) {}


            /**
             * @brief Add allow entry for the host.
             * 
             * @param host 
             */
            void allow(const Address& host);


            /**
             * @brief Add reject entry for the host.
             * 
             * @param host 
             */
            void reject(const Address& host);


            /**
             * @brief Test the host.
             * 
             * @param host 
             * @return true 
             * @return false 
             */
            bool test(const Address& host) const;


        private:

            action _action;

            rules_table rules;

    };

}