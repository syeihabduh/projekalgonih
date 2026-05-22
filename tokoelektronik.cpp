#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// ---------- Struktur Data ----------
struct Barang {
    int id;
    char nama[50];       // ubah ke char array agar kompatibel dengan file biner
    char kategori[30];
    int harga;
    int stok;
    Barang* next;
};

Barang* head = NULL;
int idOtomatis = 0;

// ---------- Prototype Fungsi ----------
int hitungData();
void simpanKeFileTeks();
void muatDariFileTeks();
void simpanKeFileBiner();
void muatDariFileBiner();

void tambahDiAwal();
void tambahSetelahID();
void quickSortHarga();
void binarySearchHarga();

// ---------- TAMBAH BARANG (di akhir) ----------
void tambahBarang() {
    Barang* baru = new Barang;
    baru->id = ++idOtomatis;

    cout << "Nama Barang : ";
    cin >> baru->nama;
    cout << "Kategori : ";
    cin >> baru->kategori;
    cout << "Harga : ";
    cin >> baru->harga;
    cout << "Stok : ";
    cin >> baru->stok;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Barang* bantu = head;
        while (bantu->next != NULL)
            bantu = bantu->next;
        bantu->next = baru;
    }
    cout << "Barang berhasil ditambahkan (ID = " << baru->id << ")\n";
}

// ---------- TAMPILKAN SEMUA BARANG ----------
void tampilBarang() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }
    Barang* bantu = head;
    cout << "\n===== DATA BARANG =====\n";
    while (bantu != NULL) {
        cout << "ID       : " << bantu->id << endl;
        cout << "Nama     : " << bantu->nama << endl;
        cout << "Kategori : " << bantu->kategori << endl;
        cout << "Harga    : " << bantu->harga << endl;
        cout << "Stok     : " << bantu->stok << endl;
        cout << "========================\n";
        bantu = bantu->next;
    }
}

// ---------- SEQUENTIAL SEARCH (berdasarkan ID) ----------
void cariBarang() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }
    int cari;
    cout << "Masukkan ID barang : ";
    cin >> cari;
    Barang* bantu = head;
    while (bantu != NULL) {
        if (bantu->id == cari) {
            cout << "\nData ditemukan\n";
            cout << "ID       : " << bantu->id << endl;
            cout << "Nama     : " << bantu->nama << endl;
            cout << "Kategori : " << bantu->kategori << endl;
            cout << "Harga    : " << bantu->harga << endl;
            cout << "Stok     : " << bantu->stok << endl;
            return;
        }
        bantu = bantu->next;
    }
    cout << "Data tidak ditemukan\n";
}

// ---------- EDIT BARANG ----------
void editBarang() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }
    int cari;
    cout << "Masukkan ID barang yang diedit : ";
    cin >> cari;
    Barang* bantu = head;
    while (bantu != NULL) {
        if (bantu->id == cari) {
            cout << "Nama Baru : "; cin >> bantu->nama;
            cout << "Kategori Baru : "; cin >> bantu->kategori;
            cout << "Harga Baru : "; cin >> bantu->harga;
            cout << "Stok Baru : "; cin >> bantu->stok;
            cout << "Data berhasil diedit\n";
            return;
        }
        bantu = bantu->next;
    }
    cout << "Data tidak ditemukan\n";
}

// ---------- HAPUS BARANG ----------
void hapusBarang() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }
    int hapus;
    cout << "Masukkan ID barang yang dihapus : ";
    cin >> hapus;
    Barang* bantu = head;
    Barang* sebelum = NULL;
    while (bantu != NULL) {
        if (bantu->id == hapus) {
            if (sebelum == NULL)
                head = bantu->next;
            else
                sebelum->next = bantu->next;
            delete bantu;
            cout << "Data berhasil dihapus\n";
            return;
        }
        sebelum = bantu;
        bantu = bantu->next;
    }
    cout << "Data tidak ditemukan\n";
}

// ---------- HITUNG JUMLAH DATA ----------
int hitungData() {
    int jumlah = 0;
    Barang* bantu = head;
    while (bantu != NULL) {
        jumlah++;
        bantu = bantu->next;
    }
    return jumlah;
}

