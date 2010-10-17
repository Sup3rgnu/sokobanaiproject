all:	client	local_client stdin_client client_all

client: client.cpp board.cpp board.h
		g++-4.4 -std=c++0x client.cpp board.cpp -lboost_system -o client -g -Wno-deprecated
		
local_client: local_client.cpp board.cpp board.h
		g++-4.4 -std=c++0x local_client.cpp board.cpp -lboost_system -o local_client -g -Wno-deprecated

stdin_client: stdin_client.cpp board.cpp board.h
		g++-4.4 -std=c++0x stdin_client.cpp board.cpp -lboost_system -o stdin_client -g -Wno-deprecated

client_all:	client_all.cpp
		g++-4.4 -std=c++0x client_all.cpp -o client_all 

clean:
	rm -f client local_client stdin_client client_mac64 local_client_mac64 stdin_client_mac64
	
zip:
	zip voddler-sokoban.zip *.cpp *.h *.sh makefile 
		
# For mac with 64bit boostlibs	
all_mac64:	client_mac64	local_client_mac64 stdin_client_mac64

client_mac64: client.cpp board.cpp board.h
		g++-fsf-4.4 -m64 -std=c++0x -lboost_system client.cpp board.cpp -o client -g -Wno-deprecated
		
local_client_mac64: local_client.cpp board.cpp board.h
		g++-fsf-4.4 -m64 -std=c++0x -lboost_system local_client.cpp board.cpp -o local_client -g -Wno-deprecated

stdin_client_mac64: stdin_client.cpp board.cpp board.h
	g++-fsf-4.4 -m64 -std=c++0x -lboost_system stdin_client.cpp board.cpp -o stdin_client -g -Wno-deprecated
	