/* EL2008 Pemecahan Masalah dengan C 2003/2024
 * Tugas Besar PMC
 * Kelompok  : 9
 * Kelas     : 01
 * File      : func.h
 * Deskripsi : File header untuk deklarasi struct ,fungsi, fitur yang digunakan pada program main.c
*/

#ifndef __FUNC_H__
#define __FUNC_H__

#define MAX_Char 100
#define MAX_Data 500
#define MAX_DIAGNOSIS 50

typedef struct{
    int number;
    char namaPasien[MAX_Char];
    char alamat[MAX_Char];
    char kota[MAX_Char];
    char tempatLahir[MAX_Char];
    char tanggalLahir[MAX_Char];
    int umur;
    char bpjs[MAX_Char];
    char idPasien[MAX_Char];
} DataPasien;

typedef struct{
    int number;
    char tanggal[MAX_Char];
    char idPasien[MAX_Char];
    char diagnosis[MAX_Char];
    char tindakan[MAX_Char];
    char kontrol[MAX_Char];
    int biaya;
} RiwayatPasien;

typedef struct {
    char diagnosis[50];
    int jumlah;
} DiagnosisCount;


// Fungsi parsing CSV
void parseCSV();

// Fungsi Write CSV
void writePatient();

// Fitur 1
void addDataPasien(DataPasien patient_data[], int *count);
void changeDataPasien(DataPasien patient_data[], int count);
void deleteDataPasien(DataPasien patient_data[], int *count);
void findDataPasien(DataPasien patient_data[], int count);

// Fungsi Write CSV
void writeRecords();

// Fitur 2
void getDiagnosis(char *diagnosis);
int getTindakan(char *tindakan);
void addRiwayatPasien();
void updateRiwayatPasien();
void deleteRiwayatPasien();
void searchRiwayatPasien();

// Fitur 3
DataPasien* cari_ID(const char* id);
void informasiRiwayatPatient(const char* id);

// Fitur 4
int convertDate(const char *input, char *output);
void laporanPendapatan(RiwayatPasien riwayat[], int count);

// Fitur 5
int convertTanggal(const char *input, char *output);
void laporanJumlahPasien(RiwayatPasien riwayat[], int count);

// Fitur 6
void kontrolPatient();

#endif 
