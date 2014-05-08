#ifndef __LIGHT_H
#define __LIGHT_H

#include "conf.h"
#include "GeometryTools.h"

class CLight
{
	CNaviArray <nvPoint2d> m_VerticesBuffer0;	CNaviArray <nvPoint2d> m_VerticesBuffer1;	CNaviArray <nvPoint2d> *m_CurrentVerticesBufferPtr;
	CNaviArray <int> m_IndicesBuffer0;			CNaviArray <int> m_IndicesBuffer1;			CNaviArray <int> *m_CurrentIndicesBufferPtr;

	int m_Width,m_Height;
	float m_OffsetX, m_OffsetY;
	nvRGBA m_Color;
	GLuint m_ArrayBuffer, m_IndicesBuffer;
	size_t m_IndicesLength;
	bool m_FirstTime;
	void CreateVBO();
	void Generate();
	bool IsBuffer();
	

public:

	CLight();
	~CLight();
	
	void AddIndice(int id);
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
	void RenderData();
	void Render();	
	
};


#endif