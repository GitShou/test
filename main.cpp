#include <Windows.h>
#include "C_MemMng.h"


void main(void){
	bool isEnd = false;
	int num;
	C_MemMng* memMng = new(C_MemMng);

	OBJ_LIST* list = new(OBJ_LIST);

	memMng->DispCnt();

	while (!isEnd){
		printf("番号入力して 0 = 終わる, 1 = 欲しい, 2 = 返す)\n");
		//scanf_s(&btn, sizeof(char));

		cin >> num;

		switch ((int)num){
		case 0:
			isEnd = true;
			break;
		case 1:
			printf("いくつ欲しい？\n");
			cin >> num;
			memMng->GetObjectPtr(num, list);
			memMng->DispCnt();

			break;
		case 2:
			memMng->RetObjectPtr(list->start);
			list->start = list->start->next;
			printf("先頭を返した\n");

			break;

		default:
			printf("有効な番号を入力して\n");
			break;
		}
	}

	delete(memMng);
	delete(list);
}