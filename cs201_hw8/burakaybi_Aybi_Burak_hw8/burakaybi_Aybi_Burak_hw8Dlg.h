
// burakaybi_Aybi_Burak_hw8Dlg.h : header file
//

#pragma once


// Cburakaybi_Aybi_Burak_hw8Dlg dialog
class Cburakaybi_Aybi_Burak_hw8Dlg : public CDialogEx
{
// Construction
public:
	Cburakaybi_Aybi_Burak_hw8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BURAKAYBI_AYBI_BURAK_HW8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
