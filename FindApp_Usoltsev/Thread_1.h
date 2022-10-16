//---------------------------------------------------------------------------

#ifndef Thread_1H
#define Thread_1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "VirtualTrees.hpp"
#include <Vcl.Grids.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.Samples.DirOutln.hpp>
#include <Vcl.ExtCtrls.hpp>


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TLabel *Label1;
	TVirtualStringTree *VirtualStringTree1;
	TButton *OpenDiskButton;
	TButton *DeleteStringButton;
	TButton *ClearDBButton;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit2;
	TLabel *Label4;
	void __fastcall OpenDiskButtonClick(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall DeleteStringButtonClick(TObject *Sender);
	void __fastcall ClearDBButtonClick(TObject *Sender);


private:
	void SQLtoDB(AnsiString str);
	class Thread2 *Thread2Ptr;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void ReloadViewDB();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct{

	unsigned long clusterNum;
	UnicodeString   name;

} TreeNodeStruct;
//---------------------------------------------------------------------------
#endif
