#include <stdio.h>
// Tutorial recommends the unistd library, but that only works on Linux OSs; since I'm running this on a Windows OS, I'm going to use the stdio library instead (the alternatives seem convoluted, or require a virtual Linux environment, which is not what I want; I want this to run on Windows).
// stdin.h (https://en.cppreference.com/w/c/io)
// fread (https://en.cppreference.com/w/c/io/fread)

#include <windows.h>

void enableRawMode() {
  // windows.h (https://stackoverflow.com/questions/9217908/how-to-disable-echo-in-windows-console)
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}

int main() {
  enableRawMode();

  char c;
  while (fread(&c, 1, 1, stdin) == 1 && c != 'q'){
    fwrite(&c, 1, sizeof(c), stdout);
  };
  return 0;
}