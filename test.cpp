#include<iostream>
#include<cstring>
#include<stdio.h>
#include <sqlite3.h>
#include <sstream>
#include <locale>
#include <iomanip>
#include<time.h>

using namespace std;
struct trx 
{
	int m,type,pil,status,lama,biaya;
	char plat[100];
	char tgl_masuk[100];
	char tgl_keluar[100];

}trx[100];

sqlite3* DB;

sqlite3_stmt *stmt_insert_trx_in = NULL;



static int time_2_epoch(std::string timestamp){
	std::tm t = {};
    // std::istringstream ss("2023-09-18 18:18:39");
	std::istringstream ss(timestamp);
	

    if (ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S"))
    {
        std::cout << std::mktime(&t) << "\n";
    }
    else
    {
        std::cout << "Parse failed\n";
    }
    return std::mktime(&t);
}




static int create_table_trx_in(){

	int exit = 0;
	exit = sqlite3_open("parkee.db", &DB);
  
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

		std::string sql = "CREATE TABLE IF NOT EXISTS in_trx("
                      "id 				 INTEGER PRIMARY KEY   AUTOINCREMENT, "
                      "plat_no           VARCHAR(255)    NOT NULL, "
                      "date_time         VARCHAR(255)    NOT NULL, "
					  "type_trx          INT     NOT NULL, "
                      "status_trx            INT     NOT NULL);";
		
		exit = sqlite3_open("parkee.db", &DB);
		char* messaggeError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	
		if (exit != SQLITE_OK) {
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messaggeError);
		}
		else
			std::cout << "Table created Successfully" << std::endl; sqlite3_close(DB); return 0;
	
}

static int create_table_trx_tmp(){

	int exit = 0;
	exit = sqlite3_open("parkee.db", &DB);
  
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

		std::string sql = "CREATE TABLE IF NOT EXISTS tmp_trx("
                      "id 				 INTEGER PRIMARY KEY   AUTOINCREMENT, "
                      "plat_no           VARCHAR(255)    NOT NULL, "
                      "date_time          VARCHAR(255)     NOT NULL, "
					  "type_trx          INT     NOT NULL, "
                      "status_trx            INT     NOT NULL);";
		
		exit = sqlite3_open("parkee.db", &DB);
		char* messaggeError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	
		if (exit != SQLITE_OK) {
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messaggeError);
		}
		else
			std::cout << "Table created Successfully" << std::endl; sqlite3_close(DB); return 0;
	
	
}

static int create_table_trx_out(){
	int exit = 0;
	exit = sqlite3_open("parkee.db", &DB);
  
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

		std::string sql = "CREATE TABLE IF NOT EXISTS out_trx("
                      "id 				 INTEGER PRIMARY KEY   AUTOINCREMENT, "
                      "plat_no           VARCHAR(255)    NOT NULL, "
                      "date_time          VARCHAR(255)     NOT NULL, "
					  "type_trx          INT     NOT NULL, "
                      "status_trx            INT     NOT NULL);";
		
		exit = sqlite3_open("parkee.db", &DB);
		char* messaggeError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	
		if (exit != SQLITE_OK) {
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messaggeError);
			return -1;
		}
		else std::cout << "Table created Successfully" << std::endl; sqlite3_close(DB); return 0;
	
}

static int insert_trx_in(const char *plat_no,const char *date_time, const int status_trx, const int type_trx){
	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};

	sprintf (sql,"INSERT INTO in_trx (plat_no,date_time,type_trx,status_trx) VALUES ('%s','%s',%d,%d);",plat_no,date_time,type_trx,status_trx);
	
  
    exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB);
        sqlite3_free(messaggeError);
		return -1;
    }
    else std::cout << "Records created Successfully! \n" << std::endl; sqlite3_close(DB); return 0;

}

static int insert_trx_tmp(const char *plat_no,const char *date_time, const int status_trx, const int type_trx){
	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};

	sprintf (sql,"INSERT INTO tmp_trx (plat_no,date_time,type_trx,status_trx) VALUES ('%s','%s',%d,%d);",plat_no,date_time,type_trx,status_trx);
	

  
    exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB);
        sqlite3_free(messaggeError);
		return -1;
    }
    else std::cout << "Records created Successfully! \n" << std::endl; sqlite3_close(DB);return 0;

}

