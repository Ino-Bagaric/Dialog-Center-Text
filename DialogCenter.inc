/*
	---------------------------------------

		Dialog Center Text
		@author: Ino
		@version: 1.0.2
		@release: 27/12/2016
		@build: 3	
		@download: github.com/Ino42O/Dialog-Center-Text

	---------------------------------------

	 	Changelog:

	 		27-12-2016:
	 			* Initial release

	 		28-12-2016:
	 			* Fixed space char
	 			* Added new characters

	 		10-01-2017:
	 			* Added support for caption (title) [beta]



	 	Thanks to:
	 		[uL]Kanada42O - Consultations

	---------------------------------------
*/

#include <a_samp>


#define _INC_CENTER_DIALOG // For other includes


static const stock letters[ ] [ ] = 
{
	// Uppercase
	{ 'A' , 12},
	{ 'B' , 11}, 
	{ 'C' , 11},  
	{ 'D' , 11},  
	{ 'E' , 10},  
	{ 'F' ,  9},  
	{ 'G' , 12},  
	{ 'H' , 11},  
	{ 'I' ,  4},  
	{ 'J' ,  9},  
	{ 'K' , 12}, 
	{ 'L' ,  9}, 
	{ 'M' , 13},  
	{ 'N' , 11},  
	{ 'O' , 12},  
	{ 'P' , 10},  
	{ 'Q' , 12},  
	{ 'R' , 12},  
	{ 'S' , 10},  
	{ 'T' , 10},  
	{ 'U' , 11},  
	{ 'V' , 11},  
	{ 'W' , 15},  
 	{ 'X' , 12},  
	{ 'Y' , 12},  
	{ 'Z' , 10}, 

	// Lowercase
	{ 'a' ,  9}, 
	{ 'b' ,  9}, 
	{ 'c' ,  8}, 
	{ 'd' ,  9}, 
	{ 'e' ,  9}, 
	{ 'f' ,  8}, 
	{ 'g' ,  9}, 
	{ 'h' ,  9}, 
	{ 'i' ,  4}, 
	{ 'j' ,  5}, 
	{ 'k' ,  9}, 
	{ 'l' ,  4}, 
	{ 'm' , 12}, 
	{ 'n' ,  9}, 
	{ 'o' ,  9}, 
	{ 'p' ,  9}, 
	{ 'q' ,  9}, 
	{ 'r' ,  7}, 
	{ 's' ,  8}, 
	{ 't' ,  7}, 
	{ 'u' ,  9}, 
	{ 'v' , 11}, 
	{ 'w' , 13}, 
	{ 'x' , 11}, 
	{ 'y' ,  9}, 
	{ 'z' ,  8},

	// Numbers
	{ '1' ,  7},
	{ '2' ,  9},
	{ '3' ,  9},
	{ '4' ,  9},
	{ '5' ,  9},
	{ '6' ,  9},
	{ '7' ,  9},
	{ '8' ,  9},
	{ '9' ,  9},
	{ '0' ,  9},

	// Special characters
	{ '!' ,  4},
	{ '"' ,  8}, 
	{ '$' ,  9}, 
	{ '%' , 14}, 
	{ '&' , 12}, 
	{ '/' ,  6}, 
	{ '(' ,  6}, 
	{ ')' ,  6}, 
	{ '=' , 10}, 
	{ '?' , 10}, 
	{ '+' , 10}, 
	{ '\'',  4}, 
	{ '[' ,  6}, 
	{ ']' ,  6}, 
	{ '-' ,  6}, 
	{ '.' ,  4}, 
	{ ',' ,  4},
	{ '|' ,  4},
	{ '_' , 10},
	{ '#' ,  9},
	{ '^' , 10},
	{ '~' , 10},
	{ ' ' ,  3}
};

#define MAX_LINES 	(100)

static 
	centerBuffer[0xF06],
	centerTitle [0xFA],
	bool:use = false
;

