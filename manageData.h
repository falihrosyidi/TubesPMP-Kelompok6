#ifndef MANAGEDATA_H
#define MANAGEDATA_H

typedef struct Dokter Dokter;
typedef struct Data Data;

Dokter* findDokter(Data* listDokter, int id);
void addDokter(Data* listDokter, int id, char* nama, int maxShift, char prefShift);
void manual_addDokter(Data* listDokter);
void printData(Data* listDokter);
void editDokter(Data* listDokter);
void deleteNode(Data* listDokter);
void collectData(Data* listDokter, char* fileInput);
void updateData(Data* listDokter, char* namaFile);

#endif // MANAGEDATA_H