static int insert_trx_out(const char *plat_no,const char *date_time, const int status_trx, const int type_trx){

	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};

	sprintf (sql,"INSERT INTO out_trx (plat_no,date_time,type_trx,status_trx) VALUES ('%s','%s',%d,%d);",plat_no,date_time,type_trx,status_trx);
	
  
    exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB);
        sqlite3_free(messaggeError);
		return -1;
    }
    else std::cout << "Records created Successfully! \n" << std::endl; sqlite3_close(DB); return 0;

	

}

static int delete_trx_tmp(const char *param){
	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};

	sprintf (sql,"DELETE FROM tmp_trx WHERE plat_no = '%s';",param);
  
    exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Delete" << sqlite3_errmsg(DB);
        sqlite3_free(messaggeError);
		return -1;
    }
    else std::cout << "Delete Successfully! \n" << std::endl; sqlite3_close(DB); return 0;

}


static int check_trx_tmp(const char *param_check){
	
	sqlite3_stmt *stmt;
	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};


	sprintf (sql,"SELECT COUNT(*) FROM tmp_trx WHERE plat_no LIKE '%s';",param_check);

	
  
    sqlite3_stmt *stmt_select = NULL;
	sqlite3_prepare_v2(DB,sql,-1,&stmt_select,NULL);
	int rv = sqlite3_step(stmt_select);
	int count = sqlite3_column_int(stmt_select, 0);
	cout<<"count "<<count;

	if (sqlite3_step(stmt_select) != SQLITE_DONE) {
		sqlite3_finalize(stmt_select);
		stmt_select = NULL;
		sqlite3_close(DB);
		return -1;
	}
	if(count==0){
		sqlite3_finalize(stmt_select);
		stmt_select = NULL;
		sqlite3_close(DB);
		return 0;

	}else sqlite3_finalize(stmt_select); stmt_select = NULL; sqlite3_close(DB); return -1;

	
	
}

static int get_time_tmp(const char *param_check){
	
	sqlite3_stmt *stmt;
	char* messaggeError;
	int exit = 0;
    exit = sqlite3_open("parkee.db", &DB);

	char sql[1024]={0};


	sprintf (sql,"SELECT date_time FROM tmp_trx WHERE plat_no LIKE '%s';",param_check);

	
  
    sqlite3_stmt *stmt_select = NULL;
	sqlite3_prepare_v2(DB,sql,-1,&stmt_select,NULL);
	int rv = sqlite3_step(stmt_select);
 
	std::string datetime_tmp = (const char*) sqlite3_column_text(stmt_select,0);

	
	sqlite3_finalize(stmt_select); stmt_select = NULL; sqlite3_close(DB);

	int epoch = time_2_epoch(datetime_tmp);

	

	return epoch;

	
}




static int init(){

	cout<<"---- Init Sistem Parkir  ----"<<endl;
   
   	
    int crv_in = create_table_trx_in();
	int crv_out = create_table_trx_out();
	int crv_tmp = create_table_trx_tmp();

	if(crv_in == 0 && crv_out ==0){
		return 0;
	}else{
		return -1;
	}


}

