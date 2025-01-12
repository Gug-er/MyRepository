//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef NOTEPAD_PLUS_H
#define NOTEPAD_PLUS_H

#ifndef SCINTILLA_EDIT_VIEW_H
#include "ScintillaEditView.h"
#endif //SCINTILLA_EDIT_VIEW_H

#ifndef DOCTABVIEW_H
#include "DocTabView.h"
#endif //DOCTABVIEW_H

#ifndef SPLITTER_CONTAINER_H
#include "SplitterContainer.h"
#endif //SPLITTER_CONTAINER_H

#ifndef FIND_REPLACE_DLG_H
#include "FindReplaceDlg.h"
#endif //FIND_REPLACE_DLG_H

#ifndef ABOUT_DLG_H
#include "AboutDlg.h"
#endif //ABOUT_DLG_H

#ifndef RUN_DLG_H
#include "RunDlg.h"
#endif //RUN_DLG_H

#ifndef STATUS_BAR_H
#include "StatusBar.h"
#endif //STATUS_BAR_H

#ifndef LASTRECENTFILELIST_H
#include "lastRecentFileList.h"
#endif //LASTRECENTFILELIST_H

#ifndef GOTILINE_DLG_H
#include "GoToLineDlg.h"
#endif //GOTILINE_DLG_H

#ifndef COLUMNEDITOR_H
#include "columnEditor.h"
#endif //COLUMNEDITOR_H

#ifndef WORD_STYLE_H
#include "WordStyleDlg.h"
#endif //WORD_STYLE_H

#ifndef TRAY_ICON_CONTROLER_H
#include "trayIconControler.h"
#endif //TRAY_ICON_CONTROLER_H

#ifndef PLUGINSMANAGER_H
#include "PluginsManager.h"
#endif //PLUGINSMANAGER_H
/*
#ifndef NOTEPAD_PLUS_MSGS_H
#include "Notepad_plus_msgs.h"
#endif //NOTEPAD_PLUS_MSGS_H
*/
#ifndef PREFERENCE_DLG_H
#include "preferenceDlg.h"
#endif //PREFERENCE_DLG_H

#ifndef WINDOWS_DLG_H
#include "WindowsDlg.h"
#endif //WINDOWS_DLG_H

#ifndef RUN_MACRO_DLG_H
#include "RunMacroDlg.h"
#endif //RUN_MACRO_DLG_H

#ifndef DOCKINGMANAGER_H
#include "DockingManager.h"
#endif //DOCKINGMANAGER_H

#ifndef PROCESSUS_H
#include "Process.h"
#endif //PROCESSUS_H

#ifndef AUTOCOMPLETION_H
#include "AutoCompletion.h"
#endif //AUTOCOMPLETION_H

#ifndef SMARTHIGHLIGHTER_H
#include "SmartHighlighter.h"
#endif //SMARTHIGHLIGHTER_H

#ifndef SCINTILLACTRLS_H
#include "ScintillaCtrls.h"
#endif //SCINTILLACTRLS_H

#ifndef SIZE_DLG_H
#include "lesDlgs.h"
#endif //SIZE_DLG_H

#include "localization.h"

#define MENU 0x01
#define TOOLBAR 0x02

#define URL_REG_EXPR "[A-Za-z]+://[A-Za-z0-9_\\-\\+~.:?&@=/%#,;\\{\\}\\(\\)\\[\\]\\|\\*\\!\\\\]+"

enum FileTransferMode {
	TransferClone		= 0x01,
	TransferMove		= 0x02
};

enum WindowStatus {	//bitwise mask
	WindowMainActive	= 0x01,
	WindowSubActive		= 0x02,
	WindowBothActive	= 0x03,	//little helper shortcut
	WindowUserActive	= 0x04,
	WindowMask			= 0x07
};

enum trimOp {
	lineHeader = 0,
	lineTail = 1,
	lineEol = 2
};

struct TaskListInfo;

