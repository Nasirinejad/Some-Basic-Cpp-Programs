struct user{
	char firstname[250];
	long int id;
	char lastname[250];
};
class Users{
private:

public:
	Users(){
		FILE *db;
		fopen_s(&db, "user.dat", "rb");
		if (!db)
			fopen_s(&db, "user.dat", "wb");
		fclose(db);
	}
};