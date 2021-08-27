#network-communicator

Simple chat application to communicate over network. Clients connect to the server_
and send messages to other connected clients (broadcast). 

*Conan* dependency manager need to be installed.

Install *Conan*:
```
	pip install conan
```

Install dependencies, using *Conan*:
```
	conan install . -s build_type=Debug -if conan-debug
	conan install . -s build_type=Release -if conan-release
```