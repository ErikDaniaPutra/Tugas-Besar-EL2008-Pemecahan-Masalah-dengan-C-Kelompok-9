/* EL2008 Pemecahan Masalah dengan C 2003/2024
 * Tugas Besar PMC
 * Kelompok  : 9
 * Kelas     : 01
 * File      : func.c
 * Deskripsi : File berisi algoritma fungsi yang digunakan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_Char 100
#define MAX_Data 500
#define MAX_DIAGNOSIS 50
#define MAX_YEARS 100

// Deklarasi array global untuk menyimpan data
DataPasien patient_data[MAX_Data];
RiwayatPasien patient_record[MAX_Data];
int total_patients = 0;
int total_records = 0;

// Fungsi parsing CSV
void parseCSV(){
    // Deklarasi variabel yang dibutuhkan
    char buffer[512];

    // Membuka file CSV
    FILE *file1 = fopen("../data/data_pasien.csv", "r"); // open file external ../data/data_pasien.csv
    if (file1 == NULL){
        printf("file 1 not found.");
    } 

    // Bagian parsing file CSV
    fgets(buffer, sizeof(buffer), file1); // Membaca baris pertama teks dari file1


    // Parsing file 1
    while(fgets(buffer, sizeof(buffer), file1)){
        char* no = strtok(buffer, ",");
        char* name = strtok(NULL, ",");
        char* address = strtok(NULL, ",");
        char* city = strtok(NULL, ",");
        char* place_of_birth = strtok(NULL, ",");
        char* date_of_birth = strtok(NULL, ",");
        char* age = strtok(NULL, ",");
        char* id_bpjs= strtok(NULL, ","); 
        char* id = strtok(NULL, "\n");

        if(no == NULL || name == NULL ||address == NULL || city == NULL || place_of_birth == NULL 
        || date_of_birth == NULL || age == NULL || id_bpjs == NULL || id == NULL){
            continue;
        }

        patient_data[total_patients].number = atoi(no);
        strncpy(patient_data[total_patients].namaPasien, name, sizeof(patient_data[total_patients].namaPasien));
        strncpy(patient_data[total_patients].alamat, address, sizeof(patient_data[total_patients].alamat));
        strncpy(patient_data[total_patients].kota, city, sizeof(patient_data[total_patients].kota));
        strncpy(patient_data[total_patients].tempatLahir, place_of_birth, sizeof(patient_data[total_patients].tempatLahir));
        strncpy(patient_data[total_patients].tanggalLahir, date_of_birth, sizeof(patient_data[total_patients].tanggalLahir));
        patient_data[total_patients].umur = atoi(age);
        strncpy(patient_data[total_patients].bpjs, id_bpjs, sizeof(patient_data[total_patients].bpjs));
        strncpy(patient_data[total_patients].idPasien, id, sizeof(patient_data[total_patients].idPasien));
        total_patients++;
    }
    fclose(file1);

        
    FILE *file2 = fopen("../data/riwayat_pasien.csv", "r"); // open file external ../data/riwayat_pasien.csv
        if (file2 == NULL){
        printf("file 2 not found.");
    }

    
    fgets(buffer, sizeof(buffer), file2); // Membaca baris pertama teks dari file2 
    
    // Parsing file 2
    while(fgets(buffer, sizeof(buffer), file2)){
        char* no = strtok(buffer, ",");
        char* date = strtok(NULL, ",");
        char* id = strtok(NULL, ",");
        char* diagnose = strtok(NULL, ",");
        char* act = strtok(NULL, ",");
        char* control = strtok(NULL, ",");
        char* cost = strtok(NULL, "\n");

        if(no == NULL || date == NULL || id == NULL || diagnose == NULL || control == NULL || cost == NULL){
            continue;;
        }

        patient_record[total_records].number = atoi(no);
        strncpy(patient_record[total_records].tanggal, date, sizeof(patient_record[total_records].tanggal));
        strncpy(patient_record[total_records].idPasien, id, sizeof(patient_record[total_records].idPasien));
        strncpy(patient_record[total_records].diagnosis, diagnose, sizeof(patient_record[total_records].diagnosis));
        strncpy(patient_record[total_records].tindakan, act, sizeof(patient_record[total_records].tindakan));
        strncpy(patient_record[total_records].kontrol, control, sizeof(patient_record[total_records].kontrol));
        patient_record[total_records].biaya = atoi(cost);
        total_records++;
    }
    fclose(file2);
}

/*Fitur nomor 1*/
void writePatient() {
    FILE *file1 = fopen("../data/data_pasien.csv", "w");
    if (file1 == NULL) {
        printf("File 1 not found.\n");
        return;
    }
    fprintf(file1, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien\n");
    for (int i = 0; i < total_patients; i++) {
        fprintf(file1, "%d,%s,%s,%s,%s,%s,%d,%s,%s\n", patient_data[i].number, patient_data[i].namaPasien,
                patient_data[i].alamat, patient_data[i].kota, patient_data[i].tempatLahir,
                patient_data[i].tanggalLahir, patient_data[i].umur, patient_data[i].bpjs, patient_data[i].idPasien);
    }
    fclose(file1);
}

void addDataPasien(DataPasien patient_data[], int *count) {
    if (*count < MAX_Data) {
        DataPasien new_data;
        new_data.number = *count + 1;

        printf("Masukkan nama pasien: ");
        fgets(new_data.namaPasien, MAX_Char, stdin);
        strtok(new_data.namaPasien, "\n"); // remove newline character

        printf("Masukkan alamat pasien: ");
        fgets(new_data.alamat, MAX_Char, stdin);
        strtok(new_data.alamat, "\n");

        printf("Masukkan kota pasien: ");
        fgets(new_data.kota, MAX_Char, stdin);
        strtok(new_data.kota, "\n");

        printf("Masukkan tempat lahir pasien: ");
        fgets(new_data.tempatLahir, MAX_Char, stdin);
        strtok(new_data.tempatLahir, "\n");

        printf("Masukkan tanggal lahir pasien: ");
        fgets(new_data.tanggalLahir, MAX_Char, stdin);
        strtok(new_data.tanggalLahir, "\n");

        printf("Masukkan umur pasien: ");
        scanf("%d", &new_data.umur);
        getchar();

        printf("Masukkan BPJS pasien: ");
        fgets(new_data.bpjs, MAX_Char, stdin);
        strtok(new_data.bpjs, "\n");

        printf("Masukkan ID pasien: ");
        fgets(new_data.idPasien, MAX_Char, stdin);
        strtok(new_data.idPasien, "\n");

        patient_data[*count] = new_data;
        (*count)++;
        printf("Data berhasil ditambahkan.\n");
        writePatient();
    } else {
        printf("Array data penuh.\n");
    }
}

void changeDataPasien(DataPasien patient_data[], int count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan diperbarui: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            DataPasien updated_data;
            updated_data.number = patient_data[i].number;

            printf("Masukkan nama pasien baru: ");
            fgets(updated_data.namaPasien, MAX_Char, stdin);
            strtok(updated_data.namaPasien, "\n");

            printf("Masukkan alamat pasien baru: ");
            fgets(updated_data.alamat, MAX_Char, stdin);
            strtok(updated_data.alamat, "\n");

            printf("Masukkan kota pasien baru: ");
            fgets(updated_data.kota, MAX_Char, stdin);
            strtok(updated_data.kota, "\n");

            printf("Masukkan tempat lahir pasien baru: ");
            fgets(updated_data.tempatLahir, MAX_Char, stdin);
            strtok(updated_data.tempatLahir, "\n");

            printf("Masukkan tanggal lahir pasien baru: ");
            fgets(updated_data.tanggalLahir, MAX_Char, stdin);
            strtok(updated_data.tanggalLahir, "\n");

            printf("Masukkan umur pasien baru: ");
            scanf("%d", &updated_data.umur);
            getchar();

            printf("Masukkan BPJS pasien baru: ");
            fgets(updated_data.bpjs, MAX_Char, stdin);
            strtok(updated_data.bpjs, "\n");

            printf("Masukkan ID pasien baru: ");
            fgets(updated_data.idPasien, MAX_Char, stdin);
            strtok(updated_data.idPasien, "\n");

            patient_data[i] = updated_data;
            printf("Data berhasil diperbarui.\n");
            writePatient();
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void deleteDataPasien(DataPasien patient_data[], int *count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan dihapus: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < *count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                patient_data[j] = patient_data[j + 1];
                patient_data[j].number = j + 1; // update number to reflect new order
            }
            (*count)--;
            printf("Data berhasil dihapus.\n");
            writePatient();
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void findDataPasien(DataPasien patient_data[], int count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan dicari: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            printf("Data ditemukan:\n");
            printf("No: %d\n", patient_data[i].number);
            printf("Nama Pasien: %s\n", patient_data[i].namaPasien);
            printf("Alamat: %s\n", patient_data[i].alamat);
            printf("Kota: %s\n", patient_data[i].kota);
            printf("Tempat Lahir: %s\n", patient_data[i].tempatLahir);
            printf("Tanggal Lahir: %s\n", patient_data[i].tanggalLahir);
            printf("Umur: %d\n", patient_data[i].umur);
            printf("BPJS: %s\n", patient_data[i].bpjs);
            printf("ID Pasien: %s\n", patient_data[i].idPasien);
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}


/*Fitur nomor 2*/
// Fungsi menambahkan data pada daftar riwayat pasien (add, update, delete)
void writeRecords() {
    FILE *file2 = fopen("../data/riwayat_pasien.csv", "w");
    if (file2 == NULL) {
        printf("File 2 not found.\n");
        return;
    }
    fprintf(file2, "No,Tanggal,ID,Diagnosis,Tindakan,Kontrol,Biaya\n");
    for (int i = 0; i < total_records; i++) {
        fprintf(file2, "%d,%s,%s,%s,%s,%s,%d\n", patient_record[i].number, patient_record[i].tanggal,
                patient_record[i].idPasien, patient_record[i].diagnosis, patient_record[i].tindakan,
                patient_record[i].kontrol, patient_record[i].biaya);
    }
    fclose(file2);
}

// Fungsi untuk menampilkan daftar diagnosis dan mendapatkan pilihan dari user
void getDiagnosis(char *diagnosis) {
    int choice;
    printf("Pilih Diagnosis:\n");
    printf("1. Masuk Angin\n");
    printf("2. Dehidrasi\n");
    printf("3. Keseleo\n");
    printf("4. Pusing\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            strcpy(diagnosis, "Masuk Angin");
            break;
        case 2:
            strcpy(diagnosis, "Dehidrasi");
            break;
        case 3:
            strcpy(diagnosis, "Keseleo");
            break;
        case 4:
            strcpy(diagnosis, "Pusing");
            break;
        default:
            printf("Pilihan tidak valid. Diagnosis diatur ke 'Tidak Diketahui'.\n");
            strcpy(diagnosis, "Tidak Diketahui");
            break;
    }
}

// Fungsi untuk menampilkan daftar tindakan dan mendapatkan pilihan dari user
int getTindakan(char *tindakan) {
    int choice, biaya_tindakan = 0;
    printf("Pilih Tindakan:\n");
    printf("1. Pemeriksaan (Rp125000)\n");
    printf("2. Vaksinasi (Rp100000)\n");
    printf("3. Cek gula darah (Rp25000)\n");
    printf("4. Pemasangan infus (Rp125000)\n");
    printf("5. Pengobatan (Rp150000)\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            strcpy(tindakan, "Pemeriksaan");
            biaya_tindakan = 0;
            break;
        case 2:
            strcpy(tindakan, "Vaksinasi");
            biaya_tindakan = 100000;
            break;
        case 3:
            strcpy(tindakan, "Cek gula darah");
            biaya_tindakan = 25000;
            break;
        case 4:
            strcpy(tindakan, "Pemasangan infus");
            biaya_tindakan = 125000;
            break;
        case 5:
            strcpy(tindakan, "Pengobatan");
            biaya_tindakan = 150000;
            break;
        default:
            printf("Pilihan tidak valid. Tindakan diatur ke 'Tidak Diketahui'.\n");
            strcpy(tindakan, "Tidak Diketahui");
            biaya_tindakan = 0;
            break;
    }
    return biaya_tindakan;
}

// Fungsi add riwayat pasien
void addRiwayatPasien() {
    printf("Masukkan detail riwayat pasien:\n");
    patient_record[total_records].number = total_records + 1; // Atur nomor berdasarkan hitungan saat ini
    printf("Tanggal: ");
    scanf(" %[^\n]", patient_record[total_records].tanggal);
    printf("ID Pasien: ");
    scanf(" %[^\n]", patient_record[total_records].idPasien);
    
    getDiagnosis(patient_record[total_records].diagnosis);
    int biaya_tindakan = getTindakan(patient_record[total_records].tindakan);
    
    printf("Kontrol: ");
    scanf(" %[^\n]", patient_record[total_records].kontrol);
    patient_record[total_records].biaya = 15000 + 125000 + biaya_tindakan; // Pendaftaran + Pemeriksaan + Tindakan
    total_records++;

    // Panggil fungsi writeRecords untuk memperbarui file CSV
    writeRecords();
    printf("Data riwayat pasien berhasil ditambahkan.\n");
}

// Fungsi update riwayat pasien dengan akses id pasien
void updateRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id);
    int found = 0;
    printf("Pilih nomor urut rekam medis pasien:\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Riwayat pasien %d: Tanggal: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya (Rp): %d\n",
                   i + 1, patient_record[i].tanggal, patient_record[i].diagnosis,
                   patient_record[i].tindakan, patient_record[i].kontrol, patient_record[i].biaya);
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
        return;
    }
    printf("Masukkan nomor urut rekam medis pasien: ");
    int k; //recordNumber
    scanf("%d", &k);
    if (k < 1 || k > total_records) {
        printf("Nomor urut rekam medis tidak valid.\n");
        return;
    }
    k--; 
    printf("Masukkan detail data riwayat pasien yang baru:\n");
    printf("Tanggal: ");
    scanf(" %[^\n]", patient_record[k].tanggal);
    
    getDiagnosis(patient_record[k].diagnosis);
    int biaya_tindakan = getTindakan(patient_record[k].tindakan);
    
    printf("Kontrol: ");
    scanf(" %[^\n]", patient_record[k].kontrol);
    patient_record[k].biaya = 15000 + 125000 + biaya_tindakan; // Pendaftaran + Pemeriksaan + Tindakan

    writeRecords(); // Memperbarui file CSV setelah melakukan update
    printf("Data riwayat pasien berhasil diubah.\n");
}