// ================= SORTING =================

// Bubble Sort Harga (ascending) - sudah ada, ditampilkan tanpa mengubah LL
void bubbleSortHarga() {
    int jumlah = hitungData();
    if (jumlah == 0) {
        cout << "Data kosong\n";
        return;
    }
    Barang* data[100];
    Barang* bantu = head;
    int i = 0;
    while (bantu != NULL) {
        data[i++] = bantu;
        bantu = bantu->next;
    }
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j]->harga > data[j+1]->harga) {
                Barang* temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
    cout << "\nData setelah Bubble Sort (harga ascending):\n";
    for (int i = 0; i < jumlah; i++) {
        cout << data[i]->id << " | " << data[i]->nama << " | " << data[i]->harga << endl;
    }
}

// Quick Sort (rekursif) pada array pointer Barang*
void quick(Barang* arr[], int kiri, int kanan) {
    if (kiri >= kanan) return;
    int low = kiri, high = kanan;
    int pivot = arr[(kiri+kanan)/2]->harga;
    while (low <= high) {
        while (arr[low]->harga < pivot) low++;
        while (arr[high]->harga > pivot) high--;
        if (low <= high) {
            Barang* temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
            low++; high--;
        }
    }
    quick(arr, kiri, high);
    quick(arr, low, kanan);
}

void quickSortHarga() {
    int jumlah = hitungData();
    if (jumlah == 0) {
        cout << "Data kosong\n";
        return;
    }
    Barang* data[100];
    Barang* bantu = head;
    int i = 0;
    while (bantu != NULL) {
        data[i++] = bantu;
        bantu = bantu->next;
    }
    quick(data, 0, jumlah-1);
    cout << "\nData setelah Quick Sort (harga ascending):\n";
    for (int i = 0; i < jumlah; i++) {
        cout << data[i]->id << " | " << data[i]->nama << " | " << data[i]->harga << endl;
    }
}

// ================= SEARCHING (Binary Search) =================
void binarySearchHarga() {
    int jumlah = hitungData();
    if (jumlah == 0) {
        cout << "Data kosong\n";
        return;
    }
    // Salin ke array dan urutkan dengan quick sort
    Barang* data[100];
    Barang* bantu = head;
    int i = 0;
    while (bantu != NULL) {
        data[i++] = bantu;
        bantu = bantu->next;
    }
    quick(data, 0, jumlah-1);  // urutkan berdasarkan harga
    
    int target;
    cout << "Masukkan harga yang dicari : ";
    cin >> target;
    int kiri = 0, kanan = jumlah-1, tengah;
    bool ditemukan = false;
    int pos = -1;
    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;
        if (data[tengah]->harga == target) {
            ditemukan = true;
            pos = tengah;
            break;
        } else if (data[tengah]->harga < target) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    if (ditemukan) {
        cout << "\nData dengan harga " << target << " ditemukan:\n";
        // Bisa lebih dari satu, tampilkan semua yang harganya sama
        cout << "ID\tNama\t\tHarga\n";
        for (int i = pos; i >= 0 && data[i]->harga == target; i--) {
            cout << data[i]->id << "\t" << data[i]->nama << "\t\t" << data[i]->harga << endl;
        }
        for (int i = pos+1; i < jumlah && data[i]->harga == target; i++) {
            cout << data[i]->id << "\t" << data[i]->nama << "\t\t" << data[i]->harga << endl;
        }
    } else {
        cout << "Harga " << target << " tidak ditemukan.\n";
    }
}

// Sequential Search berdasarkan nama (string)
void cariBarangByName() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }
    char cari[50];
    cout << "Masukkan Nama barang : ";
    cin >> cari;
    Barang* bantu = head;
    bool ketemu = false;
    while (bantu != NULL) {
        if (strcmp(bantu->nama, cari) == 0) {
            cout << "\nData ditemukan\n";
            cout << "ID : " << bantu->id << " | Nama : " << bantu->nama
                 << " | Harga : " << bantu->harga << " | Stok : " << bantu->stok << endl;
            ketemu = true;
        }
        bantu = bantu->next;
    }
    if (!ketemu) cout << "Nama \"" << cari << "\" tidak ditemukan.\n";
}

