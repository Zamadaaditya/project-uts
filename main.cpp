#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Struktur Data Kontak (Linked List)
struct Kontak {
    string nama;
    string nomor;
    Kontak *next;
};
Kontak *headKontak = nullptr;

// Struktur Data Antrian (Queue)
struct Antrian {
    string nomorDicari;
    Antrian *next;
};
Antrian *frontQueue = nullptr;
Antrian *rearQueue = nullptr;

// Fungsi Menambah Kontak
void tambahKontak() {
    Kontak *baru = new Kontak();
    cout << "\nMasukkan Nama  : ";
    getline(cin, baru->nama);
    cout << "Masukkan Nomor : ";
    getline(cin, baru->nomor);
    baru->next = nullptr;

    if (baru->nama.empty() || baru->nomor.empty()) {
        cout << "❌ Nama atau nomor tidak boleh kosong!\n";
        delete baru;
        return;
    }

    if (headKontak == nullptr) {
        headKontak = baru;
    } else {
        Kontak *temp = headKontak;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }
    cout << "✅ Kontak berhasil ditambahkan!\n";
}

// Fungsi Menampilkan Semua Kontak
void tampilkanKontak() {
    if (headKontak == nullptr) {
        cout << "\n⚠️ Belum ada data kontak.\n";
        return;
    }

    cout << "\n=== DAFTAR KONTAK ===\n";
    Kontak *temp = headKontak;
    int i = 1;
    while (temp != nullptr) {
        cout << i << ". Nama: " << temp->nama << " | Nomor: " << temp->nomor << endl;
        temp = temp->next;
        i++;
    }
}

// Fungsi Rekursif untuk Mencari Nomor
Kontak* cariNomorRekursif(Kontak *node, const string &nomorDicari) {
    if (node == nullptr)
        return nullptr;
    if (node->nomor == nomorDicari)
        return node;
    return cariNomorRekursif(node->next, nomorDicari);
}

// Fungsi Menambah Nomor ke Antrian (Enqueue)
void enqueuePencarian(const string &nomorDicari) {
    // Validasi nomor agar hanya angka
    for (char c : nomorDicari) {
        if (!isdigit(c)) {
            cout << "❌ Nomor tidak valid! Harus berupa angka.\n";
            return;
        }
    }

    Antrian *baru = new Antrian();
    baru->nomorDicari = nomorDicari;
    baru->next = nullptr;

    if (rearQueue == nullptr) {
        frontQueue = rearQueue = baru;
    } else {
        rearQueue->next = baru;
        rearQueue = baru;
    }
    cout << "✅ Nomor berhasil dimasukkan ke antrian pencarian!\n";
}

// Fungsi Menghapus Data dari Antrian (Dequeue)
string dequeuePencarian() {
    if (frontQueue == nullptr)
        return "";

    Antrian *temp = frontQueue;
    string nomor = temp->nomorDicari;
    frontQueue = frontQueue->next;
    if (frontQueue == nullptr)
        rearQueue = nullptr;
    delete temp;
    return nomor;
}

// Fungsi Memproses Semua Antrian Pencarian
void prosesPencarian() {
    if (frontQueue == nullptr) {
        cout << "\n⚠️ Tidak ada antrian pencarian.\n";
        return;
    }

    cout << "\n=== MEMPROSES ANTRIAN PENCARIAN ===\n";
    while (frontQueue != nullptr) {
        string nomor = dequeuePencarian();
        cout << "\n🔍 Mencari nomor: " << nomor << endl;
        Kontak *hasil = cariNomorRekursif(headKontak, nomor);
        if (hasil != nullptr)
            cout << "✅ Ditemukan! Nama: " << hasil->nama << " | Nomor: " << hasil->nomor << endl;
        else
            cout << "❌ Nomor " << nomor << " tidak ditemukan dalam daftar kontak.\n";
    }
    cout << "\n✅ Semua antrian telah diproses.\n";
}

// Fungsi Menu Utama
int main() {
    int pilihan;
    string nomorDicari;

    do {
        cout << "\n==============================\n";
        cout << "   SIMULASI APLIKASI GET CONTACT\n";
        cout << "==============================\n";
        cout << "1. Tambah Kontak\n";
        cout << "2. Lihat Semua Kontak\n";
        cout << "3. Tambah ke Antrian Pencarian\n";
        cout << "4. Proses Antrian Pencarian\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> pilihan;
        cin.ignore(); // menghapus newline buffer

        switch (pilihan) {
            case 1:
                tambahKontak();
                break;
            case 2:
                tampilkanKontak();
                break;
            case 3:
                cout << "Masukkan Nomor yang ingin dicari: ";
                getline(cin, nomorDicari);
                enqueuePencarian(nomorDicari);
                break;
            case 4:
                prosesPencarian();
                break;
            case 5:
                cout << "👋 Terima kasih telah menggunakan simulasi Get Contact!\n";
                break;
            default:
                cout << "⚠️ Pilihan tidak valid! Silakan pilih antara 1 - 5.\n";
        }
    } while (pilihan != 5);

    return 0;
}
