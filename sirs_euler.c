// Program C untuk Simulasi Model SIRS Menggunakan Metode Euler
// Fokus pada implementasi komputasi untuk mahasiswa Teknik Komputer

#include <stdio.h>
#include <stdlib.h>

// Struktur untuk menyimpan parameter model SIRS
typedef struct {
    double beta;  // Laju kontak efektif (transmission rate)
    double delta; // Laju pemulihan (recovery rate)
    double lambda;// Laju kehilangan imunitas (waning immunity rate)
} SIRSParams;

// Struktur untuk menyimpan keadaan sistem (proporsi populasi)
typedef struct {
    double S; // Proporsi populasi rentan (Susceptible)
    double I; // Proporsi populasi terinfeksi (Infected)
    double R; // Proporsi populasi pulih (Recovered)
} SIRSState;

// Fungsi untuk menghitung turunan dS/dt, dI/dt, dR/dt
// Input: state saat ini (y), parameter model (params)
// Output: turunan (dydt)
void sirs_derivs(const SIRSState* y, const SIRSParams* params, SIRSState* dydt) {
    // Menghitung interaksi antar kompartemen
    double StoI = params->beta * y->I * y->S;
    double ItoR = params->delta * y->I;
    double RtoS = params->lambda * y->R;

    // Menghitung turunan untuk setiap kompartemen
    dydt->S = RtoS - StoI;
    dydt->I = StoI - ItoR;
    dydt->R = ItoR - RtoS;
}

// Fungsi untuk melakukan satu langkah integrasi menggunakan Metode Euler
// Input: state saat ini (y), turunan (dydt), step size (h)
// Output: state pada langkah berikutnya (y_next)
void euler_step(const SIRSState* y, const SIRSState* dydt, double h, SIRSState* y_next) {
    y_next->S = y->S + h * dydt->S;
    y_next->I = y->I + h * dydt->I;
    y_next->R = y->R + h * dydt->R;

    // Opsional: Normalisasi untuk menjaga S+I+R = 1 (meskipun secara teori harus terjaga jika N=1)
    // double total = y_next->S + y_next->I + y_next->R;
    // if (total > 0) {
    //     y_next->S /= total;
    //     y_next->I /= total;
    //     y_next->R /= total;
    // }
}

int main(int argc, char *argv[]) {
    // --- 1. Pengaturan Parameter dan Kondisi Awal --- 

    // Parameter model SIRS (contoh, bisa diganti atau dibaca dari input)
    SIRSParams params = {0.155, 0.100, 0.005}; // Beta, Delta, Lambda (sesuai referensi)

    // Kondisi awal (proporsi populasi, S0+I0+R0 harus mendekati 1)
    SIRSState current_state = {0.9352, 0.0193, 0.0455}; // S0, I0, R0 (sesuai referensi)

    // Parameter simulasi
    double t_final = 365.0; // Total waktu simulasi (misal: 1 tahun)
    double h = 0.1;         // Step size (ukuran langkah waktu, misal: 0.1 hari)
    double t = 0.0;         // Waktu awal

    // Validasi input sederhana (contoh, bisa diperluas)
    if (params.beta < 0 || params.delta < 0 || params.lambda < 0 || 
        current_state.S < 0 || current_state.I < 0 || current_state.R < 0 || 
        h <= 0 || t_final <= 0) {
        fprintf(stderr, "Error: Parameter atau kondisi awal tidak valid.\n");
        return 1; // Keluar dengan kode error
    }
    
    // Opsi: Baca parameter dari argumen command line jika ada
    if (argc == 8) { // Contoh: ./sirs_euler S0 I0 R0 beta delta lambda T h
        current_state.S = atof(argv[1]);
        current_state.I = atof(argv[2]);
        current_state.R = atof(argv[3]);
        params.beta     = atof(argv[4]);
        params.delta    = atof(argv[5]);
        params.lambda   = atof(argv[6]);
        t_final         = atof(argv[7]);
        h               = atof(argv[8]);
        // Tambahkan validasi lebih lanjut di sini
    }

    // --- 2. Persiapan Output --- 

    // Opsi: Buka file untuk menyimpan hasil simulasi
    FILE *outfile = fopen("sirs_euler_results.csv", "w");
    if (outfile == NULL) {
        perror("Error membuka file output");
        return 1; // Keluar jika file tidak bisa dibuka
    }
    // Tulis header ke file CSV
    fprintf(outfile, "Time,Susceptible,Infected,Recovered\n");
    // Tulis kondisi awal
    fprintf(outfile, "%.4f,%.6f,%.6f,%.6f\n", t, current_state.S, current_state.I, current_state.R);

    // --- 3. Loop Simulasi Utama --- 
    SIRSState next_state;
    SIRSState dydt;

    printf("Memulai simulasi SIRS dengan metode Euler...\n");
    printf("Parameter: beta=%.3f, delta=%.3f, lambda=%.3f\n", params.beta, params.delta, params.lambda);
    printf("Kondisi Awal: S0=%.4f, I0=%.4f, R0=%.4f\n", current_state.S, current_state.I, current_state.R);
    printf("Simulasi hingga T=%.2f dengan step h=%.4f\n", t_final, h);
    printf("Hasil disimpan di sirs_euler_results.csv\n");

    int step_count = 0;
    while (t < t_final) {
        // Hitung turunan pada state saat ini
        sirs_derivs(&current_state, &params, &dydt);
        
        // Hitung state berikutnya menggunakan metode Euler
        euler_step(&current_state, &dydt, h, &next_state);
        
        // Update waktu dan state
        t += h;
        current_state = next_state; // Salin state baru ke state saat ini
        step_count++;

        // Tulis hasil ke file CSV
        fprintf(outfile, "%.4f,%.6f,%.6f,%.6f\n", t, current_state.S, current_state.I, current_state.R);

        // Opsional: Cetak progres setiap N langkah
        // if (step_count % 100 == 0) {
        //     printf("t = %.2f, S = %.4f, I = %.4f, R = %.4f\n", t, current_state.S, current_state.I, current_state.R);
        // }
    }

    // --- 4. Cleanup --- 
    fclose(outfile); // Tutup file output
    printf("Simulasi selesai. Total langkah: %d\n", step_count);

    return 0; // Sukses
}

