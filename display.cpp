#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>


BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	SetDisplayID(NDS_GPS);
	m_Broker = NULL;
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_Devices = new wxTreeCtrl(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	m_Root = m_Devices->AddRoot(_("Devices"));
	Sizer->Add(m_Devices,1,wxALL|wxEXPAND);
	this->SetSizer(Sizer);
	m_FirstTime = true;

};

CDisplayPlugin::~CDisplayPlugin()
{

}


//wxString CDisplayPlugin::GetCaption()
//{
	//return ArrayOfTypes[GetControlType()];
//}

void CDisplayPlugin::DrawData(wxGCDC &dc, wxString caption, wxString text)
{
	
	Caption = caption;
	int Size;
	
	wxFont Font;
	if(GetWidth() < GetHeight())
		Size = GetWidth() / 2;
	else
		Size = GetHeight() / 2;
	
	wxSize FontSize;

	Font.SetPointSize( GetHeight() / 4 * 2 ) ;
	dc.SetTextForeground(wxColor(0,0,0));  
	dc.SetFont( Font );

	FontSize = dc.GetTextExtent(text);

	if( FontSize.GetWidth() > GetWidth() ) 
	{
		do {

			Font.SetPointSize( Font.GetPointSize() - 1 );
			dc.SetFont( Font );
			FontSize = dc.GetTextExtent(text);
		} while ( FontSize.GetWidth() > GetWidth() );
	}

	dc.DrawText( text, GetWidth()/2 - FontSize.GetWidth()/2, GetHeight() * 0.625 - FontSize.GetHeight() / 2 );
	
}



bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) {

	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST && m_Broker == NULL)
	{
		m_Broker = (CNaviBroker*)SignalID->GetData();
		return false;
	}

	if(SignalID->GetSignalID() == NDS_DEVICE_MANAGER)
	{
		m_MapPlugin = (CMapPlugin*)SignalID->GetData();
		m_SignalType = m_MapPlugin->GetDisplaySignalType();
		m_DeviceId = m_MapPlugin->GetDeviceId();

		
		if(m_FirstTime)
		{
			m_FirstTime = false;
			m_MapPlugin = (CMapPlugin*)SignalID->GetData();
			for(size_t i = 0; i < m_MapPlugin->GetDevicesCount(); i++)
			{
				CMySerial *Serial = m_MapPlugin->GetDevice(i);
				wxTreeItemId id = m_Devices->AppendItem(m_Root,wxString::Format(_("%s"),Serial->GetDeviceName()));
				CList *List = new CList();
				List->SetSerial(Serial);
				m_Devices->SetItemData(id,List);
				//wxString port(Serial->GetPortName(),wxConvUTF8);
				//m_Devices->AppendItem(id,wxString::Format(_("Port: %s"),port.wc_str()));
				//m_Devices->AppendItem(id,wxString::Format(_("Baud: %d"),Serial->GetBaudRate()));
			
			}
			
			//m_Devices->ExpandAll();
		}else{
		
			//m_Devices->Setit
		
		}
		

		return false;
	}
	
	return false;
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{

	DrawData(dc,wxString::Format(_("dev id:%d"),m_DeviceId),wxString::Format(_("signal id%d"),m_SignalType));
}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal) 
{
		
	Refresh();
	//wxMilliSleep(50);

}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{

	
}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}




CList::CList()
{
	m_IsDir = false;
	m_FullPath = wxEmptyString;
	m_FilePath = wxEmptyString;
}

CList::~CList()
{
}

void CList::SetSerial(CMySerial *serial)
{
	m_Serial = serial;
}

wxString CList::GetFilePath()
{
	return m_FilePath;
}


void CList::SetFullPath(wxString &str)
{
	m_FullPath = str;
}

wxString CList::GetFullPath()
{
	return m_FullPath;
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