#pragma warning(disable:4996)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;

int Num;
int XZ;

void jm();//界面
void dy();//打印
void tj();//添加
void bf();//备份
void dkfz();//打开复制
void dk(char InternetSite[]);//打开
void fz(char Text[]);//复制
void sc();//删除
int xz();//选择
int gn();//功能
void gotoxy(int x, int y);//移动光标

int main()
{
	HANDLE p = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(p, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(p, &CursorInfo);
	system("title 0.7.190605z");
	srand((unsigned)time(NULL));
	int n = rand() % 7;
	switch (n)
	{
	case 1:system("color 0a"); break;
	case 2:system("color 0b"); break;
	case 3:system("color 0c"); break;
	case 4:system("color 0d"); break;
	case 5:system("color 0e"); break;
	case 6:system("color 0f"); break;
	default:system("color 09"); break;
	}
	while (true)
	{
		jm();
		xz();
	}
	return 0;
}

void jm()
{
	system("cls");
	cout << "─────────────────────────────────────────────────────────────────" << endl;
	cout << endl;
	dy();
	cout << "        " << setw(3) << Num + 1 << "│ 添加" << endl;
	cout << "        " << setw(3) << Num + 2 << "│ 备份" << endl;
	cout << "        " << setw(3) << Num + 3 << "│ 退出" << endl;
	cout << endl;
	cout << "─────────────────────────────────────────────────────────────────" << endl;
}

void dy()
{
	Num = 0;
	string T, I;
	ifstream infile("Memo.txt", ios::in);
	if (!infile) return;
	infile >> T >> I;
	while (!infile.eof())
	{
		Num++;
		cout << "        " << setw(3) << Num << "│ " << T << endl;
		infile >> T >> I;
	}
	infile.close();
}

void tj()
{
	string T, I;
	gotoxy(1, Num + 8);
	cout << endl;
	cout << "──────────────Please enter the text(Return enter 0)──────────────" << endl;
	cin >> T;
	if (T == "0") return;
	cout << endl;
	cout << "──────────Please enter the internet site(Empty enter 0)──────────" << endl;
	cin >> I;
	ofstream outfile("Memo.txt", ios::app);
	if (!outfile) return;
	outfile << T << endl << I << endl;
	outfile.close();
}

void bf()
{
	CopyFile("Memo.txt", "Backup.txt", false);
	gotoxy(1, Num + 8);
	cout << endl;
	cout << "─────────────────────────Backup completed────────────────────────" << endl;
	cout << endl;
	cout << "───────────────────────                   ───────────────────────" << endl;
	gotoxy(25, Num + 11);
	system("pause");
}

void dkfz()
{
	string T, I;
	ifstream infile("Memo.txt", ios::in);
	if (!infile) return;
	for (int i = 0; i < XZ; i++)
	{
		infile >> T >> I;
	}
	infile.close();
	if (I != "0")
	{
		char *Ip = (char*)I.data();
		dk(Ip);
	}
	else
	{
		char *Tp = (char*)T.data();
		fz(Tp);
	}
}

void dk(char InternetSite[])
{
	ShellExecute(NULL, "open", InternetSite, NULL, NULL, SW_SHOWNORMAL);
	exit(0);
}

void fz(char Text[])
{
	// 打开剪贴板
	if (!OpenClipboard(NULL) || !EmptyClipboard())
	{
		//printf("打开或清空剪切板出错！\n");
		return;
	}

	HGLOBAL hMen;

	// 分配全局内存
	hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(Text) + 1) * sizeof(char)));

	if (!hMen)
	{
		//printf("分配全局内存出错！\n");
		// 关闭剪切板
		CloseClipboard();
		return;
	}

	// 把数据拷贝考全局内存中
	// 锁住内存区
	LPSTR lpStr = (LPSTR)GlobalLock(hMen);

	// 内存复制
	memcpy(lpStr, Text, ((strlen(Text)) * sizeof(char)));
	// 字符结束符
	lpStr[strlen(Text)] = (char)0;
	// 释放锁
	GlobalUnlock(hMen);

	// 把内存中的数据放到剪切板上
	SetClipboardData(CF_TEXT, hMen);
	CloseClipboard();
}

