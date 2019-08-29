
// CVDlg.cpp: 实现文件

#include "opencv2/opencv.hpp"
#include "stdafx.h"
#include"math.h"
#include "CV.h"
#include "CVDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;  
using namespace cv;
CCVDlg *CCVDlg::pTestdlg = NULL;  //注意要写在类外，不要写在类实现函数里面。

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
Mat frame, image; //定义一个Mat变量，用于存储每一帧的图像  
int width, height;
CRect pic_rect;
int width1, height1;
CRect pic_rect1;
int width2, height2;
CRect pic_rect2;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedGet();
	afx_msg void OnBnClickedSCalib();
	afx_msg void OnBnClickedModel();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(ID_YES, &CAboutDlg::OnBnClickedYes)
	ON_BN_CLICKED(IDC_GET, &CAboutDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDC_S_CALIB, &CAboutDlg::OnBnClickedSCalib)
	ON_BN_CLICKED(IDC_MODEL, &CAboutDlg::OnBnClickedModel)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////Main Menu
// CCVDlg 对话框

CCVDlg::CCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CV_DIALOG, pParent)
	, HEIGHT(_T(""))
	, WIDTH(_T(""))
	, CALIB_INFO(_T("NIANFI"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCVDlg::~CCVDlg()
{
}

void CCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, HEIGHT);
	DDX_Text(pDX, IDC_EDIT_WIDTH, WIDTH);

	DDX_Text(pDX, IDC_INFO, CALIB_INFO);
}

BEGIN_MESSAGE_MAP(CCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_FILE_OPEN, &CCVDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEAS, &CCVDlg::OnFileSaveas)
	ON_COMMAND(ID_ABOUT_ABOUTUS, &CCVDlg::OnAboutAboutus)
	ON_COMMAND(ID_ABOUT_CONTACT, &CCVDlg::OnAboutContact)
	ON_COMMAND(ID_INIT_ON, &CCVDlg::OnInitOn)
	ON_COMMAND(ID_INIT_OFF, &CCVDlg::OnInitOff)
	ON_COMMAND(ID_INIT_CAPTURE, &CCVDlg::OnInitCapture)
	ON_COMMAND(ID_FILE_EXIT, &CCVDlg::OnFileExit)
	ON_COMMAND(ID_DISPOSAL_ETCH, &CCVDlg::OnDisposalEtch)
	ON_COMMAND(ID_DISPOSAL_SWELL, &CCVDlg::OnDisposalSwell)
	ON_COMMAND(ID_DISPOSAL_BINARY, &CCVDlg::OnDisposalBinary)
	ON_COMMAND(ID_DISPOSAL_OPENING, &CCVDlg::OnDisposalOpening)
	ON_COMMAND(ID_DISPOSAL_CLOSING, &CCVDlg::OnDisposalClosing)
	ON_COMMAND(ID_DISPOSAL_TOPHAT, &CCVDlg::OnDisposalTophat)
	ON_COMMAND(ID_DISPOSAL_BLACK, &CCVDlg::OnDisposalBlack)
	ON_COMMAND(ID_DISPOSAL_MEDIAN, &CCVDlg::OnDisposalMedian)
	ON_COMMAND(ID_DISPOSAL_GRAY, &CCVDlg::OnDisposalGray)
	ON_COMMAND(ID_PIXEL_SOBEL, &CCVDlg::OnPixelSobel)
	ON_COMMAND(ID_PIXEL_CANNY, &CCVDlg::OnPixelCanny)
	ON_COMMAND(ID_PIXEL_LAPLACIAN, &CCVDlg::OnPixelLaplacian)
	ON_COMMAND(ID_SUBPIXEL_ZERNIKE, &CCVDlg::OnSubpixelZernike)
	ON_COMMAND(ID_FILE_NEW, &CCVDlg::OnFileNew)
	ON_COMMAND(ID_ANALYZE_SHAPE, &CCVDlg::OnAnalyzeShape)
	ON_COMMAND(ID_ANALYZE_SIZEMARKING, &CCVDlg::OnAnalyzeSizemarking)
	ON_COMMAND(ID_INITIALIZE_UNDOALLOPERATIONS, &CCVDlg::OnInitializeUndoalloperations)
	ON_COMMAND(ID_ANALYZE_OUTPUTSIZE, &CCVDlg::OnAnalyzeOutputsize)
	ON_COMMAND(ID_ADJUST_SETCAMERA, &CCVDlg::OnAdjustSetcamera)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_ON, &CCVDlg::OnBnClickedOn)
	ON_BN_CLICKED(IDC_OFF, &CCVDlg::OnBnClickedOff)
	ON_BN_CLICKED(IDC_CAPTURE, &CCVDlg::OnBnClickedCapture)
	ON_COMMAND(ID_ADJUST_CALIBRATE, &CCVDlg::OnAdjustCalibrate)
	ON_BN_CLICKED(IDC_test, &CCVDlg::OnBnClickedtest)


	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCVDlg 消息处理程序
