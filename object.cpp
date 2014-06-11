#include "Glee.h"
#include "object.h"


CObject::CObject()
{
	m_IndicesLength = 0;
	m_CurrentVerticesBufferPtr = NULL;
	m_CurrentIndicesBufferPtr = NULL;
	m_Width = 0;
	m_Height = 0;
	m_Color.R = 255;
	m_Color.G = 255;
	m_Color.B = 255;
	m_Color.A = 200;
	m_OffsetX = 0;
	m_OffsetY = 0;
	m_RenderMode = GL_TRIANGLES;
}	

CObject::~CObject(void)
{

}

void CObject::SetOffset(float vx, float vy)
{
	m_OffsetX = vx;
	m_OffsetY = vy;
}

void CObject::SetColor(nvRGBA color)
{
	m_Color = color;
}

void CObject::AddPoint(nvPoint2d pt)
{
	AddVertex(pt);
}

void CObject::Add(nvPoint2d pt, double factor)
{
	nvPoint2d p1, p2, p3, p4;
	double width = m_Width/factor;
	double height = m_Height/factor;
			
	p1.x = (-1.0 + m_OffsetX) * width;	p1.y = ( 1.0 + m_OffsetY) * height;
	p2.x = ( 1.0 + m_OffsetX) * width;	p2.y = ( 1.0 + m_OffsetY) * height;
	p3.x = ( 1.0 + m_OffsetX) * width;	p3.y = (-1.0 + m_OffsetY) * height;
	p4.x = (-1.0 + m_OffsetX) * width;	p4.y = (-1.0 + m_OffsetY) * height;
	
	p1.x += pt.x; p1.y += pt.y;
	p2.x += pt.x; p2.y += pt.y;
	p3.x += pt.x; p3.y += pt.y;
	p4.x += pt.x; p4.y += pt.y;
		
	AddVertex(p1);
	AddVertex(p2);
	AddVertex(p3);
	AddVertex(p4);

	int id = GetVertexLength();
		
	AddIndice(id - 4);	//0
	AddIndice(id - 3);	//1
	AddIndice(id - 2);	//2
	AddIndice(id - 4);	//0
	AddIndice(id - 2);	//2
	AddIndice(id - 1);	//3

}


void CObject::AddIndice(int id)
{
	m_IndicesBuffer0.Append(id);
}

size_t CObject::GetIndiceLength()
{
	return	m_IndicesBuffer0.Length();
}

int *CObject::GetIndiceArray()
{
	return m_IndicesBuffer0.GetRawData();
}


void CObject::AddVertex(nvPoint2d pt)
{
	m_VerticesBuffer0.Append(pt);
}

size_t CObject::GetVertexLength()
{
	return	m_VerticesBuffer0.Length();
}

nvPoint2d *CObject::GetVertexArray()
{
	return m_VerticesBuffer0.GetRawData();
}

void CObject::ClearBuffers()
{
	m_VerticesBuffer0.Clear();
	m_IndicesBuffer0.Clear();
}

void CObject::CopyBuffers()
{
	m_VerticesBuffer1.Clear();
	m_VerticesBuffer1.SetSize(m_VerticesBuffer0.Length());
	
	for(size_t i = 0; i < m_VerticesBuffer0.Length(); i++)
		m_VerticesBuffer1.Set(i,m_VerticesBuffer0.Get(i));

	m_IndicesBuffer1.Clear();
	m_IndicesBuffer1.SetSize(m_IndicesBuffer0.Length());
	
	for(size_t i = 0; i < m_IndicesBuffer0.Length(); i++)
		m_IndicesBuffer1.Set(i,m_IndicesBuffer0.Get(i));

}

void CObject::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

bool CObject::IsBuffer()
{
	if(m_CurrentVerticesBufferPtr == NULL)
		return false;

	if(m_CurrentVerticesBufferPtr->Length() == 0)
		return false;
	
	return true;
}

void CObject::Generate()
{
	if(m_FirstTime)
	{
		glGenBuffers(1, &m_ArrayBuffer);
		glGenBuffers(1, &m_IndicesBuffer);
		m_FirstTime = false;
	}
}

void CObject::SetCurrentPtr(bool buffer)
{
	if(buffer)
	{
		m_CurrentVerticesBufferPtr = &m_VerticesBuffer1;
		m_CurrentIndicesBufferPtr = &m_IndicesBuffer1;
	
	}else{
	
		m_CurrentVerticesBufferPtr = &m_VerticesBuffer0;
		m_CurrentIndicesBufferPtr = &m_IndicesBuffer0;
	}

}

void CObject::SetRenderMode(GLenum mode)
{
	m_RenderMode = mode;
}

void CObject::CreateVBO()
{
	//trójkaty
	glBindBuffer(GL_ARRAY_BUFFER, m_ArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nvPoint2d) * m_CurrentVerticesBufferPtr->Length(), m_CurrentVerticesBufferPtr->GetRawData(), GL_STATIC_DRAW);
			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_CurrentIndicesBufferPtr->Length(), m_CurrentIndicesBufferPtr->GetRawData(), GL_STATIC_DRAW);
		
	//glBindBuffer(GL_ARRAY_BUFFER, m_BSColorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(nvRGBA) * m_CurrentBSColorBufferPtr->Length(), m_CurrentBSColorBufferPtr->GetRawData(), GL_STATIC_DRAW);
	
	m_IndicesLength = m_CurrentIndicesBufferPtr->Length();

}

void CObject::RenderData()
{

	glColor4ub(m_Color.R,m_Color.G,m_Color.B,m_Color.A);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_ArrayBuffer);
	glVertexPointer(2, GL_DOUBLE,  0, 0);
		
	//glBindBuffer(GL_ARRAY_BUFFER, m_BSColorBuffer);
	//glColorPointer(4, GL_UNSIGNED_BYTE,  0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuffer);
	glDrawElements(m_RenderMode, m_IndicesLength, GL_UNSIGNED_INT,0);
			
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void CObject::Render()
{
	if(!IsBuffer())
		return;
	
	Generate();
	CreateVBO();
	RenderData();
}