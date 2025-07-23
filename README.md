# 🌌 Simulasi Tata Surya 3D Interaktif 🪐

[![Bahasa](https://img.shields.io/badge/Bahasa-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Grafika](https://img.shields.io/badge/Grafika-OpenGL-green.svg)](https://www.opengl.org/)
[![Lisensi](https://img.shields.io/badge/Lisensi-MIT-yellow.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Selesai-brightgreen.svg)]()

Selamat datang di proyek simulasi Tata Surya 3D! Jelajahi keindahan kosmos langsung dari komputer Anda. Proyek ini adalah sebuah visualisasi sistem tata surya yang dibangun dengan **C++** dan **OpenGL**, menampilkan Matahari, planet-planet, dan Bulan dalam sebuah tarian orbit yang dinamis dan interaktif.

---

## 📋 Daftar Isi

* [Fitur Unggulan](#-fitur-unggulan)
* [Teknologi yang Digunakan](#-teknologi-yang-digunakan)
* [Instalasi & Kompilasi](#-instalasi--kompilasi)
* [Kontrol Aplikasi](#-kontrol-aplikasi)

---

## ✨ Fitur Unggulan

Proyek ini tidak hanya menampilkan planet yang berputar, tetapi juga dilengkapi berbagai fitur untuk menciptakan pengalaman yang imersif.

* **🪐 Model Tata Surya Lengkap**
    * Visualisasi Matahari, Merkurius, Venus, Bumi, Mars, Jupiter, Saturnus, Uranus, Neptunus, dan Pluto.
    * **Sistem Bumi-Bulan**: Bulan ditampilkan mengorbit Bumi secara akurat.
    * **Cincin Saturnus**: Saturnus digambarkan lengkap dengan sistem cincinnya yang ikonik.

* **🌠 Latar Belakang Kosmik yang Hidup**
    * **Taburan Bintang Dinamis**: Ratusan bintang dihasilkan secara prosedural dengan efek berkelip (*twinkling*) untuk menciptakan kesan langit yang hidup.
    * **Awan Nebula & Debu Kosmik**: Latar belakang dipercantik dengan gumpalan nebula berwarna-warni dan partikel debu kosmik yang bergerak perlahan, menambah kedalaman visual.

* **💡 Sistem Pencahayaan Cerdas**
    * Matahari berfungsi sebagai satu-satunya sumber cahaya (`GL_LIGHT0`), memberikan efek bayangan dan pencahayaan realistis pada sisi planet yang menghadapnya.
    * Setiap benda langit memiliki properti material (warna, kilau) yang unik.

* **🕹️ Interaktivitas Penuh**
    * Kontrol kamera, kecepatan simulasi, dan elemen visual lainnya ada di tangan Anda. Lihat detailnya di [bagian kontrol](#-kontrol-aplikasi).

---

## 🛠️ Teknologi yang Digunakan

* **C++**: Bahasa pemrograman utama yang digunakan untuk membangun logika simulasi.
* **OpenGL**: API grafika lintas platform untuk rendering 2D dan 3D.
* **GLUT (OpenGL Utility Toolkit)**: Pustaka untuk membuat jendela, mengelola input, dan menjalankan *event loop* OpenGL dengan mudah.

---

## 🚀 Instalasi & Kompilasi

Untuk menjalankan simulasi ini di komputer Anda, ikuti langkah-langkah berikut.

**Prasyarat:**
* Compiler C++ (seperti `g++` atau `MinGW` di Windows).
* Pustaka `GLUT` terinstal di sistem Anda.

**Langkah-langkah Kompilasi:**

1.  **Clone Repositori (jika ada di Git)**
    ```bash
    git clone [https://github.com/AliSultonsPalilati/UAS-TATASURYA3D-GRAFIK-KOMPUTER.git](https://github.com/AliSultonsPalilati/UAS-TATASURYA3D-GRAFIK-KOMPUTER.git)
    cd UAS-TATASURYA3D-GRAFIK-KOMPUTER
    ```

2.  **Kompilasi Kode**
    Buka terminal atau command prompt, lalu jalankan perintah berikut:
    ```bash
    # Untuk pengguna Linux atau macOS
    g++ tatasurya.cpp -o tatasurya -lglut -lGL -lGLU

    # Untuk pengguna Windows (dengan MinGW/MSYS2)
    g++ tatasurya.cpp -o tatasurya.exe -lopengl32 -lglu32 -lfreeglut
    ```
    *Catatan: Nama pustaka mungkin sedikit berbeda tergantung pada instalasi Anda.*

3.  **Jalankan Aplikasi**
    ```bash
    # Linux / macOS
    ./tatasurya

    # Windows
    .\tatasurya.exe
    ```

---

## ⌨️ Kontrol Aplikasi

Gunakan keyboard untuk berinteraksi dengan simulasi:

| Tombol | Fungsi |
| :---: | :--- |
| **`+` / `=`** | **Mempercepat** laju orbit semua planet. |
| **`-`** | **Memperlambat** laju orbit semua planet. |
| **`z`** | **Zoom In** (mendekatkan kamera). |
| **`x`** | **Zoom Out** (menjauhkan kamera). |
| **`c`** | **Toggle rotasi kamera otomatis** (ON/OFF). |
| **`r`** | **Reset** simulasi ke posisi dan kecepatan awal. |
| **`s`** | **Regenerasi** posisi bintang dan nebula secara acak. |
| **`Esc`**| **Keluar** dari aplikasi. |
