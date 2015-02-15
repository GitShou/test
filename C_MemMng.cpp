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
	this->wait->objSum = objSum;

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

void C_MemMng::GetObjectPtr(int qty, OBJ_LIST* outObj){
	OBJECT* workS, *workE;

	outObj->end = workE = RetEndPt(qty);
	if (outObj->end == nullptr){
		cout << "MemMngError そんなに持ってねーわ\n";
		return;
	}
	outObj->start = workS = this->wait->start;

	if (outObj->end->next == nullptr){	// waitにオブジェクトが残っているかをチェック
		this->wait->start = this->wait->end = nullptr;
	} else{
		this->wait->start = outObj->end->next;
	}

	if (this->act->objSum == 0){		// actにオブジェクトが存在するかチェック
		this->act->start = workS;
		this->act->end = workE;
	} else{
		this->act->end->next = workS;
		this->act->end = workE;
	}
	this->wait->objSum -= qty;
	this->act->objSum += qty;
	outObj->end->next = nullptr;

	cout << "%d個上げる\n",qty;
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
	act->objSum--;

	// waitリストに対象を追加する
	list->back = wait->end;
	list->next = nullptr;
	wait->end = list;

	if (wait->start == nullptr){
		wait->start = list;
	}
	wait->objSum++;

	this->DispCnt();
}

void C_MemMng::DispCnt(){

	cout << "---------- sum値 ----------\n";
	cout << "wait = " << this->wait->objSum << "個\n";
	cout << "act = " << this->act->objSum << "個\n";



	cout << "---------- リストカウント値 ----------\n";
	int cnt = 0;
	OBJECT* work;

	if (wait->start != nullptr){
		work = this->wait->start;
		while (work->next != nullptr){
			work = work->next;
			cnt++;
		}
	}
	cout << "wait = " << cnt << "個\n";
	cnt = 0;
	if (act->start != nullptr){
		work = this->act->start;
		while (work->next != nullptr){
			work = work->next;
			cnt++;
		}
	}
	cout << "act = " << cnt << "個\n";



}