#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "informasi.h"

#define MAX_DOKTER 100
#define MAX_HARI 30
#define SHIFT_PER_HARI 3 // Pagi, Siang, Malam
#define HARI_PER_MINGGU 7

// Struktur Dokter
typedef struct {
    int id;
    char nama[50];
    int max_shift_per_minggu;
    char preferensi_shift; // 'P', 'S', 'M'
} Dokter;

// Struktur Shift dan Hari
typedef struct {
    int id_dokter;
    char shift; // 'P', 'S', 'M'
} Shift;

typedef struct {
    Shift shift[SHIFT_PER_HARI];
} Hari;

// Struktur Statistik untuk tracking shift per dokter
typedef struct {
    int total_shift;
    int pelanggaran_preferensi;
} StatistikDokter;

// Inisialisasi dokter dummy
void inisialisasi_dokter(Dokter dokter[], int *jumlah) {
    *jumlah = 16;
    strcpy(dokter[0].nama, "Dr. A"); dokter[0].id = 1; dokter[0].max_shift_per_minggu = 5; dokter[0].preferensi_shift = 'P';
    strcpy(dokter[1].nama, "Dr. B"); dokter[1].id = 2; dokter[1].max_shift_per_minggu = 5; dokter[1].preferensi_shift = 'S';
    strcpy(dokter[2].nama, "Dr. C"); dokter[2].id = 3; dokter[2].max_shift_per_minggu = 6; dokter[2].preferensi_shift = 'M';
    strcpy(dokter[3].nama, "Dr. D"); dokter[3].id = 4; dokter[3].max_shift_per_minggu = 4; dokter[3].preferensi_shift = 'P';
    strcpy(dokter[4].nama, "Dr. E"); dokter[4].id = 5; dokter[4].max_shift_per_minggu = 5; dokter[4].preferensi_shift = 'S';
    strcpy(dokter[5].nama, "Dr. F"); dokter[5].id = 6; dokter[5].max_shift_per_minggu = 5; dokter[5].preferensi_shift = 'M';
    strcpy(dokter[6].nama, "Dr. G"); dokter[6].id = 7; dokter[6].max_shift_per_minggu = 6; dokter[6].preferensi_shift = 'P';
    strcpy(dokter[7].nama, "Dr. H"); dokter[7].id = 8; dokter[7].max_shift_per_minggu = 4; dokter[7].preferensi_shift = 'S';
    strcpy(dokter[8].nama, "Dr. I"); dokter[8].id = 9; dokter[8].max_shift_per_minggu = 5; dokter[8].preferensi_shift = 'M';
    strcpy(dokter[9].nama, "Dr. J"); dokter[9].id = 10; dokter[9].max_shift_per_minggu = 5; dokter[9].preferensi_shift = 'P';
    strcpy(dokter[10].nama, "Dr. K"); dokter[10].id = 11; dokter[10].max_shift_per_minggu = 5; dokter[10].preferensi_shift = 'S';
    strcpy(dokter[11].nama, "Dr. L"); dokter[11].id = 12; dokter[11].max_shift_per_minggu = 5; dokter[11].preferensi_shift = 'M';
    strcpy(dokter[12].nama, "Dr. M"); dokter[12].id = 13; dokter[12].max_shift_per_minggu = 5; dokter[12].preferensi_shift = 'P';
    strcpy(dokter[13].nama, "Dr. N"); dokter[13].id = 14; dokter[13].max_shift_per_minggu = 5; dokter[13].preferensi_shift = 'S';
    strcpy(dokter[14].nama, "Dr. O"); dokter[14].id = 15; dokter[14].max_shift_per_minggu = 5; dokter[14].preferensi_shift = 'M';
    strcpy(dokter[15].nama, "Dr. P"); dokter[15].id = 16; dokter[15].max_shift_per_minggu = 5; dokter[15].preferensi_shift = 'P';
}

