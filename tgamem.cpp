// TGA Load From Memory
// Written by(2011): Bruno Szymkowiak

#include "tgamem.h"
#include <string.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#endif
#include <GL/glu.h>

unsigned char uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// uncompressed
unsigned char cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// compressed

bool ReadUncompressedTGA( const TMemoryBlock *MemoryBlock, TTexture *Texture );
bool ReadCompressedTGA( const TMemoryBlock *MemoryBlock, TTexture *Texture );

void FreeTexture(TTexture *_Texture) {

    if( _Texture == NULL )
        return;

    if( _Texture->Data != NULL )
        free(_Texture->Data);

    free( _Texture );
}

TTexture* LoadFromMemoryBlockTGA(TMemoryBlock *MemoryBlock) {

	TTGAHeader	TGAHeader;
	TTexture	*Texture = (TTexture*)malloc( sizeof(TTexture) );
    Texture->Data = NULL;

	memcpy( &TGAHeader, (char*)MemoryBlock->Ptr, sizeof( TTGAHeader ) );

	if( memcmp( &TGAHeader, uTGAcompare, sizeof(TTGAHeader) ) == 0 ) {

		if( !ReadUncompressedTGA(MemoryBlock, Texture) ) {
		    free( Texture );
			return NULL;
		};
	} else {

		if( !ReadCompressedTGA(MemoryBlock, Texture) ) {
		    free( Texture );
			return NULL;
		};
	};

	return Texture;
};

bool ReadUncompressedTGA( const TMemoryBlock *MemoryBlock, TTexture *Texture ) {

	 TTGA TGA;

	memcpy( &TGA.Header, (char*)MemoryBlock->Ptr + sizeof( TTGAHeader ), sizeof( TGA.Header ) );
	Texture->Width = TGA.Header[1] * 256 + TGA.Header[0];
	Texture->Height = TGA.Header[3] * 256 + TGA.Header[2];
	Texture->Bpp = TGA.Header[4];

	if( Texture->Bpp == 24 )
		Texture->Type = GL_RGB;
	else
		Texture->Type = GL_RGBA;

	unsigned int ImageSize = (Texture->Bpp / 8) * Texture->Width * Texture->Height;
	Texture->Data = (GLubyte*)malloc( ImageSize );

	memcpy( Texture->Data, (char*)MemoryBlock->Ptr + sizeof( TTGAHeader ) + sizeof( TGA.Header ), ImageSize );


	for(GLuint i = 0; i < ImageSize; i += (Texture->Bpp / 8)) {
		Texture->Data[i] ^= Texture->Data[i+2] ^=
		Texture->Data[i] ^= Texture->Data[i+2];
	};

	return true;
};

bool ReadCompressedTGA( const TMemoryBlock *MemoryBlock, TTexture *Texture ) {

	TTGA TGA;

	memcpy( &TGA.Header, (char*)MemoryBlock->Ptr + sizeof( TTGAHeader ), sizeof( TGA.Header ) );
	Texture->Width = TGA.Header[1] * 256 + TGA.Header[0];
	Texture->Height = TGA.Header[3] * 256 + TGA.Header[2];
	Texture->Bpp = TGA.Header[4];

	if( Texture->Bpp == 24 )
		Texture->Type = GL_RGB;
	else
		Texture->Type = GL_RGBA;

	int BytesPerPixel = Texture->Bpp / 8;
	int ImageSize = BytesPerPixel * Texture->Width * Texture->Height;
	Texture->Data = (GLubyte*)malloc( ImageSize );

	unsigned int PixelCount = Texture->Width * Texture->Height;
	GLuint CurrentPixel	= 0;
	GLuint CurrentByte	= 0;
	GLubyte *ColorBuffer = (GLubyte *)malloc( BytesPerPixel );
	int id = sizeof( TTGAHeader ) + sizeof( TGA.Header );

	do {

		GLubyte ChunkHeader = 0;
		memcpy( &ChunkHeader, (char*)MemoryBlock->Ptr + id , sizeof( GLubyte ) );
		id += sizeof( GLubyte );

		if( ChunkHeader < 128 ) {

			ChunkHeader++;
			for(int Counter = 0; Counter < ChunkHeader; Counter++ ) {

				memcpy( ColorBuffer, (char*)MemoryBlock->Ptr + id, BytesPerPixel);
				id += BytesPerPixel;

				Texture->Data[ CurrentByte     ] = ColorBuffer[2];
				Texture->Data[ CurrentByte + 1 ] = ColorBuffer[1];
				Texture->Data[ CurrentByte + 2 ] = ColorBuffer[0];

				if( BytesPerPixel == 4 )
					Texture->Data[ CurrentByte + 3 ] = ColorBuffer[3];

				CurrentByte += BytesPerPixel;
				CurrentPixel++;

			};

		} else {

			ChunkHeader -= 127;
			memcpy( ColorBuffer, (char*)MemoryBlock->Ptr + id, BytesPerPixel);
			id += BytesPerPixel;
			for(int Counter = 0; Counter < ChunkHeader; Counter++ ) {


				Texture->Data[ CurrentByte     ] = ColorBuffer[2];
				Texture->Data[ CurrentByte + 1 ] = ColorBuffer[1];
				Texture->Data[ CurrentByte + 2 ] = ColorBuffer[0];

				if( BytesPerPixel == 4 )
					Texture->Data[ CurrentByte + 3 ] = ColorBuffer[3];

				CurrentByte += BytesPerPixel;
				CurrentPixel++;

			};


		};


	} while ( CurrentPixel < PixelCount );

	free( ColorBuffer );
	return true;
};

