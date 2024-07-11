// Tutorial (https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html)
#include <stdio.h>
// Tutorial recommends the unistd library, but that only works on Linux OSs; since I'm running this on a Windows OS, I'm going to use the stdio library instead (the alternatives seem convoluted, or require a virtual Linux environment, which is not what I want; I want this to run on Windows).
// stdin.h (https://en.cppreference.com/w/c/io)
// fread (https://en.cppreference.com/w/c/io/fread)
#include <windows.h>
#include <stdlib.h>
#include <errno.h>

void die(const char *error) {
  perror(error);
  exit(1);
}

void disableRawMode(HANDLE console, DWORD mode) {
  if (SetConsoleMode(console, mode) == 0) die("disable raw mode error");
}

void enableRawMode(HANDLE console, DWORD mode) {
  // windows.h (https://stackoverflow.com/questions/9217908/how-to-disable-echo-in-windows-console)
  // turning off canonical mode (https://gist.github.com/cloudwu/96ec4d6636d65b7974b633e01d97a1f9)
  if (SetConsoleMode(console, mode & ~ENABLE_ECHO_INPUT & ~ENABLE_LINE_INPUT & ~ENABLE_PROCESSED_INPUT) == 0) die("enable raw mode error");
}

int main() {
  // Defining variables for enable/disableRawMode
  // Occurs here so the initial mode of the console can be passed to disableRawMode
  HANDLE console = GetStdHandle(STD_INPUT_HANDLE); 
  DWORD mode;
  GetConsoleMode(console, &mode);

  enableRawMode(console, mode);

  char c;
  while (1) {
    fread(&c, 1, 1, stdin);
    if (ferror(stdin) != 0) die("read error");
    if (c == 'q') break;
    if (iscntrl(c)) printf("%d\n", c);
    else printf("%d ('%c')\n", c, c);
  };

  disableRawMode(console, mode);
  return 0;
}