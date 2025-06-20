/* TUBES PMP NO. 2 */

#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  


#define NDokterMax 100 
#define JUMLAH_HARI_JADWAL 30 /* Bergantung bulannya */
#define JUMLAH_SHIFT_PER_HARI 3 /* Jumlah tipe shift (Pagi, Siang, Malam) */
#define NDktrperShift 3    /* Jumlah dokter per satu shift */
#define BATAS_TOTAL_SHIFT_DOKTER 30 /* Batas maksimal total shift untuk satu dokter selama 30 hari */


typedef struct Dokter {
    char nama[30];
    int maks_shift_per_minggu; /* Shift maksimal dalam seminggu */
    int preferensi_shift[JUMLAH_SHIFT_PER_HARI]; /* Pagi, siang atau malam */
    int total_shift_terjadwal; /* Total shift yang sudah dijadwalkan untuk dokter */
    int shift_mingguan_terjadwal[JUMLAH_HARI_JADWAL / 7 + 1];
    struct Dokter *berikutnya;
} Dokter;

/* Struktur untuk menyimpan jadwal satu hari */
typedef struct {
    Dokter *dokter_bertugas[JUMLAH_SHIFT_PER_HARI][NDktrperShift];
} ShiftHarian;


Dokter *head_dokter = NULL;
ShiftHarian jadwal_akhir[JUMLAH_HARI_JADWAL];

/* Baca file csv */
void bacafile(const char *nama_file) {
    FILE *file_input = fopen(nama_file, "r");

    char baris[256];
    Dokter *ekor_list = NULL;
    int jumlahDokter = 0; 

    while (fgets(baris, sizeof(baris), file_input) && jumlahDokter < NDokterMax) {
        Dokter *node_baru = (Dokter *)malloc(sizeof(Dokter));
        node_baru->berikutnya = NULL;

        char *token;
        token = strtok(baris, ","); 
        if (token == NULL) { /* Periksa jika baris kosong atau format salah */
            free(node_baru); /* Bebaskan node yang baru dialokasikan */
            continue; 
        }
        strcpy(node_baru->nama, token);

        token = strtok(NULL, ","); 
        if (token == NULL) { free(node_baru); continue; }
        node_baru->maks_shift_per_minggu = atoi(token);

        token = strtok(NULL, ","); 
        if (token == NULL) { free(node_baru); continue; }
        node_baru->preferensi_shift[0] = atoi(token);

        token = strtok(NULL, ","); 
        if (token == NULL) { free(node_baru); continue; }
        node_baru->preferensi_shift[1] = atoi(token);

        token = strtok(NULL, "\n"); 
        if (token == NULL) { free(node_baru); continue; }
        node_baru->preferensi_shift[2] = atoi(token);

        node_baru->total_shift_terjadwal = 0; /* belum dijadwalkan */
        for (int i = 0; i < (JUMLAH_HARI_JADWAL / 7 + 1); i++) {
            node_baru->shift_mingguan_terjadwal[i] = 0;
        }

        /* Masuk ke linked list */
        if (head_dokter == NULL) {
            head_dokter = node_baru;
            ekor_list = node_baru;
        } else {
            ekor_list->berikutnya = node_baru;
            ekor_list = node_baru;
        }
        jumlahDokter++;
    }
    fclose(file_input);
}


void reset_jadwal() {
    /*Buat tidak ada dokter dalam jadwal*/
    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        for (int j = 0; j < JUMLAH_SHIFT_PER_HARI; j++) {
            for (int k = 0; k < NDktrperShift; k++) {
                jadwal_akhir[i].dokter_bertugas[j][k] = NULL; 
            }
        }
    }
    /*shift terjadwal dokter masih 0*/
    Dokter *saat_ini = head_dokter;
    while (saat_ini != NULL) {
        saat_ini->total_shift_terjadwal = 0;
        for (int j = 0; j < (JUMLAH_HARI_JADWAL / 7 + 1); j++) {
            saat_ini->shift_mingguan_terjadwal[j] = 0;
        }
        saat_ini = saat_ini->berikutnya;
    }
}


void lihatDokter() {
    printf("\nDATA DOKTER YANG TERDAFTAR\n");
    Dokter *saat_ini = head_dokter;
    int hitung = 0;
    while (saat_ini != NULL) {
        printf("No: %d, Nama: %s, Max Shift/Minggu: %d, Preferensi:[ %d ; %d ; %d ]\n",
               hitung++, saat_ini->nama, saat_ini->maks_shift_per_minggu,
               saat_ini->preferensi_shift[0],
               saat_ini->preferensi_shift[1],
               saat_ini->preferensi_shift[2]);
        saat_ini = saat_ini->berikutnya;
    }
    printf("Total Dokter: %d\n", hitung);
}

/* periksa kevalid an dokter saat membuat jadwal */
int periksa_valid(Dokter *dokter_ptr, int hari, int tipe_shift, int posisi_dalam_shift) {
    for (int i = 0; i < JUMLAH_SHIFT_PER_HARI; i++) {
        for (int j = 0; j < NDktrperShift; j++) {
            /* Tidak boleh dijadwalkan di shift lain dalam satu hari */
            if (i != tipe_shift && jadwal_akhir[hari].dokter_bertugas[i][j] == dokter_ptr) {
                return 0; 
            }
            
            /* Agar satu shift tidak diisi oleh dokter yang sama */
            if (i == tipe_shift && j < posisi_dalam_shift && jadwal_akhir[hari].dokter_bertugas[i][j] == dokter_ptr) {
                return 0;
            }
        }
    }

    if (dokter_ptr->total_shift_terjadwal >= BATAS_TOTAL_SHIFT_DOKTER) {
        return 0; /* beban kerja melebihi batas dokter */
    }

    /* Memeriksa beban kerja dalam satu minggu */
    int minggu_saat_ini = hari / 7;
    if (dokter_ptr->shift_mingguan_terjadwal[minggu_saat_ini] >= dokter_ptr->maks_shift_per_minggu) {
        return 0; 
    }

    return 1;
}

