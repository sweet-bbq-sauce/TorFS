#include <torfs/torfs.hpp>
#include <torfs/address.hpp>
#include <torfs/utils.hpp>
#include <torfs/client.hpp>

int main(){

    torfs::utils::debug = true;

    torfs::utils::initialize();

    torfs::Client client;
    client.connect("localhost:9090");

    client.login("user", "password");

    for(const torfs::path_t& entry : client.ls()){

        std::cout << entry << std::endl;

    }

    return 0;

}