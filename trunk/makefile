all:	client	local_client

client: client.cc board.cpp board.h
		g++ client.cc board.cpp -lboost_system -o client
		
local_client: local_client.cpp board.cpp board.h
		g++ local_client.cpp board.cpp -lboost_system -o local_client

clean:
	rm client local_client
