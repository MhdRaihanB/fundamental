#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datautang
{
    int tgl, bln, thn, jml, dtgl, dbln, dthn;
    char nama[15];
}data, Adata[100], temp;

char filename[20];
int i, j;

FILE *fp;

void Masuk(int mode)
{
    char name[20], pw[20], regname[20], regpw[20], logname[20], logpw[20];

    if (mode == 1)
    {
        printf("===== REGISTRASI =====\n");
        registrasi:
        fp = fopen("akun.txt", "a+"); // membuka file dalam mode membaca dan menulis
        fflush(stdin);
        // membaca input username dan password baru dari pengguna
        printf("Masukkan username: ");
        scanf("%s", name);
        printf("Masukkan password: ");
        scanf("%s", pw);
        // Mengecek apakah username yang diinput sudah ada di file akun
        while(!feof(fp)) // pengulangan sampai akhir dari isi file
        {
            fscanf(fp, "%s %s", regname, regpw); // membaca file per baris
            if(strcmp(name, regname) == 0) // mengecek username yang diinput dengan username yang tersimpan di file
            {
                printf("==============================================================\n"
                       "Username sudah terpakai, mohon registrasi dengan username lain\n"
                       "==============================================================\n\n");
                fclose(fp);
                goto registrasi; // Jika username sudah ada di file maka proses registrasi diulang
            }
        }

        fprintf(fp, "%s %s\n", name, pw); // menulis username dan password ke dalam file
        fclose(fp); // menutup file

        printf("\n==================================\n"
               "Registrasi berhasil. Silahkan login!\n"
               "==================================\n\n");
        goto login; // lanjut ke menu login
    }
    else if (mode == 2)
    {
        printf("===== LOGIN =====\n");
        login:
        fp=fopen("akun.txt", "r"); // membuka file dalam mode membaca
        fflush(stdin);
        // membaca input username dan password dari pengguna
        printf("Masukkan username: ");
        scanf("%s", logname);
        printf("Masukkan password: ");
        scanf("%s", logpw);
        // Mengecek apakah username dan password yang diinput sesuai dengan yang ada di file
        while(!feof(fp)) // pengulangan sampai akhir dari isi file
        {
            fscanf(fp, "%s %s", regname, regpw); // membaca file per baris
            if(strcmp(logname, regname) == 0 && strcmp(logpw, regpw) == 0) // jika username & password cocok keluar dari loop
            {
                printf("Login berhasil.\n");
                strcpy(filename, logname); // menyalin username ke filename
                system("cls");
                break;
            }
            else if(feof(fp)) // Jika sudah sampai akhir dari isi file tidak ada yang cocok proses login diulang
            {
                printf("\n========================================================\n"
                       "Login gagal. Pastikan username dan password sudah benar!\n"
                       "========================================================\n\n");
                fclose(fp);
                goto login;
            }
        }

    fclose(fp); // menutup file
    }
    else
    {
        system("cls");
        goto login;
    }
}

