#pragma once


// BackgroundColor dialog

class BackgroundColor : public CDialogEx
{
	DECLARE_DYNAMIC(BackgroundColor)

public:
	BackgroundColor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BackgroundColor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORBOXBACGROUND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	CSliderCtrl sliderB;
	CSliderCtrl sliderR;
	CEdit boxValueG;
	CSliderCtrl sliderG;
	CEdit boxValueR;
	CEdit boxValueB;
	class COfflineeditorDlg* base;

public:
	virtual BOOL OnInitDialog();
	afx_msg void UpdateBox(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void UpdateBoxR();
	afx_msg void UpdateBoxG();
	afx_msg void UpdateBoxB();
	DECLARE_MESSAGE_MAP()
	afx_msg void ScrollUpdateR();
	afx_msg void ScrollUpdateG();
	afx_msg void ScrollUpdateB();
	afx_msg void OnBnClickedColorok();
};
