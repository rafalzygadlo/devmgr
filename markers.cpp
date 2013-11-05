#include "conf.h"
#include "markers.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tools.h"

struct TDataDefinition_s MarkerTab[] = 
{
	#include "markers.dat"
	{-1,NULL,NULL,NULL,false},
};

size_t GetLen(void) 
{
	int id = 0;

	while( MarkerTab[id].DataID != -1 )
		id++;
	
	return id;
}

struct TDataDefinition_s *GetItem(int id)
{
	return &MarkerTab[id];
}

struct TDataDefinition_s *GetMarker(int marker_id)
{
	int id = 0;
	while( MarkerTab[id].DataID != -1 )
	{
		if(MarkerTab[id].DataID == marker_id)
			return &MarkerTab[id];
		id++;
		
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------------
/*
int GetParamNumber(const char *ParamName) {

	int id = 0;

	while( MarkerTab[id].name != NULL ) {

		if( strcmp( Grib2Tab[id].name, ParamName ) == 0 )
			return id;

		id++;
	};

	return -1;
};

const char *GetParamName(const char *ParamDesc) 
{

	int id = 0;

	while( MarkerTab[id].desc != NULL ) {

		if( strcmp( Grib2Tab[id].desc, ParamDesc ) == 0 )
			return Grib2Tab[id].name;

		id++;
	};

	return NULL;

};

const char *GetParamDescription(const char *ParamName) 
{

	int id = 0;

	while( MarkerTab[id].desc != NULL ) 
	{

		if( strcmp( Grib2Tab[id].name, ParamName ) == 0 )
			return Grib2Tab[id].desc;

		id++;
	};

	return NULL;

};



struct gribtab_s *GetGrib2Item(int ItemID) {

	return &Grib2Tab[ItemID];
};

const char *GetUnit(int ItemID) {
	
	return Grib2Tab[ItemID].unit;
};

int GetIsolinesCount(int ParamID) {

	return DEFAULT_ISOLINES_COUNT;
};

// ------------------------------------------------------------------------------------------------------

TGribVectorPair *IsParamInVectorTab(int IDParam1, int IDParam2) {

	int id = 0;

	while( GribVectorPairTab[ id ].IDParam1 != -1 ) {

		if( (GribVectorPairTab[ id ].IDParam1 == IDParam1) && (GribVectorPairTab[ id ].IDParam2 == IDParam2) )
			return &GribVectorPairTab[ id ];

		id++;
	};

	return NULL;
};

// ------------------------------------------------------------------------------------------------------

int GetConvId(const char *FromUnit, const wchar_t *ToUnit) {

	int id = 0;
	if( ToUnit == NULL )
		return -1;

	while( UnitConvTab[id].FromUnit != NULL ) {

		if( (strcmp(FromUnit, UnitConvTab[id].FromUnit) == 0) && (wcscmp(ToUnit, UnitConvTab[id].ToUnit) == 0)  )
			return id;

		id++;
	};
	return -1;
};

bool ConvertValue(const char *FromUnit, const wchar_t *ToUnit, double Value, double *Result) {

	int ConvId = GetConvId(FromUnit, ToUnit);
	TConvFn ConvFn;

	if( ConvId != -1 ) {

		ConvFn = UnitConvTab[ConvId].ConvFn;
		if( ConvFn != NULL ) {
			// istnieje funkcja konwertująca
			*Result = ConvFn(Value);
		} else {
			// nie istnieje funkcja konwertująca
			*Result = Value;
		};

		return true;
	} else {
		return false;
	};
};

// zwraca ilość możliwych konwersji dla wybranego unit'a
int GetConversionUnitsCount(const char *FromUnit) {

	int count = 0;
	int id = 0;
	while( UnitConvTab[id].FromUnit != NULL ) {

		if( strcmp(FromUnit, UnitConvTab[id].FromUnit) == 0 )
			count++;

		id++;
	};	

	return count;
};

wchar_t **GetConversionUnits(const char *FromUnit) {

	int ConvUnitsCount = GetConversionUnitsCount( FromUnit );
	wchar_t **tab = NULL;
	if( ConvUnitsCount > 0 ) {

		tab = (wchar_t**)malloc( sizeof(wchar_t**) * (ConvUnitsCount + 1) );
		memset(tab, NULL,  sizeof(wchar_t**) * (ConvUnitsCount + 1) );

		int id = 0, tab_id = 0;
		while( UnitConvTab[id].FromUnit != NULL ) {
			if( strcmp(FromUnit, UnitConvTab[id].FromUnit) == 0 ) {

				tab[tab_id] = CreateCopyWchar( UnitConvTab[id].ToUnit );
				tab_id++;
			};

			id++;
		};
	};
	return tab;
};

void FreeUnits(wchar_t **v) {

	int id = 0;
	while( v[id] != NULL ) {

		free( v[id] );
		id++;
	};

	free( v );
};

double KelvinToKelvin(double v) {

	return v;
};

double KelvinToCelsius(double v) {

	return v - 273.15;
};

double KelvinToFahrenheit(double v) {

	return ((v - 273.15) * 1.8) + 32;
};

double KelvinToRankine(double v) {

	return (v * 1.8);
};

double KelvinToReaumur(double v) {

	return (v - 273.15) * 4 / 5;
};

double KelvinToRomer(double v) {

	return ((v - 273.15) * 21 / 40) + 7.5;
};

double KelvinToDelisle(double v) {

	return (100.0 -(v - 273.15)) * 3 / 2;
};

double KelvinToNewton(double v) {

	return (v - 273.15) * 33 / 100;
};

double PaToPa(double v) {

	return v;
};

double PaTohPa(double v) {

	return v / 100.0;
};

double PaToBa(double v) {

	return v * 0.00001;
};

double PaTommHg(double v) {

	return v * 0.00750061683;
};

double PaToPsi(double v) {

	return v * 0.000145037738;
};

double msToms(double v) {

	return v;
};

double msTokmh(double v) {

	return v * 3.6;
};

double msTomph(double v) {

	return v * 2.236936;
};

double msTokn(double v) {

	return v * 1.943844;
};

double kgm2sTokgm2s(double v) {

	return v;
};

double kgm2sTommh(double v) {

	return v * 3600.0;
};

// ------------------------------------------------------------------------------------------------------

void UVWindConv(double inv1, double inv2, double *outv1, double *outv2) {

	*outv1 = sqrt( (inv1 * inv1) + (inv2 * inv2 ));
	*outv2 = (57.29578 * (atan2(inv1, inv2))) + 180.0;

};

void VUWindConv(double inv1, double inv2, double *outv1, double *outv2) {

	*outv1 = sqrt( (inv1 * inv1) + (inv2 * inv2 ));
	*outv2 = (57.29578 * (atan2(inv2, inv1))) + 180.0;

};
*/