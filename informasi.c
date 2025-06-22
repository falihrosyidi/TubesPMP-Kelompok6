#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "informasi.h"
#include "buatjadwal.h"
#include "manageData.h"

#define MAX_DOKTER 100
#define MAX_HARI 30
#define SHIFT_PER_HARI 3
#define DOKTER_PER_SHIFT 3
#define JUMLAH_HARI_JADWAL MAX_HARI
#define HARI_PER_MINGGU 7

int get_index_dokter(DataDokter data_dokter[], int jumlah, int id) {
    for (int i = 0; i < jumlah; i++) {
        if (data_dokter[i].data.id == id) return i;
    }
    return -1;
}

void tampilkan_jadwal_harian(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int hari) {
    printf("\nJadwal Hari ke-%d:\n", hari);
    for (int j = 0; j < SHIFT_PER_HARI; j++) {
        char* shift_nama = (j == 0) ? "Pagi" : (j == 1) ? "Siang" : "Malam";
        printf("  Shift %s:\n", shift_nama);
        for (int d = 0; d < DOKTER_PER_SHIFT; d++) {
            int id = jadwal[hari - 1].shift[j].id_dokter[d];
            if (id == -1) {
                printf("    [Kosong]\n");
                continue;
            }
            for (int k = 0; k < jumlah_dokter; k++) {
                if (dokter[k].id == id) {
                    printf("    %s (ID %d)\n", dokter[k].nama, dokter[k].id);
                    break;
                }
            }
        }
    }
}

void tampilkan_jadwal_mingguan(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int minggu) {
    int awal = (minggu - 1) * 7;
    int akhir = (minggu == 5) ? MAX_HARI : awal + 7;
    printf("\n=== Jadwal Minggu ke-%d (Hari %d - %d) ===\n", minggu, awal + 1, akhir);
    for (int i = awal; i < akhir; i++) {
        printf("Hari ke-%d:\n", i + 1);
        for (int j = 0; j < SHIFT_PER_HARI; j++) {
            char* shift_nama = (j == 0) ? "Pagi" : (j == 1) ? "Siang" : "Malam";
            printf("  Shift %s:\n", shift_nama);
            for (int d = 0; d < DOKTER_PER_SHIFT; d++) {
                int id = jadwal[i].shift[j].id_dokter[d];
                if (id == -1) {
                    printf("    [Kosong]\n");
                    continue;
                }
                for (int k = 0; k < jumlah_dokter; k++) {
                    if (dokter[k].id == id) {
                        printf("    %s (ID %d)\n", dokter[k].nama, dokter[k].id);
                        break;
                    }
                }
            }
        }
    }
}

void tampilkan_jadwal_bulanan(Dokter dokter[], int jumlah_dokter, Hari jadwal[]) {
    for (int minggu = 1; minggu <= 5; minggu++) {
        tampilkan_jadwal_mingguan(dokter, jumlah_dokter, jadwal, minggu);
    }
}

void tampilkan_pelanggaran(DataDokter data_dokter[], int jumlah_dokter) {
    printf("\n=== Pelanggaran Preferensi Shift ===\n");
    int total = 0;
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("%s (ID %d): %d pelanggaran preferensi\n",
            data_dokter[i].data.nama,
            data_dokter[i].data.id,
            data_dokter[i].pelanggaran_preferensi);
        total += data_dokter[i].pelanggaran_preferensi;
    }
    printf("\nTotal Pelanggaran Preferensi: %d\n", total);
}
/*
int main() {
    Dokter dokter[MAX_DOKTER];
    DataDokter data_dokter[MAX_DOKTER];
    Hari jadwal[MAX_HARI];
    int jumlah_dokter;

    inisialisasi_dokter(dokter, &jumlah_dokter);
    buat_jadwal_otomatis(dokter, jumlah_dokter, jadwal, MAX_HARI, data_dokter);

    tampilkan_jadwal_harian(dokter, jumlah_dokter, jadwal, 1);
    tampilkan_jadwal_mingguan(dokter, jumlah_dokter, jadwal, 2);
    tampilkan_jadwal_bulanan(dokter, jumlah_dokter, jadwal);
    tampilkan_pelanggaran(data_dokter, jumlah_dokter);

    return 0;
}
*/