void sc()
{
	string T, I;
	ifstream infile("Memo.txt", ios::in);
	if (!infile) return;
	ofstream outfile("Temp.txt", ios::out);
	if (!outfile) return;
	for (int i = 1; i <= Num; i++)
	{
		infile >> T >> I;
		if (i != XZ) outfile << T << endl << I << endl;
	}
	infile.close();
	outfile.close();
	remove("Memo.txt");
	rename("Temp.txt", "Memo.txt");
}

int xz()
{
	XZ = 1;
	char userHit;
	int n = 0;
	gotoxy(7, XZ + 2);
	cout << "〇";
	while (true)
	{
		Sleep(20);
		if (kbhit())
		{
			userHit = getch();
			switch (userHit)
			{
			case 48:case 49:case 50:case 51:case 52:case 53:case 54:case 55:case 56:case 57:
			{
				gotoxy(2, XZ + 2);
				cout << "       ";
				if (n == 0)
				{
					XZ = int(userHit) - 48;
					n++;
				}
				else
				{
					if (XZ * 10 + int(userHit) - 48 >= 1 && XZ * 10 + int(userHit) - 48 <= Num + 3)
					{
						XZ = XZ * 10 + int(userHit) - 48;
						n++;
					}
					else if (XZ / 10 * 10 + int(userHit) - 48 >= 1 && XZ / 10 * 10 + int(userHit) - 48 <= Num + 3)
					{
						XZ = XZ / 10 * 10 + int(userHit) - 48;
					}
				}
				gotoxy(2, XZ + 2);
				cout << " " << setw(3) << XZ << " 〇";
				break;
			}
			case 72:
			{
				gotoxy(2, XZ + 2);
				cout << "       ";
				if (XZ > 1 && XZ <= Num + 3) XZ--;
				else if (XZ == 1) XZ = Num + 3;
				gotoxy(2, XZ + 2);
				if (n == 0) cout << "     〇";
				else cout << " " << setw(3) << XZ << " 〇";
				break;
			}
			case 80:
			{
				gotoxy(2, XZ + 2);
				cout << "       ";
				if (XZ >= 1 && XZ < Num + 3) XZ++;
				else if (XZ == Num + 3) XZ = 1;
				gotoxy(2, XZ + 2);
				if (n == 0) cout << "     〇";
				else cout << " " << setw(3) << XZ << " 〇";
				break;
			}
			case 8:case 77:
			{
				if (n > 0)
				{
					gotoxy(2, XZ + 2);
					cout << "       ";
					if (XZ / 10 >= 1 && XZ / 10 <= Num + 3)
					{
						XZ = XZ / 10;
						n--;
						gotoxy(2, XZ + 2);
						cout << " " << setw(3) << XZ << " 〇";
					}
					else if (XZ >= 1 && (XZ <= 9 || XZ <= Num + 3))
					{
						n = 0;
						gotoxy(2, XZ + 2);
						cout << "     〇";
					}
				}
				break;
			}
			case 13:case 75:
			{
				gotoxy(2, XZ + 2);
				cout << "     ●";
				if (XZ == Num + 1)
				{
					tj();
					return -1;
				}
				if (XZ == Num + 2)
				{
					bf();
					return -2;
				}
				if (XZ == Num + 3)
				{
					exit(0);
				}
				int xz = gn();
				if (xz == -1) break;
				else return xz;
			}
			default:break;
			}
		}
		Sleep(10);
	}
}

int gn()
{
	int gn = 1;
	char userHit;
	gotoxy(2, XZ + 2);
	cout << "打开";
	while (true)
	{
		Sleep(20);
		if (kbhit())
		{
			userHit = getch();
			switch (userHit)
			{
			case 75:
			{
				gn++;
				gotoxy(2, XZ + 2);
				switch (gn % 2)
				{
				case 1:
				{
					cout << "打开";
					break;
				}
				case 0:
				{
					cout << "删除";
					break;
				}
				}
				break;
			}
			case 8:case 77:
			{
				gotoxy(2, XZ + 2);
				cout << "     〇";
				return -1;
			}
			case 13:
			{
				if (gn % 2 == 1) dkfz();
				else sc();
				gotoxy(2, XZ + 2);
				cout << "     〇";
				return gn % 2;
			}
			default:break;
			}
		}
		Sleep(10);
	}
}

void gotoxy(int x, int y)
{
	COORD p;
	p.X = x - 1;
	p.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}