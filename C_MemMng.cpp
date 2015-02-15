#include "C_MemMng.h"

C_MemMng::C_MemMng(){


	this->wait = new(OBJ_LIST);
	this->act = new(OBJ_LIST);

	this->wait->start = new(OBJECT);

	OBJECT* now = wait->start;

	for (int i = 0; i < objSum; i++){
		OBJECT* work = new(OBJECT);
		now->next = work;
		work->back = now;
		now = work;
	}
}
C_MemMng::~C_MemMng(){
	delete(wait);
	delete(act);
}

OBJECT* C_MemMng::RetEndPt(int qty){
	if (wait->start == nullptr) return nullptr;

	OBJECT* work = this->wait->start;

	for (int i = 1; i < qty; i++){
		if (work->next == nullptr) return nullptr;
		work = work->next;

	}
	return work;
}

void C_MemMng::GetObjectPtr(int qty, OBJECT* start, OBJECT* end){
	OBJECT* workE = RetEndPt(qty);
	if (workE == nullptr){
		printf("MemMngError そんなに持ってねーわ\n");
		return;
	}
	OBJECT* workS = this->wait->start;

	start = workS;
	end = workE;

	if (workE->next == nullptr){	// waitにオブジェクトが残っているかをチェック
		this->wait->start = this->wait->end = nullptr;
	} else{
		this->wait->start = workE->next;
	}

	if (act->start == nullptr){		// actにオブジェクトが存在するかチェック
		act->start = workS;
		act->end = workE;
	} else{
		act->end->next = workS;
		act->end = workE;
	}
	end->next = nullptr;

	printf("%d個上げる\n",qty);
}

void C_MemMng::RetObjectPtr(OBJECT* list){

	// actリストから対象を除外する
	if (list == act->start){					// actの先頭要素が返却された
		act->start = act->start->next;

	} else{
		OBJECT* work = this->act->start->next;
		while (1){
			if (list == work){
				work->back->next = work->next;
				work->next->back = work->back;
				break;
			}
			work = work->next;
		}
	}

	// waitリストに対象を追加する
	list->back = wait->end;
	list->next = nullptr;
	wait->end = list;

	if (wait->start == nullptr){
		wait->start = list;
	}

}

void C_MemMng::DispCnt(){
	int cnt = 0;
	OBJECT* work;

	if (wait->start != nullptr){
		work = this->wait->start;
		while (work->next != nullptr){
			work = work->next;
			cnt++;
		}
	}
	printf("wait = %d個\n", cnt);
	cnt = 0;
	if (act->start != nullptr){
		work = this->act->start;
		while (work->next != nullptr){
			work = work->next;
			cnt++;
		}
	}
	printf("act = %d個\n", cnt);


}