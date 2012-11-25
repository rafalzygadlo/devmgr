#include <wx/wx.h>
#include <vector>
#include "conf.h"

class CTrack
{

		wxString FileName;
		wxString TrackName;
		std::vector <SPointInfo>  vPointInfo;
		std::vector <SPoint> vPoint;
		bool Visible;
		void SaveToFile();
		
	public:
		CTrack();
		~CTrack();
		size_t GetSize();
		std::vector<SPointInfo> CTrack::GetTrack();
		std::vector<SPoint> CTrack::GetTrackPoints();

		void AddPoint(double x, double y);
		void AddPointInfo(double x, double y, nmeaINFO *info);
		void LoadFromFile(wxString filename);
		wxString GetFileName();
		wxString GetTrackName();
		bool GetVisible();
		void SetVisible(bool value);
		
		void Render();
};

class CTrackList
{
		CTrack *Track;
		std::vector<CTrack*> vTracks;
		void LoadTracks();
		
	public:
	
		void AddTrack(CTrack *track);
		std::vector<CTrack*> CTrackList::GetList();
		size_t GetSize();
		CTrackList();
		~CTrackList();

};