main(int argc, char* argv[]){
	int pil,a,b,total;
	char ch, temp,yn;
	int m = -1; 
	int d = -1; 
    

	int rc_db = -1;
	rc_db=init();

	if(rc_db!=0){
		cout<<"---- Sistem Parkir Failed Init ----"<<endl;
		return -1;

	}else{
		cout<<"---- Sistem Parkir Successful Init ----"<<endl;
	}


	menu:
	cout<<"---- Sistem Parkir -----"<<endl;
    cout<<"-------- Menu ----------\n";
    cout<<" 1. Transaksi IN	       \n";
    cout<<" 2. Transaksi OUT       \n";
    cout<<"------------------------\n";
    cout<<"Masukan Pilihan anda[ 1 s.d. 2 ] = ";
	cin>>pil;

	system("cls");
	
	if(pil == 1)
	{
		trxmasuk:
		m++;
		cout<<"\n\n \t\t\t ------- TRANSAKSI MASUK ------- \t\t\t";
		cout<<"\n Masukkan Plat No: ";
		cin>>trx[m].plat;
		cout<<"\n type kendaraan : \n  1. motor \n  2. mobil \n";
		cout<<" pilih type kendaraan [1 / 2 ] : ";
		cin>>trx[m].type;



		int inv_tmp = check_trx_tmp(trx[m].plat);

		if(inv_tmp == 0){

			char timestamp[32] ={0};
			time_t now = time(0);
			struct tm tstruct = *localtime(&now);
			sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, tstruct.tm_hour , tstruct.tm_min, tstruct.tm_sec);
			strcpy(trx[m].tgl_masuk,timestamp);
			int timestamp_p = time_2_epoch(timestamp);
			int inv_in = insert_trx_in(trx[m].plat,trx->tgl_masuk,1,trx->type);
			int inv_tmo = insert_trx_tmp(trx[m].plat,trx->tgl_masuk,1,trx->type);

			
			if (inv_in==0)
			{

				cout<<"---------------------------------------\n";
				cout<<"         SELAMAT                       \n";
				cout<<"      BERHASIL MASUK                   \n";
				cout<<" waktu masuk  : "<<trx[m].tgl_masuk<<" \n";
				cout<<"          		                      \n";
				cout<<"                                       \n";
				cout<<"---------------------------------------\n";

			}else {
				cout<<"------------------------\n";
				cout<<"                        \n";
				cout<<"      GAGAL MASUK       \n";
				cout<<"          		       \n";
				cout<<"                        \n";
				cout<<"------------------------\n";

			}
				
		}else{
			cout<<"------------------------\n";
			cout<<"                        \n";
			cout<<"      GAGAL MASUK       \n";
			cout<<"          		       \n";
			cout<<"                        \n";
			cout<<"------------------------\n";

		}

        goto menu;	
		
	}
	else if(pil == 2)
	{
		
		trxkeluar:
		system("cls");
		m++;
		cout<<"\n\n \t\t\t ------- TRANSAKSI KELUAR ------- \t\t\t";
		cout<<"\n Masukkan Plat No: ";
		cin>>trx[m].plat;
		cout<<"\n type kendaraan : \n  1. motor \n  2. mobil \n";
		cout<<" pilih type kendaraan [1 / 2 ] : ";
		cin>>trx[m].type;
	
		
		int inv_tmp = check_trx_tmp(trx[m].plat);

		

		if(inv_tmp == -1){

			char timestamp[32] ={0};
			time_t now = time(0);
			struct tm tstruct = *localtime(&now);
			sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);
			strcpy(trx[m].tgl_keluar,timestamp);
			int timestamp_p = time_2_epoch(timestamp);
			int inv_get_time_tmp = get_time_tmp(trx[m].plat);
			int inv_in = insert_trx_out(trx[m].plat,trx->tgl_keluar,0,trx->type);
			int inv_dlt = delete_trx_tmp(trx[m].plat);

			int epoch_masuk = inv_get_time_tmp;
			int epoch_keluar = timestamp_p;
			float cal= ((epoch_keluar-epoch_masuk)/3600)*3000;

			if (cal < 1)
			{
				trx[m].biaya = 3000;
			}else{
				trx[m].biaya = cal;
			}


			
			if (inv_in==0)
			{

				cout<<"-----------------------------------------\n";
				cout<<"         SELAMAT                         \n";
				cout<<"      BERHASIL KELUAR                    \n";
				cout<<" waktu keluar  : "<<trx[m].tgl_keluar<<" \n";
				cout<<" biaya         : "<<trx[m].biaya<<"      \n";
				cout<<"          		                        \n";
				cout<<"                                         \n";
				cout<<"-----------------------------------------\n";

			}else {
				cout<<"------------------------\n";
				cout<<"                        \n";
				cout<<"      GAGAL KELUAR      \n";
				cout<<"          		       \n";
				cout<<"                        \n";
				cout<<"------------------------\n";

			}
				
		}else{
			cout<<"------------------------\n";
			cout<<"                        \n";
			cout<<"      GAGAL KELUAR      \n";
			cout<<"          		       \n";
			cout<<"                        \n";
			cout<<"------------------------\n";

		}

		


		 goto menu;	
	}
	
	else
	{
		cout<<"\n\n -- pilihan tidak tersedia -- \n\n";

		goto menu;	
	} 

    //return 0;
		
}