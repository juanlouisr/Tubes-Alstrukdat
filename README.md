# Tubes-Alstrukdat

Untuk Pemenuhan Tugas Besar Algoritma Struktur Data IF2110

## Tentang Program

Permainan monangis adalah permain mengantarkan pesanan secepatnya. Disini anda berperan sebagai Mobita yang harus mengantarkan pesananan dari suatu lokasi ke lokasi lainnya. Semakin berjalannya permainan akan ada pesanan pesanan yang datang dan harus diantar. Pesanan yang diambil dari suatu lokasi akan masuk ke dalam tas. Terdapat juga ability dan gadget yang dapat digunakan dalam untuk membantu mobita mengantarkan pesanan pelanggan. Salah satu pelanggan Mobita adalah Zhisuka, Zhisuka adalah pelanggan sekai-ichiban Mobita delivery. Jadi kamu harus segera mengantarkan pesanan Zhisuka jika ada pesanan dia yang masuk.


Untuk menjalankan program dapat dilihat di [Build & Run](#Build--Run). Struktur Program dapat di lihat di [Struktur Program](#Struktur-Program). Status pengerjaan dapat dilihat di [Status](#Status).

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
|   Original ADT     | ✅         |                 | 
|   Proses Input     | ✅         |                 | 
|   Main Menu        | ✅         |                 | 
|   Mekanisme Waktu  | ✅         |                 |
|   Daftar pesanan   | ✅         |                 |
|   To do list       | ✅         |                 | 
|   In Progress list | ✅         |                 | 
|   Tas              | ✅         |                 | 
|   item             | ✅         |                 | 
|   Ability          | ✅         |                 | 
|   Gadget           | ✅         |                 | 
|   Inventory Gadget | ✅         |                 | 
|   Peta             | ✅         |                 | 
|   Lokasi           | ✅         |                 | 
|   Command (MOVE,PICK_UP,HELP,etc) | ✅        |              | 
|   Save dan Load    | ✅         |                    | 
|   VIP Item & RETURN command  | ✅         |                    | 
|   Flow program dan merging   | ✅         |                    |
|   Test case        | ✅         |                 | 
|   Dokumen-dokumen  | ✅         |                 | 
|   Laporan          | ❌         |   Semua              | 

## Build & Run

### Build / Compile
```powershell
gcc src/*.c src/ADT/implementation/*.c src/Utility/implementation/*.c -o bin/Main
```
### Run
```powershell
./bin/Main
```
### Build & Run
```powershell
./run.bat
```

## Test
### Build & Running Test
```powershell
./testADT.bat
```

## Technologies

- Mingw-w64 Windows Distributions (C/C++ Compiler)

## About

- 13518026 [@farisfadhilah](https://github.com/farisfadhilah)

- 13519075 [@mizuday](https://github.com/mizuday)

- 13520085 [@ubaidalih](https://github.com/ubaidalih)

- 13520091 [@IMYELI](https://github.com/IMYELI)

- 13520093 [@vincen-tho](https://github.com/vincen-tho)