struct VisibleGUIConf {
	bool isPostIt;
	bool isFullScreen;
	
	//Used by both views
	bool isMenuShown;
	//bool isToolbarShown;	//toolbar forcefully hidden by hiding rebar
	DWORD_PTR preStyle;

	//used by postit only
	bool isTabbarShown;
	bool isAlwaysOnTop;
	bool isStatusbarShown;

	//used by fullscreen only
	WINDOWPLACEMENT _winPlace;

	VisibleGUIConf() : isPostIt(false), isFullScreen(false),
		isAlwaysOnTop(false), isMenuShown(true), isTabbarShown(true),
		isStatusbarShown(true), preStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)
	{
		_winPlace.length = 0;
	};
};

class FileDialog;
class Notepad_plus_Window;

	
class Notepad_plus {

friend class Notepad_plus_Window;

public:
	Notepad_plus();
	virtual ~Notepad_plus();
	LRESULT init(HWND hwnd);
	LRESULT process(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	void killAllChildren();
    /*
    HWND getWindowHandle() const {
        return _pPublicInterface->getHSelf();
    };
    */

	enum comment_mode {cm_comment, cm_uncomment, cm_toggle};

	void setTitle();
	void getTaskListInfo(TaskListInfo *tli);

	// For filtering the modeless Dialog message

// fileOperations
	//The doXXX functions apply to a single buffer and dont need to worry about views, with the excpetion of doClose, since closing one view doesnt have to mean the document is gone
    BufferID doOpen(const TCHAR *fileName, bool isReadOnly = false, int encoding = -1);
	bool doReload(BufferID id, bool alert = true);
	bool doSave(BufferID, const TCHAR * filename, bool isSaveCopy = false);
	void doClose(BufferID, int whichOne);
	//bool doDelete(const TCHAR *fileName) const {return ::DeleteFile(fileName) != 0;};

	void fileOpen();
	void fileNew();

    bool fileReload() {
	    BufferID buf = _pEditView->getCurrentBufferID();
	    return doReload(buf, buf->isDirty());
    };

	bool fileClose(BufferID id = BUFFER_INVALID, int curView = -1);	//use curView to override view to close from
	bool fileCloseAll();
	bool fileCloseAllButCurrent();
	bool fileSave(BufferID id = BUFFER_INVALID);
	bool fileSaveAll();
	bool fileSaveAs(BufferID id = BUFFER_INVALID, bool isSaveCopy = false);
	bool fileDelete(BufferID id = BUFFER_INVALID);
	bool fileRename(BufferID id = BUFFER_INVALID);

	bool addBufferToView(BufferID id, int whichOne);
	bool moveBuffer(BufferID id, int whereTo);	//assumes whereFrom is otherView(whereTo)
	bool switchToFile(BufferID buffer);			//find buffer in active view then in other view.
// end fileOperations

	bool isFileSession(const TCHAR * filename);
	void filePrint(bool showDialog);
	bool saveScintillaParams();

	bool saveGUIParams();
	void saveDockingParams();
    void saveUserDefineLangs() {
        if (ScintillaEditView::getUserDefineDlg()->isDirty())
		(NppParameters::getInstance())->writeUserDefinedLang();
    };
    void saveShortcuts(){
        NppParameters::getInstance()->writeShortcuts();
    };
	void saveSession(const Session & session);
    void saveFindHistory(){
        _findReplaceDlg.saveFindHistory();
	    (NppParameters::getInstance())->writeFindHistory();
    };

	void getCurrentOpenedFiles(Session & session);

	bool fileLoadSession(const TCHAR *fn = NULL);
	const TCHAR * fileSaveSession(size_t nbFile, TCHAR ** fileNames, const TCHAR *sessionFile2save);
	const TCHAR * fileSaveSession(size_t nbFile = 0, TCHAR ** fileNames = NULL);
	void changeToolBarIcons();

	bool doBlockComment(comment_mode currCommentMode);
	bool doStreamComment();
	bool addCurrentMacro();
	void macroPlayback(Macro);
    
    void loadLastSession(){
    	Session lastSession = (NppParameters::getInstance())->getSession();
	    loadSession(lastSession);
    };

	bool loadSession(Session & session);

	

	void notifyBufferChanged(Buffer * buffer, int mask);
	bool findInFiles();
	bool replaceInFiles();
	void setFindReplaceFolderFilter(const TCHAR *dir, const TCHAR *filters);
	vector<generic_string> addNppComponents(const TCHAR *destDir, const TCHAR *extFilterName, const TCHAR *extFilter);
    int getHtmlXmlEncoding(const TCHAR *fileName) const;
		HACCEL getAccTable() const{
		return _accelerator.getAccTable();
	};
	bool emergency(generic_string emergencySavedDir);

	
private:
	Notepad_plus_Window *_pPublicInterface;
    Window *_pMainWindow;
	DockingManager _dockingManager;

	AutoCompletion _autoCompleteMain;
	AutoCompletion _autoCompleteSub;	//each Scintilla has its own autoComplete

	SmartHighlighter _smartHighlighter;
    NativeLangSpeaker _nativeLangSpeaker;
    DocTabView _mainDocTab;
    DocTabView _subDocTab;
    DocTabView *_pDocTab;
	DocTabView *_pNonDocTab;

    ScintillaEditView _subEditView;
    ScintillaEditView _mainEditView;
	ScintillaEditView _invisibleEditView;	//for searches
	ScintillaEditView _fileEditView;		//for FileManager

    ScintillaEditView *_pEditView;
	ScintillaEditView *_pNonEditView;

    SplitterContainer *_pMainSplitter;
    SplitterContainer _subSplitter;

    ContextMenu _tabPopupMenu, _tabPopupDropMenu;

	ToolBar	_toolBar;
	IconList _docTabIconList;
	
    StatusBar _statusBar;
	bool _toReduceTabBar;
	ReBar _rebarTop;
	ReBar _rebarBottom;

	// Dialog
	FindReplaceDlg _findReplaceDlg;
	FindIncrementDlg _incrementFindDlg;
    AboutDlg _aboutDlg;
	RunDlg _runDlg;
    GoToLineDlg _goToLineDlg;
	ColumnEditorDlg _colEditorDlg;
	WordStyleDlg _configStyleDlg;
	PreferenceDlg _preference;
	
	// a handle list of all the Notepad++ dialogs
	vector<HWND> _hModelessDlgs;

	LastRecentFileList _lastRecentFileList;

	//vector<iconLocator> _customIconVect;

	WindowsMenu _windowsMenu;
	HMENU _mainMenuHandle;

	bool _sysMenuEntering;
	

	// For FullScreen/PostIt features
	VisibleGUIConf	_beforeSpecialView;
	void fullScreenToggle();
	void postItToggle();

	// Keystroke macro recording and playback
	Macro _macro;
	bool _recordingMacro;
	RunMacroDlg _runMacroDlg;

	// For hotspot
	bool _linkTriggered;
	bool _isDocModifing;
	bool _isHotspotDblClicked;

	//For Dynamic selection highlight
	CharacterRange _prevSelectedRange;

	struct ActivateAppInfo {
		bool _isActivated;
		int _x;
		int _y;
		ActivateAppInfo() : _isActivated(false), _x(0), _y(0){};
	} _activeAppInf;

	//Synchronized Scolling
	
	struct SyncInfo {
		int _line;
		int _column;
		bool _isSynScollV;
		bool _isSynScollH;
		SyncInfo():_line(0), _column(0), _isSynScollV(false), _isSynScollH(false){};
		bool doSync() const {return (_isSynScollV || _isSynScollH); };
	} _syncInfo;

	bool _isUDDocked;

	trayIconControler *_pTrayIco;
	int _zoomOriginalValue;

	Accelerator _accelerator;
	ScintillaAccelerator _scintaccelerator;

	PluginsManager _pluginsManager;
    ButtonDlg _restoreButton;

	bool _isFileOpening;

	ScintillaCtrls _scintillaCtrls4Plugins;

	vector<pair<int, int> > _hideLinesMarks;
	StyleArray _hotspotStyles;
    bool _rememberThisSession; // always true. except -nosession is indicated on the launch time



	BOOL notify(SCNotification *notification);
	void specialCmd(int id);
	void command(int id);

//Document management
	UCHAR _mainWindowStatus;	//For 2 views and user dialog if docked
	int _activeView;

	//User dialog docking
	void dockUserDlg();
    void undockUserDlg();

	//View visibility
	void showView(int whichOne);
	bool viewVisible(int whichOne);
	void hideView(int whichOne);
	void hideCurrentView();
	bool bothActive() { return (_mainWindowStatus & WindowBothActive) == WindowBothActive; };
	bool reloadLang();
	bool loadStyles();

	int currentView(){
		return _activeView;
	};

	int otherView(){
		return (_activeView == MAIN_VIEW?SUB_VIEW:MAIN_VIEW);
	};

	int otherFromView(int whichOne){
		return (whichOne == MAIN_VIEW?SUB_VIEW:MAIN_VIEW);
	};

	bool canHideView(int whichOne);	//true if view can safely be hidden (no open docs etc)

	int switchEditViewTo(int gid);	//activate other view (set focus etc)

	void docGotoAnotherEditView(FileTransferMode mode);	//TransferMode
	void docOpenInNewInstance(FileTransferMode mode, int x = 0, int y = 0);

	void loadBufferIntoView(BufferID id, int whichOne, bool dontClose = false);		//Doesnt _activate_ the buffer
	void removeBufferFromView(BufferID id, int whichOne);	//Activates alternative of possible, or creates clean document if not clean already

	bool activateBuffer(BufferID id, int whichOne);			//activate buffer in that view if found
	void notifyBufferActivated(BufferID bufid, int view);
	void performPostReload(int whichOne);
//END: Document management

	int doSaveOrNot(const TCHAR *fn);
	int doReloadOrNot(const TCHAR *fn, bool dirty);
	int doCloseOrNot(const TCHAR *fn);
	int doDeleteOrNot(const TCHAR *fn);
	int doActionOrNot(const TCHAR *title, const TCHAR *displayText, int type);

	void enableMenu(int cmdID, bool doEnable) const;
	void enableCommand(int cmdID, bool doEnable, int which) const;
	void checkClipboard();
	void checkDocState();
	void checkUndoState();
	void checkMacroState();
	void checkSyncState();
	void dropFiles(HDROP hdrop);
	void checkModifiedDocument();

    void getMainClientRect(RECT & rc) const;
	void staticCheckMenuAndTB() const;
	void dynamicCheckMenuAndTB() const;
	void enableConvertMenuItems(formatType f) const;
	void checkUnicodeMenuItems() const;

	generic_string getLangDesc(LangType langType, bool shortDesc = false);

	void setLangStatus(LangType langType){
		_statusBar.setText(getLangDesc(langType).c_str(), STATUSBAR_DOC_TYPE);
	};

	void setDisplayFormat(formatType f);
	int getCmdIDFromEncoding(int encoding) const;
	void setUniModeText();

	void checkLangsMenu(int id) const ;
    void setLanguage(LangType langType);
	enum LangType menuID2LangType(int cmdID);

	void checkMenuItem(int itemID, bool willBeChecked) const {
		::CheckMenuItem(_mainMenuHandle, itemID, MF_BYCOMMAND | (willBeChecked?MF_CHECKED:MF_UNCHECKED));
	};
	void charAdded(TCHAR chAdded);
	void MaintainIndentation(TCHAR ch);
	
	void addHotSpot(bool docIsModifing = false);

    void bookmarkAdd(int lineno) const {
		if (lineno == -1)
			lineno = _pEditView->getCurrentLineNumber();
		if (!bookmarkPresent(lineno))
			_pEditView->execute(SCI_MARKERADD, lineno, MARK_BOOKMARK);
	};
    void bookmarkDelete(int lineno) const {
		if (lineno == -1)
			lineno = _pEditView->getCurrentLineNumber();
		if ( bookmarkPresent(lineno))
			_pEditView->execute(SCI_MARKERDELETE, lineno, MARK_BOOKMARK);
	};
    bool bookmarkPresent(int lineno) const {
		if (lineno == -1)
			lineno = _pEditView->getCurrentLineNumber();
		LRESULT state = _pEditView->execute(SCI_MARKERGET, lineno);
		return ((state & (1 << MARK_BOOKMARK)) != 0);
	};
    void bookmarkToggle(int lineno) const {
		if (lineno == -1)
			lineno = _pEditView->getCurrentLineNumber();

		if (bookmarkPresent(lineno))
			bookmarkDelete(lineno);
		else
    		bookmarkAdd(lineno);
	};
    void bookmarkNext(bool forwardScan);
	void bookmarkClearAll() const {
		_pEditView->execute(SCI_MARKERDELETEALL, MARK_BOOKMARK);
	};

	void copyMarkedLines();
	void cutMarkedLines();
	void deleteMarkedLines();
	void pasteToMarkedLines();
	void deleteMarkedline(int ln);
	void inverseMarks();
	void replaceMarkedline(int ln, const TCHAR *str);
	generic_string getMarkedLine(int ln);
    void findMatchingBracePos(int & braceAtCaret, int & braceOpposite);
    bool braceMatch();

    void activateNextDoc(bool direction);
	void activateDoc(int pos);

	void updateStatusBar();
	size_t getSelectedCharNumber(UniMode);
	size_t getCurrentDocCharCount(UniMode u);
	int getSelectedAreas();
	size_t getSelectedBytes();
	bool isFormatUnicode(UniMode);
	int getBOMSize(UniMode);

	void showAutoComp();
	void autoCompFromCurrentFile(bool autoInsert = true);
	void showFunctionComp();

	//void changeStyleCtrlsLang(HWND hDlg, int *idArray, const char **translatedText);
	bool replaceAllFiles();
	bool findInOpenedFiles();
	bool findInCurrentFile();

	bool matchInList(const TCHAR *fileName, const vector<generic_string> & patterns);
	void getMatchedFileNames(const TCHAR *dir, const vector<generic_string> & patterns, vector<generic_string> & fileNames, bool isRecursive, bool isInHiddenDir);

	void doSynScorll(HWND hW);
	void setWorkingDir(const TCHAR *dir);
	bool str2Cliboard(const TCHAR *str2cpy);
	bool bin2Cliboard(const UCHAR *uchar2cpy, size_t length);

	bool getIntegralDockingData(tTbData & dockData, int & iCont, bool & isVisible);
	int getLangFromMenuName(const TCHAR * langName);
	generic_string getLangFromMenu(const Buffer * buf);

    generic_string Notepad_plus::exts2Filters(generic_string exts) const;
	int setFileOpenSaveDlgFilters(FileDialog & fDlg, int langType = -1);
	void markSelectedTextInc(bool enable);
	Style * getStyleFromName(const TCHAR *styleName);
	bool dumpFiles(const TCHAR * outdir, const TCHAR * fileprefix = TEXT(""));	//helper func
	void drawTabbarColoursFromStylerArray();

	void loadCommandlineParams(const TCHAR * commandLine, CmdLineParams * pCmdParams);
	bool noOpenedDoc() const;
	bool goToPreviousIndicator(int indicID2Search, bool isWrap = true) const;
	bool goToNextIndicator(int indicID2Search, bool isWrap = true) const;
	int wordCount();
	
	void wsTabConvert(bool whichWay);
	void doTrim(trimOp whichPart);
};


#endif //NOTEPAD_PLUS_H