BOOL CCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	CRect rect;
	GetClientRect(&rect); //取客户区大小   
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pTestdlg = this;  //为这个之前定义的指针变量赋值为主对话框指针
	namedWindow("REALIMAGE", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("REALIMAGE");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_RT)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	GetDlgItem(IDC_RT)->GetClientRect(&pic_rect);
	width = pic_rect.right;
	height = pic_rect.bottom;
	Mat src = imread("OFF.jpg");
	resize(src, src, Size(width, height));
	imshow("REALIMAGE", src);



		namedWindow("Catch", WINDOW_AUTOSIZE);
		HWND hWnd1 = (HWND)cvGetWindowHandle("Catch");
		HWND hParent1 = ::GetParent(hWnd1);
		::SetParent(hWnd1, GetDlgItem(IDC_CAP)->m_hWnd);
		::ShowWindow(hParent1, SW_HIDE);
		GetDlgItem(IDC_CAP)->GetClientRect(&pic_rect1);
		width1 = pic_rect1.right;
		height1 = pic_rect1.bottom;
		Mat src1 = imread("init.jpg");
		resize(src1, src1, Size(width1, height1));
		imshow("Catch", src1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
////void ShowImage(const char* winname, InputArray mat, UINT ID)
//void CCVDlg::ShowImage(const Mat &mat, UINT ID)
//{
//	//	//把CImage转化为Mat
//	//CImage image,scaledImage;
//	//Mat img,img1;
//	//	MatCImage MatCImage;
//	//	MatCImage.CImageToMat(image, img);
//	//	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
//	//	resize(img, scaledImage, Size(rect.Width(), rect.Height()));
//	//	if (!scaledImage.data)
//	//	{
//	//		MatCImage.MatToCImage(scaledImage, img1);
//	//	}
//
//
//
//	//CDC *pDC = GetDlgItem(ID)->GetDC();//根据ID获得窗口指针再获取与该窗口关联的上下文指针
//	//HDC hdc = pDC->GetSafeHdc();
//	//CRect rect;
//	//GetDlgItem(ID)->GetClientRect(&pic_rect); //获取box1客户区
//	//CWnd *pWnd = GetDlgItem(IDC_STATIC);//获得pictrue控件窗口的句柄   
//	//CDC *pDC = pWnd->GetDC();//获得pictrue控件的DC  
//	//CImage src;
//	//MatCImage MatCImage;
//	//MatCImage.MatToCImage(img, img_show);
//	//	src.Draw(pDC->m_hDC, rect); //将图片画到Picture控件表示的矩形区域    
//	//
//	//
//	//Mat src; // 定义IplImage指针变量src     
//	//src = imread("E:\\二值像素图像保存\\8_3\\aa\\7_6\\suanzi\\len图像_几种算子结果\\1_canny算子结果.bmp", -1); // 将src指向当前工程文件目录下的图像me.bmp    
//	//src.DrawToHDC(hdc, &pic_rect);
//	//ReleaseDC(pDC);
//	namedWindow("winname", WINDOW_AUTOSIZE);
//	HWND hWnd = (HWND)cvGetWindowHandle("winname");
//	HWND hParent = ::GetParent(hWnd);
//	::SetParent(hWnd, GetDlgItem(ID)->m_hWnd);
//	::ShowWindow(hParent, SW_HIDE);
//	GetDlgItem(ID)->GetClientRect(&pic_rect);
//	width = pic_rect.right;
//	height = pic_rect.bottom;
//	Mat src;
//	resize(mat, src, Size(width, height));
//	imshow("winname", src);
//}

void CCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CCVDlg::OnAboutAboutus()///////////////////////////Dialog:about&contact
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg *dlg = new CAboutDlg;//非模态
	dlg->Create(IDD_ABOUTBOX, this);    //第一个参数是对话框ID号
	dlg->ShowWindow(SW_SHOW);   // TODO: 在此添加命令处理程序代码
}
//void CCVDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//	// TODO:  在此处添加消息处理程序代码
//	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)//窗体大小发生变动。处理程序
//	{
//		float fsp[2];
//		POINT Newp; //获取现在对话框的大小
//		CRect recta;
//		GetClientRect(&recta); //取客户区大小   
//		Newp.x = recta.right - recta.left;
//		Newp.y = recta.bottom - recta.top;
//		fsp[0] = (float)Newp.x / Old.x;
//		fsp[1] = (float)Newp.y / Old.y;
//		CRect Rect;
//		int woc;
//		CPoint OldTLPoint, TLPoint; //左上角
//		CPoint OldBRPoint, BRPoint; //右下角
//		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件   
//		while (hwndChild)
//		{
//			woc = ::GetDlgCtrlID(hwndChild);//取得ID
//			GetDlgItem(woc)->GetWindowRect(Rect);
//			ScreenToClient(Rect);
//			OldTLPoint = Rect.TopLeft();
//			TLPoint.x = long(OldTLPoint.x*fsp[0]);
//			TLPoint.y = long(OldTLPoint.y*fsp[1]);
//			OldBRPoint = Rect.BottomRight();
//			BRPoint.x = long(OldBRPoint.x *fsp[0]);
//			BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
//			Rect.SetRect(TLPoint, BRPoint);
//			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
//			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
//		}
//		Old = Newp;
//	}
//
//}
void CCVDlg::OnAboutContact()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg*dlg = new CAboutDlg;//非模态
	dlg->Create(IDD_ABOUTBOX, this);    //第一个参数是对话框ID号
	dlg->ShowWindow(SW_SHOW);
}

HBRUSH CCVDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)/////////////////background
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	static CBrush gBr;
	static bool isInited = false;
	if (!isInited)
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_BG);
		gBr.CreatePatternBrush(&bitmap);
		COLORREF clearColor = -1;
		bitmap.DeleteObject();
		isInited = true;
	}
	if (pWnd == this)
	{
		pDC->SetBkMode(TRANSPARENT);
		return gBr; //主窗口背景使用这个背景刷
	}
	else
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH); //其他控件使用透明背景
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CCVDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	
	String FPathName;
	CString FilePathName;
	CString defaultDir = "";	//默认文件路径	
	//CString fileName = "cap.jpg";			//默认打开的文件	
	CString filter = "JPG Files (*.jpg)|*.jpg|Bitmap Files(*.bmp)| *.bmp|PNG Files(.png)| *.png|ALL Files(*.*)|*.*||";	//文件的类型
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		defaultDir,//默认路径
		NULL,//默认文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		filter,//文件类型
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		char *FPathName = (char*)FilePathName.GetBuffer(FilePathName.GetLength());//CString转换到char
		
		Mat srcImage = imread(FPathName);
		Mat dstImage;
		//GetDlgItem(IDC_RT)->GetClientRect(&pic_rect);
		//width = pic_rect.right;
		//height = pic_rect.bottom;
		resize(srcImage, dstImage, Size(width, height));
		imwrite("CAPTURE.jpg", dstImage);
		imwrite("MODIFY.jpg", dstImage);
		imshow("Catch", dstImage);
	}
	
}


