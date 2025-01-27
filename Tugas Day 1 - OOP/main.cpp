#include <iostream>
#include <string>
using namespace std;

void clearScreen() { // Untuk membersihkan layar konsol
    #ifdef _WIN32
        system("cls"); // Untuk Windows
    #else
        system("clear"); // Untuk Linux
    #endif
}

class Contact {
    public: 
        // Constructor default (untuk kontak kosong)
        Contact() : nama(""), alamat(""), kekuatan("") {}

        // Constructor untuk mengisi informasi kontak
        Contact(string nama_contact, string alamat_contact, string kekuatan_contact) : nama(nama_contact), alamat(alamat_contact), kekuatan(kekuatan_contact) {}
        
        string getNama() { // Mengambil nilai dari variabel nama yang bersifat private
            return nama;
        }

        void tampilkan_info() {
            if (nama.empty()) {
                cout << "Kontak kosong.\n";
            } else {
                cout << "Nama\t\t:" << nama << endl;
                cout << "Alamat\t\t:" << alamat << endl;
                cout << "Kekuatan\t:" << kekuatan << endl;
            }
        }
    
    private:
        // Deklarasi informasi yang disimpan
        string nama;
        string alamat;
        string kekuatan; 
};

class Phonebook : public Contact {
    public:
        Phonebook(): jumlah(0){}
        
        int getJumlah() {
            return jumlah;
        }

        // Menambahkan informasi kontak baru
        void tambah_kontak(string nama, string alamat, string kekuatan) {
            if (jumlah < 8) {
                contacts[jumlah] = Contact(nama, alamat, kekuatan);
                jumlah++;
                cout << "Kontak berhasil ditambahkan!\n";
            } else {
                cout << "Phonebook penuh! Tidak dapat menambahkan lebih dari 8 kontak.\n";
            }
        }

        // Menampilkan semua kontak yang tersedia (nama saja)
        void tampilkan_daftar() {
            if (jumlah == 0) {
                cout << "Phonebook kosong!\n";
                return;
            }

            cout << "Daftar Kontak:\n";
            for (int i = 0; i < jumlah; ++i) {
                cout << i + 1 << ". " << contacts[i].getNama() << endl;
            }
        }

        // Mencari kontak berdasarkan nama
        void cari_kontak(string nama) {
            if (jumlah == 0) {
                cout << "Tidak ada kontak yang dapat dicari. Phonebook kosong.\n";
                return;
            }
            
            for (int i = 0; i < jumlah; ++i) {
                if (contacts[i].getNama() == nama) {
                    contacts[i].tampilkan_info();
                    return;
                }
            }
            cout << "Kontak dengan nama \"" << nama << "\" tidak ditemukan.\n";
        }

        // Menghapus kontak berdasarkan nama
        void hapus_kontak(string nama) {
            if (jumlah == 0) {
                cout << "Tidak ada kontak yang dapat dihapus. Phonebook kosong.\n";
                return;
            }

            for (int i = 0; i < jumlah; ++i) {
                if (contacts[i].getNama() == nama) {
                    // Geser kontak setelahnya satu posisi ke atas
                    for (int j = i; j < jumlah - 1; ++j) {
                        contacts[j] = contacts[j + 1];
                    }
                    jumlah--; // Kurangi jumlah kontak
                    cout << "Kontak \"" << nama << "\" berhasil dihapus.\n";
                    return;
                }
            }
            cout << "Kontak dengan nama \"" << nama << "\" tidak ditemukan.\n";
        }
    
    private:
        Contact contacts[8]; // Array untuk menyimpan maksimal 8 kontak
        int jumlah; // Jumlah kontak yang saat ini tersimpan
};

