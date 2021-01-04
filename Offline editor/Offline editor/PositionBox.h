#pragma once


// PositionBox dialog

class PositionBox : public CDialogEx
{
	DECLARE_DYNAMIC(PositionBox)

public:
	PositionBox(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PositionBox();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POSITIONBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
private:
	class COfflineeditorDlg* base;
	int selected = LB_ERR, valueX, valueY, valueZ;
	CListBox Spheres;
	CEdit boxValueX;
	CEdit boxValueY;
	CEdit boxValueZ;
public:
	afx_msg void UpdateBox();
	afx_msg void UpdateBoxY();
	afx_msg void UpdateBoxX();
	afx_msg void UpdateBoxZ();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedPositionok();
};
