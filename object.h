#ifndef __OBJECT_H
#define __OBJECT_H

#include "conf.h"
#include "GeometryTools.h"
#include "nvFastFont.h"
#include "NaviBroker.h"

class CObject
{
	CNaviArray <nvPoint2d> m_VerticesBuffer0;	CNaviArray <nvPoint2d> m_VerticesBuffer1;	CNaviArray <nvPoint2d> *m_CurrentVerticesBufferPtr;
	CNaviArray <int> m_IndicesBuffer0;			CNaviArray <int> m_IndicesBuffer1;			CNaviArray <int> *m_CurrentIndicesBufferPtr;
	CNaviArray <SAisNames*> m_FontBuffer0;		CNaviArray <SAisNames*> m_FontBuffer1;		CNaviArray <SAisNames*> *m_CurrentFontBufferPtr;
	
	int m_Width,m_Height;
	float m_OffsetX, m_OffsetY;
	nvRGBA m_Color;
	GLuint m_ArrayBuffer, m_IndicesBuffer;
	size_t m_IndicesLength;
	GLenum m_RenderMode;
	nvFastFont *m_Font;
	bool m_FirstTime;
	void CreateVBO();
	void Generate();
	bool IsBuffer();
	

public:

	CObject();
	~CObject();
	
	void InitGL();
	void AddIndice(int id);
	void AddPoint(nvPoint2d pt);
	void AddText(double x, double y, wchar_t *txt);
	size_t GetIndiceLength();
	int *GetIndiceArray();
	void Add(nvPoint2d pt, double factor);
	void AddVertex(nvPoint2d pt);
	void SetSize(int width, int height);
	size_t GetVertexLength();
	nvPoint2d *GetVertexArray();
	void ClearBuffers();
	void CopyBuffers();
	void SetCurrentPtr(bool buffer);
	void SetColor(nvRGBA color);
	void SetOffset(float vx, float vy);
	void SetRenderMode(GLenum mode);
	void RenderData();
	void RenderFont();
	void Render();	
	
};


#endif