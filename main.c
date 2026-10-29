#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSAKSI 10
#define JUMLAH_BARANG 5

// --- Array Data Peralatan (Ketentuan Teknis #6) ---
const char NAMA_BARANG[JUMLAH_BARANG][30] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

const int HARGA_BARANG[JUMLAH_BARANG] = {
    50000,
    15000,
    20000,
    10000,
    12000
};

// --- Array Data Riwayat Transaksi (Ketentuan C.6 & Teknis #7) ---
char riwayatNama[MAX_TRANSAKSI][50];
char riwayatPeralatan[MAX_TRANSAKSI][30];
int riwayatUnit[MAX_TRANSAKSI];
int riwayatLama[MAX_TRANSAKSI];
int riwayatTotal[MAX_TRANSAKSI];
int jumlahTransaksi = 0; // Menghitung total transaksi yang tersimpan

// --- Deklarasi Fungsi (Ketentuan Teknis #5) ---
void tampilkanMenuUtama();
void tampilkanDaftarPeralatan();
void prosesPenyewaan();
void tampilkanRiwayatTransaksi();
float hitungDiskon(int lamaSewa, int subtotal);
void bersihkanBuffer();

int main() {
    int pilihan;

    do {
        tampilkanMenuUtama();
        printf("Pilih menu [1-4]: ");
        if (scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            printf("\n[!] Masukan tidak valid. Harap masukkan angka 1-4.\n\n");
            continue;
        }
        bersihkanBuffer();

        switch (pilihan) {
            case 1:
                tampilkanDaftarPeralatan();
                break;
            case 2:
                prosesPenyewaan();
                break;
            case 3:
                tampilkanRiwayatTransaksi();
                break;
            case 4:
                printf("\nTerima kasih telah menggunakan program Adventure Camp!\n");
                break;
            default:
                printf("\n[!] Pilihan tidak tersedia. Harap pilih angka 1-4.\n\n");
        }
    } while (pilihan != 4);

    return 0;
}

// --- Fungsi 1: Menampilkan Menu Utama ---
void tampilkanMenuUtama() {
    printf("========================================");
    printf("\n             ADVENTURE CAMP             \n");
    printf("       SISTEM PENYEWAAN PERALATAN       \n");
    printf("========================================\n");
    printf("1. Lihat Daftar Peralatan\n");
    printf("2. Sewa Peralatan\n");
    printf("3. Lihat Riwayat Transaksi\n");
    printf("4. Keluar\n");
    printf("----------------------------------------\n");
}

// --- Fungsi 2: Menampilkan Daftar Peralatan ---
void tampilkanDaftarPeralatan() {
    printf("\n======================================================\n");
    printf("               DAFTAR PERALATAN SEWA                  \n");
    printf("======================================================\n");
    printf("%-4s | %-30s | %-15s\n", "No.", "Peralatan", "Harga / Hari");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < JUMLAH_BARANG; i++) {
        printf("%-4d | %-30s | Rp%d\n", i + 1, NAMA_BARANG[i], HARGA_BARANG[i]);
    }
    printf("======================================================\n\n");
}

// --- Fungsi 3: Menghitung Persentase Diskon (Ketentuan C.4) ---
float hitungDiskon(int lamaSewa, int subtotal) {
    if (lamaSewa >= 5) {
        return subtotal * 0.15; // Diskon 15%
    } else if (lamaSewa >= 3) {
        return subtotal * 0.10; // Diskon 10%
    } else {
        return 0.0;             // Diskon 0%
    }
}

