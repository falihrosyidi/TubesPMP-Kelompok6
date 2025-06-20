#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 30

typedef struct Dokter
{
    int id;
    char* nama;
    int maxShift;
    char prefShift;
    struct Dokter* next; 
};

typedef struct Data {
	struct Dokter* head;
	int size;
} Data;

Dokter* findDokter(Data listDokter, int id) {
    Dokter* curr = listDokter.head;
    while (curr != NULL) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

void addDokter(Data listDokter) {
    Dokter* newNode = (Dokter*)malloc(sizeof(Dokter));
    newNode->nama = malloc(MAX_STR*sizeof(char));
    char* ansPref = malloc(MAX_STR*sizeof(char));
	// INTERFACE INPUT
	printf("Nama Dokter: ");
	fgets(newNode->nama, MAX_STR, stdin);

	printf("Maksimal Shift/Minggu: ");
	scanf("%d", &(newNode->maxShift));

	printf("Preferensi Shift (Pagi/Siang/Malam): ");
	fgets(ansPref, MAX_STR, stdin);
	while(ansPref != "Pagi" || ansPref != "Siang" || ansPref != "Malam"){
		printf("Input tidak sesuai data. Silahkan input ulang !!!!\n")
		printf("Preferensi Shift (Pagi/Siang/Malam): ");
		fgets(ansPref, MAX_STR, stdin);
	}
	if(ansPref == "Pagi"){
		newNode->prefShift = 'P';
	} else if(ansPref == "Siang"){
		newNode->prefShift = 'S';
	} else{
		newNode->prefShift = 'M';
	}

	// Memasukkan data di akhir list
    if (listDokter.head == NULL) {
    	newNode->id = 1;
        listDokter.head = newNode;
    } else {
        Dokter* curr = listDokter.head;
        while (curr->next != NULL) curr = curr->next;
        newNode->id = curr->id + 1;
        curr->next = newNode;
    }
}

void printData(Data listDokter){
	char str[MAX_STR];
	Dokter* curr = listDokter.head;
	while(curr!=NULL){
		if(curr->prefShift == 'P'){
			str = "Pagi";
		} else if(curr->prefShift == 'S'){
			str = "Siang";
		} else {
			str = "Malam";
		}
		printf(" ID: %d, Nama: %s, Maksimal Shift/Minggu: %d, Preferensi Shift: %s", curr->id, curr->nama, curr->maxShift, curr->str);
		curr = curr->next;
	}
	listDokter.size = i;
}

void editDokter(Data listDokter) {
	// Tampilkan dokter
	printData(listDokter);

	// Input ID yang dicari
	int id;
	printf("Masukkan ID Dokter yang ingin diubah: ");
	scanf("%d", id);

	// data Dokter
	Dokter* newNode = findDokter(listDokter, id);
	while(newNode == NULL){
		printf("ID dokter tidak ada, masukkan id lagi: ")
		scanf("%d", id);
		newNode = findDokter(listDokter, id);
	}

    char* ansPref = malloc(MAX_STR*sizeof(char));

	// INTERFACE EDIT INPUT
	printf("-------------------------- EDIT DATA DOKTER ------------------------------------")
	printf("Nama Dokter: ");
	fgets(newNode->nama, MAX_STR, stdin);

	printf("Maksimal Shift per Minggu: ");
	scanf("%d", &(newNode->maxShift));

	printf("Preferensi Shift (Pagi/Siang/Malam): ");
	fgets(ansPref, MAX_STR, stdin);
	while(ansPref != "Pagi" || ansPref != "Siang" || ansPref != "Malam"){
		printf("Input tidak sesuai data. Silahkan input ulang !!!!\n")
		printf("Preferensi Shift (Pagi/Siang/Malam): ");
		fgets(ansPref, MAX_STR, stdin);
	}
	if(ansPref == "Pagi"){
		newNode->prefShift = 'P';
	} else if(ansPref == "Siang"){
		newNode->prefShift = 'S';
	} else{
		newNode->prefShift = 'M';
	}

	// Memasukkan data di akhir list
    if (listDokter.head == NULL) {
    	newNode->id = 1;
        listDokter.head = newNode;
        listDokter.size = 1;
    } else {
        Dokter* curr = listDokter.head;
        while (curr->next != NULL) curr = curr->next;
        newNode->id = curr->id + 1;
        curr->next = newNode;
        listDokter.size +=1;
    }
}

void deleteNode(Data listDokter){
	// Input ID
	printData(listDokter);
	// Input ID yang dicari
	int id;
	printf("Masukkan ID Dokter yang ingin diubah: ");
	scanf("%d", id);

	// data Dokter
	Dokter* newNode = findDokter(listDokter, id);
	while(newNode == NULL){
		printf("ID dokter tidak ada, masukkan id lagi: ")
		scanf("%d", id);
		newNode = findDokter(listDokter, id);
	}

	// Main Function
	Dokter* temp, curr;
	curr = listDokter.head;
	while(curr!=NULL){
		temp = curr->next;
		if(temp->id == id){
			curr->next = temp->next;
			free(temp->nama);
			free(temp);
		}
		curr = curr->next;
	}
}

void collectData(Data listDokter){
	
}