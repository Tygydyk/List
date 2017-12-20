# List
п»ї#include <sstream>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
using namespace std;

struct List {
	int value;
	List* next;
};

List* create(int value) { // РЎРѕР·РґР°С‚СЊ СЃРїРёСЃРѕРє
	List* res = new List;
	res->value = value;
	res->next = 0;
	return res;
}

List * add(List* l, int value) { // Р”РѕР±Р°РІРёС‚СЊ СЌР»РµРјРµРЅС‚
	List* n = new List;
	n->value = value;
	n->next = 0;

	List* it = l;
	if (l == 0) {
		return n;
	}
	while (it->next != 0)
		it = it->next;
	it->next = n;
	return l;
}

bool find(List* l, int value, int* out, int counter=0) {
	if (l == 0)
		return false;
	if (l->value == value) {
		*out = counter;
		return true;
	}
	return find(l->next, value, out, counter + 1);
}

void printfind(List* l, int value, int counter = 0) {
	if (l == 0) return;
	if (l->value == value) {
		wcout << counter << L" ";
	}
	printfind(l->next, value, counter + 1);
}

List* del(List*l, int value) { // РЈРґР°Р»РµРЅРёРµ СЌР»РµРјРµРЅС‚Р°
	if (l == 0) {
		wcout << L"Р­Р»РµРјРµРЅС‚ " << value << L" РѕС‚СЃСѓС‚СЃС‚РІСѓРµС‚";
		return l;
	}
	if (l->value == value) {
		List* res = l->next;
		delete l;
		return res;
	}
	List* it = l;
	while (it->next != 0) {
		if (it->next->value == value) {
			List* res = it->next;
			it->next = res->next;
			delete res;
			return l;
		}
		it = it->next;
	}
	wcout << L"Р­Р»РµРјРµРЅС‚ " << value << L" РѕС‚СЃСѓС‚СЃС‚РІСѓРµС‚";
	return l;
}

void set(List*l, int index, int value) {// РЈСЃС‚Р°РЅРѕРІРєР° СЌР»-С‚Р°
	if (l == 0)
		return;
	if (index == 0) {
		l->value = value;
		return;
	}
	set(l->next, index - 1, value);
}


void print(List* l) {
	if (l == 0) {
		wcout << "List empty\n";
	}
	else {
		while (true) {
			wcout << l->value;
			l = l->next;
			if (l == 0)
				return;
			wcout << "->";
		}
	}
}

void find_minimum(List* l,int* outindex, int*outvalue) {
	int min = l->value;
	int minindex = 0;
	int i = 0;
	while (l != 0) {
		if (l->value < min) {
			min = l->value;
			minindex = i;
		}
		l = l->next;
	}
	*outindex = minindex;
	*outvalue = min;
}

List* sort(List* head) { // РЎРѕСЂС‚РёСЂРѕРІР°РєР° РІСЃС‚Р°РІРєР°РјРё
	List* l = 0;

	while (head != 0) {
		int minindex, minvalue;
		find_minimum(head, &minindex, &minvalue);
		l = add(l, minvalue);
		head = del(head, minvalue);
	}
	return l;
}

