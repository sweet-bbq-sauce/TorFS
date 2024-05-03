#include <torfs/torfs.hpp>
#include <torfs/address.hpp>
#include <torfs/utils.hpp>
#include <torfs/server.hpp>

int main(){

    torfs::utils::debug = true;

    torfs::utils::initialize();

    torfs::Server server;

    server.listen(torfs::Address("localhost:9090"));

    server.wait();

    return 0;

}