#include <stdio.h>
#include <string.h>
#include "buatjadwal.h"
#include "manageData.h"

DataDokter* arrDataDokter;
int jumlah_dokter = 0;
int status_langgar[JUMLAH_HARI_JADWAL][JUMLAH_SHIFT_PER_HARI][NDktrperShift];

// FUNGSI UTILITAS untuk arrDataDokter

void arrPrefShift(Dokter* dokter, int* preferensi_shift){
    if (dokter->prefShift == 'P') preferensi_shift[0] = 1;
    else if (dokter->prefShift == 'S') preferensi_shift[1] = 1;
    else preferensi_shift[2] = 1;
}

void clear_arrDataDokter(DataDokter* arrDataDokter){
    if (arrDataDokter == NULL) {
        return;
    }
    
    // Note: We don't free arrDataDokter[i].data because these point to 
    // the original list nodes and aren't owned by this array
    
    free(arrDataDokter);
}

void init_arrDataDokter(DataDokter** arrDataDokter, Data* listDokter){
    *arrDataDokter = (DataDokter*)malloc((listDokter->size)*sizeof(DataDokter));
    Dokter* curr = listDokter->head;

    for (int i = 0; i < listDokter->size; i++)
    {
        arrDataDokter[i].data = curr;
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++){
            arrDataDokter[i].preferensi_shift[j] = 0;
        }
        arrPrefShift(curr, arrDataDokter->preferensi_shift);
        arrDataDokter[i].total_shift_terjadwal = 0;
        for (int j = 0; j < (JUMLAH_HARI_JADWAL/7 + 1); j++){
            arrDataDokter[i].shift_mingguan_terjadwal[j] = 0;
        }

        curr = curr->next;
    }
}


// MAIN FUNGSI OTOMATISASI JADWAL

void reset_jadwal(ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            for (int k = 0; k < NDktrperShift; k++) {
                jadwal[i].dokter_bertugas[j][k] = -1;
                status_langgar[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < jumlah_dokter; i++) {
        arrDataDokter[i].total_shift_terjadwal = 0;
        for (int j = 0; j < (JUMLAH_HARI_JADWAL / 7 + 1); j++) {
            arrDataDokter[i].shift_mingguan_terjadwal[j] = 0;
        }
    }
}

int periksa_valid(DataDokter *d, int hari, int tipe_shift, int posisi_dalam_shift, ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_SHIFT_PER_HARI; i++) {
        for (int j = 0; j < NDktrperShift; j++) {
            if (jadwal[hari].dokter_bertugas[i][j] == d->data->id) return 0;
        }
    }
    if (d->total_shift_terjadwal >= BATAS_TOTAL_SHIFT_DOKTER) return 0;
    int minggu = hari / 7;
    if (d->shift_mingguan_terjadwal[minggu] >= d->data->maxShift) return 0;
    return 1;
}

int hitung_skor(DataDokter *d, int tipe_shift, int hari) { /*Bisa diubah ubah guys skornya, */
    int skor = 0;
    if (d->preferensi_shift[tipe_shift] == 1) skor += 10;
    else skor -= 5;
    int minggu = hari / 7;
    skor += (d->data->maxShift - d->shift_mingguan_terjadwal[minggu]) * 2;
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
        if (periksa_valid(&arrDataDokter[i], hari, tipe_shift, shiftKe, jadwal)) {
            int skor = hitung_skor(&arrDataDokter[i], tipe_shift, hari);
            if (skor > best_skor) {
                best_skor = skor;
                best_idx = i;
            }
        }
    }

    if (best_idx != -1) {
        DataDokter *pilih = &arrDataDokter[best_idx];
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = pilih->data->id;
        pilih->total_shift_terjadwal++;
        pilih->shift_mingguan_terjadwal[hari / 7]++;
        status_langgar[hari][tipe_shift][shiftKe] = 0;
        if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe, jadwal)) return 1;
        pilih->total_shift_terjadwal--;
        pilih->shift_mingguan_terjadwal[hari / 7]--;
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = -1;
    }

    /* Jika tidak ada yang valid, pilih yang "melanggar" */
    for (int i = 0; i < jumlah_dokter; i++) {
        int skor = hitung_skor(&arrDataDokter[i], tipe_shift, hari);
        if (skor > best_skor) {
            best_skor = skor;
            best_idx = i;
        }
    }
    if (best_idx != -1) {
        DataDokter *pilih = &arrDataDokter[best_idx];
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = pilih->data->id;
        pilih->total_shift_terjadwal++;
        pilih->shift_mingguan_terjadwal[hari / 7]++;
        status_langgar[hari][tipe_shift][shiftKe] = 1;
        if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe, jadwal)) return 1;
        pilih->total_shift_terjadwal--;
        pilih->shift_mingguan_terjadwal[hari / 7]--;
        jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = -1;
    }

    return 0;
}



// // /*
// // int main() {
// //     if (jumlah_dokter < NDktrperShift * JUMLAH_SHIFT_PER_HARI) {
// //         printf("Jumlah dokter terlalu sedikit.\n");
// //         return 1;
// //     }

// //     ShiftHarian jadwal[JUMLAH_HARI_JADWAL];
// //     reset_jadwal(jadwal);

// //     buatJadwal(0, 0, 0, jadwal);

// //     lihatJadwal(jadwal);

// //     return 0;
// // }

// // */
