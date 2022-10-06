//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"

#include <string>
#include <string.h>
#include "sqlite3.h"
//---------------------------------------------------------------------------

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *VirtualStringTree1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall Button2Click(TObject *Sender);

public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};

//---------------------------------------------------------------------------

extern PACKAGE TForm2 *Form2;

//---------------------------------------------------------------------------

typedef struct
{
	int id;
	UnicodeString origin;
	UnicodeString name;
	UnicodeString description;
} TreeNodeStruct;
#endif
