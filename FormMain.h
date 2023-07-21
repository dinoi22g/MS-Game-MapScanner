//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *tmrGetProcess;
	TComboBox *cbMap;
	TLabel *Label1;
	TButton *btnScanMap;
	TListView *lsvMap;
	TLabel *lblStatus;
	TTimer *MapTelePortTimer;
	TTimer *ChangeMapTimer;
	TButton *Button1;
	TButton *Button2;
	void __fastcall tmrGetProcessTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnScanMapClick(TObject *Sender);
	void __fastcall cbMapChange(TObject *Sender);
	void __fastcall MapTelePortTimerTimer(TObject *Sender);
	void __fastcall ChangeMapTimerTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
