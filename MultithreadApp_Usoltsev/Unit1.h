//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class Read_Thread : public TThread
{
private:
	class ProcessThread *ProcessThreadPtr;
	TEvent* MyEvent;
protected:
	void __fastcall Execute();
public:
	__fastcall Read_Thread(bool CreateSuspended);
    BYTE dataBuffer;
};
//---------------------------------------------------------------------------
#endif