int main(int argc, char *argv[]) {
	_setmode(_fileno(stdout), _O_WTEXT); // Р”Р»СЏ РѕС‚РѕР±СЂР°Р¶РµРЅРёСЏ СЂСѓСЃСЃРєРѕРіРѕ

	List* l = 0;
	for (int i = 1; i < argc; i++) { // РЎС‡РёС‚С‹РІР°РµРј Р°СЂРіСѓРјРµРЅС‚С‹
		int value;
		istringstream ss(argv[i]);
		ss >> value;
		l = add(l, value); // Р”РѕР±Р°РІР»СЏРµС‚ РІ СЃРїРёСЃРѕРє
	}

	while (true) { // Р‘РµСЃРєРѕРЅРµС‡РЅРѕ РїСЂРµРґР»Р°РіР°РµРј РІР°СЂРёР°РЅС‚С‹ РјРµРЅСЋ
		wcout << L"\n1. Р Р°СЃРїРµС‡Р°С‚Р°С‚СЊ СЃРїРёСЃРѕРє\n2. Р”РѕР±Р°РІРёС‚СЊ СЌР»РµРјРµРЅС‚С‹ РІ СЃРїРёСЃРѕРє\n3. РЈРґР°Р»РёС‚СЊ СЌР»РµРјРµРЅС‚\n4. РќР°Р№С‚Рё РїРѕР·РёС†РёРё СЌР»РµРјРµРЅС‚РѕРІ\n";
		wcout << L"5. Р—Р°РјРµРЅРёС‚СЊ СЌР»РµРјРµРЅС‚ РЅР° РґСЂСѓРіРѕР№\n6. РћС‚СЃРѕСЂС‚РёСЂРѕРІР°С‚СЊ СЌР»РµРјРµРЅС‚С‹ СЃРїРёСЃРєР°\n7. Р—Р°РІРµСЂС€РёС‚СЊ СЂР°Р±РѕС‚Сѓ РїСЂРѕРіСЂР°РјРјС‹\n";
		int cmd;
		cin >> cmd; // РЎС‡РёС‚С‹РІР°РµРј РєРѕРјР°РЅРґСѓ

		if (cmd == 1) {
			print(l); // Р Р°СЃРїРµС‡Р°С‚Р°С‚СЊ СЃРїРёСЃРѕРє
		}
		else if (cmd == 2) {
			wcout << L"Р’РІРµРґРёС‚Рµ СЌР»РµРјРµРЅС‚С‹:\n";
			int c;
			string line;
			std::getline(cin, line); // РџСЂРѕРїСѓСЃРєР°РµРј РїРµСЂРµРІРѕРґ СЃС‚СЂРѕРєРё
			std::getline(cin, line); // РЎС‡РёС‚С‹РІР°РµРј СЃС‚СЂРѕРєСѓ
			std::istringstream iss(line);
			while (iss >> c) {
				l = add(l, c); // Р”РѕР±Р°РІР»СЏРµРј РІ СЃРїРёСЃРѕРє
			}
		}
		else if (cmd == 3) {
			wcout << L"Р’РІРµРґРёС‚Рµ Р·РЅР°С‡РµРЅРёРµ СЌР»РµРјРµРЅС‚Р° :\n";
			int elem;
			cin >> elem; // РЎС‡РёС‚С‹РІР°РµРј СЌР»РµРјРµРЅС‚
			l = del(l, elem); // РЈРґР°Р»СЏРµРј
		}
		else if (cmd == 4) {
			wcout << L"Р’РІРµРґРёС‚Рµ Р·РЅР°С‡РµРЅРёРµ СЌР»РµРјРµРЅС‚Р° :\n";
			int elem;
			cin >> elem; // РЎС‡РёС‚С‹Р°РµРј СЌР»РµРјРµРЅС‚
			printfind(l, elem); // РС‰РµРј РїРѕР·РёС†РёРё
		}
		else if (cmd == 5) {
			wcout << L"Р’РІРµРґРёС‚Рµ РїРѕР·РёС†РёСЋ Рё РЅРѕРІРѕРµ Р·РЅР°С‡РµРЅРёРµ:\n";
			int elem, value;
			cin >> elem >> value; // РЎС‡РёС‚С‹РІР°РµРј РїРѕР·РёС†РёСЋ Рё Р·РЅР°С‡РµРЅРёРµ
			set(l, elem, value); // РЈСЃС‚Р°РЅР°РІР»РёРІР°РµРј
		}
		else if (cmd == 6) {
			l = sort(l); // РЎРѕСЂС‚РёСЂРѕРІРєР°
		}
		else if (cmd == 7) {
			wcout << L"Р’С‹ С…РѕС‚РёС‚Рµ РІС‹Р№С‚Рё РёР· РїСЂРѕРіСЂР°РјРјС‹ ? (y, n) :\n";
			string yN;
			cin >> yN;
			if (yN == "y" || yN == "Y" || yN == "Yes" || yN == "yes" )
				return 0;
		}

	}
	return 0;
}
