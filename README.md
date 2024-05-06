# TorFS

## Introduction
TorFS is a library, protocol and toolkit for remote file manipulation.  It is cross-platform and written in modern C++.  It works on the client-server principle, where the client logs in to the server and then sends requests to the server.  Access to files can be either FTP style (where we operate on the files as a whole), or in real time, where the file can be remotely opened, saved and read.  The library interface is simple and intuitive, focusing on quick workflow with the library.

## TODO
* SSL support
* LibMagic support
* More documentation

## Examples
Server side:
```cpp
#include <torfs/torfs.hpp>
#include <torfs/address.hpp>
#include <torfs/utils.hpp>
#include <torfs/server.hpp>

int main(){

	// Set the "debug" flag to true.
	// This will display some helpful information while running.
	torfs::utils::debug = true;

	// Initialize TorFS and WinSock
	torfs::utils::initialize();

	// Create server object
	torfs::Server server;

	// Listen on localhost:9090
	server.listen(torfs::Address("localhost:9090"));

	// Wait while the server is running
	server.wait();
	
	return  0;
}
```

Client side:
```cpp
#include <torfs/torfs.hpp>
#include <torfs/address.hpp>
#include <torfs/utils.hpp>
#include <torfs/client.hpp>

int main(){

	torfs::utils::debug = true;
	torfs::utils::initialize();
	
	// Create client object
	torfs::Client  client;
	client.connect("localhost:9090");

	// Login to server
	client.login("user", "password");

	// List all entries in remote current directory
	for(const  torfs::path_t&  entry : client.ls()){
		std::cout  <<  entry  <<  std::endl;
	}

	// Close connection
	client.close();
	
	return  0;
}
```

### Licence
This software is under MIT licence. See LICENCE for details.