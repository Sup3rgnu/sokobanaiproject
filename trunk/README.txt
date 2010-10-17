To compile the program go to the code folder and run “make”.
To run the program against sokoban server and level 1, execute “client 1”
or run the script compileAndRun.sh. To test many boards, for example the first 100,
you can run “client_all 100”.
We used g++ 4.4 to be able to use the new c++ standard.
g++4.3 could work but we have not verified that.
On a Mac OSX system we also had to add the -m64 flag because
the boost libraries were 64bit.
