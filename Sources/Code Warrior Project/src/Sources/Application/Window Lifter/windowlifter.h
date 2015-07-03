#define 	pinch 64
#define 	up 65
#define 	down 66
#define		bdown	SIU.GPDI[down].R == 0
#define		bup		SIU.GPDI[up].R == 0
#define		bapinch	SIU.GPDI[pinch].R == 0

void downmanual(void);
void autodown(void);
void upmanual(void);
void autoup(void);