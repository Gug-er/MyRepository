/*
this file is part of notepad++
Copyright (C)2003 Don HO < donho@altern.org >

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef PREFERENCE_DLG_H
#define PREFERENCE_DLG_H

#ifndef CONTROLS_TAB_H
#include "ControlsTab.h"
#endif //CONTROLS_TAB_H

#ifndef PREFERENCE_RC_H
#include "preference_rc.h"
#endif //PREFERENCE_RC_H

#ifndef URLCTRL_INCLUDED
#include "URLCtrl.h"
#endif //URLCTRL_INCLUDED

#ifndef PARAMETERS_H
#include "Parameters.h"
#endif //PARAMETERS_H

#ifndef REG_EXT_DLG_H
#include "regExtDlg.h"
#endif //REG_EXT_DLG_H

#ifndef WORD_STYLE_H
#include "WordStyleDlg.h"
#endif //WORD_STYLE_H

class SettingsDlg : public StaticDialog
{
public :
	SettingsDlg() {};
	virtual void destroy() {
		_nbHistoryVal.destroy();
	};
private :
	URLCtrl _nbHistoryVal;
	bool isCheckedOrNot(int checkControlID) const {
		return (BST_CHECKED == ::SendMessage(::GetDlgItem(_hSelf, checkControlID), BM_GETCHECK, 0, 0));
	};
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};

class BarsDlg : public StaticDialog
{
public :
	BarsDlg() {};
private :
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};

class MarginsDlg : public StaticDialog
{
public :
	MarginsDlg() {};
	virtual void destroy() {
		_verticalEdgeLineNbColVal.destroy();
	};
	
private :
	URLCtrl _verticalEdgeLineNbColVal;
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	void initScintParam();
};

struct LangID_Name
{
	LangType _id;
	generic_string _name;
	LangID_Name(LangType id, generic_string name) : _id(id), _name(name){};
};

class DefaultNewDocDlg : public StaticDialog
{
public :
	DefaultNewDocDlg() {};
private :
	std::vector<LangID_Name> _langList;
	void makeOpenAnsiAsUtf8(bool doIt){
		if (!doIt)
			::SendDlgItemMessage(_hSelf, IDC_CHECK_OPENANSIASUTF8, BM_SETCHECK, BST_UNCHECKED, 0);
		::EnableWindow(::GetDlgItem(_hSelf, IDC_CHECK_OPENANSIASUTF8), doIt);
	};
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};

class LangMenuDlg : public StaticDialog
{
public :
	LangMenuDlg() {};
    virtual void destroy() {
		_tabSizeVal.destroy();
	};

private :
    URLCtrl _tabSizeVal;
    LexerStylerArray _lsArray;
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	vector<LangMenuItem> _langList;
};

struct strCouple {
	generic_string _varDesc;
	generic_string _var;
	strCouple(TCHAR *varDesc, TCHAR *var): _varDesc(varDesc), _var(var){};
};

class PrintSettingsDlg : public StaticDialog
{
public :
	PrintSettingsDlg():_focusedEditCtrl(0), _selStart(0), _selEnd(0){};
private :
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	vector<strCouple> varList;
	int _focusedEditCtrl;
	DWORD _selStart;
	DWORD _selEnd;
};

class BackupDlg : public StaticDialog
{
public :
	BackupDlg() {};
private :
	URLCtrl _nbCharVal;
	void updateBackupGUI();
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};



/*
class PrintSettings2Dlg : public StaticDialog
{
public :
	PrintSettings2Dlg():_focusedEditCtrl(0), _selStart(0), _selEnd(0){};
private :
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);

};
*/

class PreferenceDlg : public StaticDialog
{
//friend class Notepad_plus;
friend class NativeLangSpeaker;

public :
	PreferenceDlg(){};

    void init(HINSTANCE hInst, HWND parent)	{
        Window::init(hInst, parent);
	};

    void doDialog(bool isRTL = false) {
    	if (!isCreated())
		{
			create(IDD_PREFERENCE_BOX, isRTL);
			goToCenter();
		}
	    display();
    };

	virtual void destroy() {
		_ctrlTab.destroy();
		_barsDlg.destroy();
		_marginsDlg.destroy();
		_settingsDlg.destroy();
		_fileAssocDlg.destroy();
		_langMenuDlg.destroy();
		_printSettingsDlg.destroy();
		//_printSettings2Dlg.destroy();
		_defaultNewDocDlg.destroy();
	};
private :
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	ControlsTab _ctrlTab;
	WindowVector _wVector;
	BarsDlg _barsDlg;
	MarginsDlg _marginsDlg;
	SettingsDlg _settingsDlg;
	RegExtDlg _fileAssocDlg;
	LangMenuDlg _langMenuDlg;
	PrintSettingsDlg _printSettingsDlg;
	//PrintSettings2Dlg _printSettings2Dlg;
	DefaultNewDocDlg _defaultNewDocDlg;
	BackupDlg _backupDlg;
};



#endif //PREFERENCE_DLG_H