// Fungsi delete riwayat pasien dengan akses id pasien
void deleteRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: "); 
    scanf(" %[^\n]", id);          //<-------------- input
    int found = 0;
    int valid_indices[total_records];
    int valid_count = 0;

    printf("Pilih nomor urut rekam medis pasien:\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Rekam medis %d: Tanggal: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya (Rp): %d\n",
                   i + 1, patient_record[i].tanggal, patient_record[i].diagnosis,
                   patient_record[i].tindakan, patient_record[i].kontrol, patient_record[i].biaya);
            valid_indices[valid_count++] = i + 1;  // Store valid indices
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
        return;
    }
    printf("Masukkan nomor urut rekam medis pasien: ");

    int k; // recordNumber
    scanf("%d", &k);                  // <------------------ input

    // Check if k is a valid index
    int is_valid = 0;
    for (int i = 0; i < valid_count; i++) {
        if (k == valid_indices[i]) {
            is_valid = 1;
            break;
        }
    }

    if (!is_valid) {
        printf("Nomor urut rekam medis tidak valid.\n");
        return;
    }

    // Convert k to zero-based index for internal processing
    k--;

    // Geser indeks nomor urut dan mengubah indeks
    for (int i = k; i < total_records - 1; i++) {
        patient_record[i] = patient_record[i + 1];
        patient_record[i].number = i + 1; // Ubah nomor urutan dengan geser indeks
    }
    total_records--;

    writeRecords(); // Menulis kembali ke file setelah melakukan delete
    printf("Data riwayat pasien berhasil dihapus.\n");
}


