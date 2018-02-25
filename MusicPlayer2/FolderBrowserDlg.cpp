#include "stdafx.h"
#include "FolderBrowserDlg.h"


CFolderBrowserDlg::CFolderBrowserDlg(HWND hParent)
	: m_hParent{ hParent }
{
}


CFolderBrowserDlg::~CFolderBrowserDlg()
{
}

int CFolderBrowserDlg::DoModal()
{
	TCHAR szPath[MAX_PATH];		//���ѡ���Ŀ¼·��
	CString str;

	BROWSEINFO bi;
	bi.hwndOwner = m_hParent;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = m_info;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
	browse:
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp)
	{
		if (!SHGetPathFromIDList(lp, szPath))
		{
			AfxMessageBox(_T("��Ч��Ŀ¼��������ѡ��"));
			goto browse;
		}
		m_path = szPath;
		return IDOK;
	}
	return IDCANCEL;
}