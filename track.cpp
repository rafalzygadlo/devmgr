#include <wx/file.h>
#include <wx/dir.h>
#include "track.h"
#include "tools.h"

CTrack::CTrack()
{
	
	TrackName = _("Track");
}

CTrack::~CTrack()
{
	SaveToFile();	
}

void CTrack::AddPointInfo(double x, double y, nmeaINFO *info)
{
	SPointInfo Track;
    Track.x = x;
    Track.y = y;
	memset(&Track,0,sizeof(nmeaINFO));
	memcpy(&Track.nmea_info,info,sizeof(nmeaINFO));
    vPointInfo.push_back(Track);
}

void CTrack::AddPoint(double x, double y)
{
	SPoint Point;
    Point.x = x;
    Point.y = y;
	vPoint.push_back(Point);
}

void CTrack::LoadFromFile(wxString filename)
{

	FileName = filename;
	wxFile file;
	if(file.Exists(filename))
	{
		
		if(file.Open(filename))
		{
			STrackHeader *header_buffer = (STrackHeader*)malloc(sizeof(STrackHeader));
			file.Read(header_buffer,sizeof(STrackHeader));
			wxString str(header_buffer->track_name);
			TrackName = str;
			Visible = header_buffer->visible;
			
			SPointInfo *buffer = (SPointInfo*)malloc(sizeof(SPointInfo));
			memset(buffer,0,sizeof(SPointInfo));
			while(!file.Eof())
			{	
				file.Read(buffer,sizeof(SPointInfo));
				AddPoint(buffer->x,buffer->y);
				AddPointInfo(buffer->x,buffer->y,&buffer->nmea_info);
			}
		
			file.Close();
		}
	}

}

void CTrack::SaveToFile()
{
	if(vPointInfo.size() > 0)
	{
		wxFile file;
		wxString filename = GenerateRandomFileName(GetWorkDir(),_(TRACK_FILE_EXTENSION),10);
		STrackHeader Header;
		wcscpy(Header.track_name,TrackName.wc_str());
		Header.visible = Visible;
				
		if(file.Open(wxString::Format(_("%s"),filename),wxFile::write))
		{
			file.Write(&Header,sizeof(STrackHeader));
			for(unsigned int i = 0; i < vPointInfo.size();i++)	
				file.Write(&vPointInfo[i],sizeof(vPointInfo));
		}
		
		file.Close();
	}

}

std::vector<SPointInfo> CTrack::GetTrack()
{
	return vPointInfo;
}

std::vector<SPoint> CTrack::GetTrackPoints()
{
	return vPoint;
}

wxString CTrack::GetFileName()
{
	return FileName;

}

wxString CTrack::GetTrackName()
{
	return TrackName;
}

bool CTrack::GetVisible()
{
	return Visible;
}

void CTrack::SetVisible(bool value)
{
	Visible = value;
}



//..........................................................................................................
//
// Track list - lista tras gps'a
//
//..........................................................................................................
CTrackList::CTrackList()
{
	LoadTracks();
}

CTrackList::~CTrackList()
{

}
void CTrackList::AddTrack(CTrack *track)
{
	vTracks.push_back(track);
}

void CTrackList::LoadTracks()
{
	
	wxDir dir(GetWorkDir());

    if(!dir.IsOpened())
        return;

    wxString filename;
	
	bool ok = dir.GetFirst(&filename,wxString::Format(wxT("*.%s"),_(TRACK_FILE_EXTENSION)), wxDIR_DEFAULT );

    while( ok )
    {
        wxString fullpath = wxString::Format(wxT("%s%s%s"),dir.GetName().wc_str(), wxT(DIR_SEPARATOR), filename.wc_str());
		Track = new CTrack();
		Track->LoadFromFile(fullpath);
		vTracks.push_back(Track);
        ok = dir.GetNext(&filename);
    }
	
}

std::vector<CTrack*> CTrackList::GetList() 
{
	return vTracks;
}

size_t CTrackList::GetSize() 
{
	return vTracks.size();

}
