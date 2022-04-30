# Important
This code was compiled in linux, runnig in windows might get errors.

# Executable
The "exe" folder contains the "executable" file, you can run it going into exe/ folder a running "./executable" command.

# Runnig the code
To run all the code, on the folder project run "g++ **/*.cpp -pthread -g wsObjects/websockh.o wsObjects/handshake.o -lssl -lcrypto -o exe/executable" command. If some error get appeard please communicate, thanks.

# Sytem operation
The program first store all the prime numbers in a variable (this takes more or less 5s), after the primes number are stored, the system get connected to ws and it creates two threads for the system, one for parsing the information and the other one to process the numbers found before. on the while loop it starts to receive information from the server and storing on system buffer. After 60 seconds of processing data the system will show the results, and will start again.