#pragma once


// AddSphere dialog

class AddSphere : public CDialogEx
{
	DECLARE_DYNAMIC(AddSphere)

public:
	AddSphere(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddSphere();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDSPHERE };
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
	CEdit boxValueX;
	CEdit boxValueY;
	CEdit boxValueZ;
	CEdit boxValueRad;
	CEdit boxValueRef;
	CEdit boxValueTr;
	CStatic TextWarning;
	class COfflineeditorDlg* base;
	int valueX, valueY, valueZ, valueRad, valueRef, valueTr;
	bool R, G, B, X, Y, Z, Rad, Ref, Tr;

public:
	virtual BOOL OnInitDialog();
	afx_msg void UpdateBox(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void UpdateBoxR();
	afx_msg void UpdateBoxG();
	afx_msg void UpdateBoxB();
	afx_msg void UpdateBoxRad();
	afx_msg void UpdateBoxRef();
	afx_msg void UpdateBoxTr();
	DECLARE_MESSAGE_MAP()
	afx_msg void ScrollUpdateR();
	afx_msg void ScrollUpdateG();
	afx_msg void ScrollUpdateB();
	afx_msg void OnBnClickedOk();
	afx_msg void UpdateBoxY();
	afx_msg void UpdateBoxX();
	afx_msg void UpdateBoxZ();

};
