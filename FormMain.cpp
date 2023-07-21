//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "Function.cpp"
#include "MapFunctions.h"
#include "CommonFunction.cpp"
#include "Pointer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
int pID_n;
String MyPath = ::ExtractFilePath(Application->ExeName);
long NowID;

bool StatusText(int index){
	String str;
	switch (index) {
	   case 0:
		  str = "�a�Ϫ�l�ƿ��~�I";
		  break;
	   case 1:
		  str = "�C�X�i��a�ϥX���I";
		  break;
	   case 2:
		  str = "�j�M���|�L�{�X���I";
		  break;
	   case 3:
		  str = "���|�w���\�C�X�I";
		  break;
	   case 4:
		  str = "��l�Ʀ��\�I";
		  break;
	   case 5:
		  str = "�a�Ϸj�M���\�I";
		  break;
	}
	Form1->lblStatus->Caption = "���A : " + str;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmrGetProcessTimer(TObject *Sender)
{
	GetMapleStoryDelhProcessByWindowName();
	if (pID_n != pID){
		GetMapleStoryByWindowName();
		pID_n = pID;
		this->Caption = IntToStr((int)pID) + "," +  IntToStr((int)hProcess);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	this->Caption =  MyPath;
	if (!FileExists(MyPath + "\\Map.dat") || !FileExists(MyPath + "\\Map.ini")) {
		StatusText(0);
		Application->Terminate();
	}
	InitMapList(AnsiString(MyPath + "\\Map.dat").c_str(), AnsiString(MyPath + "\\Map.ini").c_str());
	StatusText(4);
}
//---------------------------------------------------------------------------
long EnumProc(char *Name, long MapId, void *Param)
{
	Form1->cbMap->Items->Add(Name);
	return 1;
}
long nowmap;
void __fastcall TForm1::btnScanMapClick(TObject *Sender)
{
	long Mapd = ReadPointer(MapBase,MapID);
	NowID =  ReadPointer(MapBase,MapID);
	nowmap = ReadPointer(MapBase,MapID);
	try {
		Form1->cbMap->Items->Clear();
		EnumPossibleMap(Mapd, EnumProc, NULL);
		StatusText(5);
	} catch (...) {
		StatusText(1);
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbMapChange(TObject *Sender)
{
	if (cbMap->ItemIndex != -1) {
		try {
			long Start = NowID;
			long End = GetMapId(AnsiString(cbMap->Items->Strings[cbMap->ItemIndex]).c_str());
			long *path = SearchPath(Start, End);
			long *tmp = path;
			POINT pt;
			lsvMap->Items->Clear();
			String name;
			while(*tmp != End) {
				if(GetTeleportPoint(*tmp, *(tmp+1), &pt))
				name = GetMapName(*tmp);

				//-----------------------------------------
				TListItem *item;
				item = lsvMap->Items->Add();
				item->Caption = name;
				item->SubItems->Add(IntToStr((int)pt.x));
				item->SubItems->Add(IntToStr((int)pt.y));
				//-----------------------------------------
				tmp++;
			}
			delete path;
			StatusText(3);
		} catch (...) {
			StatusText(2);
		}
	}
}
//---------------------------------------------------------------------------

int gc,teleporttime;
int tx,ty;
void __fastcall TForm1::MapTelePortTimerTimer(TObject *Sender)
{
	if(gc == teleporttime)
	{
		teleporttime = teleporttime + 1;
		nowmap = ReadPointer(MapBase,MapID);
		tx = StrToInt(lsvMap->Items->Item[gc]->SubItems[0].Strings[0]);
		ty = StrToInt(lsvMap->Items->Item[gc]->SubItems[0].Strings[1]);
		Teleport(tx-5,ty-5,1);

		ChangeMapTimer->Enabled = true;
	}
	if(lsvMap->Items->Count == teleporttime - 1)
		MapTelePortTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeMapTimerTimer(TObject *Sender)
{
	if(ReadPointer(TeleportBase,TeleportSwitch) == 0)
	{
		MyPostMessage(38);
		if (nowmap != ReadPointer(MapBase,MapID))
		{
			gc += 1;
			ChangeMapTimer->Enabled = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	MapTelePortTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	MapTelePortTimer->Enabled = false;
}
//---------------------------------------------------------------------------

