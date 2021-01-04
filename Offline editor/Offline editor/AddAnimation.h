#pragma once


// AddAnimation dialog

class AddAnimation : public CDialogEx
{
	DECLARE_DYNAMIC(AddAnimation)

public:
	AddAnimation(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddAnimation();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDANIMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	class COfflineeditorDlg* base;
	int selected = LB_ERR, valueStartX, valueStartY, valueStartZ, valueEndX, valueEndY, valueEndZ, valueFrames = 1;
	CListBox Spheres;
	CEdit boxValueStartX;
	CEdit boxValueStartY;
	CEdit boxValueStartZ;
	CEdit boxValueEndX;
	CEdit boxValueEndY;
	CEdit boxValueEndZ;
	CEdit boxValueFrames;
public:
	afx_msg void UpdateBox();
	afx_msg void UpdateBoxStartY();
	afx_msg void UpdateBoxStartX();
	afx_msg void UpdateBoxStartZ();
	afx_msg void UpdateBoxEndY();
	afx_msg void UpdateBoxEndX();
	afx_msg void UpdateBoxEndZ();
	afx_msg void UpdateBoxFrames();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedPositionok();
};