void CCVDlg::OnFileSaveas()
{
	// TODO: 在此添加命令处理程序代码
	String FPathName;
	CString FilePathName;
	CString defaultDir = "";
	CString filter = "JPG Files (*.jpg)|*.jpg|Bitmap Files(*.bmp)| *.bmp|PNG Files(.png)| *.png|ALL Files(*.*)|*.*||";
	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		defaultDir,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		/*(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||")*/
		filter,
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		char *FPathName = (char *)FilePathName.GetBuffer(FilePathName.GetLength());//CString转换到char
		Mat srcImage=imread("MODIFY.JPG");
		Mat dstImage;
		resize(srcImage, dstImage, Size(width1, height1));
		imwrite(FPathName, dstImage);
		imshow("Catch", dstImage);
	}
	else
	{
		return;
	}

}

BOOL FLAG = FALSE;
void CCVDlg::OnInitializeUndoalloperations()
{
	// TODO: 在此添加命令处理程序代码
	Mat img = imread("CAPTURE.JPG");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	else
		imwrite("MODIFY.JPG", img);
	imshow("Catch", img);
	return;
}
//////////////////////////////////////////
//////////////////////////////////////////
void CCVDlg::OnInitOn()
{
	// TODO: 在此添加命令处理程序代码

	/*CvCapture* capture;
	capture =cvCaptureFromCAM (0);
	IplImage *frame;
	frame = cvQueryFrame(capture);
	Mat image = cvarrToMat(frame, 0, CV_8UC1);*/
	VideoCapture Capture(0);
	FLAG = TRUE;
	if (!Capture.isOpened())
	{
		AfxMessageBox(_T("Unable to establish link with camera！"));
		return;
	}
	while (FLAG == TRUE)
	{
		Capture >> frame;
		resize(frame, frame, Size(width, height));
		imshow("REALIMAGE", frame);
		waitKey(5);
	}
	return;
}


void CCVDlg::OnInitOff()
{
	// TODO: 在此添加命令处理程序代码
	if (FLAG==FALSE)
	{
		AfxMessageBox(_T("Camera off! "));
		return;
	}
	FLAG = FALSE;
	Mat src = imread("OFF.jpg");
	resize(src, src, Size(width, height));
	imshow("REALIMAGE", src);
	return;
}

		Mat dst;////////////////////////////定义所有处理过的图片名称
void CCVDlg::OnInitCapture()
{
	// TODO: 在此添加命令处理程序代码
		image = frame;
		if (FLAG == FALSE)
		{
			Mat src = imread("init.jpg");
			resize(src, src, Size(width, height));
			imshow("Catch", src);
			AfxMessageBox(_T("Camera off! "));
			return;
		}
		else
			
		imwrite("CAPTURE.jpg", image);
		resize(image,dst, Size(width, height));
		imwrite("MODIFY.JPG", dst);
		imshow("Catch", dst);
		return;
}



void CCVDlg::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	image = frame;
	if (FLAG == FALSE)
	{
		Mat src = imread("init.jpg");
		resize(src, dst, Size(width, height));
		imshow("Catch", dst);
		AfxMessageBox(_T("Camera off!"));

		return;
	}
	else
		
	imwrite("CAPTURE.jpg", image);
	resize(image, dst, Size(width, height));
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}

void CCVDlg::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg*dlg = new CAboutDlg;//非模态
	dlg->Create(IDD_EXIT, this);    //第一个参数是对话框ID号
	dlg->ShowWindow(SW_SHOW);
	
}
void CAboutDlg::OnBnClickedYes()
{
	// TODO: 在此添加控件通知处理程序代码
	//cvReleaseCapture(&capture);
	PostMessage(WM_QUIT, 0, 0);//最常用
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);//最常用
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);//最常用
	FLAG = FALSE;
	remove("CAPTURE.jpg");
	remove("MODIFY.JPG");
}


void CCVDlg::OnDisposalEtch()
{
	// TODO: 在此添加命令处理程序代码
	Mat ele = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat srcImage = imread("MODIFY.jpg");
	if (!srcImage.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	erode(srcImage, dst, ele);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}


void CCVDlg::OnDisposalSwell()
{
	// TODO: 在此添加命令处理程序代码
	Mat ele = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat srcImage = imread("MODIFY.jpg");
	if (!srcImage.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	dilate(srcImage, dst, ele);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}


	//////////////////////////////////////////////////////////
	//MORTH_CLOSE              函数做闭运算
	//MORTH_GRADIENT       函数做形态学梯度运算
	//MORTH_TOPHAT            函数做顶帽运算
	//MORTH_BLACKHAT       函数做黑帽运算
	//MORTH_DILATE              函数做膨胀运算
	//MORTH_ERODE             函数做腐蚀运算
	///////////////////////////////////////////////////////////
void CCVDlg::OnDisposalOpening()
{
	Mat img = imread("MODIFY.jpg");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	// 获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18));
	morphologyEx(img, dst, MORPH_OPEN, element);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}

void CCVDlg::OnDisposalClosing()
{
	Mat img = imread("MODIFY.jpg");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18));
	morphologyEx(img, dst, MORPH_CLOSE, element);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnDisposalTophat()
{
	Mat img = imread("MODIFY.jpg");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18));
	morphologyEx(img, dst, MORPH_TOPHAT, element);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnDisposalBlack()
{
	Mat img = imread("MODIFY.jpg");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18));
	morphologyEx(img, dst, MORPH_BLACKHAT, element);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnDisposalMedian()
{
	Mat img = imread("MODIFY.jpg");
	if (!img.data)
	{
		AfxMessageBox(_T("No preprocessing image ！"));
		return;
	}
	Mat grayImage;
	medianBlur(img, dst, 13);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}


