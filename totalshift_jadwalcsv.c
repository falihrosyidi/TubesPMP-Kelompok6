#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "totalshift_jadwalcsv.h"

// Variabel global
// DataDokter* arrDataDokter;
// ShiftHarian jadwal[JUMLAH_HARI_JADWAL];

//Cetak total shift dokter
void printJumlahShiftDokter(ShiftHarian jadwal[], DataDokter* arrDataDokter, int jumlahDokter) {
    if (jadwal == NULL || arrDataDokter == NULL || jumlahDokter <= 0 || jumlahDokter > MAX_DOKTER) {
        printf("Error: Salah satu parameter input kosong/tidak valid!.\n");
        return;
    }
    //Menghitung total shift per dokter dari array jadwal
    int totalShift[MAX_DOKTER] = {0};
    for (int hari = 0; hari < JUMLAH_HARI_JADWAL; hari++) {
        for (int shift = 0; shift < JUMLAH_SHIFT_PER_HARI; shift++) {
            for (int doc = 0; doc < NDktrperShift; doc++) {
                int id = jadwal[hari].dokter_bertugas[shift][doc];
                if (id >= 1 && id <= jumlahDokter) {
                    totalShift[id - 1]++;
                }
            }
        }
    }
    //Cetak total shift per dokter dalam list
    printf("\nTotal Shift per Dokter:\n");
    printf("==================================\n");
    printf("ID\tNama Dokter\tTotal Shift\n");
    printf("===================================\n");

    for (int i = 0; i < jumlahDokter; i++) {
        printf("%d\t%-15s%d\n", arrDataDokter[i].data->id, arrDataDokter[i].data->nama, totalShift[i]);
    }
}

// Simpan jadwal ke file CSV
int updateJadwalCSV(ShiftHarian jadwal[], DataDokter* arrDataDokter, int jumlahDokter, const char *filename) {
    // if (jadwal == NULL || arrDataDokter == NULL || filename == NULL || jumlahDokter <= 0 || jumlahDokter > MAX_DOKTER) {
    //     printf("Error: Tidak bisa update jadwal! Salah satu parameter tidak valid/kosong.\n");
    //     return -1;
    // }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Gagal membuka file %s untuk ditulis.\n", filename);
        return -1;
    }

    fprintf(file, "Tanggal;Hari;Shift;Nama Dokter\n");
    const char *namaShift[] = {"Pagi", "Siang", "Malam"};
    const char *namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

    for (int hari = 0; hari < JUMLAH_HARI_JADWAL; hari++) {
        int tanggal = hari + 1;
        int indexHari = hari % 7;
        for (int shift = 0; shift < JUMLAH_SHIFT_PER_HARI; shift++) {
            fprintf(file, "%d;%s;%s;", tanggal, namaHari[indexHari], namaShift[shift]);
            int first = 1;
            for (int doc = 0; doc < NDktrperShift; doc++) {
                int id = jadwal[hari].dokter_bertugas[shift][doc];
                if (id >= 1 && id <= jumlahDokter) {
                    for (int i = 0; i < jumlahDokter; i++) {
                        if (arrDataDokter[i].data->id == id) {
                            if (!first) fprintf(file, ", ");
                            fprintf(file, "%s", arrDataDokter[i].data->nama);
                            first = 0;
                            break;
                        }
                    }
                }
            }
            if (first) {
                fprintf(file, "Tidak Dijadwalkan");
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    // printf("Jadwal berhasil disimpan ke %s.\n", filename);
    return 1;
}

// int main() {//TESTING AJA!! ASLINYA GAPERLU
//     // Inisialisasi listDokter (contoh data dokter aja buat di test), benttuknya disesuain sama punya fatur dan falih
//     Data listDokter;
//     listDokter.size = 16;
//     listDokter.head = NULL;
//     Dokter* tail = NULL;

//     struct {
//         char* nama;
//         int id;
//         int max_shift;
//         char pref_shift;
//     } init_data[] = {
//         {"Dr. A", 1, 5, 'P'}, {"Dr. B", 2, 5, 'S'}, {"Dr. C", 3, 6, 'M'},
//         {"Dr. D", 4, 4, 'P'}, {"Dr. E", 5, 5, 'S'}, {"Dr. F", 6, 5, 'M'},
//         {"Dr. G", 7, 6, 'P'}, {"Dr. H", 8, 4, 'S'}, {"Dr. I", 9, 5, 'M'},
//         {"Dr. J", 10, 5, 'P'}, {"Dr. K", 11, 5, 'S'}, {"Dr. L", 12, 5, 'M'},
//         {"Dr. M", 13, 5, 'P'}, {"Dr. N", 14, 5, 'S'}, {"Dr. O", 15, 5, 'M'},
//         {"Dr. P", 16, 5, 'P'}
//     };
//     int jumlah_dokter= listDokter.size;
   
//     // Alokasi memori untuk listDokter
//     for (int i = 0; i < jumlah_dokter; i++) {
//         Dokter* newDokter = (Dokter*)malloc(sizeof(Dokter));
//         newDokter->id = init_data[i].id;
//         newDokter->nama = strdup(init_data[i].nama); // Salin string
//         newDokter->maxShift = init_data[i].max_shift;
//         newDokter->prefShift = init_data[i].pref_shift;
//         newDokter->next = NULL;
//         if (listDokter.head == NULL) {
//             listDokter.head = newDokter;
//             tail = newDokter;
//         } else {
//             tail->next = newDokter;
//             tail = newDokter;
//         }
//     }

//     // Alokasi memori untuk arrDataDokter
//     arrDataDokter = (DataDokter*)malloc(jumlah_dokter * sizeof(DataDokter));
//     Dokter* current = listDokter.head;
//     for (int i = 0; i < jumlah_dokter; i++) {
//         arrDataDokter[i].data = current;
//         // Inisialisasi preferensi shift (contoh sederhana: 1 untuk shift yang sesuai prefShift, 0 untuk lainnya)
//         for (int s = 0; s < JUMLAH_SHIFT_PER_HARI; s++) {
//             arrDataDokter[i].preferensi_shift[s] = (s == (current->prefShift == 'P' ? 0 : current->prefShift == 'S' ? 1 : 2)) ? 1 : 0;
//         }
//         arrDataDokter[i].total_shift_terjadwal = 0;
//         for (int w = 0; w < (JUMLAH_HARI_JADWAL / 7 + 1); w++) {
//             arrDataDokter[i].shift_mingguan_terjadwal[w] = 0;
//         }
//         current = current->next;
//     }

//     // Inisialisasi jadwal contoh
//     for (int hari = 0; hari < JUMLAH_HARI_JADWAL; hari++) {
//         for (int shift = 0; shift < JUMLAH_SHIFT_PER_HARI; shift++) {
//             for (int doc = 0; doc < NDktrperShift; doc++) {
//                 // Isi dengan ID dokter secara berurang (contoh sederhana)
//                 int id = ((hari * JUMLAH_SHIFT_PER_HARI * NDktrperShift + shift * NDktrperShift + doc) % jumlah_dokter) + 1;
//                 jadwal[hari].dokter_bertugas[shift][doc] = id;
//             }
//         }
//     }

//     // Tampilkan total shift
//     printJumlahShiftDokter(jadwal, arrDataDokter, jumlah_dokter);

//     // Simpan ke CSV
//     if (updateJadwalCSV(jadwal, arrDataDokter, jumlah_dokter, "jadwal.csv") == 1) {
//         printf("Jadwal telah disimpan ke jadwal.csv!\n");
//     } else {
//         printf("Gagal menyimpan jadwal.\n");
//     }


//     return 0;
// }
