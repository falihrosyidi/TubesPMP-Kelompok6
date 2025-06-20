#ifndef INFORMASI_H
#define INFORMASI_H
#define MAX_DOKTER 100
#define MAX_HARI 30
#define SHIFT_PER_HARI 3 // Pagi, Siang, Malam
#define HARI_PER_MINGGU 7

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

// Struktur Statistik untuk tracking shift per dokter
typedef struct {
    int total_shift;
    int pelanggaran_preferensi;
} StatistikDokter;

// Inisialisasi dokter dummy
void inisialisasi_dokter(Dokter dokter[], int *jumlah);

void buat_jadwal_otomatis(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int jumlah_hari);

void tampilkan_jadwal_harian(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int hari);

void tampilkan_jadwal_mingguan(Dokter dokter[], int jumlah_dokter, Hari jadwal[], int minggu);

void tampilkan_pelanggaran_preferensi(Dokter dokter[], int jumlah_dokter, StatistikDokter statistik[]);

void hitung_pelanggaran_preferensi(Hari jadwal[MAX_HARI], Dokter dokter[], StatistikDokter statistik[], int jumlah_dokter);

#endif
