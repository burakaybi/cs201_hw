
// burakaybi_Aybi_Burak_hw8.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cburakaybi_Aybi_Burak_hw8App:
// See burakaybi_Aybi_Burak_hw8.cpp for the implementation of this class
//

class Cburakaybi_Aybi_Burak_hw8App : public CWinApp
{
public:
	Cburakaybi_Aybi_Burak_hw8App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cburakaybi_Aybi_Burak_hw8App theApp;