#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	

};

CDisplayPlugin::~CDisplayPlugin()
{

}


//wxString CDisplayPlugin::GetCaption()
//{
	//return ArrayOfTypes[GetControlType()];
//}


bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST && Broker == NULL)
	{
		Broker = (CNaviBroker*)SignalID->GetData();
		return false;
	}

	if(SignalID->GetSignalID() == NDS_GPS)
	{
		MapPlugin = (CMapPlugin*)SignalID->GetData();
		return true;
	}
	
	return false;
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{

}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	Refresh();
	wxMilliSleep(300);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{

	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}

const wchar_t *NaviDisplayIntroduce(int LanguageID) 
{

	switch( LanguageID ) 
	{

		case 0: 
			return L"devmgr";
			break;

		default:
			return L"devmgr";
	}

}

const int NaviDisplayID()
{
	return NDS_GPS;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}