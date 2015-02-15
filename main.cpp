#include <Windows.h>
#include "C_MemMng.h"


void main(void){
	bool isEnd = false;
	int num;
	C_MemMng* memMng = new(C_MemMng);

	OBJ_LIST* list = new(OBJ_LIST);

	memMng->DispCnt();

	while (!isEnd){
		printf("”Ô†“ü—Í‚µ‚Ä 0 = I‚í‚é, 1 = —~‚µ‚¢, 2 = •Ô‚·)\n");
		//scanf_s(&btn, sizeof(char));

		cin >> num;

		switch ((int)num){
		case 0:
			isEnd = true;
			break;
		case 1:
			printf("‚¢‚­‚Â—~‚µ‚¢H\n");
			cin >> num;
			memMng->GetObjectPtr(num, list);
			memMng->DispCnt();

			break;
		case 2:
			memMng->RetObjectPtr(list->start);
			list->start = list->start->next;
			printf("æ“ª‚ğ•Ô‚µ‚½\n");

			break;

		default:
			printf("—LŒø‚È”Ô†‚ğ“ü—Í‚µ‚Ä\n");
			break;
		}
	}

	delete(memMng);
	delete(list);
}