// --- Fungsi 4: Memproses Transaksi Penyewaan ---
void prosesPenyewaan() {
    // Validasi Kapasitas Array Transaksi (Ketentuan C.6 point 6)
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\n[!] Mohon maaf, kapasitas riwayat transaksi sudah penuh (Maksimal %d transaksi).\n\n", MAX_TRANSAKSI);
        return;
    }

    char namaPenyewa[50];
    int pilihanBarang, jumlahUnit, lamaSewa;
    char kembaliMenu;

    printf("\n========================================\n");
    printf("            FORM PENYEWAAN              \n");
    printf("========================================\n");

    // Input Nama Penyewa
    printf("Masukkan Nama Penyewa : ");
    fgets(namaPenyewa, sizeof(namaPenyewa), stdin);
    namaPenyewa[strcspn(namaPenyewa, "\n")] = 0; // Menghapus karakter newline

    // Validasi Input Jenis Peralatan
    tampilkanDaftarPeralatan();
    do {
        printf("Pilih Nomor Peralatan (1-%d): ", JUMLAH_BARANG);
        if (scanf("%d", &pilihanBarang) != 1 || pilihanBarang < 1 || pilihanBarang > JUMLAH_BARANG) {
            bersihkanBuffer();
            printf("[!] Pilihan peralatan tidak valid. Silakan coba lagi.\n");
        } else {
            break;
        }
    } while (1);

    // Validasi Input Jumlah Unit (Minimal 1)
    do {
        printf("Masukkan Jumlah Unit (Min. 1) : ");
        if (scanf("%d", &jumlahUnit) != 1 || jumlahUnit < 1) {
            bersihkanBuffer();
            printf("[!] Jumlah unit minimal 1. Silakan coba lagi.\n");
        } else {
            break;
        }
    } while (1);

    // Validasi Input Lama Sewa (Minimal 1 Hari)
    do {
        printf("Masukkan Lama Sewa /Hari (Min. 1): ");
        if (scanf("%d", &lamaSewa) != 1 || lamaSewa < 1) {
            bersihkanBuffer();
            printf("[!] Lama penyewaan minimal 1 hari. Silakan coba lagi.\n");
        } else {
            break;
        }
    } while (1);
    bersihkanBuffer();

    // Perhitungan Biaya
    int hargaPerHari = HARGA_BARANG[pilihanBarang - 1];
    int subtotal = hargaPerHari * jumlahUnit * lamaSewa;
    float diskon = hitungDiskon(lamaSewa, subtotal);
    int totalBayar = subtotal - (int)diskon;

    // Simpan Data Transaksi ke Array Riwayat
    strcpy(riwayatNama[jumlahTransaksi], namaPenyewa);
    strcpy(riwayatPeralatan[jumlahTransaksi], NAMA_BARANG[pilihanBarang - 1]);
    riwayatUnit[jumlahTransaksi] = jumlahUnit;
    riwayatLama[jumlahTransaksi] = lamaSewa;
    riwayatTotal[jumlahTransaksi] = totalBayar;
    jumlahTransaksi++;

    // Menampilkan Struk Penyewaan (Ketentuan C.5)
    printf("\n========================================\n");
    printf("             ADVENTURE CAMP             \n");
    printf("            STRUK PENYEWAAN             \n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", namaPenyewa);
    printf("Peralatan      : %s\n", NAMA_BARANG[pilihanBarang - 1]);
    printf("Harga per Hari : Rp%d\n", hargaPerHari);
    printf("Jumlah Unit    : %d\n", jumlahUnit);
    printf("Lama Sewa      : %d hari\n", lamaSewa);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%d\n", subtotal);
    printf("Diskon (%.0f%%)   : Rp%.0f\n", (lamaSewa >= 5 ? 15.0 : (lamaSewa >= 3 ? 10.0 : 0.0)), diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%d\n", totalBayar);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\nlayanan Adventure Camp!\n");
    printf("========================================\n");

    // Konfirmasi Kembali ke Menu Utama
    do {
        printf("Kembali ke menu utama? (Y/T): ");
        scanf(" %c", &kembaliMenu);
        bersihkanBuffer();
        if (kembaliMenu == 'Y' || kembaliMenu == 'y') {
            printf("\n");
            break;
        } else if (kembaliMenu == 'T' || kembaliMenu == 't') {
            printf("\nTerima kasih telah menggunakan layanan Adventure Camp!\n");
            exit(0); // Keluar dari program
        } else {
            printf("[!] Pilihan tidak valid. Harap masukkan 'Y' atau 'T'.\n");
        }
    } while (1);
}

// --- Fungsi 5: Menampilkan Riwayat Transaksi (Ketentuan C.6) ---
void tampilkanRiwayatTransaksi() {
    printf("\n======================================================\n");
    printf("                  RIWAYAT TRANSAKSI                   \n");
    printf("======================================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("======================================================\n\n");
        return;
    }

    int totalPendapatan = 0;

    printf("%-3s | %-15s | %-23s | %-10s\n", "No", "Nama", "Peralatan", "Total");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-3d | %-15s | %-23s | Rp%d\n",
               i + 1, riwayatNama[i], riwayatPeralatan[i], riwayatTotal[i]);
        totalPendapatan += riwayatTotal[i];
    }

    printf("------------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%d\n", totalPendapatan);
    printf("======================================================\n\n");
}

// --- Fungsi Pembantu: Membersihkan Buffer Input ---
void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
