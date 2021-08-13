#network-communicator

*Conan* dependency manager need to be installed.

Install *Conan*:
```
	pip install conan
```

Install dependencies, using *Conan*:
```
	conan install -s build_type=Debug -if conan-debug
	conan install -s build_type=Release -if conan-release
```