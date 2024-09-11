//---------------------------------------------------------------------------

#ifndef SystemMonitoringH
#define SystemMonitoringH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp> // For TCanvas and drawing
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "perfgrap.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TLabel *Label4;
	TEdit *Edit2;
	TLabel *Label6;
	TProgressBar *ProgressBar1;
	TEdit *Edit3;
	TLabel *Label8;
	TLabel *Label9;
	TProgressBar *ProgressBar3;
	TEdit *Edit4;
	TEdit *Edit5;
	TButton *Button1;
	TButton *Button2;
	TMemo *Memo1;
	TLabel *Label13;
	TMemo *Memo2;
	TLabel *Label14;
	TMainMenu *MainMenu1;
	TMenuItem *F1;
	TMenuItem *Monitor1;
	TMenuItem *Monitor2;
	TMenuItem *SaveAs1;
	TMenuItem *SaveAs2;
	TMenuItem *SaveReport1;
	TMenuItem *SaveReport2;
	TMenuItem *PreferencesSettings1;
	TMenuItem *PreferencesSettings2;
	TMenuItem *CPUUsage1;
	TMenuItem *CPUUsage2;
	TMenuItem *DiskUsage1;
	TMenuItem *DiskUsage2;
	TMenuItem *GPUUsage1;
	TMenuItem *GPUUsage2;
	TMenuItem *FanSpeeds1;
	TMenuItem *FanSpeeds2;
	TMenuItem *PowerUsage1;
	TMenuItem *view1;
	TMenuItem *ShowHideComponents1;
	TMenuItem *ShowHideComponents2;
	TMenuItem *DarkModeLightMode1;
	TMenuItem *DarkModeLightMode2;
	TMenuItem *FullScreen1;
	TMenuItem *FullScreen2;
	TMenuItem *askManager1;
	TMenuItem *askManager2;
	TMenuItem *Benchmarking1;
	TMenuItem *Benchmarking2;
	TMenuItem *Diagnostics1;
	TMenuItem *Diagnostics2;
	TMenuItem *Documentation1;
	TMenuItem *Documentation2;
	TMenuItem *About1;
	TMenuItem *About2;
	TMenuItem *Support1;
	TPanel *Panel1;
	TTimer *Timer1;
	TTimer *Timer2;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Edit4Change(TObject *Sender);



void __fastcall Timer1Timer(TObject *Sender);


private:	// User declarations


public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
