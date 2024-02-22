#include <iostream>
#include <unistd.h>
int main() {
int pipe_fd[2]; // File descriptors for the pipe
// Create a pipe
if (pipe(pipe_fd) == -1) {
perror("Pipe creation failed");
return 1;
}
pid_t child_pid = fork(); // Fork a child process
if (child_pid == -1) {
perror("Fork failed");
return 1;
}
if (child_pid > 0) { // Parent process
close(pipe_fd[0]); // Close the read end in the parent
std::string message = "Hello from parent!";
// Write the message to the pipe
if (write(pipe_fd[1], message.c_str(), message.length()) == -1) {
perror("Write to pipe failed");
return 1;
}
close(pipe_fd[1]); // Close the write end in the parent
} else { // Child process
close(pipe_fd[1]); // Close the write end in the child
char buffer[50];
ssize_t bytes_read;
// Read the message from the pipe
bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
if (bytes_read == -1) {
perror("Read from pipe failed");
return 1;
}
buffer[bytes_read] = '\0'; // Null-terminate the string
std::cout << "Child process received message: " << buffer << std::endl;
close(pipe_fd[0]); // Close the read end in the child
}
return 0;
}
