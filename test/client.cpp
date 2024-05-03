#include <torfs/torfs.hpp>
#include <torfs/address.hpp>
#include <torfs/utils.hpp>

int main(){

    torfs::utils::debug = true;

    torfs::utils::initialize();

    const torfs::Address proxy("localhost", 9150);
    const torfs::Address target("api.ipify.org", 80);

    torfs::IOSocket google = torfs::Address::socks5_connect(proxy, target);

    while(true){

        std::cout << google.reado<char>() << std::flush;

    }

    return 0;

}