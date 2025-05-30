# Simulasi Model SIRS Menggunakan Metode Euler

## Kelompok 7

### Anggota Kelompok:

- Wiellona Darlene Oderia Saragih (NPM: 2306264396)

### Deskripsi Program

Program ini merupakan implementasi dalam bahasa C untuk mensimulasikan model epidemiologi Susceptible-Infected-Recovered-Susceptible (SIRS) menggunakan metode numerik Euler. Model SIRS digunakan untuk memodelkan penyebaran penyakit menular di mana individu yang telah pulih dapat kehilangan imunitasnya dan kembali menjadi rentan terhadap infeksi.

Program ini dirancang dengan fokus pada perspektif komputasi, relevan untuk mata kuliah Komputasi Numerik. Fitur utama program meliputi:

- **Implementasi Metode Euler:** Menggunakan metode Euler orde pertama untuk mengaproksimasi solusi sistem persamaan diferensial biasa (PDB) yang mendefinisikan model SIRS.
- **Modularitas Kode:** Kode disusun secara modular dengan fungsi terpisah untuk perhitungan turunan (`sirs_derivs`) dan langkah integrasi Euler (`euler_step`), serta struktur data (`struct`) untuk parameter dan keadaan sistem.
- **Input Fleksibel:** Menerima parameter model (laju kontak β, laju pemulihan δ, laju kehilangan imunitas λ), kondisi awal (proporsi S0, I0, R0), waktu total simulasi (T_final), dan ukuran langkah (h) melalui nilai default atau argumen baris perintah.
- **Output Data:** Menghasilkan data time series (waktu, S(t), I(t), R(t)) dalam format CSV (`sirs_euler_results.csv`) untuk memudahkan analisis dan visualisasi lebih lanjut (misalnya, menggunakan Excel atau Python).
- **Komentar dan Validasi:** Dilengkapi dengan komentar penjelasan dan validasi input dasar untuk memastikan parameter yang digunakan masuk akal.

Program ini bertujuan untuk mendemonstrasikan penerapan metode numerik dasar dalam menyelesaikan masalah di bidang epidemiologi komputasi dan memahami aspek-aspek komputasional seperti efisiensi, akurasi, dan stabilitas.

### Cara Kompilasi dan Menjalankan

1.  **Kompilasi:** Gunakan kompiler C (seperti GCC) untuk mengkompilasi kode:

    ```bash
    gcc sirs_euler.c -o sirs_euler -lm
    ```

    _(Flag `-lm` diperlukan untuk me-link library matematika)_

2.  **Menjalankan (dengan parameter default):**

    ```bash
    ./sirs_euler
    ```

    Ini akan menjalankan simulasi dengan parameter dan kondisi awal yang ditentukan di dalam kode dan menyimpan hasilnya ke `sirs_euler_results.csv`.

3.  **Menjalankan (dengan parameter custom via command line - opsional):**
    ```bash
    ./sirs_euler [S0] [I0] [R0] [beta] [delta] [lambda] [T_final] [h]
    ```
    Ganti nilai dalam kurung siku dengan nilai numerik yang diinginkan.
    Contoh:
    ```bash
    ./sirs_euler 0.99 0.01 0.0 0.2 0.1 0.01 100 0.1
    ```
