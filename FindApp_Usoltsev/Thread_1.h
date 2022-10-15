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
	TButton *OpenDiskButton;
	TLabel *Label3;
	void __fastcall OpenDiskButtonClick(TObject *Sender);

private:
	
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

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
