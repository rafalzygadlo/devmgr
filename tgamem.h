// TGA Load From Memory
// Written by(2011): Bruno Szymkowiak

#ifndef __TGAMEM_H
#define __TGAMEM_H

typedef struct {
	void *Ptr;
	long Size;
} TMemoryBlock;

typedef struct {
	unsigned char Header[12];
} TTGAHeader;

typedef struct {
	unsigned int	Width;
	unsigned int	Height;
	unsigned int	Bpp;
	unsigned int	Type;
	unsigned int	ID;
	unsigned char	*Data;
} TTexture;

typedef struct {
	unsigned char		Header[6];
	unsigned int		TytesPerPixel;
	unsigned int		TmageSize;
	unsigned int		Temp;
	unsigned int		Type;
	unsigned int		Height;
	unsigned int		Width;
	unsigned int		Bpp;
} TTGA;


TTexture* LoadFromMemoryBlockTGA(TMemoryBlock *MemoryBlock);
void FreeTexture(TTexture *_Texture);

#endif  // __TGAMEM_H
