#ifndef __MARKER
#define __MARKER

size_t GetLen(void);
struct TDataDefinition_s *GetItem(int id);
struct TDataDefinition_s *GetMarker(int marker_id);
//int GetParamNumber(const char *ParamName);
//const char *GetParamName(const char *ParamDesc);
//const char *GetParamDescription(const char *ParamName); 
//int GetGrib2TabLen(void);
//struct gribtab_s *GetGrib2Item(int ItemID);
//const char *GetUnit(int ItemID);

#endif