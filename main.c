#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilSystem.h"
#include "manageData.h"
#include "buatjadwal.h"
#include "informasi.h"
#include "totalshift_jadwalcsv.h"

// FUNGSI User Interface

void ui_first(int* choice){
	if (*choice >= 0 && *choice <= 2){
		printf("Selamat Datang User di Sistem Penjadwalan Dokter ^_^\n");
	}
	sleepUniv(1);
	printf("1. Kelola Database\n");
	printf("2. Informasi Jadwal\n");
	printf("0. Exit Program\n");
	sleepUniv(0.5);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}

void ui_close(){
	printf("Terima kasih telah menggunakan program ini\n");
	printf("\n");
}

void ui_kelolaData(int* choice){
	printf("----- MENU KELOLA DATA DOKTER -----\n");
	printf("1. Tampilkan Data Dokter\n");
	printf("2. Tambah Data Dokter\n");
    printf("3. Edit Data Dokter\n");
	printf("4. Hapus Data Dokter\n");
	printf("0. Kembali ke Menu Utama\n");
	sleepUniv(0.5);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}

void ui_Jadwal(int* choice){
	printf("----- MENU INFORMASI JADWAL -----\n");
    printf("1. Jadwal Jaga Harian\n");
    printf("2. Jadwal Jaga Mingguan\n");
    printf("3. Jadwal Jaga Bulanan\n");
    printf("4. Rincian Total Shift tiap Dokter\n");
    printf("5. Total Pelanggaran Jadwal\n");
    printf("0. Kembali ke Menu Utama\n");
	sleepUniv(0.5);
	printf("Masukkan Input : ");
	scanf("%d", choice);
	clear_input_buffer();
	printf("\n");
}	

// FUNGSI TEST DEBUGING

void printJadwal(ShiftHarian jadwal[]){
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++){
        for (int j = 0; j < SHIFT_PER_HARI; j++){
            char shift = (j == 0) ? 'P' : (j == 1) ? 'S' : 'M';
            for (int k = 0; k < NDktrperShift; k++){
                printf("Hari %d, Shift %c, ID DOKTER: %d\n", i, shift, jadwal[i].dokter_bertugas[j][k]);
            }
        }
    }
}

/* GLOBAL VARIABLE */
/* Yang di "//" kan artinya udh dari library lain */ 

// DataDokter* arrDataDokter =  NULL;
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
        
        // Array of Dokter
        clearDokterArray(arrDokter,jumlah_dokter);
        arrDokter = listToArray(&listDokter);

        // Inititae Array of DataDokter
        clear_arrDataDokter(arrDataDokter);
        arrDataDokter = init_arrDataDokter(&listDokter);
        jumlah_dokter = listDokter.size;

        // Run Jadwal
        reset_jadwal(jadwal);
        if(jumlah_dokter >= NDktrperShift * JUMLAH_SHIFT_PER_HARI ){
            buatJadwal(0, 0, 0, jadwal);
        }
        // Update Jadwal
        updateJadwalCSV(jadwal, arrDataDokter, listDokter.size, jadwalFile);

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
                    fixIdDokter(&listDokter);
                    printf("Memperbaiki ID Dokter ");
                    for (int i = 0; i < 5; i++){
                        sleepUniv(0.5);
                        printf(".");
                    }
                    printf("\n");
                    
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
            // Run Jadwal
            if (jumlah_dokter < NDktrperShift * JUMLAH_SHIFT_PER_HARI) {
                printf("Doktor yang ada kurang! Ada %d, butunya %d\n", 
                    listDokter.size, NDktrperShift * JUMLAH_SHIFT_PER_HARI);
                sleepUniv(1);
                continue;
            }
            
			clearScreen();

            while(1){
                ui_Jadwal(&choice);
            	if(choice == 1){ // Jadwal Jaga Hari ini
                    // printf("\n");
                    int hari; printf("Mau lihat jadwal hari ke berapa (1-30): "); scanf("%d", &hari);
                    while (hari < 0 || hari > 30){
                        printf("\nInput tidak sesuai. Silahkan Masukkan lagi!!!!\n");
                        printf("Mau lihat jadwal hari ke berapa (1-30): "); scanf("%d", &hari);
                    }
                    
                    tampilkan_jadwal_harian(arrDokter, listDokter.size, jadwal, hari);
                    sleepUniv(1);
                    printf("\n");

            	}else if(choice == 2){ // Jadwal Jaga Minggu ini
                    // printf("\n");
                    int minggu; printf("Mau lihat jadwal Minggu ke berapa (1-5): "); scanf("%d", &minggu);
                    while (minggu < 0 || minggu> 5){
                        printf("\nInput tidak sesuai. Silahkan Masukkan lagi!!!!\n");
                        printf("Mau lihat jadwal Minggu ke berapa (1-5): "); scanf("%d", &minggu);
                    }

                    tampilkan_jadwal_mingguan(arrDokter, listDokter.size, jadwal, minggu);
                    sleepUniv(1);
                    printf("\n");

            	}else if(choice == 3){ // Jadwal Jaga Bulan ini
                    // printf("\n");
                    tampilkan_jadwal_bulanan(arrDokter, listDokter.size, jadwal);
                    sleepUniv(1);
                    printf("\n");

            	}else if(choice == 4){ // Rincian Total Shift tiap Dokter
                    // printf("\n");
                    printJumlahShiftDokter(jadwal, arrDataDokter, listDokter.size);
                    sleepUniv(3);
                    printf("\n");

                }else if(choice == 5){ // Total Pelanggaran Jadwal
                    // printf("\n");
                    tampilkan_pelanggaran(arrDataDokter, listDokter.size, jadwal, JUMLAH_HARI_JADWAL);
                    sleepUniv(3);
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
			printf("Input yang dimasukkan salah!!!!\nSilahkan input lagi!!!!!!!\n\n");
			sleepUniv(0.8);
			ui_first(&choice);
		}
	}

    // CLEAN ALL ALLOCATE MEMORY
    clearList(&listDokter);
    clearDokterArray(arrDokter,listDokter.size);
    clear_arrDataDokter(arrDataDokter);
	return 0;
}