CC = gcc
CFLAGS = -Wall
OBJ = main.o manageData.o buatjadwal.o #informasi.o totalshift_jadwalcsv.o

program: $(OBJ)
	$(CC) -o $@ $^

main.o: main.c manageData.h buatjadwal.h #informasi.h totalshift_jadwalcsv.h
	$(CC) $(CFLAGS) -c main.c

manageData.o: manageData.c manageData.h
	$(CC) $(CFLAGS) -c manageData.c

buatjadwal.o: buatjadwal.c buatjadwal.h manageData.h
	$(CC) $(CFLAGS) -c buatjadwal.c

# informasi.o: informasi.c informasi.h manageData.h
# 	$(CC) $(CFLAGS) -c informasi.c 

# totalshift_jadwalcsv.o: totalshift_jadwalcsv.c totalshift_jadwalcsv.h manageData.h
# 	$(CC) $(CFLAGS) -c totalshift_jadwalcsv.c 

run: 
	program.exe daftar_dokter.csv jadwal.csv

clean:
	del /f /q *.o program.exe