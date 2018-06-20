struct user{
	int id;
	char fname[250];
	char lname[250];
	int code;
};

class Users
{
private:
	int prepage = 2;
public:
	Users(){
		//check file exist
		FILE *db;
		fopen_s(&db, "Users.dat", "rb");
		if (!db)
			fopen_s(&db, "Users.dat", "wb");
		fclose(db);
	}

	bool insert(user data){
		bool affect = true;
		FILE *db;
		fopen_s(&db, "Users.dat", "ab");
		affect = (fwrite(&data, sizeof(user), 1, db)) ? true : false;
		fclose(db);
		return affect;
	}
	bool Adduser(){
		user b;
		cout << "Enter fname: ";
		cin >> b.fname;
		cout << "Enter lname: ";
		cin >> b.lname;
		cout << "Enter IECode: ";
		cin >> b.code;
		cout << "Enter id: ";
		cin >> b.id;
		while (findByID(b.id).id){
			cout << "Your id existed please try again: ";
			cin >> b.id;
		}
		insert(b);
		return 1;
	}
	user findByID(int id){
		user result;
		result.id = 0;
		FILE *db;
		fopen_s(&db, "Users.dat", "rb");
		if (db){
			fread(&result, sizeof(user), 1, db);
			while (result.id != id && !feof(db)){
				fread(&result, sizeof(user), 1, db);
			}
			if (result.id != id)
				result.id = 0;
		}
		fclose(db);
		return result;
	}
	user findByfname(char fname[250]){
		user result;
		result.id = 0;
		FILE *db;
		fopen_s(&db, "Users.dat", "rb");
		if (db){
			fread(&result, sizeof(user), 1, db);
			while (!strstr(result.fname, fname) && !feof(db)){
				fread(&result, sizeof(user), 1, db);
			}
			if (!strstr(result.fname, fname))
				result.id = 0;
		}
		fclose(db);
		return result;
	}
	void Find(bool t){
		user b;
		if (t){
			char fname[250];
			gets_s(fname);
			b = findByfname(fname);
		}
		else{
			int id;
			cin >> id;
			b = findByID(id);
		}
		if (b.id != 0){
			cout << "\n| #Id \t\t fname \t\t lname \t\t Code |";
			cout << "\n  " << b.id << " \t\t " << b.fname << " \t\t " << b.lname << " \t\t " << b.code;
		}
		else
			cout << "No Result";
	}
	int showlist(int p){
		user b;
		FILE *db;
		int i;
		fopen_s(&db, "Users.dat", "rb");
		if (!db)
			return -1;
		for (i = 0; i < prepage*p && !feof(db); i++)
			fread(&b, sizeof(user), 1, db);
		i = 0;
		cout << "\n| #Id \t\t fname \t\t lname \t\t Code |";
		while (i < prepage && !feof(db))
		{
			fread(&b, sizeof(user), 1, db);
			if (!feof(db)){
				cout << "\n  " << b.id << " \t\t " << b.fname << " \t\t " << b.lname << " \t\t " << b.code;
			}
			else{
				fclose(db);
				return 1;
			}
			i++;
		}
		fclose(db);
		return 2;
	}
	bool remove(){
		int id;
		cout << "Enter id of user for delete: ";
		cin >> id;
		user b;
		bool result = false;
		FILE *db;
		FILE *temp;
		fopen_s(&db, "Users.dat", "rb");
		fopen_s(&temp, "temp.dat", "w+b");
		if (!db)
			return 0;
		while (!feof(db)){
			fread(&b, sizeof(user), 1, db);
			if (b.id == id){
				result = 1;
				continue;
			}
			if (!feof(db))
				fwrite(&b, sizeof(user), 1, temp);
		}
		fflush(temp);
		fclose(db);
		fopen_s(&db, "Users.dat", "wb");
		while (!feof(temp)){
			fread(&b, sizeof(user), 1, temp);
			if (!feof(temp))
				fwrite(&b, sizeof(user), 1, db);
		}
		fclose(db);
		fclose(temp);
		return result;
	}

	~Users(){}
};