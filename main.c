#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manageData.h"
#include "buatjadwal.h"
#include "informasi.h"
#include "totalshift_jadwalcsv.h"

#ifdef _WIN32
#include <windows.h> // For Sleep() on Windows
#else
#include <unistd.h>  // For sleep() on POSIX systems
#endif

#define MAX_STR_MAIN 30

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

// FUNGSI User Interface

void ui_first(int* choice){
	if (*choice >= 0 && *choice <= 2){
		printf("Selamat Datang User di Sistem Penjadwalan Dokter ^_^\n");
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
    printf("3. Edit Data Dokter\n");
	printf("4. Hapus Data Dokter\n");
	printf("0. Kembali ke Menu Utama\n");
	sleepUniv(0.8);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}

void ui_Jadwal(int* choice){
	printf("----- MENU INFORMASI JADWAL -----\n");
    printf("1. Jadwal Jaga Harian\n");
    printf("2. Jadwal Jaga Minnguan\n");
    printf("3. Jadwal Jaga Bulanan\n");
    printf("4. Rincian Total Shift tiap Dokter\n");
    printf("5. Total Pelanggaran Jadwal\n");
    printf("0. Kembali ke Menu Utama\n");
	sleepUniv(0.8);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}	

/* GLOBAL VARIABLE */
/* Yang di "//" kan artinya udh dari library lain */ 

// DataDokter* arrDataDokter;
// int jumlah_dokter = 0;
// int status_langgar[JUMLAH_HARI_JADWAL][JUMLAH_SHIFT_PER_HARI][NDktrperShift];
Dokter* arrDokter;


// FUNGSI MAIN
int main(int argc, char const *argv[])
{
	// Deklarasi
	if (argc < 3) {
        printf("Usage: %s <dokterFile.csv> <jadwalFile.csv>\n", argv[0]);
        return 1;
    }

    char dokterFile[MAX_STR_MAIN], jadwalFile[MAX_STR_MAIN];
    strcpy(dokterFile, argv[1]);
    strcpy(jadwalFile, argv[2]);

    Data listDokter = {NULL, 0};

    ShiftHarian jadwal[JUMLAH_HARI_JADWAL];

	// PROGRAM
	int choice = 0; //Flag awal
	while(1){
        clearScreen();
        // Extract data dari csv
		collectData(&listDokter, dokterFile);
        clearDokterArray(arrDokter,listDokter.size);
        arrDokter = listToArray(&listDokter);

        // Run Jadwal
        reset_jadwal(jadwal);
        buatJadwal(0, 0, 0, jadwal);
        sleepUniv(1);

        // Update Jadwal
        updateJadwalCSV(jadwal, arrDokter, listDokter.size, jadwalFile);
        // input jadwal masih belum sesuai !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// UI MAIN
        printf("\n");
		ui_first(&choice);
		if(choice == 1){ // Kelola Database
			clearScreen();

			while(1){
				ui_kelolaData(&choice);
				if(choice == 1){ // Tampilkan Data Dokter
					printData(&listDokter);
                    printf("\n");

				} else if(choice == 2){ // Tambah Data Dokter
					manual_addDokter(&listDokter);
                    printf("\n");

				} else if(choice == 3){ // Edit Data Dokter
                    editDokter(&listDokter);
                    printf("\n");

                } else if(choice == 4){ // Hapus Data Dokter
					manual_deleteDokter(&listDokter);
                    printf("\n");

				} else if(choice == 0){ // Kembali ke Menu Utama
					updateData(&listDokter, dokterFile);
                    printf("\n");
					break;

				} else { // INPUT SALAH
					printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n");
					sleepUniv(0.8);
					ui_kelolaData(&choice);
				}
			}
		} else if (choice == 2){ // Lihat Jadwal
			clearScreen();
            // if (jumlah_dokter < NDktrperShift * JUMLAH_SHIFT_PER_HARI) {
            //     printf("Jumlah dokter terlalu sedikit.\n");
            //     break;
            // }
            // Dokter* arrDokter = listToArray(&listDokter);

            while(1){
            	ui_Jadwal(&choice);
            	if(choice == 1){ // Jadwal Jaga Hari ini
                    printf("\n");
                    int hari; printf("Mau lihat jadwal hari ke berapa (1-30): "); scanf("%d", &hari);
                    tampilkan_jadwal_harian(arrDokter, listDokter.size, jadwal, hari);
                    // input jadwal masih belum sesuai !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    printf("\n");

            	}else if(choice == 2){ // Jadwal Jaga Minggu ini
                    printf("\n");
                    int minggu; printf("Mau lihat jadwal hari ke berapa (1-5): "); scanf("%d", &minggu);
                    tampilkan_jadwal_mingguan(arrDokter, listDokter.size, jadwal, minggu);
                    // input jadwal masih belum sesuai !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    printf("\n");

            	}else if(choice == 3){ // Jadwal Jaga Bulan ini
                    printf("\n");
                    printf("\n");

            	}else if(choice == 4){ // Rincian Total Shift tiap Dokter
                    printf("\n");
                    StatistikDokter *statistik; // dummy aja !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    tampilkan_pelanggaran_preferensi(arrDokter, listDokter.size, statistik);
                    // statistik ntar diganti setelah ada revisi !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    printf("\n");

                }else if(choice == 5){ // Total Pelanggaran Jadwal
                    printf("\n");
                    printJumlahShiftDokter(jadwal, arrDokter, listDokter.size);
                    sleepUniv(3);
                    // input jadwal masih belum sesuai !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    printf("\n");

            	}else if(choice == 0){ // Kembali ke Menu Utama
            		printf("\n");
					break;

            	}else{
            		printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n");
					sleepUniv(0.8);
					ui_Jadwal(&choice);
            	}
            }

		} else if (choice == 0){ // Exit Program
			ui_close();
			sleepUniv(1);
			break;

		} else { // INPUT SALAH
			printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n");
			sleepUniv(0.8);
			ui_first(&choice);
		}
	}

	return 0;
}