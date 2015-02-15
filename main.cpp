using namespace std;
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "C_MemMng.h"


void main(void){
	bool isEnd = false;
	int num;
	C_MemMng* memMng = new(C_MemMng);

	OBJ_LIST* list = new(OBJ_LIST);

	memMng->DispCnt();

	while (!isEnd){
		printf("ボタン押して(0 = 終わる, 1 = 欲しい, 2 = 返す)\n");
		//scanf_s(&btn, sizeof(char));

		cin >> num;

		switch ((int)num){
		case 0:
			isEnd = true;
			break;
		case 1:
			printf("いくつ欲しい？\n");
			cin >> num;
			memMng->GetObjectPtr(num, list->start, list->end);
			memMng->DispCnt();

			break;
		case 2:
			memMng->RetObjectPtr(list->start);
			list->start = list->start->next;
			printf("先頭を返した\n");

			break;
		}
	}

	delete(memMng);
	delete(list);
}