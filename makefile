all:	client	local_client stdin_client

client: client.cc board.cpp board.h
		g++ client.cc board.cpp -lboost_system -o client
		
local_client: local_client.cpp board.cpp board.h
		g++ local_client.cpp board.cpp -lboost_system -o local_client

stdin_client: stdin_client.cpp board.cpp board.h
		g++ stdin_client.cpp board.cpp -lboost_system -o stdin_client

clean:
	rm client local_client
