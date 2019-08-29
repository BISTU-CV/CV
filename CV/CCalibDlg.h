#pragma once


// CCalibDlg 对话框

class CCalibDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalibDlg)

public:
	CCalibDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCalibDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALIBRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString INFO;
	afx_msg void OnBnClickedSCalib();
	// 标准件的宽
	CString model_W;
	// 标准件的高
	CString model_H;
	CString PIC_NUM;
	afx_msg void OnBnClickedModel();

	afx_msg void OnBnClickedGet();
	afx_msg void OnBnClickedSave();
};
