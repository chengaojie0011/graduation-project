
// WaterDivision3Dlg.h : header file

#include "highgui.h"
#include "CvvImage.h"
#include <CString>
#include "cv.h"
#include "cxcore.h"
using namespace std;

#pragma once


// CWaterDivision3Dlg dialog
class CWaterDivision3Dlg : public CDialogEx
{
// Construction
public:
	CWaterDivision3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WATERDIVISION3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenButton();

	//myself
	void ShowImage(IplImage * pImage, int ID);

	void ShowPic(IplImage *img);

	CString m_filename;

	IplImage *  oriimg;
	IplImage *  transimg;
	CRect  mypicrect;

	IplImage * m_firstImage;

	IplImage * m_grayImage;

	IplImage * m_targetImage;
	IplImage * m_rayImage;
	IplImage * m_cutImage;
	IplImage * m_preprocessImage;

	int T1;
	int T2;
	//afx_msg void OnEnChangeT1();
	int T3;
	int T4;
	int i, j, height, width, p, height_cut, width_cut;
	CvPoint p1, p2;
	afx_msg void OnCut();
	afx_msg void OnErzhi();
	afx_msg void OnPreprocess();
	afx_msg void OnRect();
	//	afx_msg void OnCut1();
	afx_msg void OnCut1();


	afx_msg void OnBnClickedLinebutton();
};
