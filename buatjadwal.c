#include <stdio.h>
#include <string.h>
#include "buatjadwal.h"

#define NDokterMax 100
#define JUMLAH_HARI_JADWAL 30
#define JUMLAH_SHIFT_PER_HARI 3
#define NDktrperShift 3
#define BATAS_TOTAL_SHIFT_DOKTER 30

typedef struct {
    int id;
    char nama[30];
    int maks_shift_per_minggu;
    int preferensi_shift[JUMLAH_SHIFT_PER_HARI]; 
} DataDokter;

typedef struct {
    DataDokter data;
    int total_shift_terjadwal;
    int shift_mingguan_terjadwal[JUMLAH_HARI_JADWAL / 7 + 1];
} Dokter;

typedef struct {
    Dokter *dokter_bertugas[JUMLAH_SHIFT_PER_HARI][NDktrperShift];
} ShiftHarian;

Dokter dokter[NDokterMax];
int jumlah_dokter = 0;
int status_langgar[JUMLAH_HARI_JADWAL][JUMLAH_SHIFT_PER_HARI][NDktrperShift];

void reset_jadwal(ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            for (int k = 0; k < NDktrperShift; k++) {
                jadwal[i].dokter_bertugas[j][k] = NULL;
                status_langgar[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < jumlah_dokter; i++) {
        dokter[i].total_shift_terjadwal = 0;
        for (int j = 0; j < (JUMLAH_HARI_JADWAL / 7 + 1); j++) {
            dokter[i].shift_mingguan_terjadwal[j] = 0;
        }
    }
}

int periksa_valid(Dokter *d, int hari, int tipe_shift, int posisi_dalam_shift, ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_SHIFT_PER_HARI; i++) {
        for (int j = 0; j < NDktrperShift; j++) {
            if (jadwal[hari].dokter_bertugas[i][j] == d) return 0;
        }
    }
    if (d->total_shift_terjadwal >= BATAS_TOTAL_SHIFT_DOKTER) return 0;
    int minggu = hari / 7;
    if (d->shift_mingguan_terjadwal[minggu] >= d->data.maks_shift_per_minggu) return 0;
    return 1;
}

int hitung_skor(Dokter *d, int tipe_shift, int hari) { /*Bisa diubah ubah guys skornya, */
    int skor = 0;
    if (d->data.preferensi_shift[tipe_shift] == 1) skor += 10;
    else skor -= 5;
    int minggu = hari / 7;
    skor += (d->data.maks_shift_per_minggu - d->shift_mingguan_terjadwal[minggu]) * 2;
    skor -= d->total_shift_terjadwal;
    return skor;
}

int buatJadwal(int hari, int tipe_shift, int shiftKe, ShiftHarian jadwal[]) {
    if (hari == JUMLAH_HARI_JADWAL) return 1;

    int next_hari = hari;
    int next_tipe_shift = tipe_shift;
    int next_shiftKe = shiftKe + 1;

    if (next_shiftKe == NDktrperShift) {
        next_shiftKe = 0;
        next_tipe_shift++;
        if (next_tipe_shift == JUMLAH_SHIFT_PER_HARI) {
            next_tipe_shift = 0;
            next_hari++;
        }
    }

    int best_idx = -1, best_skor = -9999;
    for (int i = 0; i < jumlah_dokter; i++) {
        if (periksa_valid(&dokter[i], hari, tipe_shift, shiftKe, jadwal)) {
            int skor = hitung_skor(&dokter[i], tipe_shift, hari);
            if (skor > best_skor) {
                best_skor = skor;
                best_idx = i;
            }
        }
    }

    if (best_idx != -1) {
        Dokter *pilih = &dokter[best_idx];
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = pilih;
        pilih->total_shift_terjadwal++;
        pilih->shift_mingguan_terjadwal[hari / 7]++;
        status_langgar[hari][tipe_shift][shiftKe] = 0;
        if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe, jadwal)) return 1;
        pilih->total_shift_terjadwal--;
        pilih->shift_mingguan_terjadwal[hari / 7]--;
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = NULL;
    }

    /* Jika tidak ada yang valid, pilih yang "melanggar" */
    for (int i = 0; i < jumlah_dokter; i++) {
        int skor = hitung_skor(&dokter[i], tipe_shift, hari);
        if (skor > best_skor) {
            best_skor = skor;
            best_idx = i;
        }
    }
    if (best_idx != -1) {
        Dokter *pilih = &dokter[best_idx];
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = pilih;
        pilih->total_shift_terjadwal++;
        pilih->shift_mingguan_terjadwal[hari / 7]++;
        status_langgar[hari][tipe_shift][shiftKe] = 1;
        if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe, jadwal)) return 1;
        pilih->total_shift_terjadwal--;
        pilih->shift_mingguan_terjadwal[hari / 7]--;
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = NULL;
    }

    return 0;
}

void lihatJadwal(ShiftHarian jadwal[]) {
    const char *shift_str[] = {"Pagi", "Siang", "Malam"};
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        printf("Hari ke-%d:\n", i + 1);
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            printf("  Shift %s: ", shift_str[j]);
            for (int k = 0; k < NDktrperShift; k++) {
                if (jadwal[i].dokter_bertugas[j][k] != NULL) {
                    printf("%s", jadwal[i].dokter_bertugas[j][k]->data.nama);
                    if (status_langgar[i][j][k]) printf(" (langgar)");
                } else {
                    printf("KOSONG");
                }
                if (k != NDktrperShift - 1) printf(", ");
            }
            printf("\n");
        }
    }
}


int main() {
    if (jumlah_dokter < NDktrperShift * JUMLAH_SHIFT_PER_HARI) {
        printf("Jumlah dokter terlalu sedikit.\n");
        return 1;
    }

    ShiftHarian jadwal[JUMLAH_HARI_JADWAL];
    reset_jadwal(jadwal);

    buatJadwal(0, 0, 0, jadwal);

    lihatJadwal(jadwal);

    return 0;
}
