
// CVDlg.h: 头文件
//

#pragma once
#include"CCalibDlg.h"
// CCVDlg 对话框
class CCVDlg : public CDialogEx
{
// 构造
public:
	CCVDlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CCVDlg();
	POINT Old;//存放对话框的宽和高。
	static CCVDlg *pTestdlg;
CCalibDlg *dlg;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	
	//void ShowImage(const Mat & mat, UINT ID);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveas();
	afx_msg void OnAboutAboutus();
	afx_msg void OnAboutContact();
	afx_msg void OnInitOn();
	afx_msg void OnInitOff();
	afx_msg void OnInitCapture();
	afx_msg void OnFileExit();
	afx_msg void OnDisposalEtch();
	afx_msg void OnDisposalSwell();
	afx_msg void OnDisposalBinary();
	afx_msg void OnDisposalOpening();
	afx_msg void OnDisposalClosing();
	afx_msg void OnDisposalTophat();
	afx_msg void OnDisposalBlack();
	afx_msg void OnDisposalMedian();
	afx_msg void OnDisposalGray();
	afx_msg void OnPixelSobel();
	afx_msg void OnPixelCanny();
	afx_msg void OnPixelLaplacian();
	afx_msg void OnSubpixelZernike();
	afx_msg void OnFileNew();
	afx_msg void OnAnalyzeShape();
	afx_msg void OnAnalyzeSizemarking();
	afx_msg void OnInitializeUndoalloperations();
	afx_msg void OnAnalyzeOutputsize();
	afx_msg void OnAdjustSetcamera();
	/*afx_msg void OnSize(UINT nType, int cx, int cy);*/
	afx_msg void OnBnClickedOn();
	afx_msg void OnBnClickedOff();
	afx_msg void OnBnClickedCapture();
	CString HEIGHT;
	CString WIDTH;
	afx_msg void OnAdjustCalibrate();
	// 标定信息
	CString CALIB_INFO;
	afx_msg void OnBnClickedtest();
	//void ShowImage(const Mat & mat, UINT ID);

	afx_msg void OnClose();
};
