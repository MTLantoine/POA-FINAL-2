coin:
	g++ -Wall -Werror -std=c++11 coinminer.cpp -o coinminer -lcrypto

packages:
	sudo apt-get install libssl-dev g++ -y