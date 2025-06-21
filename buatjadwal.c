#include <stdio.h>
#include <string.h>
#include "buatjadwal.h"

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



/*
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

*/
