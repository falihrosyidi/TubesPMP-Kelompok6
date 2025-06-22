#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <string.h>
#include "manageData.h"

#define NDokterMax 100
#define JUMLAH_HARI_JADWAL 30
#define JUMLAH_SHIFT_PER_HARI 3
#define NDktrperShift 3
#define BATAS_TOTAL_SHIFT_DOKTER 30

typedef struct {
    Dokter data;
    int total_shift_terjadwal;
    int shift_mingguan_terjadwal[JUMLAH_HARI_JADWAL / 7 + 1];
} DataDokter;

typedef struct {
    DataDokter *dokter_bertugas[JUMLAH_SHIFT_PER_HARI][NDktrperShift];
} ShiftHarian;

extern DataDokter dokter[NDokterMax];
extern int jumlah_dokter;
extern int status_langgar[JUMLAH_HARI_JADWAL][JUMLAH_SHIFT_PER_HARI][NDktrperShift];

void reset_jadwal(ShiftHarian jadwal[]);
int periksa_valid(DataDokter *d, int hari, int tipe_shift, int posisi_dalam_shift, ShiftHarian jadwal[]);
int hitung_skor(DataDokter *d, int tipe_shift, int hari);
int buatJadwal(int hari, int tipe_shift, int shiftKe, ShiftHarian jadwal[]);
void lihatJadwal(ShiftHarian jadwal[]);

#endif