// Fungsi search riwayat pasien dengan akses id pasien
void searchRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id);
    int found = 0;
    printf("\nHasil Pencarian:\n");
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");
    printf("|  No  |       Tanggal        |        ID        |       Diagnosis      |       Tindakan      |       Kontrol       |    Biaya   |\n");
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("| %4d | %-20s | %-16s | %-20s | %-19s | %-19s | Rp %-7d |\n",
                patient_record[i].number, patient_record[i].tanggal, patient_record[i].idPasien,
                patient_record[i].diagnosis, patient_record[i].tindakan, patient_record[i].kontrol,
                patient_record[i].biaya);
            found = 1;
        }
    }
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");

    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
    }
}


/*Fitur nomor 3*/
// mencari pasien berdasarkan ID Pasien
DataPasien* cari_ID(const char* id) {
    for (int i = 0; i < total_patients; i++) {
        if (strcmp(patient_data[i].idPasien, id) == 0) {
            return &patient_data[i];
        }
    }
    return NULL;
}

// informasi pasien dan riwayatnya
void informasiRiwayatPatient(const char* id) {
    DataPasien* patient = cari_ID(id);
    if (patient == NULL) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    
    // informasi pasien
    printf("\nInformasi Pasien:\n");
    printf("Nama Pasien: %s\n", patient->namaPasien);
    printf("Alamat: %s\n", patient->alamat);
    printf("Kota: %s\n", patient->kota);
    printf("Tempat Lahir: %s\n", patient->tempatLahir);
    printf("Tanggal Lahir: %s\n", patient->tanggalLahir);
    printf("Umur: %d\n", patient->umur);
    printf("No BPJS: %s\n", patient->bpjs);
    printf("ID Pasien: %s\n\n", patient->idPasien);
    
    // riwayat pasien
    printf("Riwayat Pasien:\n");
    int found = 0;
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Tanggal: %s\n", patient_record[i].tanggal);
            printf("Diagnosis: %s\n", patient_record[i].diagnosis);
            printf("Tindakan: %s\n", patient_record[i].tindakan);
            printf("Kontrol: %s\n", patient_record[i].kontrol);
            printf("Biaya: %d\n\n", patient_record[i].biaya);
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat tidak ditemukan.\n");
    }
}


