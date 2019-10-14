#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include "password.h"

void mainmenu();
void submenu1();
void submenu2();
void tambah();
void absensi();
void hapus();
void edit();
void search();
void view();
void viewabsence();
void hapusabsen();
void kembali();
void Password();
void keluar();
int getdata();
int checknpm(int npm2);
int waktu();
int help();
int pilihan;
char cari;
char log[30];
FILE *fp,*ft,*fs;
COORD coord = {0, 0};

void gotoxy (int x, int y){
		coord.X = x; coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


typedef struct kelas{
	int npm;
	char name[50];
	int contact;
} kelas;

kelas data;
kelas Sort[100];

int getdata(){
	int npm2;
	gotoxy(21,3);
	printf("Masukkan Data:");
	gotoxy(21,5);
	printf("NPM\t:");
	scanf("%d",&npm2);

	if(checknpm(npm2) == 0){
		gotoxy(21,13);
		printf("\aNPM sudah dipakai\a");
		getch();
		mainmenu();
		return 0;
	}
	data.npm=npm2;
	gotoxy(21,7);
	printf("Nama\t:");
	gotoxy(35,7);
	scanf("%s",data.name);
	gotoxy(21,9);
	printf("Kontak\t:");
	gotoxy(35,9);
	scanf("%d",&data.contact);
	gotoxy(31,10);
	return 1;
}

int checknpm(int npm2){
	rewind(fp);
	while(fread(&data,sizeof(data),1,fp)==1){
		if(data.npm==npm2){
			return 0;
		}
	}
	return 1;
}

void mainmenu(){
	system("cls");
	gotoxy(20,3);
    printf("\=============== MENU UTAMA");
    printf(" ===============");
    gotoxy(20,5);
    printf("===== 1. DATA");
    gotoxy(20,7);
    printf("===== 2. ABSENSI");
    gotoxy(20,17);
    printf("===== 9. Kembali ke Menu Awal");
    gotoxy(20,19);
    printf("===== 0. Keluar Aplikasi");
    gotoxy(20,22);
    printf("------------------------------------------");
    gotoxy(20,23);
    waktu();
    gotoxy(20,21);
    printf("Pilihan: ");
    switch(getch()){
    	case '1':
			submenu1();
			break;
		case '2':
			submenu2();
			break;
		case '9':
			main();
			break;
		case '0':
			keluar();
        default:{
        	gotoxy(10,25);
	        printf("\aPilihan Salah!!Masukkan pilihan yang tepat!");
	        if(getch())
	        mainmenu();
		}
	}
}

void submenu1(){
	Password();
	system("cls");
	gotoxy(20,3);
    printf("============== DATA");
    printf(" ==============");
    gotoxy(20,5);
    printf("===== 1. Tambah Data");
	gotoxy(20,7);
	printf("===== 2. Lihat Data");
    gotoxy(20,9);
    printf("===== 3. Cari Data");
    gotoxy(20,11);
    printf("===== 4. Ubah Data");
    gotoxy(20,17);
    printf("===== 5. Kembali ke menu utama");
    gotoxy(20,20);
    printf("------------------------------------------");
    gotoxy(20,22);
    waktu();
    gotoxy(20,19);
    printf("Pilihan:");
    switch(getch()){
		case '1':
			tambah();
			break;
		case '2':
			view();
			break;
		case '3':
			search();
			break;
		case '4':{
			Password();
			system("cls");
			gotoxy(20,3);
			printf("===== 1. Hapus Data");
			gotoxy(20,5);
			printf("===== 2. Edit Data");
			gotoxy(20,7);
			printf("===== 3. Kembali ke menu utama");
			gotoxy(20,9);
			printf("Pilihan:");
			switch(getch()){
				case '1':
				hapus();
				break;
				case '2':
				edit();
				break;
				case '3':
				mainmenu();
				default:{
					gotoxy(10,23);
					printf("\aPilihan Salah!!Masukkan pilihan yang tepat!");
					if(getch()){
					    Password();
					}
		        }
			}
			break;
		}
		case '5':
			mainmenu();
			break;
		default:{
			gotoxy(10,24);
			printf("\aPilihan Salah!!Masukkan pilihan yang tepat!");
			if(getch()){
				submenu1();
			}
		}
	}
}

void submenu2(){
	system("cls");
	gotoxy(20,3);
    printf("============== ABSENSI");
    printf(" ==============");
    gotoxy(20,5);
    printf("===== 1. Absensi");
    gotoxy(20,7);
    printf("===== 2. Lihat Absen");
    gotoxy(20,9);
    printf("===== 3. Hapus Absensi");
    gotoxy(20,17);
    printf("===== 4. Kembali ke menu utama");
    gotoxy(20,20);
    printf("------------------------------------------");
    gotoxy(20,21);
    waktu();
    gotoxy(20,19);
    printf("Pilihan:");
    switch(getch()){
        case '1':
			absensi();
        	break;
    	case '2':
        	viewabsence();
        	break;
        case '3':
        	hapusabsen();
        	break;
        case '4':
			mainmenu();
			break;
        default:{
	        gotoxy(10,23);
	        printf("\aPilihan Salah!!Masukkan pilihan yang tepat!");
	        if(getch()){
	        	submenu2();
			}
        }
	}
}

void tambah(){
	system("cls");
	gotoxy(20,5);
	printf("*******  Pilih Kategori: ");
	gotoxy(20,7);
	printf("===== 1. Tambah Data Kelas");
	gotoxy(20,9);
	printf("===== 9. Kembali ke Menu");
	gotoxy(20,15);
	printf("Pilihan:");
	pilihan = getch();
	if(pilihan=='9'){
		submenu1();
	}
	system("cls");
	fp=fopen("stf.dat","ab+");

	if(getdata()==1){
		fseek(fp,0,SEEK_END);
		fwrite(&data,sizeof(data),1,fp);
		fclose(fp);
		gotoxy(21,14);
		printf("Data tersimpan");
		gotoxy(21,15);
		printf("Ingin tambah lagi?(y=Ya, lainnya=tidak):");

		if(getch()=='y'){
			system("cls");
			tambah();
		}
		else{
			submenu1();
		}
	}
}

void view(){
	int j=8, i=0, k, n, npmtemp, conttemp;
	char nametemp[50];
	system("cls");
	gotoxy(20, 5);
	printf("============================== List Data Kelas ==============================");
	gotoxy(30, 8);
	printf("===== 1. Urut Waktu Input");
	gotoxy(30, 10);
	printf("===== 2. Urut Abjad");
	gotoxy(30, 11);
	fp=fopen("stf.dat","rb");
	printf("Pilihan: ");
	switch(getch()){
		case '1':
			system("cls");
			gotoxy(20,5);
			printf(" ============================== List Data Kelas ==============================");
			gotoxy(30, 7);
			printf("NPM =================== NAMA ================== KONTAK");
			while(fread(&data,sizeof(data),1,fp)==1){
				gotoxy(30,j);
				printf("%d",data.npm);
				gotoxy(50,j);
				printf("%s",data.name);
				gotoxy(78,j);
				printf("%d",data.contact);
				gotoxy(80,j);
				printf("\n\n");
				j++;
			}
			fclose(fp);
			break;
		case '2':
			system("cls");
			gotoxy(20,5);
			printf("============================== List Data Kelas ==============================");
			gotoxy(30,7);
			printf("NPM =================== NAMA ================== KONTAK");
			while(fread(&data,sizeof(data),1,fp)==1){
				Sort[i] = data;
				i++;
			}
			for(k=0; k<i-1; k++){
				for(n=0; n<i-1; n++){
					if(strcmp(Sort[n].name, Sort[n+1].name)>0){
						npmtemp = Sort[n].npm;
						Sort[n].npm = Sort[n+1].npm;
						Sort[n+1].npm = npmtemp;

						strcpy(nametemp, Sort[n].name);
						strcpy(Sort[n].name, Sort[n+1].name);
						strcpy(Sort[n+1].name, nametemp);

						conttemp = Sort[n].contact;
						Sort[n].contact = Sort[n+1].contact;
						Sort[n+1].contact = conttemp;
					}
				}
			}
			for(k=0; k<i; k++){
				gotoxy(30,j);
				printf("%d",Sort[k].npm);
				gotoxy(50,j);
				printf("%s",Sort[k].name);
				gotoxy(78,j);
				printf("%d",Sort[k].contact);
				gotoxy(80,j);
				printf("\n\n");
				j++;
			}
			fclose(fp);
			break;
		}
		gotoxy(35,25);
		kembali();
}

void search(){
	system("cls");
	int npm3;
	gotoxy(20,3);
	printf("============================== Cari Data ==============================");
	gotoxy(20,10);
	printf("1. Cari berdasarkan NPM");
	gotoxy(20,14);
	printf("2. Cari berdasarkan Nama");
	gotoxy( 15,20);
	printf("Pilihan: ");
	fp=fopen("stf.dat","rb+");
	rewind(fp);
	switch(getch()){
		case '1':{
			system("cls");
			gotoxy(25,4);
			printf("===== Cari berdasarkan NPM =====");
			gotoxy(20,5);
			printf("Masukkan NPM: ");
			scanf("%d",&npm3);
			gotoxy(20,7);
			while(fread(&data,sizeof(data),1,fp)==1){
				if(data.npm==npm3){
					Sleep(2);
					gotoxy(20,6);
					printf("Data ditemukan\n");
					gotoxy(20,8);
					printf("NPM:%d",data.npm);
					gotoxy(20,9);
					printf("Nama:%s",data.name);
					gotoxy(20,10);
					printf("Kontak:%d ",data.contact);
					cari='t';
				}
			}
			if(cari!='t'){
				gotoxy(20,6);
				printf("\aData tidak ditemukan");
			}
			gotoxy(20,17);
			printf("Ingin mencari lagi?(y=Ya, lainnya=tidak)");
			if(getch()=='y'){
				search();
			}
			else{
				mainmenu();
			}
			break;
		}
		case '2':{
			char nama[50];
			system("cls");
			gotoxy(25,4);
			printf("===== Cari berdasarkan Nama =====");
			gotoxy(20,5);
			printf("Masukkan Nama: ");
			scanf("%s",nama);

			int d=0;
			while(fread(&data,sizeof(data),1,fp)==1){
				if(strcmp(data.name,(nama))==0){
					gotoxy(20,d+7);
					printf("Data ditemukan\n");
					gotoxy(20,d+8);
					printf("NPM:%d",data.npm);
					gotoxy(20,d+10);
					printf("Nama:%s",data.name);
					gotoxy(20,d+11);
					printf("Kontak:%d ",data.contact);
					gotoxy(20,d+14);
					getch();
					d+=6;
				}
			}
			if(d==0){
				printf("\aData tidak ditemukan");
			}
			gotoxy(20,d+11);
			printf("Ingin mencari lagi?(y=Ya, lainnya=tidak)");
			if(getch()=='y'){
				search();
			}
			else{
				mainmenu();
			}
			break;
		}
		default :{
			printf("Pilihan salah, masukkan pilihan yang tepat");
			getch();
			search();
		}
	}
	fclose(fp);
}


void hapus(){
	int npm4;
	char hapus = 'y';
	while(hapus=='y'){
		system("cls");
		gotoxy(10,5);
		printf("NPM yang akan dihapus:");
		scanf("%d",&npm4);
		fp=fopen("stf.dat","rb+");
		rewind(fp);
		while(fread(&data,sizeof(data),1,fp)==1){
			if(data.npm==npm4){
				gotoxy(10,7);
				printf("Data NPM ditemukan");
				gotoxy(10,8);
				printf("Nama: %s",data.name);
				gotoxy(10,9);
				cari='t';
			}
		}
		if(cari!='t'){
			gotoxy(10,10);
			printf("Data NPM tidak ditemukan");
			if(getch()){
				submenu1();
			}
		}
		if(cari=='t'){
			gotoxy(10,10);
			printf("Hapus data NPM ?(y=Ya, lainnya=tidak)");
			gotoxy(10,11);
			printf("Pilihan: ");
			if(getch()=='y'){
				ft=fopen("dlt.dat","wb+");
				rewind(fp);
				while(fread(&data,sizeof(data),1,fp)==1){
					if(data.npm!=npm4){
						fseek(ft,0,SEEK_CUR);
						fwrite(&data,sizeof(data),1,ft);
					}
				}
				fclose(ft);
				fclose(fp);
				remove("stf.dat");
				rename("dlt.dat","stf.dat");
				fp=fopen("stf.dat","rb+");
				gotoxy(10,11);
				printf("Data telah dihapus");
				gotoxy(10,15);
				printf("Hapus data lainnya? (y=Ya, lainnya=tidak)");
				gotoxy(10,16);
				printf("Pilihan: ");
				hapus=getch();
			}
			else{
				mainmenu();
				fflush(stdin);
				hapus=getch();
			}
		}
	}
	gotoxy(10,15);
	mainmenu();
}

void edit(){
	system("cls");
	int c=0;
	int npm5,e;
	gotoxy(20,4);
	printf("===== Edit Data =====");
	system("cls");
	gotoxy(15,6);
	printf("NPM data yang ingin diedit:");
	scanf("%d",&npm5);
	fp=fopen("stf.dat","rb+");
	while(fread(&data,sizeof(data),1,fp)==1){
		if(checknpm(npm5)==0){
			gotoxy(15,7);
			printf("Data NPM ditemukan");
			gotoxy(15,8);
			printf("NPM:%d",data.npm);
			gotoxy(15,9);
			printf("Nama Baru:");
			scanf("%s",data.name);
			gotoxy(15,10);
			printf("Kontak Baru:");
			scanf("%d",&data.contact);
			gotoxy(15,12);
			printf("Data telah diubah");
			fseek(fp,ftell(fp)-sizeof(data),0);
			fwrite(&data,sizeof(data),1,fp);
			fclose(fp);
			c=1;
		}
		if(c==0){
			gotoxy(15,9);
			printf("Data NPM tidak ditemukan");
		}
	}
	fflush(stdin);
	getch() ;
	kembali();
}

void absensi(){
	system("cls");
	int d, k;
	gotoxy(20,3);
	printf("============================== ABSENSI ==============================");
	gotoxy(20,5);
	printf("Masukkan NPM: ");
	fp=fopen("stf.dat","rb+");
	scanf("%d",&d);
	time_t t;
	time(&t);
	strcpy(log,ctime(&t));
	gotoxy(20,7);
	while(fread(&data,sizeof(data),1,fp)==1){
		if(data.npm==d){
			Sleep(2);
			gotoxy(20,8);
			printf("Absensi telah dicatat\n");
			gotoxy(20,10);
			printf("Nama: %s",data.name);
			gotoxy(20,12);
			printf("Date and time: %s\n",log);
			fs=fopen("abs.dat", "ab+");
			k = 1;
			fseek(fs,0,SEEK_END);
			fwrite(&data,sizeof(data),1,fs);
			fseek(fs,10,SEEK_CUR);
			fwrite(log,sizeof(log),1,fs);
			fclose(fs);
			getch();
		}
	}
	if(k != 1){
		gotoxy(20, 10);
		printf("\aNPM tidak ditemukan");
		getch();
	}
	fclose(fp);
	submenu2();
}

void viewabsence(){
	int j=9;
	system("cls");
	gotoxy(10,5);
	printf("=================================== List Absensi ===================================");
	gotoxy(15,8);
	printf("NPM =================== NAMA ================== KONTAK ============ WAKTU ============");
	fs=fopen("abs.dat","rb");
	while(fread(&data,sizeof(data),1,fs)==1){
		gotoxy(15,j);
		printf("%d",data.npm);
		gotoxy(35,j);
		printf("%s",data.name);
		gotoxy(63,j);
		printf("%d",data.contact);
		gotoxy(75,j);
		fread(log,sizeof(log),1,fs);
		printf("%s",log);
		gotoxy(85,j);
		printf("\n\n");
		j++;
	}
	fclose(fs);
	kembali();
}

void hapusabsen(){
	Password();
	system("cls");
	printf("\n\n ANDA YAKIN AKAN MENGHAPUS DATA ABSENSI?(y=Ya, lainnya=tidak)");
	printf("\n Pilihan: ");
	if(getch()=='y'){
		remove("abs.dat");
		printf("\n\n Data telah terhapus");
		getch();
		mainmenu();
	}
	else{
		printf("\n\n :)");
		getch();
		submenu2();
	}
}

void kembali(){
	gotoxy(15,26);
	printf("Tekan ENTER untuk kembali ke Menu Utama");
	a:
	if(getch()==13){
		mainmenu();
	}
	else{
		goto a;
	}
}

int waktu(){
	time_t t;
	time(&t);
	printf("Date and time: %s\n",ctime(&t));
	return 0 ;
}

int help(){
	system("cls");
	gotoxy(20,3);
	printf("\t\tBANTUAN");
	gotoxy(20,4);
	printf("==============================\n");
	gotoxy(14,5);
	printf("Aplikasi ini berfungsi untuk absensi kelas\n\n");
	gotoxy(14,6);
	printf("Cara Menggunakan:\n\n[1]Pilih Mulai\n[2]Pilih Menu:\n\n\t[1]DATA, untuk memasukkan data kelas\n\t[2]ABSENSI, untuk mengisi absensi\n");
	gotoxy(14,14);
	printf("Menu DATA:\n\t\t[1]Tambah Data, untuk menambah data kelas\n\t\t[2]Lihat Data, untuk melihat daftar data kelas\n\t\t[3]Cari Data, untuk mencari info data kelas\n\t\t[4]Ubah Data, untuk menghapus maupun merubah informasi data kelas\n\t\t[5]Kembali ke menu utama");
	gotoxy(14,21);
	printf("Menu ABSENSI:\n\t\t[1]Absensi, untuk mengisi absensi kelas\n\t\t[2]Lihat Absensi, untuk melihat daftar hadir kelas\n\t\t[3]Kembali ke menu utama");
	gotoxy(1,26);
	printf("Format Nama = Namadepan_Namatengah_Namabelakang");
	gotoxy(1,27);
	printf("Contoh: Joseph_Elroy_Manurung");
	getch();
	system("cls");
	return main();
}

void keluar(){
	system("cls");
	gotoxy(16,3);
    printf("Terimakasih Sudah menggunakan Program ini :)");
	gotoxy(16,7);
	printf("Keluar dalam 5 detik........>");
	delay(5000);
	exit(0);
}

int main(){
	system("cls");
	system("color f0");
    char pilihan;
        gotoxy(20, 5);
	    printf("============== Sistem Absensi Kelas");
	    printf(" ==============");
	    gotoxy(20,9);
	    printf("===== 1. Start");
	    gotoxy(20,14);
	    printf("===== 9. Help");
	    gotoxy(20,16);
	    printf("===== 0. Keluar Aplikasi");
	    gotoxy(20,18);
        printf("Pilihan: ");
        switch(getch()){
		case '1':
			mainmenu();
		break;
		case '9':
            help();
        break;
        case '0':
        	keluar();
        	break;
        default:{
        	gotoxy(10,23);
	        printf("\aPilihan Salah!!Masukkan pilihan yang tepat!");
	        if(getch())
	        system("cls");
	        main();
        }
    }
    return 0;
}
