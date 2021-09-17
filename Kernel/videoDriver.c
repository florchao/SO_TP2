#include <videoDriver.h>

// aca estaría mejor armar un TAD

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

static void scroll() 
{
	currentVideo = video;
	uint8_t * aux = video + width * 2;
	while( aux < video + width * 2 * height) 
	{
		writeAscii(*aux, getInformation(aux));
		aux+=2;
	}
	aux -= width * 2;
	currentVideo = aux;
	clearLine(currentVideo);
}

static int getInformation(uint8_t * dir)
{
	return *(dir+1);
}

// habria que tocar el color? podria usar directamente la de imprimir el char con el color negro
static void clearLine(uint8_t * p) 
{
	for(int i = 0; i < width; i++)
		p[i * 2] = ' ';
}

void writeAscii(char character, int color)
{
	if(currentVideo ==  video + width * 2 * height) {
		scroll();
	}

	*currentVideo = character;
	*(currentVideo + 1) = color;
	currentVideo += 2;
}

void clearScreen()
{ // este deberia aprovechar clearLine
	int i;
	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

void newLine()
{
	do
	{
		writeAscii(' ', 0); // podria definir BLACK
	} while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void clearLastAscii()
{
	writeAscii(' ', 0);
	currentVideo-=2;
}