/*Fitur nomor 4*/
int convertDate(const char *input, char *output) {
    int tahun, bulan, hari;
    char bulan_str[20];

    // Format: dd-mm-yyyy atau yyyy-mm-dd atau dd-MMM-yy atau dd MMMM yyyy
    if (sscanf(input, "%d-%d-%d", &hari, &bulan, &tahun) == 3 || sscanf(input, "%d-%d-%d", &tahun, &bulan, &hari) == 3) {
        if (tahun < 100) {
            tahun += (tahun < 50) ? 2000 : 1900;
        }
        sprintf(output, "%d-%02d", tahun, bulan);
        return 1;
    } else if (sscanf(input, "%d %s %d", &hari, bulan_str, &tahun) == 3 || sscanf(input, "%d-%3s-%2d", &hari, bulan_str, &tahun) == 3) {
        if (strcmp(bulan_str, "Januari") == 0 || strcmp(bulan_str, "Jan") == 0) bulan = 1;
        else if (strcmp(bulan_str, "Februari") == 0 || strcmp(bulan_str, "Feb") == 0) bulan = 2;
        else if (strcmp(bulan_str, "Maret") == 0 || strcmp(bulan_str, "Mar") == 0) bulan = 3;
        else if (strcmp(bulan_str, "April") == 0 || strcmp(bulan_str, "Apr") == 0) bulan = 4;
        else if (strcmp(bulan_str, "Mei") == 0 || strcmp(bulan_str, "Mei") == 0) bulan = 5;
        else if (strcmp(bulan_str, "Juni") == 0 || strcmp(bulan_str, "Jun") == 0) bulan = 6;
        else if (strcmp(bulan_str, "Juli") == 0 || strcmp(bulan_str, "Jul") == 0) bulan = 7;
        else if (strcmp(bulan_str, "Agustus") == 0 || strcmp(bulan_str, "Agu") == 0) bulan = 8;
        else if (strcmp(bulan_str, "September") == 0 || strcmp(bulan_str, "Sep") == 0) bulan = 9;
        else if (strcmp(bulan_str, "Oktober") == 0 || strcmp(bulan_str, "Okt") == 0) bulan = 10;
        else if (strcmp(bulan_str, "November") == 0 || strcmp(bulan_str, "Nov") == 0) bulan = 11;
        else if (strcmp(bulan_str, "Desember") == 0 || strcmp(bulan_str, "Des") == 0) bulan = 12;

        if (tahun < 100) {
            tahun += (tahun < 50) ? 2000 : 1900;
        }
        sprintf(output, "%d-%02d", tahun, bulan);
        return 1;
    }
    return 0;
}

