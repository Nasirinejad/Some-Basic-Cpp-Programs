struct book{
	int id;
	char name[250];
	char author[250];
	bool stat;
};

class Books
{
private:
	int prepage = 2;
public:
	Books(){
		cout << "Loading...";
		//check file exist
		FILE *db;
		fopen_s(&db, "Books.dat", "rb");
		if (!db)
			fopen_s(&db, "Books.dat", "wb");
		fclose(db);
	}

	bool insert(book data){
		bool affect = true;
		FILE *db;
		fopen_s(&db, "Books.dat", "a+b");
		affect = (fwrite(&data, sizeof(book), 1, db)) ? true : false;
		fclose(db);
		return affect;
	}
	bool AddBook(){
		book b;
		cout << "Enter name: ";
		cin >> b.name;
		cout << "Enter author: ";
		cin >> b.author;
		cout << "Enter id: ";
		cin >> b.id;
		while (findByID(b.id).id){
			cout << "Your id existed please try again: ";
			cin >> b.id;
		}
		b.stat = 1;
		if (insert(b))
			return 1;
		else
			return 0;
	}
	book findByID(int id){
		book result;
		result.id = 0;
		FILE *db;
		fopen_s(&db, "Books.dat", "rb");
		fread(&result, sizeof(book), 1, db);
		while (result.id != id && !feof(db)){
			fread(&result, sizeof(book), 1, db);
		}
		if (result.id != id)
			result.id = 0;
		fclose(db);
		return result;
	}
	book findByName(char name[250]){
		book result;
		result.id = 0;
		FILE *db;
		fopen_s(&db, "Books.dat", "rb");

		fread(&result, sizeof(book), 1, db);
		while (!strstr(result.name, name) && !feof(db)){
			fread(&result, sizeof(book), 1, db);
		}
		if (!strstr(result.name, name))
			result.id = 0;

		fclose(db);
		return result;
	}
	void Find(bool t){
		book b;
		if (t){
			char name[250];
			gets_s(name);
			b = findByName(name);
		}
		else{
			int id;
			cin >> id;
			b = findByID(id);
		}
		if (b.id != 0){
			cout << "\n| #Id \t\t Name \t\t Author \t\t Stat |";
			cout << "\n  " << b.id << " \t\t " << b.name << " \t\t " << b.author;
			if (b.stat)
				cout << " \t\t Existent ";
			else
				cout << " \t\t NotExistent ";
		}
		else
			cout << "No Result";
	}
	int showlist(int p){
		book b;
		FILE *db;
		int i;
		fopen_s(&db, "Books.dat", "rb");
		if (!db)
			return -1;
		for (i = 0; i < prepage*p && !feof(db); i++)
			fread(&b, sizeof(book), 1, db);
		i = 0;
		cout << "\n| #Id \t\t Name \t\t Author \t\t Stat |";
		while (i < prepage && !feof(db))
		{
			fread(&b, sizeof(book), 1, db);
			if (!feof(db)){
				cout << "\n  " << b.id << " \t\t " << b.name << " \t\t " << b.author;
				if (b.stat)
					cout << " \t \t Existent";
				else
					cout << " \t \t NotExistent";
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
		cout << "Enter id of book for delete: ";
		cin >> id;
		book b;
		bool result = false;
		FILE *db;
		FILE *temp;
		fopen_s(&temp, "temp.dat", "w+b");
		fopen_s(&db, "Books.dat", "rb");
		if (!db)
			return 0;
		while (!feof(db)){
			fread(&b, sizeof(book), 1, db);
			if (b.id == id){
				result = 1;
				continue;
			}
			if (!feof(db))
				fwrite(&b, sizeof(book), 1, temp);
		}
		fclose(db);
		fflush(temp);
		fopen_s(&db, "Books.dat", "wb");
		while (!feof(temp)){
			fread(&b, sizeof(book), 1, temp);
			if (!feof(temp))
				fwrite(&b, sizeof(book), 1, db);
		}
		_fcloseall();
		return result;
	}
	bool restat(bool type, bool by){
		if (by){
			int id;
			cout << "Enter id of book for check: ";
			cin >> id;
			book b;
			b = findByID(id);
			if (type && b.stat){
				cout << "The book is existent\n";
				return 0;
			}
			if (!type && !b.stat){
				cout << "SORRY! The book is not existent\n";
				return 0;
			}
			FILE *db;
			fopen_s(&db, "Books.dat", "r+b");
			if (!db)
				return 0;
			for (int i = 0; !feof(db); i++){
				fread(&b, sizeof(book), 1, db);
				if (b.id == id){
					fseek(db, i * sizeof(book), SEEK_SET);
					b.stat = type;
					fwrite(&b, sizeof(book), 1, db);
					break;
				}
			}
			fclose(db);
		}else{
			char name[250];
			cout << "Enter name of book for check: ";
			cin >> name;
			book b;
			b = findByName(name);
			if (type && b.stat){
				cout << "The book is existent\n";
				return 0;
			}
			if (!type && !b.stat){
				cout << "SORRY! The book is not existent\n";
				return 0;
			}
			FILE *db;
			fopen_s(&db, "Books.dat", "r+b");
			if (!db)
				return 0;
			for (int i = 0; !feof(db); i++){
				fread(&b, sizeof(book), 1, db);
				if (strstr(b.name, name)){
					fseek(db, i * sizeof(book), SEEK_SET);
					b.stat = type;
					fwrite(&b, sizeof(book), 1, db);
					break;
				}
			}
			fclose(db);
		}
		return 1;
	}

	~Books(){}
};