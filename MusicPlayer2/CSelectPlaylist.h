﻿#pragma once
#include "TabDlg.h"
#include "ListCtrlEx.h"
#include "SearchEditCtrl.h"
#include "MediaLibTabDlg.h"


// CSelectPlaylist 对话框
#define WM_PLAYLIST_SELECTED (WM_USER+119)      //WPARA: 传递对话框窗口的指针；LPARA：-2:表示要播放默认的播放列表，>=0，表示要播放列表中指定序号的曲目

class CSelectPlaylistDlg : public CMediaLibTabDlg
{
    DECLARE_DYNAMIC(CSelectPlaylistDlg)

public:
    CSelectPlaylistDlg(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CSelectPlaylistDlg();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SELECT_PLAYLIST_DIALOG };
#endif

    // 歌曲属性更新后被调用
    virtual void RefreshSongList() override;

public:
    wstring GetSelPlaylistPath() const;
    int GetTrack() const;
    int GetPosition() const;
    bool IsPlaylistModified() const;
    void AdjustColumnWidth();       //自动调整列表宽度
    // 完全重新载入标签页数据
    void RefreshTabData();
    bool IsLeftSelected() const;

private:
    int m_row_selected{ -1 };       //左侧选中的播放列表的序号（不管是否处于搜索状态都为列表中“序号”一列的值）
    int m_left_selected_index{ -1 };    //左侧列表选中行在列表中的索引（如果处于搜索状态，为列表选中项实际的索引）
    //CMenu m_menu;
    bool m_playlist_modified{ false };
    CSearchEditCtrl m_search_edit;
    vector<int> m_search_result;                //储存快速搜索结果的歌曲序号
    bool m_searched{ false };                   //是否处于搜索状态

    bool m_left_selected{};                     //最后一次选中的是左侧还是右侧
    int m_right_selected_item{ -1 };            //右侧列表选中的项目的序号
    std::vector<int> m_right_selected_items;    //右侧列表多选选中的项目的序号
    wstring m_selected_string;

    enum
    {
        SPEC_PLAYLIST_NUM = 2       //特殊播放列表的个数（这里是2，默认播放列表和我喜欢的播放列表）
    };

    enum SongColumeIndex
    {
        COL_INDEX,
        COL_TITLE,
        COL_ARTIST,
        COL_ALBUM,
        COL_TRACK,
        COL_GENRE,
        COL_BITRATE,
        COL_PATH,
        COL_MAX
    };

    CListCtrlEx m_playlist_ctrl;
    CListCtrlEx m_song_list_ctrl;
    CListCtrlEx::ListData m_list_data;  //右侧列表数据
    vector<SongInfo> m_cur_song_list;   //选中播放列表的数据

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    void QuickSearch(const wstring& key_words);         //根据关键字执行快速查找m_search_result中
    int GetPlayingItem();
    virtual void OnTabEntered() override;
    void ShowSongList();

    void LeftListClicked(int index);
    void SongListClicked(int index);

    void SetLeftListSelected(int index);
    void UpdatePlaylistInfo(const std::wstring playlist_path, int song_num, int totla_time);

    virtual const vector<SongInfo>& GetSongList() const override;
    virtual int GetItemSelected() const override;
    virtual const vector<int>& GetItemsSelected() const override;
    virtual void AfterDeleteFromDisk(const std::vector<SongInfo>& files) override;
    virtual wstring GetSelectedString() const override;

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();

private:
    void CalculateColumeWidth(vector<int>& width);
    void ShowPathList();
    void SetListRowData(int index, const PlaylistInfo& playlist_info);
    bool SelectValid() const;
    PlaylistInfo GetSelectedPlaylist() const;
    void SetButtonsEnable();
    bool SelectedCanPlay() const;
    wstring DoNewPlaylist();        //执行“新建播放列表”操作，返回新播放列表的路径

public:
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnOK();
    afx_msg void OnBnClickedNewPlaylist();
    afx_msg void OnPlayPlaylist();
    afx_msg void OnRenamePlaylist();
    afx_msg void OnDeletePlaylist();
    afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnInitMenu(CMenu* pMenu);
    afx_msg void OnNewPlaylist();
    afx_msg void OnEnChangeSearchEdit();
    //afx_msg void OnBnClickedClearButton();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    afx_msg LRESULT OnSearchEditBtnClicked(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnNMClickSongList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMRClickSongList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkSongList(NMHDR* pNMHDR, LRESULT* pResult);
    virtual void OnCancel();
    afx_msg void OnSaveAsNewPlaylist();
    afx_msg void OnPlaylistSaveAs();
    afx_msg void OnDestroy();
    afx_msg void OnPlaylistFixPathError();
    afx_msg void OnPlaylistBrowseFile();
};