void laporanPendapatan(RiwayatPasien riwayat[], int count) {
    int pendapatan_bulanan[MAX_YEARS][12] = {0};
    int tahun_terkecil = 9999, tahun_terbesar = 0;

    for (int i = 0; i < count; i++) {
        char tanggal_formatted[20];
        if (!convertDate(riwayat[i].tanggal, tanggal_formatted)) {
            printf("Format tanggal salah pada entri %d: %s\n", i, riwayat[i].tanggal);
            continue;
        }

        int tahun, bulan;
        sscanf(tanggal_formatted, "%d-%d", &tahun, &bulan);
        
        if (tahun < 2000 || tahun >= 2000 + MAX_YEARS) {
            printf("Tahun %d pada entri %d berada di luar cakupan yang ditangani\n", tahun, i);
            continue;
        }

        pendapatan_bulanan[tahun - 2000][bulan - 1] += riwayat[i].biaya;

        if (tahun < tahun_terkecil) tahun_terkecil = tahun;
        if (tahun > tahun_terbesar) tahun_terbesar = tahun;
    }

    printf("Laporan Pendapatan Bulanan:\n");
    for (int tahun = tahun_terkecil; tahun <= tahun_terbesar; tahun++) {
        printf("Tahun %d:\n", tahun);
        for (int bulan = 0; bulan < 12; bulan++) {
            printf("  Bulan %d: Rp %d\n", bulan + 1, pendapatan_bulanan[tahun - 2000][bulan]);
        }
    }

    printf("\nLaporan Pendapatan Tahunan:\n");
    int total_pendapatan_tahunan = 0;
    for (int tahun = tahun_terkecil; tahun <= tahun_terbesar; tahun++) {
        int total_tahunan = 0;
        for (int bulan = 0; bulan < 12; bulan++) {
            total_tahunan += pendapatan_bulanan[tahun - 2000][bulan];
        }
        printf("Tahun %d: Rp %d\n", tahun, total_tahunan);
        total_pendapatan_tahunan += total_tahunan;
    }
    
    int jumlah_tahun = tahun_terbesar - tahun_terkecil + 1;
    if (jumlah_tahun > 0) {
        printf("Rata-rata Pendapatan Per Tahun: Rp %d\n", total_pendapatan_tahunan / jumlah_tahun);
    } else {
        printf("Tidak ada data tahunan yang valid\n");
    }
}

