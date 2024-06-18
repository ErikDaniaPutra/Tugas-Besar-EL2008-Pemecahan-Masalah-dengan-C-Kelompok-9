/* EL2008 Pemecahan Masalah dengan C 2003/2024
 * Tugas Besar PMC
 * Kelompok  : 9
 * Kelas     : 01
 * File      : main.c
 * Deskripsi : 
*/

#include <stdio.h>
#include <stdlib.h>
#include "func.c"

int main(){
    // Parsing file CSV dan memasukkan pada Struct
    parseCSV();

    // Input Pilihan Fitur oleh User
    int choice;
    do {
        printf("\nSistem Pencatatan Pasien Klinik X\n");
        printf("1. Add Data Pasien\n");
        printf("2. Update Data Pasien\n");
        printf("3. Delete Data Pasien\n");
        printf("4. Search Data Pasien\n");
        printf("5. Add Medical Record\n");
        printf("6. Update Medical Record\n");
        printf("7. Delete Medical Record\n");
        printf("8. Search Medical Record\n");
        printf("9. Cari Informasi dan Riwayat Pasien\n");
        printf("10. Laporan Pendapatan\n");
        printf("11. Laporan Pasien\n");
        printf("12. Lihat Pasien untuk Kontrol\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addDataPasien(patient_data, &total_patients);
                break;
            case 2:
                changeDataPasien(patient_data, total_patients);
                break;
            case 3:
                deleteDataPasien(patient_data, &total_patients);
                break;
            case 4:
                findDataPasien(patient_data, total_patients);
                break;
            case 5:
                addRiwayatPasien();
                break;
            case 6:
                updateRiwayatPasien();
                break;
            case 7:
                deleteRiwayatPasien();
                break;
            case 8:
                searchRiwayatPasien();
                break;
            case 9:
                char id[MAX_Char];
                printf("Masukkan ID Pasien: ");
                fgets(id, MAX_Char, stdin);
                strtok(id, "\n");
                informasiRiwayatPatient(id);
                break;

            case 10:
                printf("\nJumlah data riwayat pasien: %d\n",total_records);
                printf("Menghitung data...\n");
                laporanPendapatan(patient_record, total_records);
                break;

            case 11: {
                printf("\nJumlah data riwayat pasien: %d\n", total_records);
                printf("Menghitung laporan jumlah pasien...\n");
                laporanJumlahPasien(patient_record, total_records);
                break;
            }
            case 12:
                kontrolPatient();
                break;

            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}
