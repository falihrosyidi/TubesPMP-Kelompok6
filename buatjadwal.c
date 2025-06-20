#include <stdio.h>
#include <string.h>

#define NDokterMax 100
#define JUMLAH_HARI_JADWAL 30
#define JUMLAH_SHIFT_PER_HARI 3
#define NDktrperShift 2
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

void reset_jadwal(ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            for (int k = 0; k < NDktrperShift; k++) {
                jadwal[i].dokter_bertugas[j][k] = NULL;
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

int periksa_valid(Dokter *dokter_ptr, int hari, int tipe_shift, int posisi_dalam_shift, ShiftHarian jadwal[]) {
    for (int i = 0; i < JUMLAH_SHIFT_PER_HARI; i++) {
        for (int j = 0; j < NDktrperShift; j++) {
            if (i != tipe_shift && jadwal[hari].dokter_bertugas[i][j] == dokter_ptr) return 0;
            if (i == tipe_shift && j < posisi_dalam_shift && jadwal[hari].dokter_bertugas[i][j] == dokter_ptr) return 0;
        }
    }
    if (dokter_ptr->total_shift_terjadwal >= BATAS_TOTAL_SHIFT_DOKTER) return 0;
    int minggu_saat_ini = hari / 7;
    if (dokter_ptr->shift_mingguan_terjadwal[minggu_saat_ini] >= dokter_ptr->data.maks_shift_per_minggu) return 0;
    return 1;
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

    for (int preferensi = 1; preferensi >= 0; preferensi--) {
        for (int k = 0; k < jumlah_dokter; k++) {
            if (dokter[k].data.preferensi_shift[tipe_shift] == preferensi &&
                periksa_valid(&dokter[k], hari, tipe_shift, shiftKe, jadwal)) {

                jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = &dokter[k];
                dokter[k].total_shift_terjadwal++;
                dokter[k].shift_mingguan_terjadwal[hari / 7]++;

                if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe, jadwal)) 
                return 1;

                jadwal[hari].dokter_bertugas[tipe_shift][shiftKe] = NULL;
                dokter[k].total_shift_terjadwal--;
                dokter[k].shift_mingguan_terjadwal[hari / 7]--;
            }
        }
    }

    return 0;
}

void lihatJadwal(ShiftHarian jadwal[]) {
    printf("\nJADWAL DOKTER:\n");
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        printf("Hari %2d | ", i + 1);
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            for (int k = 0; k < NDktrperShift; k++) {
                if (jadwal[i].dokter_bertugas[j][k] != NULL) {
                    printf("%s ", jadwal[i].dokter_bertugas[j][k]->data.nama);
                } else {
                    printf("KOSONG ");
                }
            }
            printf("| ");
        }
        printf("\n");
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

