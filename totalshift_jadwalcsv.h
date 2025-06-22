#ifndef TOTALSHIFT_JADWALCSV_H
#define TOTALSHIFT_JADWALCSV_H
#include "buatjadwal.h"

#define MAX_DOKTER 100
#define JUMLAH_HARI_JADWAL 30
#define JUMLAH_SHIFT_PER_HARI 3
#define NDktrperShift 3
#define BATAS_TOTAL_SHIFT_DOKTER 30

extern DataDokter* arrDataDokter;
extern Data listDokter;
extern ShiftHarian jadwal[JUMLAH_HARI_JADWAL];

// Deklarasi fungsi
void printJumlahShiftDokter(ShiftHarian jadwal[], DataDokter* arrDataDokter, int jumlahDokter);
int updateJadwalCSV(ShiftHarian jadwal[], DataDokter* arrDataDokter, int jumlahDokter, const char *filename);

#endif
