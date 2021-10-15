RUN THESE COMMANDS ON LINUX

gcc -pthread socket-server.c -o socket-server
./socket-server -h "0.0.0.0" -p 9082
gcc -pthread socket-client.c -o socket-client
./socket-client -h "0.0.0.0" -p 9082 "Text"
gcc -pthread shm-server.c -o shm-server
./shm-server
gcc -pthread shm-client.c -o shm-client
./shm-client "Text"