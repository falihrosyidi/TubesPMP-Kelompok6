#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "informasi.h"
#include "buatjadwal.h"
#include "manageData.h"

int get_index_dokter(DataDokter data_dokter[], int jumlah, int id) {
    for (int i = 0; i < jumlah; i++) {
        if (data_dokter[i].data->id == id) return i;
    }
    return -1;
}

void tampilkan_jadwal_harian(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[], int hari) {
    printf("\n Jadwal Hari ke-%d:\n", hari);
    printf("---------------------------------------------------\n");
    printf("| %-14s | %-14s | %-14s |\n", "Pagi", "Siang", "Malam");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < DOKTER_PER_SHIFT; i++) {
        printf("|");
        for (int j = 0; j < SHIFT_PER_HARI; j++) {
            int id = jadwal[hari - 1].dokter_bertugas[j][i];
            if (id == -1) {
                printf(" %-14s |", "[Kosong]");
            } else {
                for (int k = 0; k < jumlah_dokter; k++) {
                    if (dokter[k].id == id) {
                        printf(" %-14s |", dokter[k].nama);
                        break;
                    }
                }
            }
        }
        printf("\n");
    }
    printf("---------------------------------------------------\n");
}

void tampilkan_jadwal_mingguan(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[], int minggu) {
    int awal = (minggu - 1) * 7;
    int akhir = (minggu == 5) ? MAX_HARI : awal + 7;

    printf("\n Jadwal Mingguan ke-%d (Hari %d - %d):\n", minggu, awal + 1, akhir);
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| %-9s ", "Shift");
    for (int h = awal; h < akhir; h++) {
        printf("| Hari %-4d ", h + 1);
    }
    printf("|\n");
    printf("------------------------------------------------------------------------------------------------\n");

    const char* nama_shift[] = {"Pagi", "Siang", "Malam"};

    for (int s = 0; s < SHIFT_PER_HARI; s++) {
        for (int i = 0; i < DOKTER_PER_SHIFT; i++) {
            if (i == 0)
                printf("| %-9s ", nama_shift[s]);
            else
                printf("| %-9s ", "");

            for (int h = awal; h < akhir; h++) {
                int id = jadwal[h].dokter_bertugas[s][i];
                if (id == -1) {
                    printf("| %-9s ", "[Kosong]");
                } else {
                    for (int d = 0; d < jumlah_dokter; d++) {
                        if (dokter[d].id == id) {
                            printf("| %-9s ", dokter[d].nama);
                            break;
                        }
                    }
                }
            }
            printf("|\n");
        }
        printf("------------------------------------------------------------------------------------------------\n");
    }
}


void tampilkan_jadwal_bulanan(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[]) {
    for (int minggu = 1; minggu <= 5; minggu++) {
        tampilkan_jadwal_mingguan(dokter, jumlah_dokter, jadwal, minggu);
        sleepUniv(2);
    }
}

void tampilkan_pelanggaran(DataDokter data_dokter[], int jumlah_dokter, ShiftHarian jadwal[], int jumlah_hari) {
    int pelanggaran_pref[MAX_DOKTER] = {0};
    int pelanggaran_maks_shift[MAX_DOKTER] = {0};
    int shift_mingguan[MAX_DOKTER][JUMLAH_HARI_JADWAL / 7 + 1] = {{0}};
    int total_pref = 0, total_maks = 0;
    int minggu_total = jumlah_hari / 7 + ((jumlah_hari % 7) ? 1 : 0);

    for (int hari = 0; hari < jumlah_hari; hari++) {
        int minggu = hari / 7;
        for (int shift = 0; shift < SHIFT_PER_HARI; shift++) {
            char shift_kode = (shift == 0) ? 'P' : (shift == 1) ? 'S' : 'M';
            for (int d = 0; d < DOKTER_PER_SHIFT; d++) {
                int id = jadwal[hari].dokter_bertugas[shift][d];
                if (id == -1) continue;

                for (int i = 0; i < jumlah_dokter; i++) {
                    if (data_dokter[i].data->id == id) {
                        if (data_dokter[i].data->prefShift != shift_kode) {
                            pelanggaran_pref[i]++;
                            total_pref++;
                        }
                        shift_mingguan[i][minggu]++;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < jumlah_dokter; i++) {
        for (int m = 0; m < minggu_total; m++) {
            if (shift_mingguan[i][m] > data_dokter[i].data->maxShift) {
                pelanggaran_maks_shift[i]++;
                total_maks++;
            }
        }
    }

    // Table width calculation (exact: ID[6] + Nama[22] + Pref[26] + Maks[32] + 4 pipes/spaces)
    int table_width = 6 + 22 + 26 + 32 + 4;  // = 90

    // Header line
    for (int i = 0; i < table_width; i++) printf("=");
    printf("\n");

    // Table header
    printf("| %-4s | %-20s | %-24s | %-30s |\n", 
           "ID", "Nama Dokter", "Pelanggaran Preferensi", "Pelanggaran Maks/Minggu");

    // Middle separator
    for (int i = 0; i < table_width; i++) printf("-");
    printf("\n");

    // Table rows
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("| %-4d | %-20s | %-24d | %-30d |\n",
               data_dokter[i].data->id,
               data_dokter[i].data->nama,
               pelanggaran_pref[i],
               pelanggaran_maks_shift[i]);
    }

    // Bottom separator
    for (int i = 0; i < table_width; i++) printf("-");
    printf("\n");

    // Total row
    printf("| %-4s | %-20s | %-24d | %-30d |\n", 
           "----", "TOTAL", total_pref, total_maks);

    // Footer line
    for (int i = 0; i < table_width; i++) printf("=");
    printf("\n");
    sleepUniv(2);
}

