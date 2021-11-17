# Tubes-Alstrukdat

Untuk Pemenuhan Tugas Besar Algoritma Struktur Data IF2110

## Tentang Program

Permainan monangis adalah permain mengantarkan pesanan secepatnya. Disini anda berperan sebagai Mobita yang harus mengantarkan pesananan dari suatu lokasi ke lokasi lainnya. Semakin berjalannya permainan akan ada pesanan pesanan yang datang dan harus diantar. Pesanan yang diambil dari suatu lokasi akan masuk ke dalam tas. Terdapat juga ability dan gadget yang dapat digunakan dalam untuk membantu mobita mengantarkan pesanan pelanggan. Salah satu pelanggan Mobita adalah Zhisuka, Zhisuka adalah pelanggan sekai-ichiban Mobita delivery. Jadi kamu harus segera mengantarkan pesanan Zhisuka jika ada pesanan dia yang masuk.


Untuk menjalankan program dapat dilihat di [Build & Run](#Build--Run). Struktur Program dapat di lihat di [Struktur Program](#Struktur-Program). Status pengerjaan dapat dilihat di [Status](#Status).


Folder save dan konfigurasi berada pada [src/data](/src/data)

## Struktur Program

```
Tubes-Alstrukdat
    ├── bin
    ├── doc
    │   └── Spesifikasi....pdf
    ├── src
    │   ├── ADT
    │   │   ├── header
    │   │   │   ├── boolean.h
    │   │   │   ├── charmachine.h
    │   │   │   ├── daftarlokasi.h       
    │   │   │   ├── item.h
    │   │   │   ├── ...
    │   │   │   └── wordmachine.h
    │   │   └── implementation         
    │   │       ├── charmachine.c
    │   │       ├── daftarlokasi.c       
    │   │       ├── item.c
    │   │       ├── ...
    │   │       └── wordmachine.c
    │   ├── data
    │   │   └── config.cfg
    │   ├── Utility
    │   │   ├── header
    │   │   │   ├── iolib.h
    │   │   │   └── pcolor.h
    │   │   └── implementation
    │   │       ├── iolib.c
    │   │       └── pcolor.c
    │   ├── adtlib.h
    │   ├── game.c
    │   ├── game.h
    │   ├── Main.c
    │   └── utilib.h
    ├── test
    │   └── testADT.c
    ├── README.md
    ├── run.bat
    └── testADT.bat
```


## Status                             

|   Tugas           | Status   |   Pengerja         | 
|---                 |---          |---             |
|   Original ADT     | ✅         | 13520093        | 
|   Proses Input     | ✅         | 13519075        | 
|   Main Menu        | ✅         | 13519075        | 
|   Mekanisme Waktu  | ✅         | 13519075, 13520085    |
|   Daftar pesanan   | ✅         | 13519075        |
|   To do list       | ✅         | 13520093        | 
|   Tas              | ✅         | 13520091        | 
|   item             | ✅         | 13519075        | 
|   Ability          | ✅         | 13519075, 13520085    | 
|   Gadget           | ✅         | 13520085        | 
|   Inventory Gadget | ✅         | 13520085        | 
|   Peta             | ✅         | 13520091        | 
|   Lokasi           | ✅         | 13520091        | 
|   Command (MOVE,PICK_UP,HELP,etc) | ✅        | 13519075, 13520085, 13520091      | 
|   Save dan Load    | ✅         | 13519075           | 
|   VIP Item & RETURN command  | ✅         | 13519075          | 
|   Senter Pengecil  | ✅         | 13520085        | 
|   Flow program dan merging   | ✅         | 13518026, 13519075           |
|   Test case        | ✅         | 13518026, 13519075    | 
|   Dokumen-dokumen  | ✅         | 13520093        | 
|   Laporan          | ✅         |   Semua              | 

## Build & Run

### Build / Compile
Untuk mengcompile program dapat menjalankan command berikut pada powershell di root folder

```powershell
gcc src/*.c src/ADT/implementation/*.c src/Utility/implementation/*.c -o bin/Main
```
### Run
untuk menjalankan program dapat menjalankan command berikut pada powershell di root folder

```powershell
./bin/Main
```
### Build & Run
Pada OS Windows, bisa langsung menjalankan batch file `run.bat` di root folder

```powershell
./run.bat
```
#### catatan
- Untuk Linux terdapat beberapa include file yang perlu diubah namanya
- Kompilasi program pada linux harus menambahkan flag `-lm` untuk linking dengan `<math.h>`
- Jika program berhasil dikompilasi tetapi tidak jalan setelah input file config, pastikan compiler (gcc) menggunakan versi terbaru (direkomendasikan versi 11.2.0) atau setidaknya menggunakan distribusi MinGW atau MinGW-w64

## Test
### Build & Running Test
Untuk testing bisa menjalan script `testADT.bat` di root folder

```powershell
./testADT.bat
```

## Technologies

- MinGW-w64 Windows Distributions (C/C++ Compiler)

## About

- 13518026 [@farisfadhilah](https://github.com/farisfadhilah)

- 13519075 [@mizuday](https://github.com/mizuday)

- 13520085 [@ubaidalih](https://github.com/ubaidalih)

- 13520091 [@IMYELI](https://github.com/IMYELI)

- 13520093 [@vincen-tho](https://github.com/vincen-tho)