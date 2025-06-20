#ifndef JADWAL_H
#define JADWAL_H

#define MAX_DOKTER 100
#define HARI 30
#define SHIFT_PER_HARI 3

// Struktur Dokter
typedef struct {
    int id;
    char nama[50];
    int max_shift_per_minggu;
    char preferensi_shift; // 'P', 'S', 'M'
} Dokter;

// Struktur Shift dan Hari
typedef struct {
    int id_dokter;
    char shift; // 'P', 'S', 'M'
} Shift;

typedef struct {
    Shift shift[SHIFT_PER_HARI];
} Hari;


// Deklarasi fungsi
void inisialisasi_dokter(Dokter dokter[], int *jumlah);

void JumlahShiftDokter(Hari *jadwal, Dokter *dokter, int jumlahDokter);

int updateJadwalCSV(Hari *jadwal, Dokter *dokter, int jumlahDokter, const char *filename);

#endif