#pragma once

//#include "CorDebugManagedCallback2.h"
#include "MyIcorDebugDataTarget.h"
#include "MyICLRDebuggingLibraryProvider.h"
#include "pipe.h"

#define CMD_TARGETPROCESS 0
#define CMD_CLOSEPROCESSANDQUIT 1
#define CMD_RELEASEOBJECTHANDLE 2
#define CMD_ENUMDOMAINS 3
#define CMD_ENUMMODULELIST 4
#define CMD_ENUMTYPEDEFS 5
#define CMD_GETTYPEDEFMETHODS 6
#define CMD_GETADDRESSDATA 7

#define CMD_GETALLOBJECTS 8
#define CMD_GETTYPEDEFFIELDS 9
#define CMD_GETMETHODPARAMETERS 10

#define CMD_GETTYPEDEFPARENT 11



class CPipeServer : Pipe
{
private:
	TCHAR pipename[255];
	//HANDLE pipe;
	ULONG processid;
	HANDLE processhandle;
	ICLRDebugging *CLRDebugging = NULL;
	ICLRDebugging *CLRDebuggingCore = NULL;
	ICorDebugProcess *CorDebugProcess;
	ICorDebugProcess5 *CorDebugProcess5;

	CMyICLRDebuggingLibraryProvider *libprovider;
	CMyIcorDebugDataTarget *datacallback;


	std::map<ICorDebugModule* , IMetaDataImport*> moduleMetaData;

	


	IMetaDataImport *getMetaData(ICorDebugModule *module);

	BOOL OpenOrAttachToProcess(void);
	void enumDomains(void);
	void enumModules(UINT64 hDomain);
	void getTypeDefParent(UINT64 hModule, mdTypeDef TypeDef);
	void enumTypeDefs(UINT64 hModule);
	void enumTypeDefMethods(UINT64 hModule, mdTypeDef TypeDef);
	void enumMethodParameters(UINT64 hModule, mdMethodDef MethodDef);
	void enumTypeDefFields(UINT64 hModule, mdTypeDef TypeDef);
	void getAddressData(UINT64 Address);
	int getAllFields(COR_TYPEID cortypeid, COR_TYPE_LAYOUT layout, std::vector<COR_FIELD> *fieldlist);
	void releaseObjectHandle(UINT64 hObject);
	void enumAllObjects(void);

	void test(void);

	void sendType(COR_TYPEID cortypeid);

public:
	CPipeServer(TCHAR *name);
	~CPipeServer(void);

	int Start(void);
};
