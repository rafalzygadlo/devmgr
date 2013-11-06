#ifndef __DEVICES
#define __DEVICES


class CDevices 
{

	CDevices();

	size_t GetLen(void);
	void Sort();
	struct TDataDefinition_s *GetItem(int id);
	struct TDataDefinition_s *GetMarker(int marker_id);


};

#endif