void IsiData(int tipe)
{
    char ulang;
    system("cls");
    fp = fopen(filename, "a+"); // membuka file dalam mode membaca dan menulis
    // Membaca input data utang/piutang dari pengguna
    do
    {
        if(tipe==1){
            printf("=============PENCATATAN HUTANG=============\n");
            printf("Masukkan tanggal peminjaman (DD MM YYYY): ");
            scanf("%d %d %d", &data.tgl, &data.bln, &data.thn);
            fflush(stdin);
            printf("Masukkan nama pemberi uang: ");
            scanf("%s", data.nama);
            fflush(stdin);
            printf("Masukkan jumlah uang: ");
            scanf("%d", &data.jml);
            printf("Masukkan tenggat waktu pelunasan (DD MM YYYY): ");
            scanf("%d %d %d", &data.dtgl, &data.dbln, &data.dthn);
        }
        else {
            printf("=============PENCATATAN PIUTANG=============\n");
            printf("Masukkan tanggal peminjaman (DD MM YYYY): ");
            scanf("%d %d %d", &data.tgl, &data.bln, &data.thn);
            fflush(stdin);
            printf("Masukkan nama peminjam: ");
            scanf("%s", data.nama);
            fflush(stdin);
            printf("Masukkan jumlah uang: ");
            scanf("%d", &data.jml);
            printf("Masukkan tenggat waktu pelunasan (DD MM YYYY): ");
            scanf("%d %d %d", &data.dtgl, &data.dbln, &data.dthn);
        }
        // Mencatat hasil input dari pengguna kedalam file utang/piutang
        fprintf(fp, "%d %d %d %s %d %d %d %d\n", data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
        fflush(stdin);
        printf("Hentikan pencatatan? Y/N: ");
        scanf("%c", &ulang);
    }while (ulang != 'Y'); // pengulangan berhenti jika pengguna menginput Y
    fclose(fp); // menutup file

}

void TampilData(int tipe)
{
    i=0;

    fp = fopen(filename, "r"); // membuka file dalam mode membaca
    data:
    system("cls");
    printf("=================MENAMPILKAN DATA=================\n");
    if(tipe==1) printf("No.\tTanggal Peminjaman\tNama Pemberi Uang\tJumlah Uang\tTenggat Waktu Pelunasan\n");
    else printf("No.\tTanggal Peminjaman\tNama Peminjam Uang\tJumlah Uang\tTenggat Waktu Pelunasan\n");
    // membaca file utang/piutang dan menampilkan seluruh isinya
    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        i++;
        printf("%-8d%02d/%02d/%-18d%-24s%-16d%02d/%02d/%d\n", i, data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
    }

    fclose(fp); // menutup file
}

void UrutData()
{
    int tipe,opsi, size, ch=0;
    i=0;

    fp = fopen(filename,"r"); // membuka file dalam mode membaca

    while(ch!=EOF) // pengulangan sampai akhir file
	{
	    // membaca isi file utang/piutang dan dimasukkan ke dalam array
        fscanf(fp, "%d %d %d %s %d %d %d %d", &Adata[i].tgl, &Adata[i].bln, &Adata[i].thn, Adata[i].nama, &Adata[i].jml, &Adata[i].dtgl, &Adata[i].dbln, &Adata[i].dthn);
        ch=fgetc(fp);
        i++;
	}
    size=i-1;

    printf("=================================================================\n"
           "Urutkan berdasarkan:\n(1) Jumlah uang\n(2) Tenggat waktu pelunasan\n");
    printf("Pilihan Anda : ");
    scanf("%d", &opsi);
    // mengurutkan data utang/piutang berdasarkan jumlah uang dengan bubble sort secara ascending
    if (opsi==1)
    {
        system("cls");
        printf("==========DATA TELAH DIURUTKAN BERDASARKAN JUMLAH UANG==========\n");
        for(i=1;i<size;++i)
            for(j=0;j<size-i;j++)
                if(Adata[j+1].jml < Adata[j].jml)
                {
                    temp=Adata[j];
                    Adata[j]=Adata[j+1];
                    Adata[j+1]=temp;
                }
    }
    // mengurutkan data berdasarkan tenggat waktu pelunasan dengan bubble sort secara ascending
    else if (opsi==2)
    {
        // mengurutkan data berdasarkan tanggal
        system("cls");
        printf("========DATA TELAH DIURUTKAN BERDASARKAN TENGGAT WAKTU PELUNASAN========\n");
        for(i=1;i<size;++i)
            for(j=0;j<size-i;j++)
                if(Adata[j+1].dtgl < Adata[j].dtgl)
                {
                    temp=Adata[j];
                    Adata[j]=Adata[j+1];
                    Adata[j+1]=temp;
                }
        // mengurutkan data berdasarkan bulan
        for(i=1;i<size;++i)
            for(j=0;j<size-i;j++)
                if(Adata[j+1].dbln < Adata[j].dbln)
                {
                    temp=Adata[j];
                    Adata[j]=Adata[j+1];
                    Adata[j+1]=temp;
                }
        // mengurutkan berdasarkan tahun
        for(i=1;i<size;++i)
            for(j=0;j<size-i;j++)
                if(Adata[j+1].dthn < Adata[j].dthn)
                {
                    temp=Adata[j];
                    Adata[j]=Adata[j+1];
                    Adata[j+1]=temp;
                }
    }
    fclose(fp); // menutup file


    fp = fopen(filename,"w"); // membuka file dalam mode menulis
    // menulis data yang telah diurutkan kedalam file utang/piutang
    for(i=0; i<size; i++)
    {
        fprintf(fp, "%d %d %d %s %d %d %d %d\n", Adata[i].tgl, Adata[i].bln, Adata[i].thn, Adata[i].nama, Adata[i].jml, Adata[i].dtgl, Adata[i].dbln, Adata[i].dthn);
    }

    fclose(fp); // menutup file
    fp = fopen(filename, "r"); // membuka file dalam mode membaca
    if(tipe==1) printf("No.\tTanggal Peminjaman\tNama Pemberi Uang\tJumlah Uang\tTenggat Waktu Pelunasan\n");
    else printf("No.\tTanggal Peminjaman\tNama Peminjam Uang\tJumlah Uang\tTenggat Waktu Pelunasan\n");
    // membaca file utang/piutang dan menampilkan seluruh isinya
    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        i++;
        printf("%-8d%02d/%02d/%-18d%-24s%-16d%02d/%02d/%d\n", i, data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
    }

    fclose(fp); // menutup file
}

void HapusData(int tipe)
{
    int line=0, del;
    char ftemp[] = "temp.txt";

    FILE *fj;

    printf("======================================\n"
           "Data Utang/Piutang Sebelum Pembayaran:\n");
    TampilData(tipe); // Menampilkan data sebelum pembayaran

    fp = fopen(filename,"r"); // membuka file dalam mode membaca
	printf("Masukkan nomor barisan dari data yang ingin dihapus: ");
    scanf("%d", &del);

    fj = fopen(ftemp, "w"); // membuat file sementara dalam  mode menulis

    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        line++;
        // Mengcopy semua data dari file asli ke file sementara kecuali barisan yang dipilih pengguna
        if(line != del)
            fprintf(fj, "%d %d %d %s %d %d %d %d\n", data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
    }
    fclose(fp); // menutup file
    fclose(fj); // menutup file
    remove(filename); // Menghapus file asli
    rename(ftemp, filename); // Mengganti nama file sementara menjadi file asli
}

void CariData()
{
    char cari[20];
    int found=0;
    printf("=================================\n"
           "Masukkan nama yang ingin dicari: ");
    scanf("%s", cari);

    fp = fopen(filename,"r"); // membuka file dalam mode membaca
    // membaca file utang/piutang per baris sampai habis
    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        if (strcmp(cari, data.nama) == 0) // mencari barisan data berdasarkan nama yang diinput pengguna
        {
            printf("%02d/%02d/%-18d%-24s%-16d%02d/%02d/%d\n", data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
            found=1;
        }
    }

    if (found==0) // menampilkan pesan bila nama tidak ditemukan
        printf("=====================\n"
               "Data tidak ditemukan!\n"
               "=====================\n");

    fclose(fp); // menutup file
}

void Bayar(int tipe)
{
    int line=0, bayar, del;
    char ftemp[] = "temp.txt";

    FILE *fj;

    printf("======================================\n"
           "Data Utang/Piutang Sebelum Pembayaran:\n");
    TampilData(tipe); // Menampilkan data sebelum pembayaran

    fp = fopen(filename,"r"); // membuka file dalam mode membaca

    printf("Masukkan nomor barisan dari data yang ingin dibayar: ");
    scanf("%d", &del);

    fj = fopen(ftemp, "w"); // membuat file sementara dalam  mode menulis

    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        line++;
        // Mengcopy semua data dari file asli ke file sementara kecuali barisan yang dipilih pengguna
        if(line != del)
            fprintf(fj, "%d %d %d %s %d %d %d %d\n", data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
        else
        {
            printf("Masukkan jumlah yang ingin dibayar: ");
            scanf("%d", &bayar);
            // Mengurangi jumlah utang/piutang dengan jumlah yang dibayar
            data.jml -= bayar;
            // Jika jumlah utang/piutang sudah lunas, data tidak perlu dicatat kembali
            if(data.jml > 0)
                fprintf(fj, "%d %d %d %s %d %d %d %d\n", data.tgl, data.bln, data.thn, data.nama, data.jml, data.dtgl, data.dbln, data.dthn);
        }
    }
    fclose(fp); // menutup file
    fclose(fj); // menutup file
    remove(filename); // Menghapus file asli
    rename(ftemp, filename); // Mengganti nama file sementara menjadi file asli
}

void SimulasiBunga(int tipe){
    char cari[20];
    int found=0,masaPinjam,tahun,bunga;
    float bungaTahunan;

    printf("===== SIMULASI BUNGA =====\n");
    TampilData(tipe);
    printf("=================================\n"
           "Masukkan nama yang ingin dicari: ");
    scanf("%s", cari);

    fp = fopen(filename,"r"); // membuka file dalam mode membaca
    // membaca file utang/piutang per baris sampai habis
    while(fscanf(fp, "%d %d %d %s %d %d %d %d", &data.tgl, &data.bln, &data.thn, data.nama, &data.jml, &data.dtgl, &data.dbln, &data.dthn)==8)
    {
        if (strcmp(cari, data.nama) == 0) // mencari barisan data berdasarkan nama yang diinput pengguna
        {
            printf("Masukan suku bunga per tahun : ");
            scanf("%f",&bungaTahunan); //input nilai bunga per tahun
            getchar();
            tahun=data.dthn-data.thn; //mencari nilai tahun
            if (tahun!=0)
            {
                masaPinjam=data.dbln-data.bln+(12*tahun); //menghitunng masa pinjam
                bunga=data.jml*((bungaTahunan/100)/12)*masaPinjam; //menghitung bunga dari pinjaman
                printf("\nBunga pinjaman anda adalah Rp.%d.\n",bunga);
                printf("Total Angsuran anda adalah Rp.%d.\n",data.jml+bunga);
            } else {
                masaPinjam=data.dbln-data.bln;
                bunga=data.jml*((bungaTahunan/100)/12)*masaPinjam;
                printf("\nBunga pinjaman anda adalah Rp.%d.\n",bunga);
                printf("Total Angsuran anda adalah Rp.%d.\n",data.jml+bunga);
            }
            found=1;
        }
    }

    if (found==0) // menampilkan pesan bila nama tidak ditemukan
        printf("=====================\n"
               "Data tidak ditemukan!\n"
               "=====================\n");

    fclose(fp); // menutup file
}

int main()
{
    int pilih, menu;
    printf("===== LOAN MANAGER =====\n"
           "Masukkan pilihan:\n(1) Registrasi\n(2) Login\n"
           "Pilihan Anda : ");
    scanf("%d", &pilih);
    Masuk(pilih);

    MainMenu:
    system("cls");
    printf("MENU UTAMA:\n(1) KELOLA UTANG\n(2) KELOLA PIUTANG\n(3) KELUAR\n");
    printf("Pilihan Anda : ");
    scanf("%d", &pilih);
    while(pilih <= 2)
    {
        if(pilih == 1)
        {
            strcat(filename, "UTANG.txt"); // membuat nama file khusus utang
            printf("============================================\n"
                   "Masukkan pilihan:\n(1) Catat Utang\n(2) Daftar Utang\n(3) Bayar Utang\n"
                   "(4) Mengurutkan Data Utang\n(5) Mencari Data Utang\n(6) Menghapus Data Utang\n(7) Simulasi Bunga\n(8) Kembali ke Menu Utama\n");
            printf("Pilihan Anda : ");
            scanf("%d", &menu);
            switch(menu)
            {
                case 1: IsiData(pilih); break;
                case 2: TampilData(pilih); break;
                case 3: Bayar(pilih); break;
                case 4: UrutData(); break;
                case 5: CariData(); break;
                case 6: HapusData(pilih); break;
                case 7: SimulasiBunga(pilih); break;
                case 8: filename[strlen(filename)-9] = 0; goto MainMenu; // menghapus UTANG.txt dari filename dan kembali ke menu utama
            }
            filename[strlen(filename)-9] = 0; // menghapus UTANG.txt dari filename
        }
        else if(pilih == 2)
        {
            strcat(filename, "PIUTANG.txt"); // membuat nama file khusus piutang
            printf("============================================\n"
                   "Masukkan pilihan:\n(1) Catat Piutang\n(2) Daftar Piutang\n(3) Bayar Piutang\n"
                   "(4) Mengurutkan Data Piutang\n(5) Mencari Data Piutang\n(6) Menghapus Data Piutang\n(7) Simulasi Bunga\n(8) Kembali ke Menu Utama\n");
            printf("Pilihan Anda : ");
            scanf("%d", &menu);
            switch(menu)
            {
                case 1: IsiData(pilih); break;
                case 2: TampilData(pilih); break;
                case 3: Bayar(pilih); break;
                case 4: UrutData(); break;
                case 5: CariData(); break;
                case 6: HapusData(pilih); break;
                case 7: SimulasiBunga(pilih); break;
                case 8: filename[strlen(filename)-11] = 0; goto MainMenu; // menghapus PIUTANG.txt dari filename dan kembali ke menu utama
            }
            filename[strlen(filename)-11] = 0; // menghapus PIUTANG.txt dari filename
        }
        system("pause");
        system("cls");
    }

    return 0;
}
