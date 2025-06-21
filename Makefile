CC = gcc
CFLAGS = -Wall
OBJ = manageData.o buatjadwal.o informasi.o totalshift_jadwalcsv.o

program: $(OBJ)
	$(CC) -o $@ $^

manageData.o: manageData.c manageData.h
	$(CC) -c manageData.c $(CFLAGS)

# informasi.o: informasi.c informasi.h manageData.h
# 	$(CC) -c informasi.c $(CFLAGS)

# buatjadwal.o: buatjadwal.c buatjadwal.h manageData.h
# 	$(CC) -c buatjadwal.c $(CFLAGS)

# totalshift_jadwalcsv.o: totalshift_jadwalcsv.c totalshift_jadwalcsv.h manageData.h
# 	$(CC) -c totalshift_jadwalcsv.c $(CFLAGS)

run: 
	program.exe daftar_dokter.csv jadwal.csv

clean:
	del /f /q *.o program.exe