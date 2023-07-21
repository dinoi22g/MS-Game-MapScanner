//---------------------------------------------------------------------------
#pragma hdrstop

//-----------------------------------------------------------------
//Twms v183.2 Pointer
#define TeleportBase   	0x0193C650
#define TeleportSwitch 	0xBFC0
#define TeleportX	   	0xBFC8
#define TeleportY	   	0xBFCC

#define SystemBase 		0x0193C644
#define SpawnX			0x7F1C
#define	SpawnY			0x7F20
#define	SpawnSwitch		0x7F24

#define MapBase			0x0194C4C4
#define MapID			0x17c0

#define CharBase		0x0194C4C4
#define CharX			0x1678
#define CharY			0x167C
//------------------------------------------------------------------

//------------------------------------------------------------------
//Read in define
#define My_X ReadPointer(CharBase,CharX);
#define My_Y ReadPointer(CharBase,CharY);
#define My_MapID ReadPointer(MapBase,MapID);
//------------------------------------------------------------------

//------------------------------------------------------------------
int ReadPointerW(unsigned long ulBase, int iOffset) {
	__try {return *(long*)(*(unsigned long*)ulBase + iOffset);}	__except (EXCEPTION_EXECUTE_HANDLER) {return NULL;} }

WritePointerW(unsigned long ulBase, int iOffset, int iValue)
{
	__try { *(int*)(*(unsigned long*)ulBase + iOffset) = iValue; return true; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

int Teleport(int x,int y,int sw){
	WritePointerW(TeleportBase,TeleportX,x);
	WritePointerW(TeleportBase,TeleportY,y);
	WritePointerW(TeleportBase,TeleportSwitch,sw);
}

int Spawn(int x,int y,int sw){
	WritePointerW(SystemBase,SpawnX,x);
	WritePointerW(SystemBase,SpawnY,y);
	WritePointerW(SystemBase,SpawnSwitch,sw);
}
//------------------------------------------------------------------
