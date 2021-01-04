#pragma once


// ColorBox dialog

class ColorBox : public CDialogEx
{
	DECLARE_DYNAMIC(ColorBox)

public:
	ColorBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ColorBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORBOX };
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
	CListBox Spheres;
	class COfflineeditorDlg* base;
	int selected = NULL;

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
	afx_msg void UpdateBox();
};
