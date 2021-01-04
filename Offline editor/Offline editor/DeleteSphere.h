#pragma once


// DeleteSphere dialog

class DeleteSphere : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteSphere)

public:
	DeleteSphere(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DeleteSphere();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETESPHERE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	class COfflineeditorDlg* base;
	int selected = NULL;
	CListBox Spheres;
	CStatic TextNoSelected;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelete();
	afx_msg void Select();

};
