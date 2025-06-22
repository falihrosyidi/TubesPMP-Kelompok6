#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manageData.h"

Dokter* findDokter(Data* listDokter, int id) {
    Dokter* curr = listDokter->head;
    while (curr != NULL) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

void addDokter(Data* listDokter, int id, char* nama, int maxShift, char prefShift) {
    Dokter* newNode = (Dokter*)malloc(sizeof(Dokter));
    newNode->nama = malloc(strlen(nama) + 1);
    strcpy(newNode->nama, nama);
    newNode->maxShift = maxShift;
    newNode->prefShift = prefShift;
    newNode->next = NULL;

    if (listDokter->head == NULL) {
        newNode->id = (id == -99) ? 1 : id;
        listDokter->head = newNode;
    } else {
        Dokter* curr = listDokter->head;
        while (curr->next != NULL) curr = curr->next;
        newNode->id = (id == -99) ? curr->id + 1 : id;
        curr->next = newNode;
    }
    listDokter->size++;
}

void manual_addDokter(Data* listDokter) {
    char* nama = malloc(MAX_STR);
    int maxShift;
    char ansPref[MAX_STR];
    char prefShift;

    printf("Nama Dokter: ");
    fgets(nama, MAX_STR, stdin);
    nama[strcspn(nama, "\n")] = '\0';

    printf("Maksimal Shift/Minggu: ");
    scanf("%d", &maxShift);
    getchar(); // consume newline

    printf("Preferensi Shift (Pagi/Siang/Malam): ");
    fgets(ansPref, MAX_STR, stdin);
    ansPref[strcspn(ansPref, "\n")] = '\0';

    while (strcmp(ansPref, "Pagi") != 0 && strcmp(ansPref, "Siang") != 0 && strcmp(ansPref, "Malam") != 0) {
        printf("Input tidak sesuai data. Silahkan input ulang !!!!\n");
        printf("Preferensi Shift (Pagi/Siang/Malam): ");
        fgets(ansPref, MAX_STR, stdin);
        ansPref[strcspn(ansPref, "\n")] = '\0';
    }

    if (strcmp(ansPref, "Pagi") == 0) prefShift = 'P';
    else if (strcmp(ansPref, "Siang") == 0) prefShift = 'S';
    else prefShift = 'M';

    addDokter(listDokter, -99, nama, maxShift, prefShift);
    free(nama);
}

void printData(Data* listDokter) {
    Dokter* curr = listDokter->head;
    char str[MAX_STR];
    while (curr != NULL) {
        if (curr->prefShift == 'P') strcpy(str, "Pagi");
        else if (curr->prefShift == 'S') strcpy(str, "Siang");
        else strcpy(str, "Malam");

        printf("ID: %02d, \tNama: %s, \tMaksimal Shift/Minggu: %02d, \tPreferensi Shift: %s\n",
               curr->id, curr->nama, curr->maxShift, str);
        curr = curr->next;
    }
}

void editDokter(Data* listDokter) {
    printData(listDokter);

    int id;
    printf("Masukkan ID Dokter yang ingin diubah: ");
    scanf("%d", &id);
    getchar(); // consume newline

    Dokter* node = findDokter(listDokter, id);
    while (node == NULL) {
        printf("ID dokter tidak ada, masukkan id lagi: ");
        scanf("%d", &id);
        getchar();
        node = findDokter(listDokter, id);
    }

    char ansPref[MAX_STR];
    printf("-------------------------- EDIT DATA DOKTER ------------------------------------\n");
    printf("Nama Dokter: ");
    fgets(node->nama, MAX_STR, stdin);
    node->nama[strcspn(node->nama, "\n")] = '\0';

    printf("Maksimal Shift per Minggu: ");
    scanf("%d", &node->maxShift);
    getchar();

    printf("Preferensi Shift (Pagi/Siang/Malam): ");
    fgets(ansPref, MAX_STR, stdin);
    ansPref[strcspn(ansPref, "\n")] = '\0';

    while (strcmp(ansPref, "Pagi") != 0 && strcmp(ansPref, "Siang") != 0 && strcmp(ansPref, "Malam") != 0) {
        printf("Input tidak sesuai data. Silahkan input ulang !!!!\n");
        printf("Preferensi Shift (Pagi/Siang/Malam): ");
        fgets(ansPref, MAX_STR, stdin);
        ansPref[strcspn(ansPref, "\n")] = '\0';
    }

    if (strcmp(ansPref, "Pagi") == 0) node->prefShift = 'P';
    else if (strcmp(ansPref, "Siang") == 0) node->prefShift = 'S';
    else node->prefShift = 'M';
}

void deleteDokter(Data* listDokter, int id) {
    Dokter* curr = listDokter->head;
    Dokter* prev = NULL;

    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Dokter dengan ID %d tidak ditemukan.\n", id);
        return;
    }

    if (prev == NULL) listDokter->head = curr->next;
    else prev->next = curr->next;

    free(curr->nama);
    free(curr);
    listDokter->size--;
    printf("Data dokter dengan ID %d berhasil dihapus.\n", id);
}

void manual_deleteDokter(Data* listDokter) {
    printData(listDokter);
    int id;
    printf("Masukkan ID Dokter yang ingin dihapus: ");
    scanf("%d", &id);
    deleteDokter(listDokter, id);
}

void collectData(Data* listDokter, char* namaFile) {
    FILE* fptr = fopen(namaFile, "r");
    if (fptr == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }

    char str[MAX_INPUT_CSV];
    while (fgets(str, MAX_INPUT_CSV, fptr)) {
    	if (strcmp(str, "Id;Nama Dokter;Maksimal Shift per Minggu;Preferensi Shift\n") == 0) continue;

        char* token = strtok(str, ";"); 
        if   (!token) continue;
        int id = atoi(token); 

        char* nama = strtok(NULL, ";"); 
        if (!nama) continue;

        char* shiftStr = strtok(NULL, ";");
        if (!shiftStr) continue;
        int maxShift = atoi(shiftStr);

        char* prefStr = strtok(NULL, ";\n"); 
        if (!prefStr) continue;

        char prefShift = (strcmp(prefStr, "Pagi") == 0) ? 'P' : (strcmp(prefStr, "Siang") == 0) ? 'S' : 'M';

        addDokter(listDokter, id, nama, maxShift, prefShift);
    }
    fclose(fptr);
}

void updateData(Data* listDokter, char* namaFile) {
    FILE* fptr = fopen(namaFile, "w");
    if (fptr == NULL) {
        printf("Gagal membuka file untuk penulisan\n");
        return;
    }

    fprintf(fptr, "Id;Nama Dokter;Maksimal Shift per Minggu;Preferensi Shift\n");
    Dokter* curr = listDokter->head;
    while (curr != NULL) {
        char* ansPref = (curr->prefShift == 'P') ? "Pagi" : (curr->prefShift == 'S') ? "Siang" : "Malam";
        fprintf(fptr, "%d;%s;%d;%s\n", curr->id, curr->nama, curr->maxShift, ansPref);
        curr = curr->next;
    }
    fclose(fptr);
}