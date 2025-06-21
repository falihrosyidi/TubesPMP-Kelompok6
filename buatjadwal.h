#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <string.h>

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

extern Dokter dokter[NDokterMax];
extern int jumlah_dokter;
extern int status_langgar[JUMLAH_HARI_JADWAL][JUMLAH_SHIFT_PER_HARI][NDktrperShift];

void reset_jadwal(ShiftHarian jadwal[]);
int periksa_valid(Dokter *d, int hari, int tipe_shift, int posisi_dalam_shift, ShiftHarian jadwal[]);
int hitung_skor(Dokter *d, int tipe_shift, int hari);
int buatJadwal(int hari, int tipe_shift, int shiftKe, ShiftHarian jadwal[]);
void lihatJadwal(ShiftHarian jadwal[]);

#endif
