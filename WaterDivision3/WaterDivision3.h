
// WaterDivision3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWaterDivision3App:
// See WaterDivision3.cpp for the implementation of this class
//

class CWaterDivision3App : public CWinApp
{
public:
	CWaterDivision3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWaterDivision3App theApp;