void CCVDlg::OnDisposalGray()
{
	Mat srcImage = imread("MODIFY.jpg");
	if (!srcImage.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	cvtColor(srcImage, dst, CV_RGB2GRAY);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}

void CCVDlg::OnDisposalBinary()
{
	// TODO: 在此添加命令处理程序代码
	Mat srcImage = imread("MODIFY.jpg");
	if (!srcImage.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_RGB2GRAY);
	threshold(grayImage, dst, 100, 255, CV_THRESH_BINARY);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}

void CCVDlg::OnPixelSobel()
{
	// TODO: 在此添加命令处理程序代码
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat src = imread("MODIFY.jpg");
	Mat grayImage;
	if (!src.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	cvtColor(src, grayImage, COLOR_BGR2GRAY);
	Sobel(grayImage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	//imshow("x方向Sobel", abs_grad_x);//x方向梯度
	Sobel(grayImage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	//imshow("y方向Sobel", abs_grad_y);//x方向梯度
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnPixelCanny()
{
	// TODO: 在此添加命令处理程序代码
	Mat srcImage = imread("MODIFY.jpg");
	if (!srcImage.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	Mat edge, grayImage;
	cvtColor(srcImage, grayImage, CV_RGB2GRAY);
	medianBlur(grayImage, edge, 13);
	threshold(edge, edge, 70, 255, CV_THRESH_BINARY);
	Canny(edge, dst, 0, 30, 3);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
}


void CCVDlg::OnPixelLaplacian()
{
	Mat src, src_gray;
	src = imread("MODIFY.jpg");
	if (!src.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, dst);
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnSubpixelZernike()
{
	// TODO: 在此添加命令处理程序代码
	const double PI = 3.14159265358979323846;
	const int g_N = 7;

	Mat M00 = (Mat_<double>(7, 7) <<
		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0,
		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
		0.0807, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0807,
		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0);

	Mat M11R = (Mat_<double>(7, 7) <<
		0, -0.015, -0.019, 0, 0.019, 0.015, 0,
		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
		-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,
		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
		0, -0.015, -0.019, 0, 0.019, 0.015, 0);

	Mat M11I = (Mat_<double>(7, 7) <<
		0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,
		-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,
		-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,
		0, 0, 0, 0, 0, 0, 0,
		0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,
		0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,
		0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);

	Mat M20 = (Mat_<double>(7, 7) <<
		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,
		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
		0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,
		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);

	Mat M31R = (Mat_<double>(7, 7) <<
		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0,
		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
		-0.0190, 0.0438, 0.0390, 0, -0.0390, -0.0438, 0.0190,
		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0);

	Mat M31I = (Mat_<double>(7, 7) <<
		0, -0.0153, -0.0223, -0.019, -0.0223, -0.0153, 0,
		-0.0103, -0.0018, 0.0324, 0.0438, 0.0324, -0.0018, -0.0103,
		-0.0073, 0.0162, 0.0333, 0.039, 0.0333, 0.0162, -0.0073,
		0, 0, 0, 0, 0, 0, 0,
		0.0073, -0.0162, -0.0333, -0.039, -0.0333, -0.0162, 0.0073,
		0.0103, 0.0018, -0.0324, -0.0438, -0.0324, 0.0018, 0.0103,
		0, 0.0153, 0.0223, 0.0190, 0.0223, 0.0153, 0);

	Mat M40 = (Mat_<double>(7, 7) <<
		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0,
		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
		-0.0018, -0.0239, 0.0406, 0.0751, 0.0406, -0.0239, -0.0018,
		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0);

	Mat OriginalImage = imread("MODIFY.JPG", 0);
	if (!OriginalImage.data)
	{
		AfxMessageBox(_T("No preprocessing image！"));
		return;
	}
	Mat SubImage = OriginalImage;
	Mat NewSmoothImage, edge;
	medianBlur(OriginalImage, NewSmoothImage, 15);
	//Canny(NewSmoothImage, edge, 0, 30, 3);
	Mat NewAdaThresImage;
	adaptiveThreshold(NewSmoothImage, NewAdaThresImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 7, 4);
	vector<Point2d> SubEdgePoints;
	Mat ZerImageM00;
	filter2D(NewAdaThresImage, ZerImageM00, CV_64F, M00, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D( cannyImage, zerImageM00, CV_64F, M00, Point(-1,-1), 0, BORDER_DEFAULT);

	Mat ZerImageM11R;
	filter2D(NewAdaThresImage, ZerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D( cannyImage, zerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat ZerImageM11I;
	filter2D(NewAdaThresImage, ZerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D( cannyImage, zerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat ZerImageM20;
	filter2D(NewAdaThresImage, ZerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D( cannyImage, zerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat ZerImageM31R;
	filter2D(NewAdaThresImage, ZerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D(cannyImage, zerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat ZerImageM31I;
	filter2D(NewAdaThresImage, ZerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D(cannyImage, zerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);

	Mat ZerImageM40;
	filter2D(NewAdaThresImage, ZerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);
	//////////filter2D(cannyImage, zerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);



	int row_number = NewAdaThresImage.rows;
	int col_number = NewAdaThresImage.cols;
	//使用7个的7*7的Zernike模板（其本质是个矩阵）M00、M11R、M11I、M20、M31R、M31I、M40，分别与图像进行卷积，得到每个像素点的七个Zernike矩Z00、Z11R、Z11I、Z20、Z31R、Z31I、Z40
	//对于每个点，根据它的七个Zernike矩，求得距离参数l和灰度差参数k，当l和k都满足设定的条件时，则判读该点为边缘点，并进一步利用上述7个Zernike矩求出该点的亚像素级坐标
	//如果l或k不满足设定的条件，则该点不是边缘点，转到下一个点求解距离参数l和灰度差参数k
	for (int i = 0; i < row_number; i++)
	{
		for (int j = 0; j < col_number; j++)
		{
			if (ZerImageM00.at<double>(i, j) == 0)
			{
				continue;
			}

			//compute theta
			//vector<vector<double> > theta2(0);
			double theta_temporary = atan2(ZerImageM31I.at<double>(i, j), ZerImageM31R.at<double>(i, j));
			//theta2[i].push_back(thetaTem);

			//compute Z11'/Z31'
			double rotated_z11 = 0.0;
			rotated_z11 = sin(theta_temporary)*(ZerImageM11I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM11R.at<double>(i, j));
			double rotated_z31 = 0.0;
			rotated_z31 = sin(theta_temporary)*(ZerImageM31I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM31R.at<double>(i, j));

			//compute l
			double l_method1 = sqrt((5 * ZerImageM40.at<double>(i, j) + 3 * ZerImageM20.at<double>(i, j)) / (8 * ZerImageM20.at<double>(i, j)));
			double l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
			double l = (l_method1 + l_method2) / 2;
			//compute k/h
			double k, h;

			k = 3 * rotated_z11 / 2 / pow((1 - l_method2 * l_method2), 1.5);
			h = (ZerImageM00.at<double>(i, j) - k * PI / 2 + k * asin(l_method2) + k * l_method2*sqrt(1 - l_method2 * l_method2)) / PI;

			//judge the edge
			double k_value = 20.0;

			double l_value = sqrt(2) / g_N;

			double absl = abs(l_method2 - l_method1);
			if (k >= k_value && absl <= l_value)
			{
				Point2d point_temporary;
				point_temporary.x = j + g_N * l*cos(theta_temporary) / 2;
				point_temporary.y = i + g_N * l*sin(theta_temporary) / 2;
				SubEdgePoints.push_back(point_temporary);
			}
			else
			{
				continue;
			}
		}
	}
	//显示所检测到的亚像素边缘
	for (size_t i = 0; i < SubEdgePoints.size(); i++)
	{
		Point center_forshow(cvRound(SubEdgePoints[i].x), cvRound(SubEdgePoints[i].y));
		circle(OriginalImage, center_forshow, 1, Scalar(0, 97, 255), 1, 8, 0);
	}
	imwrite("MODIFY.jpg", OriginalImage);
	imshow("Catch", OriginalImage);
	return;
}

void CCVDlg::OnAnalyzeShape()
{
	// TODO: 在此添加命令处理程序代码
		Mat edges;  //定义转化的灰度图
		Mat src=imread("MODIFY.JPG");
		if (!src.data)
		{
			AfxMessageBox(_T("No preprocessing image！"));
				return;
		}
			cvtColor(src, edges, CV_BGR2GRAY);
			//高斯滤波
			GaussianBlur(edges, edges, Size(7, 7), 2, 2);
			vector<Vec3f> circles;//霍夫圆
			HoughCircles(edges, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
			for (size_t i = 0; i < circles.size(); i++)
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				//绘制圆心  
				circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				//绘制圆轮廓  
				circle(src, center, radius, Scalar(155, 50, 255), 3, 8, 0);
			}
			imshow("Catch", src);

			return;
	}
	/////////////////////////////////////////////////////尺寸检测
	const float g_dReferWidth =25;//参考尺寸：一元硬币尺寸mm 
	double g_dPixelsPerMetric;
	vector<vector<cv::Point>> g_vContours;
	vector<Vec4i> g_vHierarchy;
	bool g_bFirst = true;
	static cv::Point2f midpoint(cv::Point2f& ptA, cv::Point2f& ptB);//求中点 
	static float getDistance(Point2f pointA, Point2f pointB);//求距离
	static bool ContoursSortFun(vector<cv::Point> contour1, vector<cv::Point> contour2);//按照 x坐标 排序
	//////////////////////////////////////////////////////
	Point2f midpoint(Point2f& ptA, Point2f& ptB)
	{

		return Point2f((ptA.x + ptB.x)*0.5, (ptA.y + ptB.y)*0.5);

	}

	float getDistance(Point2f pointA, Point2f pointB)
	{
		float distance;
		distance = powf((pointA.x - pointB.x), 2) + powf((pointA.y - pointB.y), 2);
		distance = sqrtf(distance);
		return distance;
	}
	bool ContoursSortFun(vector<cv::Point> contour1, vector<cv::Point> contour2)
	{

		return  (contour1[0].x < contour2[0].x); // a.x < b.x;

	}
	//////////////////////////////////////////////////////
	float G_width, G_height;
void CCVDlg::OnAnalyzeSizemarking()
{
	// TODO: 在此添加命令处理程序代码

		Mat srcImage;
		Mat grayImage;
		system("color 1F");
		srcImage = imread("capture.jpg", 1);
		if (!srcImage.data)
		{
			AfxMessageBox(_T("No preprocessing image！"));
			return;
		}
		cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
		GaussianBlur(grayImage, grayImage, Size(7, 7), 0);
		Canny(grayImage, grayImage, 50, 100);
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //隔开物体
		dilate(grayImage, grayImage, element);//膨胀
		erode(grayImage, grayImage, element);//腐蚀

		//寻找轮廓
		findContours(grayImage, g_vContours, g_vHierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		std::sort(g_vContours.begin(), g_vContours.end(), ContoursSortFun);//按照从左到右 排序
		for (unsigned i = 0; i < g_vContours.size(); i++)
		{
			if (contourArea(g_vContours[i]) < 100)//面积太小 则忽略
				continue;
			RotatedRect box = minAreaRect(g_vContours[i]);

			Point2f boxPoints[4];

			box.points(boxPoints);

			Point2f pointA = midpoint(boxPoints[0], boxPoints[1]);

			Point2f pointB = midpoint(boxPoints[1], boxPoints[2]);

			Point2f pointC = midpoint(boxPoints[2], boxPoints[3]);

			Point2f pointD = midpoint(boxPoints[3], boxPoints[0]);

			circle(srcImage, pointA, 2, Scalar(0, 0, 255));

			circle(srcImage, pointB, 2, Scalar(0, 0, 255));

			circle(srcImage, pointC, 2, Scalar(0, 0, 255));

			circle(srcImage, pointD, 2, Scalar(0, 0, 255));


			line(srcImage, pointA, pointC, Scalar(255, 0, 0));

			line(srcImage, pointD, pointB, Scalar(255, 0, 0));

			double dWidth = getDistance(pointA, pointC);

			double dHeight = getDistance(pointD, pointB);

			if (g_bFirst) {

				g_dPixelsPerMetric = dWidth / g_dReferWidth; //计算像素与实际大小的比列

			//	cout << "pixelPerMetric:" << dWidth << " " << g_dReferWidth << "  " << g_dPixelsPerMetric;

				g_bFirst = false;

			}
		//	cout << "dWidth" << dWidth << "   " << dHeight << "      " << dWidth / g_dPixelsPerMetric << "    " << dHeight / g_dPixelsPerMetric;

			putText(srcImage, format("%.3f*%.3f",
					dWidth / g_dPixelsPerMetric,
					dHeight / g_dPixelsPerMetric),
					/*boxPoints[1]*/
				pointB,
				FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 0, 0));
			G_width = dWidth / g_dPixelsPerMetric;
			G_height = dHeight / g_dPixelsPerMetric;
			
			for (int i = 0; i <= 3; i++)

			{
				line(srcImage, boxPoints[i], boxPoints[(i + 1) % 4], Scalar(0, 0, 255));
			}

		}
		imwrite("measure.jpg",srcImage);
		imshow("Catch", srcImage);
		return ;
	}

void CCVDlg::OnAnalyzeOutputsize()
{
	// TODO: 在此添加命令处理程序代码
	//int length = 55;
	//CString str;
	//str.Format(_T("%f"), length);
	//int length = _ttoi(_T("15"));//字符串转整型
	//float flength = _ttof(_T("12.34")); //字符串转浮点型
		CString str1,str2;
		Mat measure = imread("measure.jpg",1);
		if (!measure.data)
		{
			/*GetDlgItem(IDC_EDIT_WIDTH)->SetWindowText(_T(""));
			CString WIDTH;
			WIDTH = "";
			UpdateData(TRUE);*/
	/*		GetDlgItem(IDC_EDIT_HEIGHT)->SetWindowText(_T(""));
			str1=(_T(" "));str2=(_T(" "));
			WIDTH.SetWindowText(str1);HEIGHT.SetWindowText(str2);*/
			MessageBox("No preprocessing image!");
			return;
		}
		
		
			//str1 = (_T("")); str2 = (_T(""));
			WIDTH.Format(_T("%.3f"), G_width);
			HEIGHT.Format(_T("%.3f"), G_height);
			GetDlgItem(IDC_HEIGHT)->SetWindowText(HEIGHT);
			GetDlgItem(IDC_WIDTH)->SetWindowText(WIDTH);
		/*	WIDTH.SetWindowText(str1);
			HEIGHT.SetWindowText(str2);*/
			UpdateData(TRUE);
			remove("MEASURE.JPG");

}


void CCVDlg::OnAdjustSetcamera()
{
	// TODO: 在此添加命令处理程序代码
	//CCalibDlg*dlg = new CCalibDlg;//非模态
	//dlg->Create(IDD_CALIBRATION, this);    //第一个参数是对话框ID号
	//dlg->ShowWindow(SW_SHOW);
	CCalibDlg dlgB; // 新建B对话框的对象 
	dlgB.DoModal();
	
		
}
////




void CCVDlg::OnBnClickedOn()
{
	CString str="vasv";
	//str = dlg->INFO;
	//GetDlgItem(dlg->IDC_CDATA)->SetWindowText(str);
			/*str1=(_T(" "));str2=(_T(" "));
			WIDTH.SetWindowText(str1);HEIGHT.SetWindowText(str2);*/
	//dlg->GetDlgItem(IDC_CDATA);
	// TODO: 在此添加控件通知处理程序代码
	VideoCapture Capture(0);
	FLAG = TRUE;
	if (!Capture.isOpened())
	{
		AfxMessageBox(_T("Unable to establish link with camera！"));
		return;
	}
	while (FLAG == TRUE)
	{
		Capture >> frame;
		resize(frame, frame, Size(width, height));
		imshow("REALIMAGE", frame);
		waitKey(5);
	}
	return;
}


void CCVDlg::OnBnClickedOff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FLAG == FALSE)
	{
		AfxMessageBox(_T("Camera off! "));
		return;
	}
	FLAG = FALSE;
	Mat src = imread("OFF.jpg");
	resize(src, src, Size(width, height));
	imshow("REALIMAGE", src);
	return;
}


void CCVDlg::OnBnClickedCapture()
{
	// TODO: 在此添加控件通知处理程序代码
	image = frame;
	if (FLAG == FALSE)
	{
		Mat src = imread("init.jpg");
		resize(src, src, Size(width, height));
		imshow("Catch", src);
		AfxMessageBox(_T("Camera off! "));
		return;
	}
	else
	imwrite("CAPTURE.jpg", image);
	resize(image, dst, Size(width, height));
	imwrite("MODIFY.JPG", dst);
	imshow("Catch", dst);
	return;
}


void CCVDlg::OnAdjustCalibrate()
{
	VideoCapture Capture(0);
	int b = 10;
	CString file;
	if (!Capture.isOpened())
	{
		AfxMessageBox(_T("Unable to establish link with camera！"));
		return;
	}
	if (FLAG == FALSE)
	{
		AfxMessageBox(_T("Plesae turn on your device before this step!"));
		return;
	}
	AfxMessageBox(_T("Notice:Please put the calibration board in the effective range of the camera! Click the button to capture calibration board image information from the camera!"));
		for (int i = 1; i <= b; i++)
		{
			Capture >> frame;
			file.Format(_T("chess%d.bmp"), i);
			resize(frame, frame, Size(width, height));
			imshow("REALIMAGE", frame);
			AfxMessageBox(_T("This is " + file));
			imwrite(String(file), frame);
			waitKey(30);
		}
		FLAG = FALSE;
		return;
	}

	void CAboutDlg::OnBnClickedGet()
	{
		// TODO: 在此添加控件通知处理程序代码
		
	}


	void CAboutDlg::OnBnClickedSCalib()
	{
		// TODO: 在此添加控件通知处理程序代码
		ifstream fin("calibdata.txt"); /* 标定所用图像文件的路径 */
		ofstream fout("caliberation_result.txt");  /* 保存标定结果的文件 */
		//读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化	
		cout << "开始提取角点………………";
		int image_count = 0;  /* 图像数量 */
		Size image_size;  /* 图像的尺寸 */
		Size board_size = Size(4, 6);    /* 标定板上每行、列的角点数 */
		vector<Point2f> image_points_buf;  /* 缓存每幅图像上检测到的角点 */
		vector<vector<Point2f>> image_points_seq; /* 保存检测到的所有角点 */
		string filename;
		int count = -1;//用于存储角点个数。
		while (getline(fin, filename))
		{
			image_count++;
			// 用于观察检验输出
			//cout << "image_count = " << image_count << endl;
			/*INFO.calibdlg;
			INFO.Format(_T("image_count=%d"), image_count);*/
			///* 输出检验*/
			//cout << "-->count = " << count;
			Mat imageInput = imread(filename);
			if (image_count == 1)  //读入第一张图片时获取图像宽高信息
			{
				image_size.width = imageInput.cols;
				image_size.height = imageInput.rows;
				/*cout << "\nimage_size.width = " << image_size.width << endl;
				cout << "image_size.height = " << image_size.height << endl;*/
			}

			/* 提取角点 */
			if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))
			{
				MessageBox("can not find chessboard corners!\n"); //找不到角点
				exit(1);
			}
			else
			{
				Mat view_gray;
				cvtColor(imageInput, view_gray, CV_RGB2GRAY);
				/* 亚像素精确化 */
				find4QuadCornerSubpix(view_gray, image_points_buf, Size(5, 5)); //对粗提取的角点进行精确化
				image_points_seq.push_back(image_points_buf);  //保存亚像素角点
				/* 在图像上显示角点位置 */
				drawChessboardCorners(view_gray, board_size, image_points_buf, true); //用于在图片中标记角点
				imshow("Camera Calibration", view_gray);//显示图片
				waitKey(500);//暂停0.5S		
			}
		}
		int total = image_points_seq.size();
		/*cout << "total = " << total << endl;*/
		int CornerNum = board_size.width*board_size.height;  //每张图片上总的角点数
		for (int ii = 0; ii < total; ii++)
		{
			if (0 == ii % CornerNum)// 24 是每幅图片的角点个数。此判断语句是为了输出 图片号，便于控制台观看 
			{
				int i = -1;
				i = ii / CornerNum;
				int j = i + 1;
				/*	cout << "--> 第 " << j << "图片的数据 --> : " << endl;*/
			}
			if (0 == ii % 3)	// 此判断语句，格式化输出，便于控制台查看
			{
				cout << endl;
			}
			else
			{
				cout.width(10);
			}
			//输出所有的角点
			cout << " -->" << image_points_seq[ii][0].x;
			cout << " -->" << image_points_seq[ii][0].y;
		}
		cout << "角点提取完成！\n";

		//以下是摄像机标定
		cout << "开始标定………………";
		/*棋盘三维信息*/
		Size square_size = Size(10, 10);  /* 实际测量得到的标定板上每个棋盘格的大小 */
		vector<vector<Point3f>> object_points; /* 保存标定板上角点的三维坐标 */
		/*内外参数*/
		Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 摄像机内参数矩阵 */
		vector<int> point_counts;  // 每幅图像中角点的数量
		Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
		vector<Mat> tvecsMat;  /* 每幅图像的旋转向量 */
		vector<Mat> rvecsMat; /* 每幅图像的平移向量 */
		/* 初始化标定板上角点的三维坐标 */
		int i, j, t;
		for (t = 0; t < image_count; t++)
		{
			vector<Point3f> tempPointSet;
			for (i = 0; i < board_size.height; i++)
			{
				for (j = 0; j < board_size.width; j++)
				{
					Point3f realPoint;
					/* 假设标定板放在世界坐标系中z=0的平面上 */
					realPoint.x = i * square_size.width;
					realPoint.y = j * square_size.height;
					realPoint.z = 0;
					tempPointSet.push_back(realPoint);
				}
			}
			object_points.push_back(tempPointSet);
		}
		/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
		for (i = 0; i < image_count; i++)
		{
			point_counts.push_back(board_size.width*board_size.height);
		}
		/* 开始标定 */
		calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
		cout << "标定完成！\n";
		//对标定结果进行评价
		cout << "开始评价标定结果………………\n";
		double total_err = 0.0; /* 所有图像的平均误差的总和 */
		double err = 0.0; /* 每幅图像的平均误差 */
		vector<Point2f> image_points2; /* 保存重新计算得到的投影点 */
		cout << "\t每幅图像的标定误差：\n";
		fout << "每幅图像的标定误差：\n";
		for (i = 0; i < image_count; i++)
		{
			vector<Point3f> tempPointSet = object_points[i];
			/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
			projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
			/* 计算新的投影点和旧的投影点之间的误差*/
			vector<Point2f> tempImagePoint = image_points_seq[i];
			Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
			Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);
			for (int j = 0; j < tempImagePoint.size(); j++)
			{
				image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
				tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
			}
			err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
			total_err += err /= point_counts[i];
			std::cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
			fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
		}
		std::cout << "总体平均误差：" << total_err / image_count << "像素" << endl;
		fout << "总体平均误差：" << total_err / image_count << "像素" << endl << endl;
		std::cout << "评价完成！" << endl;
		//保存定标结果  	
		std::cout << "开始保存定标结果………………" << endl;
		Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
		fout << "相机内参数矩阵：" << endl;
		fout << cameraMatrix << endl << endl;
		fout << "畸变系数：\n";
		fout << distCoeffs << endl << endl << endl;
	//	HEIGHT.SetWindowText(distCoeffs); 
		for (int i = 0; i < image_count; i++)
		{
			fout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
			fout << tvecsMat[i] << endl;
			/* 将旋转向量转换为相对应的旋转矩阵 */
			Rodrigues(tvecsMat[i], rotation_matrix);
			fout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
			fout << rotation_matrix << endl;
			fout << "第" << i + 1 << "幅图像的平移向量：" << endl;
			fout << rvecsMat[i] << endl << endl;
		}
		std::cout << "完成保存" << endl;
		fout << endl;
		/************************************************************************
			   显示定标结果
		*************************************************************************/
		Mat mapx = Mat(image_size, CV_32FC1);
		Mat mapy = Mat(image_size, CV_32FC1);
		Mat R = Mat::eye(3, 3, CV_32F);
		std::cout << "保存矫正图像" << endl;
		string imageFileName;
		std::stringstream StrStm;
		for (int i = 0; i != image_count; i++)
		{
			std::cout << "Frame #" << i + 1 << "..." << endl;
			initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, image_size, CV_32FC1, mapx, mapy);
			StrStm.clear();
			imageFileName.clear();
			string filePath = "chess";
			StrStm << i + 1;
			StrStm >> imageFileName;
			filePath += imageFileName;
			filePath += ".bmp";
			Mat imageSource = imread(filePath);
			Mat newimage = imageSource.clone();
			//另一种不需要转换矩阵的方式
			//undistort(imageSource,newimage,cameraMatrix,distCoeffs);
			remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
			imshow("原始图像", imageSource);
			imshow("矫正后图像", newimage);
			waitKey();
			StrStm.clear();
			filePath.clear();
			StrStm << i + 1;
			StrStm >> imageFileName;
			imageFileName += "_d.jpg";
			imwrite(imageFileName, newimage);
		}
		std::cout << "保存结束" << endl;
		UpdateData(TRUE);
		
		return;
	}


	void CCVDlg::OnBnClickedtest()
	{
		// TODO: 在此添加控件通知处理程序代码
		Mat src = imread("init.jpg");
		//ShowImage("in", src, IDC_STATIC_test);
	}


	void CAboutDlg::OnBnClickedModel()
	{
		// TODO: 在此添加控件通知处理程序代码
		Mat srcImage;
		Mat grayImage;
		system("color 1F");
		srcImage = imread("capture.jpg", 1);
		if (!srcImage.data)
		{
			AfxMessageBox(_T("No preprocessing image！"));
			return;
		}
		cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
		GaussianBlur(grayImage, grayImage, Size(7, 7), 0);
		Canny(grayImage, grayImage, 50, 100);
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //隔开物体
		dilate(grayImage, grayImage, element);//膨胀
		erode(grayImage, grayImage, element);//腐蚀

		//寻找轮廓
		findContours(grayImage, g_vContours, g_vHierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		std::sort(g_vContours.begin(), g_vContours.end(), ContoursSortFun);//按照从左到右 排序
		for (unsigned i = 0; i < g_vContours.size(); i++)
		{
			if (contourArea(g_vContours[i]) < 100)//面积太小 则忽略
				continue;
			RotatedRect box = minAreaRect(g_vContours[i]);

			Point2f boxPoints[4];

			box.points(boxPoints);

			Point2f pointA = midpoint(boxPoints[0], boxPoints[1]);

			Point2f pointB = midpoint(boxPoints[1], boxPoints[2]);

			Point2f pointC = midpoint(boxPoints[2], boxPoints[3]);

			Point2f pointD = midpoint(boxPoints[3], boxPoints[0]);

			circle(srcImage, pointA, 2, Scalar(0, 0, 255));

			circle(srcImage, pointB, 2, Scalar(0, 0, 255));

			circle(srcImage, pointC, 2, Scalar(0, 0, 255));

			circle(srcImage, pointD, 2, Scalar(0, 0, 255));


			line(srcImage, pointA, pointC, Scalar(255, 0, 0));

			line(srcImage, pointD, pointB, Scalar(255, 0, 0));

			double dWidth = getDistance(pointA, pointC);

			double dHeight = getDistance(pointD, pointB);

			if (g_bFirst) {

				g_dPixelsPerMetric = dWidth / g_dReferWidth; //计算像素与实际大小的比列

			//	cout << "pixelPerMetric:" << dWidth << " " << g_dReferWidth << "  " << g_dPixelsPerMetric;

				g_bFirst = false;

			}
			//	cout << "dWidth" << dWidth << "   " << dHeight << "      " << dWidth / g_dPixelsPerMetric << "    " << dHeight / g_dPixelsPerMetric;

			putText(srcImage, format("%.3f*%.3f",
				dWidth / g_dPixelsPerMetric,
				dHeight / g_dPixelsPerMetric),
				/*boxPoints[1]*/
				pointB,
				FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 0, 0));
			G_width = dWidth / g_dPixelsPerMetric;
			G_height = dHeight / g_dPixelsPerMetric;

			for (int i = 0; i <= 3; i++)

			{
				line(srcImage, boxPoints[i], boxPoints[(i + 1) % 4], Scalar(0, 0, 255));
			}

		}
		imwrite("measure.jpg", srcImage);
		imshow("Catch", srcImage);
		return;

	}


	void CCVDlg::OnClose()
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		FLAG = FALSE;
		CDialogEx::OnClose();
	}
