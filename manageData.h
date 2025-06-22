#ifndef MANAGEDATA_H
#define MANAGEDATA_H

#define MAX_STR 30
#define MAX_INPUT_CSV 100

typedef struct Dokter {
    int id;
    char* nama;
    int maxShift;
    char prefShift;
    struct Dokter* next; 
} Dokter;

typedef struct Data {
    Dokter* head;
    int size;
} Data;

Dokter* findDokter(Data* listDokter, int id);
void addDokter(Data* listDokter, int id, char* nama, int maxShift, char prefShift);
void manual_addDokter(Data* listDokter);
void printData(Data* listDokter);
void editDokter(Data* listDokter);
void deleteDokter(Data* listDokter, int id);       
void manual_deleteDokter(Data* listDokter);       
void collectData(Data* listDokter, char* namaFile);
void updateData(Data* listDokter, char* namaFile);
// Dokter* listToArray(Data* listDokter);

#endif // MANAGEDATA_H