int buatJadwal(int hari, int tipe_shift, int shiftKe) {
    if (hari == JUMLAH_HARI_JADWAL) {
        return 1; /*Sudah dibuat*/
    }

    int next_hari = hari;
    int next_tipe_shift = tipe_shift;
    int next_shiftKe = shiftKe + 1;

    if (next_shiftKe == NDktrperShift) { /* Satu shift sudah terisi penuh */
        next_shiftKe = 0; 
        next_tipe_shift++;             
        if (next_tipe_shift == JUMLAH_SHIFT_PER_HARI) { /* Satu hari sudah diperiksa */
            next_tipe_shift = 0;           
            next_hari++;                   
        }
    }

    Dokter *kandidat[NDokterMax];
    int Nkandidat = 0;

    /* dokter preferensi yang sama */
    Dokter *periksa_dokter = head_dokter;
    while (periksa_dokter != NULL) {
        if (periksa_dokter->preferensi_shift[tipe_shift] == 1) {
            kandidat[Nkandidat++] = periksa_dokter;
        }
        periksa_dokter = periksa_dokter->berikutnya;
    }

    /* kurang berpreferensi di shift ini */
    periksa_dokter = head_dokter; 
    while (periksa_dokter != NULL) {
        if (periksa_dokter->preferensi_shift[tipe_shift] == 0) {
            int sudah_ada = 0;
            for(int j=0; j<Nkandidat; j++) {
                if(kandidat[j] == periksa_dokter) {
                    sudah_ada = 1;
                    break;
                }
            }
            if(!sudah_ada) {
                kandidat[Nkandidat++] = periksa_dokter;
            }
        }
        periksa_dokter = periksa_dokter->berikutnya;
    }

    for (int k = 0; k < Nkandidat; k++) {
        Dokter *node_dokter_pilihan = kandidat[k];

        if (periksa_valid(node_dokter_pilihan, hari, tipe_shift, shiftKe)) {
            jadwal_akhir[hari].dokter_bertugas[tipe_shift][shiftKe] = node_dokter_pilihan;
            node_dokter_pilihan->total_shift_terjadwal++;
            int minggu_saat_ini = hari / 7;
            node_dokter_pilihan->shift_mingguan_terjadwal[minggu_saat_ini]++;

            if (buatJadwal(next_hari, next_tipe_shift, next_shiftKe)) {
                return 1; 
            }

            jadwal_akhir[hari].dokter_bertugas[tipe_shift][shiftKe] = NULL;
            node_dokter_pilihan->total_shift_terjadwal--;
            node_dokter_pilihan->shift_mingguan_terjadwal[minggu_saat_ini]--;
        }
    }
    return 0; 
}

void LihatJadwal() {
    printf("\nJADWAL DOKTER\n");

    for (int i = 0; i < JUMLAH_HARI_JADWAL; i++) {
        printf("%4d | ", i + 1);
        for (int s = 0; s < JUMLAH_SHIFT_PER_HARI; s++) {
            char shift_str[100] = ""; 
            int first_dokter = 1;
            for (int p = 0; p < NDktrperShift; p++) {
                Dokter *dokter_bertugas = jadwal_akhir[i].dokter_bertugas[s][p];
                if (dokter_bertugas != NULL) {
                    if (!first_dokter) {
                        strcat(shift_str, ", ");
                    }
                    strcat(shift_str, dokter_bertugas->nama);
                    first_dokter = 0;
                } else {
                    if (!first_dokter) {
                        strcat(shift_str, ", ");
                    }
                    strcat(shift_str, "KOSONG"); 
                    first_dokter = 0;
                }
            }
            printf("%-26s | ", shift_str); 
        }
        printf("\n");
    }
}

int main() {
    const char *nama_file_input_dokter = "doktertubes.csv";

    bacafile(nama_file_input_dokter);
    int jumlah_dokter_terbaca = 0;
    Dokter *temp_node = head_dokter;
    while(temp_node != NULL) {
        jumlah_dokter_terbaca++;
        temp_node = temp_node->berikutnya;
    }

    if (jumlah_dokter_terbaca < NDktrperShift * JUMLAH_SHIFT_PER_HARI) { 
        printf("Jumlah dokter (%d) terlalu sedikit.\n", jumlah_dokter_terbaca, NDktrperShift * JUMLAH_SHIFT_PER_HARI);
        Dokter *saat_ini_free = head_dokter;
        Dokter *berikutnya_free;
        while (saat_ini_free != NULL) {
            berikutnya_free = saat_ini_free->berikutnya;
            free(saat_ini_free);
            saat_ini_free = berikutnya_free;
        }
        head_dokter = NULL;
        return 1; 
    }
    
    lihatDokter();

    reset_jadwal();

    if (buatJadwal(0, 0, 0)) {
        LihatJadwal();
    } 

    /* Bebaskan memori di akhir program */
    Dokter *saat_ini_free = head_dokter;
    Dokter *berikutnya_free;
    while (saat_ini_free != NULL) {
        berikutnya_free = saat_ini_free->berikutnya;
        free(saat_ini_free);
        saat_ini_free = berikutnya_free;
    }
    head_dokter = NULL; 
    
    return 0;
}