// ================= FILE HANDLING (TEKS) =================
void simpanKeFileTeks() {
    FILE *fptr = fopen("barang.txt", "w");
    if (fptr == NULL) {
        cout << "Error membuka file untuk menulis!\n";
        return;
    }
    Barang* bantu = head;
    while (bantu != NULL) {
        fprintf(fptr, "%d|%s|%s|%d|%d\n", bantu->id, bantu->nama, bantu->kategori, bantu->harga, bantu->stok);
        bantu = bantu->next;
    }
    fclose(fptr);
    cout << "Data berhasil disimpan ke barang.txt (format teks)\n";
}

void muatDariFileTeks() {
    FILE *fptr = fopen("barang.txt", "r");
    if (fptr == NULL) {
        cout << "File barang.txt tidak ditemukan!\n";
        return;
    }
    // Hapus linked list yang ada
    while (head != NULL) {
        Barang* hapus = head;
        head = head->next;
        delete hapus;
    }
    idOtomatis = 0;
    Barang* tail = NULL;
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), fptr)) {
        Barang* baru = new Barang;
        sscanf(buffer, "%d|%[^|]|%[^|]|%d|%d", &baru->id, baru->nama, baru->kategori, &baru->harga, &baru->stok);
        baru->next = NULL;
        if (baru->id > idOtomatis) idOtomatis = baru->id;
        if (head == NULL) {
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
    }
    fclose(fptr);
    cout << "Data berhasil dimuat dari barang.txt\n";
}

// ================= FILE HANDLING (BINER) =================
// Struktur untuk penyimpanan biner (fixed length)
struct BarangBiner {
    int id;
    char nama[50];
    char kategori[30];
    int harga;
    int stok;
};

void simpanKeFileBiner() {
    FILE *fptr = fopen("barang.dat", "wb");
    if (fptr == NULL) {
        cout << "Error membuka file biner!\n";
        return;
    }
    Barang* bantu = head;
    while (bantu != NULL) {
        BarangBiner bin;
        bin.id = bantu->id;
        strcpy(bin.nama, bantu->nama);
        strcpy(bin.kategori, bantu->kategori);
        bin.harga = bantu->harga;
        bin.stok = bantu->stok;
        fwrite(&bin, sizeof(BarangBiner), 1, fptr);
        bantu = bantu->next;
    }
    fclose(fptr);
    cout << "Data berhasil disimpan ke barang.dat (format biner)\n";
}