int main() {
    Phonebook phonebook;
    string perintah;
    
    while(true) {
        clearScreen();  // Menghapus layar setiap kali perulangan dimulai

        cout << "AKSANBOOK\n\n";

        cout << "-----------------------------------------------------\n";
        cout << "| Panduan Perintah:                                 |\n";
        cout << "| ADD     : Menyimpan informasi kontak baru         |\n";
        cout << "| DISPLAY : Menampilkan daftar seluruh kontak       |\n";
        cout << "| SEARCH  : Menampilkan informasi kontak tertentu   |\n";
        cout << "| DELETE  : Menghapus kontak tertentu               |\n";
        cout << "| EXIT    : Keluar program                          |\n" ;
        cout << "-----------------------------------------------------\n";

        cout << "\nMasukkan perintah (capslock): ";
        cin >> perintah;

        if (perintah == "ADD"){
            string nama, alamat, kekuatan;
            cin.ignore();  // Menangani buffer input yang tersisa sebelum menggunakan getline
            cout << "\n-----------------------------------------------------\n";
            cout << "\nADD CONTACT\n\n";
            cout << "Masukkan nama\t\t: "; 
            getline(cin, nama); // Menggunakan getline agar dapat menerima input dengan spasi
            cout << "Masukkan alamat\t\t: ";
            getline(cin, alamat);
            cout << "Masukkan kekuatan\t: ";
            getline(cin, kekuatan);
            phonebook.tambah_kontak(nama, alamat, kekuatan);
            cout << "\nTekan Enter untuk melanjutkan...";  // Menunggu input pengguna sebelum melanjutkan
            cin.get();  // Tunggu pengguna menekan Enter
        } else if (perintah == "DISPLAY") {
            cout << "\n-----------------------------------------------------\n";
            cout << "\nDISPLAY\n\n";
            phonebook.tampilkan_daftar();
            cout << "\nTekan Enter untuk melanjutkan...";  
            cin.ignore();
            cin.get();  
        } else if(perintah == "SEARCH") {
            cout << "\n-----------------------------------------------------\n";
            cout << "\nSEARCH CONTACT\n\n";
            if (phonebook.getJumlah() == 0) {
                cout << "Phonebook kosong! Tidak dapat melakukan pencarian kontak.\n";
                cout << "\nTekan Enter untuk melanjutkan...";  
                cin.ignore();
                cin.get(); 
            } else {
                phonebook.tampilkan_daftar();
                string nama;
                cin.ignore();
                cout << "\nMasukkan nama kontak yang ingin dicari (case sensitive): ";
                getline(cin, nama);
                cout << "\n-----------------------------------------------------\n";
                phonebook.cari_kontak(nama);
                cout << "-----------------------------------------------------\n";
                cout << "\nTekan Enter untuk melanjutkan...";  
                cin.get(); 
            } 
        } else if(perintah == "DELETE") {
            cout << "\n-----------------------------------------------------\n";
            cout << "\nDELETE CONTACT\n\n";
            if (phonebook.getJumlah() == 0) {
                cout << "Phonebook kosong! Tidak ada kontak untuk dihapus.\n";
                cout << "\nTekan Enter untuk melanjutkan...";  
                cin.ignore();
                cin.get();
            } else {
                phonebook.tampilkan_daftar();
                string nama;
                cin.ignore();
                cout << "\nMasukkan nama kontak yang ingin dihapus (case sensitive): ";
                getline(cin, nama);
                phonebook.hapus_kontak(nama);
                cout << "\nTekan Enter untuk melanjutkan...";  
                cin.get();
            }  
        } else if (perintah == "EXIT") {
            cout << "\n---------------------------------------------------------------------------\n";
            cout << "Program berhasil ditutup. Terima kasih telah menggunakan layanan AKSANBOOK." << endl;
            cout << "---------------------------------------------------------------------------\n";
            exit(0);
        } else {
            cout << "Perintah tidak valid!. Silakan coba lagi.\n";
            cout << "\nTekan Enter untuk melanjutkan...";  
            cin.ignore();
            cin.get();  
        }
    }
    
    return 0;
}
