#ifndef INFORMASI_H
#define INFORMASI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manageData.h"
#include "buatjadwal.h"

#define MAX_DOKTER 100
#define MAX_HARI 30
#define SHIFT_PER_HARI 3
#define DOKTER_PER_SHIFT 3
#define HARI_PER_MINGGU 7

int get_index_dokter(DataDokter data_dokter[], int jumlah, int id);
void tampilkan_jadwal_harian(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[], int hari);
void tampilkan_jadwal_mingguan(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[], int minggu);
void tampilkan_jadwal_bulanan(Dokter dokter[], int jumlah_dokter, ShiftHarian jadwal[]);
void tampilkan_pelanggaran(DataDokter data_dokter[], int jumlah_dokter, ShiftHarian jadwal[], int jumlah_hari);

#endif
