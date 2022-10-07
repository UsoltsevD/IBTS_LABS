//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include <string>
#include <string.h>
#include "sqlite3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm2 *Form2;

char* intToStr(int data);
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(TreeNodeStruct);  //������� ������� ����
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{

	VirtualStringTree1->Clear(); //������� ���� ������

	sqlite3* DataBase;  //���������� ����������

	int openResult = sqlite3_open16(L"..\\..\\Database\\Databases.db", &DataBase);  //�������� ���� ������

	//��������� ������
	if(openResult != 0)
	{
		Application->MessageBox(L"������ � �������� ���� ������.",L"������!", MB_OK);
		return;
	}

	sqlite3_stmt *pStatement;

	int result = sqlite3_prepare16_v2(DataBase, L"Select * FROM Databases", -1, &pStatement, NULL); //���������� �������

	//��������� ������
	if(result != SQLITE_OK)
	{
		Application->MessageBox(L"������ � ������� � ���� �����.",L"������!", MB_OK);
		return;
	}

	for (int  i = 0;;i++)  //���������� �������
	{
		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE) break;

        PVirtualNode entryNode = VirtualStringTree1->AddChild(VirtualStringTree1->RootNode);    //�������� ����
		TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1->GetNodeData(entryNode);   //���������� ������ ����

		//����� ����������� �������� ������� � ���� ������
		unsigned int val = sqlite3_column_int(pStatement,0);
		nodeData->id = val;

		wchar_t *wstr = (wchar_t*)sqlite3_column_text16(pStatement,1);
		nodeData->origin = wstr;

		wstr = (wchar_t*)sqlite3_column_text16(pStatement,2);
		nodeData->name = wstr;

		wstr = (wchar_t*)sqlite3_column_text16(pStatement,3);
		nodeData->description = wstr;
	};

	sqlite3_finalize(pStatement);    //���������� ��������� �������

	sqlite3_close(DataBase);        //�������� ���� ������

}
//---------------------------------------------------------------------------
void __fastcall TForm2::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

		//���������� ������ ������� � ���� ������ �� �������� � ���� ������
{
	if(!Node)return;
	TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1->GetNodeData(Node);
	switch(Column)
	{
		case 0:
		{
			CellText = UnicodeString(nodeData->id); break;
		}
		case 1:
		{
			CellText = UnicodeString(nodeData->origin); break;
		}
		case 2:
		{
			CellText = UnicodeString(nodeData->name); break;
		}
		case 3:
		{
			CellText = UnicodeString(nodeData->description); break;
		}
	};
}
//---------------------------------------------------------------------------
void __fastcall TForm2::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
	TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1->GetNodeData(Node);
	Edit1->Text = nodeData->origin;       //����� ���������� � ������ "��������"
	Edit2->Text = nodeData->description;  //����� ���������� � ������ "��������"
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender) //������ ������� �������
{
	VirtualStringTree1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender) //������ �������� ������
{
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;
	VirtualStringTree1->DeleteNode(selectedNode);        //�������� ������ �� ���� ������
	int selectedNodeIndex = selectedNode->Index;         //��������� ������ ����

	sqlite3* DataBase;
	int openResult = sqlite3_open16(L"..\\..\\Database\\Databases.db", &DataBase);  //�������� ���� ������

	//��������� ������
	if(openResult != 0)
	{
		Application->MessageBox(L"������ � �������� ���� ������.",L"������!", MB_OK);
		return;
	}

	selectedNodeIndex = selectedNodeIndex + 1;
	char *buf = intToStr(selectedNodeIndex);
	char *res = strcat("DELETE FROM Databases WHERE id = ", buf);  //���������� �������

	int deleteRes =  sqlite3_exec(DataBase, res, NULL, NULL , NULL);  //�������� ������ �� ���� ������
	sqlite3_close(DataBase);  //�������� ���� ������
}

//---------------------------------------------------------------------------
//������� �������� �� int � char
 char* intToStr(int data) {
    std::string strData = std::to_string(data);

    char* temp = new char[strData.length() + 1];
    strcpy(temp, strData.c_str());

   return temp;
}
//---------------------------------------------------------------------------

