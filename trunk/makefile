all:	client	local_client stdin_client client_all

client: client.cpp board.cpp board.h
		g++ client.cpp board.cpp -lboost_system -o client -g
		
local_client: local_client.cpp board.cpp board.h
		g++ local_client.cpp board.cpp -lboost_system -o local_client -g

stdin_client: stdin_client.cpp board.cpp board.h
		g++ stdin_client.cpp board.cpp -lboost_system -o stdin_client -g

client_all:	client_all.cpp
		g++ client_all.cpp -o client_all

clean:
	rm client local_client 

zip:
	zip voddler-sokoban.zip *.cpp *.h *.sh makefile 