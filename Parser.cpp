#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string ReadHeader(ifstream& file)
{
	char Hl2demo[8];
	int32_t demoprotocol, networkprotocol, ticks, frames, signonlength, Unknown;
	char servername[260], clientname[260], mapname[260], gamedirectory[260];
	float playbacktime;
	file.read(Hl2demo, sizeof(Hl2demo));
	file.read((char*)& demoprotocol, sizeof(demoprotocol));
	file.read((char*)& networkprotocol, sizeof(networkprotocol));
	file.read((char*)& servername, sizeof(servername));
	file.read((char*)& clientname, sizeof(clientname));
	file.read((char*)& mapname, sizeof(mapname));
	file.read((char*)& gamedirectory, sizeof(gamedirectory));
	file.read((char*)& playbacktime, sizeof(playbacktime));
	file.read((char*)& ticks, sizeof(ticks));
	file.read((char*)& frames, sizeof(frames));
	file.read((char*)& signonlength, sizeof(signonlength));
	string StringClientName(clientname);
	string StringMapName(mapname);
	string Information;
	Information = StringClientName + " " + StringMapName;
	return Information;
}
int SignOnRead(ifstream& file)
{
	int32_t InSeq, OutSeq, size;
	file.ignore(152);
	file.read((char*)& InSeq, sizeof(InSeq));
	file.read((char*)& OutSeq, sizeof(OutSeq));
	file.read((char*)& size, sizeof(size));
	file.ignore(size);
	return 0;
}
int PacketRead(ifstream& file)
{
	int32_t InSeq, OutSeq, size;
	file.ignore(152);
	file.read((char*)& InSeq, sizeof(InSeq));
	file.read((char*)& OutSeq, sizeof(OutSeq));
	file.read((char*)& size, sizeof(size));
	file.ignore(size);
	return 0;
}
int SyncTickRead(ifstream& file)
{
	return 0;
}
string ConsolecmdRead(ifstream& file)
{
	int32_t size;
	char Data[260];
	file.read((char*)& size, sizeof(size));
	file.read((char*)& Data, size);
	string StringData(Data);
	return StringData;
}
int UsercmdRead(ifstream& file)
{
	int32_t Cmd, size, CommandNumber, TickCount, Buttons, WeaponSelect, WeaponSubtype;
	short MouseDx, MouseDy;
	float ViewAnglesX, ViewAnglesY, ViewAnglesZ, SideMove, ForwardMove, UpMove;
	unsigned char Impulse;
	file.read((char*)& Cmd, sizeof(Cmd));
	file.read((char*)& size, sizeof(size));
	file.ignore(size);
	return 0;
}
int DataTableRead(ifstream& file)
{
	int32_t Size;
	file.read((char*)& Size, sizeof(Size));
	file.ignore(Size);
	return 0;
}
int StopRead(ifstream& file)
{
	return 0;
}
int CustomDataRead(ifstream& file)
{
	int32_t Unknown, Size;
	file.read((char*)& Unknown, sizeof(Unknown));
	file.read((char*)& Size, sizeof(Size));
	file.ignore(Size);
	return 0;
}
int StringTablesRead(ifstream& file)
{
	int32_t Size;
	file.read((char*)& Size, sizeof(Size));
	file.ignore(Size);
	return 0;
}

int main()
{
	ifstream demo("Sample Demos/LaserCrusherSS.dem", std::ios::in | ios::binary);

	if (demo.fail())
	{
		cerr << "Error opening file";
		exit(1);
	}

	// Reading Demo Header
	int StartTick, EndTick,position,AdjustedTicks;
	string Data, ClientName,MapName, Information,StringData;
	Information = ReadHeader(demo);
	position = Information.find(" ");
	ClientName = Information.substr(0,position);
	MapName = Information.substr(position+1);

	// Reading Demo Messages
	unsigned char Type;
	int32_t Tick;
	char Slot[1];
	while (!demo.eof() && !demo.bad())
	{
		demo.read((char*)& Type, 1);
		demo.read((char*)& Tick, sizeof(Tick));
		demo.read((char*)& Slot, sizeof(Slot));
		if (Type == 0x01 || Type == 0x02)
		{
			//cout << Tick;
			//cout << " - Demo Message - SignOn Or Packet" << endl;
			SignOnRead(demo);
		}
		else if (Type == 0x03)
		{
			//cout << Tick;
			//cout << " - Demo Message - SyncTick" << endl;
			SyncTickRead(demo);
		}
		else if (Type == 0x04)
		{
			StringData = ConsolecmdRead(demo);
			if (StringData == "ss_force_primary_fullscreen 0")
			{
				StartTick = Tick;
				cout << Tick;
				cout << " - Demo Message - Console Command - ";
				cout << StringData << endl;
			}
			else if (StringData == "playvideo_end_level_transition coop_bluebot_load 2.000000")
			{
				EndTick = Tick;
				cout << Tick;
				cout << " - Demo Message - Console Command - ";
				cout << StringData << endl;
			}
			else if (StringData == "cmd1 voice_modenable 1" || StringData == "voice_modenable 1")
			{

			}
			else
			{
				cout << Tick;
				cout << " - Demo Message - Console Command - ";
				cout << StringData << endl;
			}
		}
		else if (Type == 0x05)
		{
			//cout << Tick;
			//cout << " - Demo Message - User Command" << endl;
			UsercmdRead(demo);
		}
		else if (Type == 0x06)
		{
			//cout << Tick;
			//cout << " - Demo Message - Data Table" << endl;
			DataTableRead(demo);
		}
		else if (Type == 0x07)
		{
			//cout << Tick;
			//cout << " - Demo Message - Stop" << endl;
			StopRead(demo);
		}
		else if (Type == 0x08)
		{
			//cout << Tick;
			//cout << " - Demo Message - Custom Data" << endl;
			CustomDataRead(demo);
		}
		else if (Type == 0x09)
		{
			//cout << Tick;
			//cout << " - Demo Message - String Tables" << endl;
			StringTablesRead(demo);
		}
		else
		{
			cout << "How will Pizza get a job now" << endl;
		}
	}
	AdjustedTicks = EndTick - StartTick;
	//Useful Information
	cout << ClientName << endl;
	cout << MapName << endl;
	cout << StartTick << endl;
	cout << EndTick << endl;
	cout << AdjustedTicks << endl;
	return 0;
}