/*Fitur nomor 5*/
// Fungsi untuk mengonversi tanggal ke format "yyyy-mm"
int convertTanggal(const char *input, char *output) {
    int tahun, bulan, hari;
    char bulan_str[20];

    // Format: dd-MMM-yy atau dd MMMM yyyy
    if (sscanf(input, "%d-%3s-%2d", &hari, bulan_str, &tahun) == 3) {
        if (strcmp(bulan_str, "Jan") == 0) bulan = 1;
        else if (strcmp(bulan_str, "Feb") == 0) bulan = 2;
        else if (strcmp(bulan_str, "Mar") == 0) bulan = 3;
        else if (strcmp(bulan_str, "Apr") == 0) bulan = 4;
        else if (strcmp(bulan_str, "Mei") == 0) bulan = 5;
        else if (strcmp(bulan_str, "Jun") == 0) bulan = 6;
        else if (strcmp(bulan_str, "Jul") == 0) bulan = 7;
        else if (strcmp(bulan_str, "Agu") == 0) bulan = 8;
        else if (strcmp(bulan_str, "Sep") == 0) bulan = 9;
        else if (strcmp(bulan_str, "Okt") == 0) bulan = 10;
        else if (strcmp(bulan_str, "Nov") == 0) bulan = 11;
        else if (strcmp(bulan_str, "Des") == 0) bulan = 12;
        else return 0;

        if (tahun < 100) {
            tahun += (tahun < 50) ? 2000 : 1900;
        }
        sprintf(output, "%d-%02d", tahun, bulan);
        return 1;
    } else if (sscanf(input, "%d %s %d", &hari, bulan_str, &tahun) == 3) {
        if (strcmp(bulan_str, "Januari") == 0) bulan = 1;
        else if (strcmp(bulan_str, "Februari") == 0) bulan = 2;
        else if (strcmp(bulan_str, "Maret") == 0) bulan = 3;
        else if (strcmp(bulan_str, "April") == 0) bulan = 4;
        else if (strcmp(bulan_str, "Mei") == 0) bulan = 5;
        else if (strcmp(bulan_str, "Juni") == 0) bulan = 6;
        else if (strcmp(bulan_str, "Juli") == 0) bulan = 7;
        else if (strcmp(bulan_str, "Agustus") == 0) bulan = 8;
        else if (strcmp(bulan_str, "September") == 0) bulan = 9;
        else if (strcmp(bulan_str, "Oktober") == 0) bulan = 10;
        else if (strcmp(bulan_str, "November") == 0) bulan = 11;
        else if (strcmp(bulan_str, "Desember") == 0) bulan = 12;
        else return 0;

        if (tahun < 100) {
            tahun += (tahun < 50) ? 2000 : 1900;
        }
        sprintf(output, "%d-%02d", tahun, bulan);
        return 1;
    }
    return 0;
}

