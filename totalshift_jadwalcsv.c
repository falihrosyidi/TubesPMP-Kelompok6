#include <stdio.h>
#include <string.h>
#include "totalshift_jadwalcsv.h"

// Inisialisasi dokter (cuma buat testing, jd ijin pakai punya kadit aja ya hehe)
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

// Cetak total shift dokter
void printJumlahShiftDokter(Hari *jadwal, Dokter *dokter, int jumlahDokter) {
    // Validasi parameter
    if (jadwal == NULL || dokter == NULL || jumlahDokter <= 0 || jumlahDokter > MAX_DOKTER) {
        printf("Error: Parameter tidak valid untuk printTotalShiftPerDokter.\n");
        return;
    }

    int totalShift[MAX_DOKTER] = {0}; // Array untuk menyimpan total shift per dokter

    // Hitung total shift per dokter
    for (int hari = 0; hari < HARI; hari++) {
        for (int shift = 0; shift < SHIFT_PER_HARI; shift++) {
            int id = jadwal[hari].shift[shift].id_dokter;
            if (id >= 1 && id <= jumlahDokter) { // Validasi ID dokter (1-based)
                totalShift[id - 1]++;
            }
        }
    }

    // Cetak header
    printf("\nTotal Shift per Dokter:\n");
    printf("================================\n");
    printf("ID\tNama Dokter\tTotal Shift\n");
    printf("================================\n");

    // Cetak total shift tiap dokter
    for (int i = 0; i < jumlahDokter; i++) {
        printf("%d\t%-15s%d\n", dokter[i].id, dokter[i].nama, totalShift[i]);
    }
}

// Update data ke CSV
int updateJadwalCSV(Hari *jadwal, Dokter *dokter, int jumlahDokter, const char *filename) {
    // Validasi bisa di update apa engga
    if (jadwal == NULL || dokter == NULL || filename == NULL || jumlahDokter <= 0 || jumlahDokter > MAX_DOKTER) {
        printf("Error: Gabisa update! .\n");
        return -1;
    }

    FILE *file = fopen(filename, "w"); //Write file jadwal.csv
    if (file == NULL) {
        printf("Error: Gagal membuka file %s untuk ditulis.\n", filename);
        return -1;
    }

    // Header CSV
    fprintf(file, "Tanggal;Hari;Shift;Nama Dokter\n");

    // Array buat nama shift dan hari
    const char *namaShift[] = {"Pagi", "Siang", "Malam"};
    const char *namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

    // Iterasi struct jadwal untuk nulis ke CSV
    for (int hari = 0; hari < HARI; hari++) {
        int tanggal = hari + 1; // Tanggal dari 1 sampai 30
        int indexHari = hari % 7; // Asumsi hari pertama itu minggu

        for (int shift = 0; shift < SHIFT_PER_HARI; shift++) {
            int id = jadwal[hari].shift[shift].id_dokter;
            char shiftChar = jadwal[hari].shift[shift].shift;

            // Validasi shift memastikan sesuai dengan indeks 
            const char *shiftName = (shiftChar == 'P') ? namaShift[0] : (shiftChar == 'S') ? namaShift[1] : namaShift[2];
            fprintf(file, "%d;%s;%s;", tanggal, namaHari[indexHari], shiftName);

            if (id >= 1 && id <= jumlahDokter) {
                fprintf(file, "%s\n", dokter[id - 1].nama);
            } else {
                fprintf(file, "Tidak Dijadwalkan\n");
            }
        }
    }

    fclose(file);
    printf("Jadwal berhasil disimpan ke %s.\n", filename);
    return 1;
}


int main() {
    // Inisialisasi data dokter
    Dokter dokter[MAX_DOKTER];
    int jumlahDokter;
    inisialisasi_dokter(dokter, &jumlahDokter);

    // Inisialisasi jadwal
    Hari jadwal[HARI];
    // Inisialisasi semua shift dengan id_dokter = 0 dan shift sesuai
    for (int hari = 0; hari < HARI; hari++) {
        for (int shift = 0; shift < SHIFT_PER_HARI; shift++) {
            jadwal[hari].shift[shift].id_dokter = 0;
            jadwal[hari].shift[shift].shift = shift == 0 ? 'P' : (shift == 1 ? 'S' : 'M');
        }
    }

    // Isi jadwal dengan distribusi realistis (total 90 shift)
    // Minggu 1 (Hari 1-7): 21 shift
    int minggu1[7][SHIFT_PER_HARI] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}, {16, 1, 2}, {3, 4, 5}
    };
    // Minggu 2 (Hari 8-14): 21 shift
    int minggu2[7][SHIFT_PER_HARI] = {
        {6, 7, 8}, {9, 10, 11}, {12, 13, 14}, {15, 16, 1}, {2, 3, 4}, {5, 6, 7}, {8, 9, 10}
    };
    // Minggu 3 (Hari 15-21): 21 shift
    int minggu3[7][SHIFT_PER_HARI] = {
        {11, 12, 13}, {14, 15, 16}, {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}
    };
    // Minggu 4 (Hari 22-28): 21 shift
    int minggu4[7][SHIFT_PER_HARI] = {
        {16, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}, {12, 13, 14}, {15, 16, 1}, {2, 3, 4}
    };
    // Hari 29-30: 6 shift
    int sisa[2][SHIFT_PER_HARI] = {
        {5, 6, 7}, {8, 9, 10}
    };

    // Salin jadwal ke struktur Hari
    for (int hari = 0; hari < 7; hari++) {
        for (int shift = 0; shift < SHIFT_PER_HARI; shift++) {
            jadwal[hari].shift[shift].id_dokter = minggu1[hari][shift];
            jadwal[hari + 7].shift[shift].id_dokter = minggu2[hari][shift];
            jadwal[hari + 14].shift[shift].id_dokter = minggu3[hari][shift];
            jadwal[hari + 21].shift[shift].id_dokter = minggu4[hari][shift];
            if (hari < 2) {
                jadwal[hari + 28].shift[shift].id_dokter = sisa[hari][shift];
            }
        }
    }

    // Cetak total shift dari data input
    printJumlahShiftDokter(jadwal, dokter, jumlahDokter);

    // Update ke CSV
    if (updateJadwalCSV(jadwal, dokter, jumlahDokter, "jadwal.csv") == 1) {
        printf("Jadwal telah disimpan ke jadwal.csv!\n"); //Double check aja hehe
    } else {
        printf("Gagal menyimpan jadwal.\n");
    }

    return 0;
}