void muatDariFileBiner() {
    FILE *fptr = fopen("barang.dat", "rb");
    if (fptr == NULL) {
        cout << "File barang.dat tidak ditemukan!\n";
        return;
    }
    // Hapus linked list lama
    while (head != NULL) {
        Barang* hapus = head;
        head = head->next;
        delete hapus;
    }
    idOtomatis = 0;
    Barang* tail = NULL;
    BarangBiner bin;
    while (fread(&bin, sizeof(BarangBiner), 1, fptr) == 1) {
        Barang* baru = new Barang;
        baru->id = bin.id;
        strcpy(baru->nama, bin.nama);
        strcpy(baru->kategori, bin.kategori);
        baru->harga = bin.harga;
        baru->stok = bin.stok;
        baru->next = NULL;
        if (baru->id > idOtomatis) idOtomatis = baru->id;
        if (head == NULL) {
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
    }
    fclose(fptr);
    cout << "Data berhasil dimuat dari barang.dat (biner)\n";
}



// ================= OPERASI LINKED LIST TAMBAHAN =================
void tambahDiAwal() {
    Barang* baru = new Barang;
    baru->id = ++idOtomatis;
    cout << "Nama Barang : "; cin >> baru->nama;
    cout << "Kategori : "; cin >> baru->kategori;
    cout << "Harga : "; cin >> baru->harga;
    cout << "Stok : "; cin >> baru->stok;
    baru->next = head;
    head = baru;
    cout << "Barang berhasil ditambahkan di awal (ID = " << baru->id << ")\n";
}

void tambahSetelahID() {
    if (head == NULL) {
        cout << "Data kosong, tidak bisa tambah setelah.\n";
        return;
    }
    int idTarget;
    cout << "Masukkan ID setelah barang mana: ";
    cin >> idTarget;
    Barang* bantu = head;
    while (bantu != NULL && bantu->id != idTarget) {
        bantu = bantu->next;
    }
    if (bantu == NULL) {
        cout << "ID tidak ditemukan.\n";
        return;
    }
    Barang* baru = new Barang;
    baru->id = ++idOtomatis;
    cout << "Nama Barang : "; cin >> baru->nama;
    cout << "Kategori : "; cin >> baru->kategori;
    cout << "Harga : "; cin >> baru->harga;
    cout << "Stok : "; cin >> baru->stok;
    baru->next = bantu->next;
    bantu->next = baru;
    cout << "Barang berhasil ditambahkan setelah ID " << idTarget << "\n";
}

// ================= MENU UTAMA =================
int main() {
    int pilih;
    do {
        cout << "\n===== MENU TOKO ELEKTRONIK (TERINTEGRASI) =====\n";
        cout << "1.  Tambah Barang (di akhir)\n";
        cout << "2.  Tampilkan Semua Barang\n";
        cout << "3.  Cari Barang (Sequential by ID)\n";
        cout << "4.  Edit Barang\n";
        cout << "5.  Hapus Barang\n";
        cout << "6.  Sorting (Bubble / Quick)\n";
        cout << "7.  Searching Lanjutan (Binary Harga / Nama)\n";
        cout << "8.  File Handling (Teks & Biner)\n";
        cout << "9. Linked List Tambahan (Tambah di awal / setelah ID)\n";
        cout << "0.  Keluar\n";
        cout << "Pilih Menu : ";
        cin >> pilih;
        
        if (pilih == 1) {
            tambahBarang();
        } else if (pilih == 2) {
            tampilBarang();
        } else if (pilih == 3) {
            cariBarang();
        } else if (pilih == 4) {
            editBarang();
        } else if (pilih == 5) {
            hapusBarang();
        } else if (pilih == 6) {
            int sub;
            cout << "   Sorting:\n";
            cout << "   1. Bubble Sort (harga ascending)\n";
            cout << "   2. Quick Sort (harga ascending)\n";
            cout << "   Pilih: ";
            cin >> sub;
            if (sub == 1) bubbleSortHarga();
            else if (sub == 2) quickSortHarga();
            else cout << "Pilihan salah\n";
        } else if (pilih == 7) {
            int sub;
            cout << "   Searching:\n";
            cout << "   1. Binary Search berdasarkan Harga (data diurut sementara)\n";
            cout << "   2. Sequential Search berdasarkan Nama\n";
            cout << "   Pilih: ";
            cin >> sub;
            if (sub == 1) binarySearchHarga();
            else if (sub == 2) cariBarangByName();
            else cout << "Pilihan salah\n";
        } else if (pilih == 8) {
            int sub;
            cout << "   File Handling:\n";
            cout << "   1. Simpan ke File Teks (barang.txt)\n";
            cout << "   2. Muat dari File Teks\n";
            cout << "   3. Simpan ke File Biner (barang.dat)\n";
            cout << "   4. Muat dari File Biner\n";
            cout << "   Pilih: ";
            cin >> sub;
            if (sub == 1) simpanKeFileTeks();
            else if (sub == 2) muatDariFileTeks();
            else if (sub == 3) simpanKeFileBiner();
            else if (sub == 4) muatDariFileBiner();
            else cout << "Pilihan salah\n";
        } else if (pilih == 9) {
             int sub;
            cout << "   Linked List Tambahan:\n";
            cout << "   1. Tambah Barang di Awal\n";
            cout << "   2. Tambah Barang Setelah ID Tertentu\n";
            cout << "   Pilih: ";
            cin >> sub;
            if (sub == 1) tambahDiAwal();
            else if (sub == 2) tambahSetelahID();
            else cout << "Pilihan salah\n";
         }else if (pilih != 0) {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 0);
    
    return 0;
}