void buat_jadwal_otomatis(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int jumlah_hari) {
    StatistikDokter *statistik = (StatistikDokter *) malloc(sizeof(StatistikDokter) * (size_t)jumlah_dokter);
    for (int i = 0; i < jumlah_dokter; i++) {
        statistik[i].total_shift = 0;
        statistik[i].pelanggaran_preferensi = 0;
    }
    int index_dokter = 0;

    for (int i = 0; i < jumlah_hari; i++) {
        for (int s = 0; s < SHIFT_PER_HARI; s++) {
            char kode_shift = (s == 0) ? 'P' : (s == 1) ? 'S' : 'M';
            int assigned = 0;

            for (int j = 0; j < jumlah_dokter; j++) {
                int idx = (index_dokter + j) % jumlah_dokter;
                if (statistik[idx].total_shift < dokter[idx].max_shift_per_minggu * (jumlah_hari / 7)) {
                    if (dokter[idx].preferensi_shift == kode_shift) {
                        jadwal[i].shift[s].id_dokter = dokter[idx].id;
                        jadwal[i].shift[s].shift = kode_shift;
                        statistik[idx].total_shift++;
                        assigned = 1;
                        break;
                    }
                }
            }
            if (!assigned) {
                for (int j = 0; j < jumlah_dokter; j++) {
                    int idx = (index_dokter + j) % jumlah_dokter;
                    if (statistik[idx].total_shift < dokter[idx].max_shift_per_minggu * (jumlah_hari / 7)) {
                        jadwal[i].shift[s].id_dokter = dokter[idx].id;
                        jadwal[i].shift[s].shift = kode_shift;
                        statistik[idx].total_shift++;
                        statistik[idx].pelanggaran_preferensi++;
                        break;
                    }
                }
            }
            index_dokter = (index_dokter + 1) % jumlah_dokter;
        }
    }
    free(statistik);
}

void tampilkan_jadwal_harian(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int hari) {
    printf("\nJadwal Hari ke-%d:\n", hari);
    for (int j = 0; j < SHIFT_PER_HARI; j++) {
        char* shift_nama = (j == 0) ? "Pagi" : (j == 1) ? "Siang" : "Malam";
        int id = jadwal[hari - 1].shift[j].id_dokter;
        for (int k = 0; k < jumlah_dokter; k++) {
            if (dokter[k].id == id) {
                printf("  Shift %s: %s (ID %d)\n", shift_nama, dokter[k].nama, dokter[k].id);
                break;
            }
        }
    }
}

void hitung_pelanggaran_preferensi(Hari jadwal[MAX_HARI], Dokter dokter[], StatistikDokter statistik[], int jumlah_dokter) {
    // Reset pelanggaran preferensi
    for (int i = 0; i < jumlah_dokter; i++) {
        statistik[i].pelanggaran_preferensi = 0;
    }

    // Hitung pelanggaran preferensi berdasarkan shift yang diberikan
    for (int i = 0; i < MAX_HARI; i++) {
        for (int j = 0; j < SHIFT_PER_HARI; j++) {
            int id_dokter_jadwal = jadwal[i].shift[j].id_dokter;
            char shift_dokter_jadwal = jadwal[i].shift[j].shift;

            for (int k = 0; k < jumlah_dokter; k++) {
                if (dokter[k].id == id_dokter_jadwal &&
                    dokter[k].preferensi_shift != shift_dokter_jadwal) {
                    statistik[k].pelanggaran_preferensi++;
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
            int id = jadwal[i].shift[j].id_dokter;
            for (int k = 0; k < jumlah_dokter; k++) {
                if (dokter[k].id == id) {
                    printf("  Shift %s: %s (ID %d)\n", shift_nama, dokter[k].nama, dokter[k].id);
                    break;
                }
            }
        }
    }
}

void tampilkan_pelanggaran_preferensi(Dokter dokter[], int jumlah_dokter, StatistikDokter statistik[]) {
    printf("\n=== Pelanggaran Preferensi Shift ===\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("%s (ID %d): %d pelanggaran\n", dokter[i].nama, dokter[i].id, statistik[i].pelanggaran_preferensi);
    }
}
/*
int main() {
    Dokter dokter[MAX_DOKTER];
    Hari jadwal[MAX_HARI];
    StatistikDokter statistik[MAX_DOKTER] = {0};
    int jumlah_dokter;

    inisialisasi_dokter(dokter, &jumlah_dokter);
    buat_jadwal_otomatis(dokter, jumlah_dokter, jadwal, MAX_HARI);

    // Tampilkan jadwal harian
    tampilkan_jadwal_harian(dokter, jumlah_dokter, jadwal, 1);

    // Tampilkan jadwal mingguan
    for (int minggu = 1; minggu <= 5; minggu++) {
        tampilkan_jadwal_mingguan(dokter, jumlah_dokter, jadwal, minggu);
    }

    hitung_pelanggaran_preferensi(jadwal[MAX_HARI], dokter[], statistik[], jumlah_dokter)

    tampilkan_pelanggaran_preferensi(dokter, jumlah_dokter, statistik);

    return 0;
}
*/
