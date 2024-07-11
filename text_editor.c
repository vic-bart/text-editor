#include <stdio.h>
// Tutorial recommends the unistd library, but that only works on Linux OSs; since I'm running this on a Windows OS, I've seen suggestions to use the io library instead (the alternatives seem convoluted, or require a virtual Linux environment, which is not what I want; I want this to run on Windows).
// stdin (https://en.cppreference.com/w/c/io)
// fread (https://en.cppreference.com/w/c/io/fread)

int main() {
  char c;
  while (fread(&c, 1, 1, stdin) == 1 && c != 'q'){
    fwrite(&c, 1, sizeof(c), stdout);
  };
  return 0;
}