stock dcenter_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	new defaultSize;

	switch (style)
	{
		case DIALOG_STYLE_MSGBOX: 			{ defaultSize = 0xC8; }
		case DIALOG_STYLE_INPUT: 			{ defaultSize = 0xC8; }
		case DIALOG_STYLE_LIST: 			{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		case DIALOG_STYLE_PASSWORD: 		{ defaultSize = 0xC8; }
		case DIALOG_STYLE_TABLIST: 			{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		case DIALOG_STYLE_TABLIST_HEADERS: 	{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); } // Still in progress
		default: 							{ return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2); }
	}


	if (use) return dcenter_ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);

	use = true;

	centerBuffer[0] = '\0';
	centerTitle [0] = '\0';

	new 
			 lineInfo 	 [MAX_LINES],
			 lineSize 	 [MAX_LINES],
			 lineSpace	 [MAX_LINES],
		bool:lineCenter  [MAX_LINES],
		bool:titleCenter,
			 centered,
			 biggest,
			 biggestID,
			 line = 0,

			 // Find centers
			 cpos = -2,
			 tpos = -2,

			 // Count lines
			 pos = -2,
			 lines = 0
	;	


	while (-1 != ( pos = strfind(info, "\n", false, pos + 2) ) ) lines++;

	if (lines != 0) 
		lines++;

	if (lines > 0)
	{
		// Find positions for new line
		for (new i = 0, c = 0; i < strlen(info); i++)
		{
			if (info[i] == '\n')
				lineInfo[c++] = i;

			if (i == strlen(info) - 1) lineInfo[c] = strlen(info);
		}

		for (new i = 0; i < lines; i++)
		{
			if (i == 0)	lineSize[i] = lineInfo[i];
			else if (0 < i < lines) lineSize[i] = (lineInfo[i] - lineInfo[i - 1] - 1);
		}
	}


	new tmp[3];

	// Center title
	strmid(tmp, caption, 0, 3);
	if (strfind(tmp, "\\c", false) != -1)
		titleCenter = true;


	if (lines > 0)
	{
		for (new i = 0; i < lines; i++)
		{
			
			if (i == 0)
			{
				strmid(tmp, info, 0, 3);

				if (strfind(tmp, "\\c", false) != -1)
				{
					lineCenter[i] = true;
					centered++;
				}
			}
			else 
			{
				strmid(tmp, info, (lineInfo[i - 1] + 1), (lineInfo[i - 1] + 4));

				if (strfind(tmp, "\\c", false) != -1)
				{
					lineCenter[i] = true;
					centered++;
				}
			}
		}
	}
	else
	{
		strmid(tmp, info, 0, 3);

		if (strfind(tmp, "\\c", false) != -1)
		{
			lineCenter[0] = true;
			centered++;
		}
	}


	format (centerBuffer, sizeof(centerBuffer), "%s", info);
	format (centerTitle,  sizeof(centerTitle),  "%s", caption);


	// Find biggest line
	if (lines > 0)
	{
		for (new i = 0; i < lines; i++)
		{
			new t1 = ( (lines > 0) ? ( (i == 0) ? (0) : (lineInfo[i - 1] + 1) ) : (0) );
			new t2 = ( (lines > 0) ? (lineInfo[i]) : (strlen(info)) );
			for (new u = t1; u < t2; u++)
			{
				if (centerBuffer[u] == '{')
				{
					u += 7;
					continue;
				}

				for (new j = 0; j < sizeof(letters); j++)
				{
					if (centerBuffer[u] == letters[j][0])
					{
						lineSpace[i] += letters[j][1];
						break;
					}
				}
			}
		}

		biggest = 0;
		for (new i = 0; i < lines; i++)
		{
			if (lineSpace[i] > biggest)
			{
				biggest = lineSpace[i];
				biggestID = i;
			}
		}
	}


	// Title
	if (!titleCenter) goto skip_title;

	new titleSpace;

	for (new i = 0; i < strlen(caption); i++)
	{
		if (centerTitle[i] == '{')
		{
			i += 7;
			continue;
		}

		for (new j = 0; j < sizeof(letters); j++)
		{
			if (centerTitle[i] == letters[j][0])
			{
				if (centerTitle[i] == ' ') titleSpace += letters[j][1] + 3;
				else titleSpace += letters[j][1] - 2;
				break;
			}
		}
	}

	if (titleSpace < defaultSize)
	{
		new loop;
		if (biggest < defaultSize)            loop = ( ( ( (defaultSize - titleSpace) / 4) / 2) + 4) - ( (centered == 0) ? (1) : (0));
		else 
		{
			if 	    (0xC8  < biggest < 0x15E) loop = ( ( ( (biggest - titleSpace) / 4) - 2) / 2) + 3 + ( (centered == 0) ? (1) : (0));
			else if (0x15E < biggest < 0x17C) loop = ( ( ( (biggest - titleSpace) / 4) - 2) / 2) + 4 + ( (centered == 0) ? (2) : (0));
			else if (0x17C < biggest < 0x258) loop = ( ( ( (biggest - titleSpace) / 4) - 4) / 2) + 3 + ( (centered == 0) ? (1) : (0));
			else if (0x258 < biggest < 0x384) loop = ( ( ( (biggest - titleSpace) / 4) - 5) / 2) + 3 + ( (centered == 0) ? (2) : (0));
			else 	                          loop = ( ( ( (biggest - titleSpace) / 4) - 7) / 2) + 1 + ( (centered == 0) ? (1) : (0));
		}

		for (new i = 0; i < loop; i++)
		{
			strins(centerTitle, " ", i);
		}
	}

	skip_title:

	generate_line:

	if (!lineCenter[line])
		goto generate_fail;

	new space = 0;


	for (new i = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) ); i < ( (lines > 0) ? (lineInfo[line]) : (strlen(info)) ); i++)
	{
		if (centerBuffer[i] == '{')
		{
			i += 7;
			continue;
		}

		for (new j = 0; j < sizeof(letters); j++)
		{
			if (centerBuffer[i] == letters[j][0])
			{
				space += letters[j][1];
				break;
			}
		}
	}

	if (lines == 0)
	{ 
		if (space < defaultSize)
		{
			new loop = ( ( (defaultSize - space) / 4) / 2) + 1;
			new start = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) );

			for (new i = start; i < loop + start; i++)
			{
				strins(centerBuffer, " ", i);
				space += 3;

				for (new j = 0; j < lines; j++)
					lineInfo[j]++;
			}
		}
		else
		{
			strins(centerBuffer, "  ", ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) ));

			for (new j = 0; j < lines; j++)
				lineInfo[j] += 2;
		}
	}
	else if (lines > 0)
	{
		new loop = ( ( ( ( (biggest < defaultSize) ? (defaultSize) : (biggest) ) - space) / 4) / 2) - ( ( (biggest < defaultSize) ? (-1) : ( (space < defaultSize) ? ( (lineCenter[biggestID]) ? (4) : (2) ) : (1) ) ) );
		new start = ( (lines > 0) ? ( (line == 0) ? (0) : (lineInfo[line - 1] + 1) ) : (0) );

		for (new i = start; i < loop + start; i++)
		{
			strins(centerBuffer, " ", i);
			space += 3;

			for (new j = 0; j < lines; j++)
				lineInfo[j]++;
		}
	}


	generate_fail:
	if (lines > 0)
	{
		if (line++ < lines - 1)	
			goto generate_line;
	}


	while (-1 != ( cpos = strfind(centerBuffer, "\\c", false, cpos + 2) ) )
		strdel(centerBuffer, cpos, cpos + 2);

	while (-1 != ( tpos = strfind(centerTitle, "\\c", false, tpos + 2) ) )
		strdel(centerTitle, tpos, tpos + 2);

	use = false;
	return ShowPlayerDialog(playerid, dialogid, style, centerTitle, centerBuffer, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog dcenter_ShowPlayerDialog
