// CCalibDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CV.h"
#include "CCalibDlg.h"
#include "afxdialogex.h"
#include "CVDlg.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

// CCalibDlg 对话框

IMPLEMENT_DYNAMIC(CCalibDlg, CDialogEx)

CCalibDlg::CCalibDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALIBRATION, pParent)
	, INFO(_T("DUVHIBNI"))
	, model_W(_T(""))
	, model_H(_T(""))
	, PIC_NUM(_T(""))
{

}

CCalibDlg::~CCalibDlg()
{
}

void CCalibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CDATA, INFO);
	DDX_Text(pDX, IDC_W, model_W);
	DDX_Text(pDX, IDC_H, model_H);
	DDX_Text(pDX, IDC_NUM, PIC_NUM);
}


BEGIN_MESSAGE_MAP(CCalibDlg, CDialogEx)
	ON_BN_CLICKED(IDC_S_CALIB, &CCalibDlg::OnBnClickedSCalib)
	ON_BN_CLICKED(IDC_MODEL, &CCalibDlg::OnBnClickedModel)
	ON_BN_CLICKED(IDC_GET, &CCalibDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDC_SAVE, &CCalibDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CCalibDlg 消息处理程序


void CCalibDlg::OnBnClickedSCalib()
{
	// TODO: 在此添加控件通知处理程序代码

		CCVDlg *pdlg = CCVDlg::pTestdlg;
		INFO= pdlg->CALIB_INFO;
		GetDlgItem(IDC_CDATA)->SetWindowText(INFO);
		Mat src;
	


		/*CEdit* m_Edit = (CEdit*)GetDlgItem(IDC_CDATA);
		m_Edit->SetWindowText(_T(INFO));*/
		//GetDlgItem(IDC_EDIT)->SetWindowText(_T("123"));//等价
		//设置窗口输入字符的长度为2
		/*m_Edit->SetLimitText(2);
		INFO->GetWindowText(pdlg);*/
}


void CCalibDlg::OnBnClickedModel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCalibDlg::OnBnClickedGet()
{
	// TODO: 在此添加控件通知处理程序代码
	VideoCapture Capture(0);
	Mat frame;
	/*namedWindow("Catch", WINDOW_AUTOSIZE);
	HWND hWnd1 = (HWND)cvGetWindowHandle("Catch");
	HWND hParent1 = ::GetParent(hWnd1);
	::SetParent(hWnd1, GetDlgItem(IDC_CAP)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);
	GetDlgItem(IDC_CAP)->GetClientRect(&pic_rect1);
	width1 = pic_rect1.right;
	height1 = pic_rect1.bottom;
	Mat src1 = imread("init.jpg");
	resize(src1, src1, Size(width1, height1));
	imshow("Catch", src1);*/
	//int b = 10;
	//CString file;
	//if (!Capture.isOpened())
	//{
	//	AfxMessageBox(_T("Unable to establish link with camera！"));
	//	return;
	//}
	//if (FLAG == FALSE)
	//{
	//	AfxMessageBox(_T("Plesae turn on your device before this step!"));
	//	return;
	//}
	//AfxMessageBox(_T("Notice:Please put the calibration board in the effective range of the camera! Click the button to capture calibration board image information from the camera!"));
	//for (int i = 1; i <= b; i++)
	//{
		Capture >> frame;
		imshow("REALIMAGE", frame);
		waitKey(30);
	
}


void CCalibDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_CDATA)->GetWindowText(INFO); // 获取b对话框的值，保存在m_strB中

	//CCVDlg dlg;
	
	//dlg.CALIB_INFO = INFO; // m_strA是a编辑框关联的变量，m_strB是b对话框关联的变量 
	//GetDlgItem(IDC_INFO)->SetWindowText("123");
	//UpdateData(TRUE);
	//dlg.OnInitDialog();
	
}