// Fungsi untuk menghasilkan laporan jumlah pasien berdasarkan diagnosis
void laporanJumlahPasien(RiwayatPasien riwayat[], int count) {
    int jumlah_pasien_bulanan[MAX_YEARS][12][4] = {0}; // Maksimum 4 diagnosis

    for (int i = 0; i < count; ++i) {
        char tanggal_formatted[20];
        if (!convertTanggal(riwayat[i].tanggal, tanggal_formatted)) {
            printf("Format tanggal salah pada entri %d: %s\n", i, riwayat[i].tanggal);
            continue;
        }

        int tahun, bulan;
        sscanf(tanggal_formatted, "%d-%d", &tahun, &bulan);

        if (tahun < 2000 || tahun >= 2000 + MAX_YEARS) {
            printf("Tahun %d pada entri %d berada di luar cakupan yang ditangani\n", tahun, i);
            continue;
        }

        int diagnosis_index = -1;
        if (strcmp(riwayat[i].diagnosis, "Dehidrasi") == 0) {
            diagnosis_index = 0;
        } else if (strcmp(riwayat[i].diagnosis, "Pusing") == 0) {
            diagnosis_index = 1;
        } else if (strcmp(riwayat[i].diagnosis, "Masuk Angin") == 0) {
            diagnosis_index = 2;
        } else if (strcmp(riwayat[i].diagnosis, "Keseleo") == 0) {
            diagnosis_index = 3;
        }

        if (diagnosis_index != -1) {
            jumlah_pasien_bulanan[tahun - 2000][bulan - 1][diagnosis_index]++;
        } else {
            printf("Diagnosis tidak dikenali pada entri %d: %s\n", i, riwayat[i].diagnosis);
            continue;
        }
    }

    printf("Laporan Jumlah Pasien Bulanan:\n");
    for (int tahun = 0; tahun < MAX_YEARS; tahun++) {
        for (int bulan = 0; bulan < 12; bulan++) {
            if (jumlah_pasien_bulanan[tahun][bulan][0] > 0 ||
                jumlah_pasien_bulanan[tahun][bulan][1] > 0 ||
                jumlah_pasien_bulanan[tahun][bulan][2] > 0 ||
                jumlah_pasien_bulanan[tahun][bulan][3] > 0) {
                printf("Tahun : %d\n", tahun + 2000);
                printf("Bulan - %d\n", bulan + 1);
                printf("-> Dehidrasi : %d\n", jumlah_pasien_bulanan[tahun][bulan][0]);
                printf("-> Pusing : %d\n", jumlah_pasien_bulanan[tahun][bulan][1]);
                printf("-> Masuk Angin : %d\n", jumlah_pasien_bulanan[tahun][bulan][2]);
                printf("-> Keseleo : %d\n", jumlah_pasien_bulanan[tahun][bulan][3]);
            }
        }
    }
}

/*Fitur nomor 6*/
// pasien yang perlu kembali kontrol
void kontrolPatient() {
    printf("\nPasien yang Perlu Kembali Kontrol:\n");
    int found = 0;
    for (int i = 0; i < total_records; i++) {
        if (strlen(patient_record[i].kontrol) > 0 && strcmp(patient_record[i].kontrol, "-") != 0) {
            DataPasien* patient = cari_ID(patient_record[i].idPasien);
            if (patient != NULL) {
                printf("Nama Pasien: %s\n", patient->namaPasien);
                printf("ID Pasien: %s\n", patient->idPasien);
                printf("Tanggal Kontrol: %s\n\n", patient_record[i].kontrol);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Tidak ada pasien yang perlu kembali kontrol.\n");
    }
}
