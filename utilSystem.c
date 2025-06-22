#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h>  // For sleep() on POSIX systems
#endif

// FUNGSI UTILITAS MAIN

void sleepUniv(float time){
	#ifdef _WIN32
	    Sleep(time*1000); // Sleep for 2000 milliseconds (2 seconds) on Windows
	#else
	    sleep(time);    // Sleep for 2 seconds on POSIX systems
	#endif
}

void clearScreen(){
	#ifdef _WIN32
	    system("cls");
	#else //linux or macOS
	    system("clear");
	#endif
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}