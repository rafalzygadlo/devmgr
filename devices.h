#ifndef __DEVICES
#define __DEVICES

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <vector>
#include <wx/treectrl.h>
#include "serial.h"
#include "item.h"

class CItem;
class CFrame;
class CSerial;
class CDevices: public wxPanel
{
	std::vector<CSerial*> vDevices;
	wxFileConfig  *FileConfig;
	wxTreeCtrl *Devices;
	wxTreeItemId Root;
	CSerial *SelectedDevice;
	wxTreeItemId SelectedItemId;
	CItem *SelectedItem;
	CFrame *Parent;
	wxString KeyName;
	bool Writer;
			
	void OnTreeMenu(wxTreeEvent &event);
	void OnItemActivated(wxTreeEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnStart(wxCommandEvent &event);
	void OnUninstall(wxCommandEvent &event);
	void OnConfigureDevice(wxCommandEvent &event);
	void OnConfigureData(wxCommandEvent &event);
	void OnAdd(wxCommandEvent &event);
	void OnSetLogger(wxCommandEvent &event);
	void OnStatus(wxCommandEvent &event);
	void ReadConfig();
	void WriteConfig();
	void SetGui();
	wxArrayString GetDevicesConfig(wxString path);
	void AddDevice(CSerial *serial);
	void RemoveDevice(CSerial *serial);
	void SetDevices();
	void ReindexDevices();
	
public:
	CDevices(CDisplayPlugin *parent, wxString key_name, bool writer = false);
	~CDevices();
	void SetRootName(wxString value);
	void OnLine(CSerial *serial);
	size_t GetDevicesCount();
	CSerial *GetDevice(size_t idx);
	
	
	DECLARE_EVENT_TABLE();

	enum 
	{
		ID_TREE = 4235,
		ID_START,
		ID_STOP,
		ID_CONFIGURE_DEVICE,
		ID_STATUS,
		ID_UNINSTALL,
		ID_ADD,
		ID_DEVICE,
		ID_DESTINATION,
	
	};

};


#endif
