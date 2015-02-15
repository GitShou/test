struct OBJECT{
public:
	bool operator == (OBJECT obj){
		if (this->a == obj.a && this->b == obj.b) return true;
		return false;
	};

	OBJECT* next;
	OBJECT* back;
	int a;
	char b;

	OBJECT(){
		next = back = nullptr;
		a = 0;
		b = 0;
	};
	~OBJECT(){ if(this != nullptr) delete(this); };
};

struct OBJ_LIST{
private:
	void del(OBJECT* list){
		while (list->next != nullptr){
			OBJECT* work;
			work = list->next;
			delete(list);
			list = work;
		}
	}

public:
	OBJECT* start;
	OBJECT* end;

	OBJ_LIST(){ 
		start = new(OBJECT);
		end = new(OBJECT);
	};
	~OBJ_LIST(){ 
		del(start);
		del(end);
		delete(this);
	};
};
