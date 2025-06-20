#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manageData.h"
// #include "informasi.h"

#ifdef _WIN32
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h>  // For sleep() on POSIX systems
#endif

#define MAX_STR 30

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

void ui_first(int* choice){
	if (*choice >= 0 && *choice <= 2){
		printf("Selamat Datang User di Sistem Penjadwalan Dokter (❁´◡`❁)\n");
	}
	sleepUniv(1);
	printf("1. Kelola Database\n");
	printf("2. Lihat Jadwal\n");
	printf("0. Exit Program\n");
	sleepUniv(1);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}

void ui_close(){
	printf("Terima kasih telah menggunakan program ini\n");
	printf("\xF0\x9F\x99\x8F\xF0\x9F\x99\x8F\xF0\x9F\x99\x8F\n");
}

void ui_kelolaData(int* choice){
	printf("----- MENU KELOLA DATA DOKTER -----\n");
	printf("1. Tampilkan Data Dokter\n");
	printf("2. Tambah Data Dokter\n");
	printf("3. Hapus Data Dokter\n");
	printf("0. Kembali ke Menu Utama");
	sleepUniv(2);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}

int main(int argc, char const *argv[])
{
	// Deklarasi
	char dokterFile[MAX_STR], jadwalFile[MAX_STR];
	strcpy(dokterFile, argv[1]);
	strcpy(jadwalFile, argv[2]); 
	Data listDokter = {NULL, 0};


	// PROGRAM
	int choice;
	while(1){
		collectData(&listDokter, dokterFile);
		//Run Jadwal

		// UI MAIN
		ui_first(&choice);
		if(choice == 1){
			clearScreen();

			while(1){
				ui_kelolaData(&choice);
				if(choice == 1){
					printData(&listDokter);

				} else if(choice == 2){
					manual_addDokter(&listDokter);
				} else if(choice == 3){
					manual_deleteDokter(&listDokter);

				} else if(choice == 0){
					updateData(&listDokter, dokterFile);
					break;

				} else {
					printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n");
					sleepUniv(1);
					ui_kelolaData(&choice);
				}
			}
			clearScreen();
		} else if (choice == 2){
			clearScreen();


		} else if (choice == 0){
			ui_close();
			sleepUniv(3);
			break;
		} else {
			printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n");
			sleepUniv(1);
			ui_first(&choice);
		}
	}

	return 0;
}