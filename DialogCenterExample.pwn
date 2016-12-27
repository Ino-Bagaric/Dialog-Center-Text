#include <a_samp>
#include <zcmd>
#include <DialogCenter>


CMD:dialog1(playerid, params[])
{
	new str[1024];

	format(str, sizeof(str), "\
		\\c{09E627}Server Commands\n \n\
		{FFFFFF}/command\n\
		/command - Description\n\
		/command - Description\n\
		/command - Description\n\
		/command - Description\n\
		/command - Description\n\
		/command - Description\n \n \n \n\
		\\c{09E627}Player Commands\n \n\
		{FFFFFF}/command\n\
		/command - This description can be longer than first xD\n\
		/command\n\
		/command\n\
		/command\n\
		/command\n\
	");

	ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "Title", str, "OK", "Cancel");
	return 1;
}


static stock Name[24] = "Player_Name";
CMD:dialog2(playerid, params[])
{
	new str[512];

	format(str, sizeof(str), "\
		\\c{FFFFFF}Welcome back, {09E627}%s\n \n\
		\\c{FFFFFF}Please, insert your password in box below\
	", Name);

	ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, "Login", str, "OK", "Cancel");
	return 1;
}


CMD:dialog3(playerid, params[])
{
	new str[1024];

	format(str, sizeof(str), "\
		\\cLorem Ipsum is simply dummy text of the printing and typesetting industry.\n\
		\\cLorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book.\n\
		\\cIt has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.\
	");

	ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "Test", str, "OK", "Cancel");
	return 1;
}


CMD:dialog4(playerid, params[])
{
	new str[1024];

	format(str, sizeof(str), "\
		\\cLorem Ipsum is simply dummy text of the printing and typesetting industry.\n\
		\\cLorem Ipsum has been the industry's standard dummy text ever since the 1500s,\n\
		\\cwhen an unknown printer took a galley of type and scrambled it to make a type specimen book.\n\
		\\cIt has survived not only five centuries,\n\
		\\cbut also the leap into electronic typesetting, remaining essentially unchanged.\
	");

	ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "Test", str, "OK", "Cancel");
	return 1;
}
