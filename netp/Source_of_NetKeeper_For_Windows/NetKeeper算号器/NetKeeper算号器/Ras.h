// Ras.h: interface for the CRas class. 
// 
////////////////////////////////////////////////////////////////////// 
 
#if !defined(AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_) 
#define AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_ 
 
#if _MSC_VER > 1000 
#pragma once 
#include "NetKeeper�����Dlg.h"
#endif // _MSC_VER > 1000 
 
#include <ras.h>
#pragma comment(lib, "rasapi32") 
 

 
class CRas : public CObject   
{ 
public: 
	BOOL Dail(LPCTSTR entry, LPCTSTR phone, LPCTSTR user,  
				LPCTSTR pass, LPCTSTR domain); 
	CRas(CNetKeeper�����Dlg* dlg); 
	virtual ~CRas(); 
	friend void WINAPI RasDialFunc(UINT, RASCONNSTATE, DWORD); 
 
protected: 
	RASDIALPARAMS	RasDialParams; 
	RASCONNSTATUS	RasConnStatus; 
	HRASCONN		m_hRasConn; 
	CNetKeeper�����Dlg*	m_dlg; 
}; 
 
#endif // !defined(AFX_RAS_H__4D51D463_1378_40BB_947E_AB39AF053216__INCLUDED_) 