
// WaterDivision3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "WaterDivision3.h"
#include "WaterDivision3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaterDivision3Dlg dialog



CWaterDivision3Dlg::CWaterDivision3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WATERDIVISION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaterDivision3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWaterDivision3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CWaterDivision3Dlg::OnBnClickedOpenButton)
	
	ON_BN_CLICKED(IDC_LINEBUTTON, &CWaterDivision3Dlg::OnBnClickedLinebutton)
END_MESSAGE_MAP()


// CWaterDivision3Dlg message handlers

BOOL CWaterDivision3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWaterDivision3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWaterDivision3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWaterDivision3Dlg::OnQueryDragIcon()
{	
	return static_cast<HCURSOR>(m_hIcon);
}



void CWaterDivision3Dlg::OnBnClickedOpenButton()
{
	// TODO: 在此添加控件通知处理程序代码


	//打开图像文件

	//弹出选择图片对话框 
	CFileDialog  dlg(true, _T("*.bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, _T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"), NULL);
	dlg.m_ofn.lpstrTitle = _T("open Image");
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	m_filename = dlg.GetPathName();
	m_filename.Replace(_T("//"), _T("////"));
	m_firstImage = cvLoadImage((CT2CA)m_filename, 1);

	

	ShowImage(m_firstImage, IDC_IMAGE);
}

/*显示图像*/
void  CWaterDivision3Dlg::ShowImage(IplImage * pImage, int ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	//HDC hdc = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage img;
	img.CopyOf(pImage);
	img.DrawToHDC(pDC->GetSafeHdc(), &rect);
	// DC必须Release掉，否则将会出现资源泄露
	ReleaseDC(pDC);

}




/*通过hough变换进行海天线检测*/
void CWaterDivision3Dlg::OnBnClickedLinebutton()
{
	// TODO: 在此添加控件通知处理程序代码

	//为m_grayImage 创建首地址并分配存储空间
	m_grayImage = cvCreateImage(cvGetSize(m_firstImage), IPL_DEPTH_8U, 1);
	height = m_firstImage->height;
	width = m_firstImage->width;
	m_rayImage = cvCreateImage(cvGetSize(m_firstImage), m_firstImage->depth, 3);


	//灰度化处理
	cvCvtColor(m_firstImage, m_grayImage, CV_RGB2GRAY);

	cvCvtColor(m_grayImage, m_rayImage, CV_GRAY2BGR);
	
		
	int * sum = new int[height];
	int * avg = new int[height];
	int * davg = new int[height - 1];
	int maxd, p，pr;


	for (i = 0; i<height; i++)
	{
		//Img->imageData + Img->widthStep*pt.y是该像素点所在行的首地址
		unsigned char *pimg = (unsigned char *)(m_grayImage->imageData + i*m_grayImage->widthStep);
		sum[i] = 0;
		
		for (j = 0; j<width; j++)
		{
			sum[i] = sum[i] + pimg[j];
		}

		avg[i] = (int)(sum[i] / width);
		if (i>0)
		{
			davg[i - 1] = abs(avg[i] - avg[i - 1]);
		}
	}

	maxd = davg[0];
	for (i = 0; i<height - 1; i++)
	{
		if (davg[i]>maxd)
		{
			p = i;
			maxd = davg[i];
		}
	}





	p1.x = 0;
	p1.y = p + 1;
	p2.x = width;
	p2.y = p + 1;

	//p1.p2直线的起点终点
	cvLine(m_rayImage, p1, p2, CV_RGB(0, 255, 0), 1, 8, 0);
	ShowImage(m_rayImage, IDC_LINEIMAGE);
}
