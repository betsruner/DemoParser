#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int ReadHeader(ifstream& file)
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
	return 0;
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
int ConsolecmdRead(ifstream& file)
{
	int32_t size;
	char Data[260];
	file.read((char*)&size, sizeof(size));
	file.read((char*)& Data, size);
	return 0;
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
	ifstream demo("Sample Demos/LaserCrusher.dem", std::ios::in | ios::binary);

	if (demo.fail())
	{
		cerr << "Error opening file";
		exit(1);
	}

	// Reading Demo Header
	int32_t PlaceHolder;
	string Data;
	PlaceHolder = ReadHeader(demo);

	// Reading Demo Messages
	unsigned char Type;
	int32_t Tick;
	char Slot[1];
	int weirdtick=1;
	while (!demo.eof() && !demo.bad())
	{
		cout << weirdtick << endl;
		++weirdtick;
		demo.read((char*)& Type, 1);
		cout << static_cast<unsigned int> (Type) << endl;
		demo.read((char*)& Tick, sizeof(Tick));
		demo.read((char*)& Slot, sizeof(Slot));
		if (Type == 0x01 || Type == 0x02)
		{
			cout << Tick << endl;
			cout << "This is being done" << endl;
			SignOnRead(demo);
		}
		else if (Type == 0x03)
		{
			cout << Tick << endl;
			cout << "This is being done2" << endl;
			SyncTickRead(demo);
		}
		else if (Type == 0x04)
		{
			cout << Tick << endl;
			cout << "This is being done3" << endl;
			ConsolecmdRead(demo);
		}
		else if (Type == 0x05)
		{
			cout << Tick << endl;
			cout << "This is being done4" << endl;
			UsercmdRead(demo);
		}
		else if (Type == 0x06)
		{
			cout << Tick << endl;
			cout << "This is being done5" << endl;
			DataTableRead(demo);
		}
		else if (Type == 0x07)
		{
			cout << Tick << endl;
			cout << "This is being done6" << endl;
			StopRead(demo);
		}
		else if (Type == 0x08)
		{
			cout << Tick << endl;
			cout << "This is being done7" << endl;
			CustomDataRead(demo);
		}
		else if (Type == 0x09)
		{
			cout << Tick << endl;
			cout << "This is being done8" << endl;
			StringTablesRead(demo);
		}
		else
		{
			cout << "Oh shit nibba what goin on here" << endl;
		}
	}
//First Demo Tick
	/*
		//SignOn
	int32_t InSeq, OutSeq, size;
	demo.ignore(152);
	demo.read((char*)& InSeq, sizeof(InSeq));
	demo.read((char*)& OutSeq, sizeof(OutSeq));
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);


	// Outputting useful information
	cout << endl;
	cout << "First Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

//Second Demo Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

		//DataTables
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);

	//Printout for Second Tick
	cout << endl;
	cout << "Second Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

//Third Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));


	//Output for third tick
	cout << endl;
	cout << "Third Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

		//SignOn Again
	demo.ignore(152);
	demo.read((char*)& InSeq, sizeof(InSeq));
	demo.read((char*)& OutSeq, sizeof(OutSeq));
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);

//Fourth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Output for fourth tick
	cout << endl;
	cout << "Fourth Tick" << endl;
	cout << "Type: "<< static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

		//SignOn Again
	demo.ignore(152);
	demo.read((char*)& InSeq, sizeof(InSeq));
	demo.read((char*)& OutSeq, sizeof(OutSeq));
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);

//Fifth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Fifth Tick Output
	cout << endl;
	cout << "Fifth Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

// Sixth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Sixth Tick Output
	cout << endl;
	cout << "Sixth Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

		//Custom Data
	demo.read((char*)& Unknown, sizeof(Unknown));
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);

//Seventh Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Seventh Tick Output
	cout << endl;
	cout << "Seventh Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

		//StringTables
	demo.read((char*)& size, sizeof(size));
	demo.ignore(size);

	//Eigth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

//Eigth Tick Output
	cout << endl;
	cout << "Eigth Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

		//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout <<"DATA: " << Data << endl;

//Ninth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Ninth Tick Output
	cout << endl;
	cout << "Ninth Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;


//Tenth Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Tenth Tick Output
	cout << endl;
	cout << "Tenth Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//Eleventh Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//Eleventh Tick Output
	cout << endl;
	cout << "Eleventh Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//12th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//12th Tick Output
	cout << endl;
	cout << "12th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//13th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//13th Tick Output
	cout << endl;
	cout << "13th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//14th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//14th Tick Output
	cout << endl;
	cout << "14th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//15th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//15th Tick Output
	cout << endl;
	cout << "15th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//16th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//16th Tick Output
	cout << endl;
	cout << "16th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//17th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//17th Tick Output
	cout << endl;
	cout << "17th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//18th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//18th Tick Output
	cout << endl;
	cout << "18th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//19th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//19th Tick Output
	cout << endl;
	cout << "19th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//20th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//20th Tick Output
	cout << endl;
	cout << "20th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//21st Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//21st Tick Output
	cout << endl;
	cout << "21st Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//22nd Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//22nd Tick Output
	cout << endl;
	cout << "22nd Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//23rd Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//23rd Tick Output
	cout << endl;
	cout << "23rd Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//24th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//24th Tick Output
	cout << endl;
	cout << "24th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//25th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//25th Tick Output
	cout << endl;
	cout << "25th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//26th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//26th Tick Output
	cout << endl;
	cout << "26th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//27th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//27th Tick Output
	cout << endl;
	cout << "27th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	cout << "DATA: " << Data << endl;

//28th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//28th Tick Output
	cout << endl;
	cout << "28th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Packet
	demo.ignore(152);
	demo.read((char*)& InSeq, sizeof(InSeq));
	demo.read((char*)& OutSeq, sizeof(OutSeq));
	demo.read((char*)& size, sizeof(size));
	cout << size << endl;
	demo.ignore(size);

//29th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//29th Tick Output
	cout << endl;
	cout << "29th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;

	//Console Command
	demo.read((char*)& size, sizeof(size));
	demo.read((char*)& Data, size);
	cout << size << endl;
	//cout << "DATA: " << Data << endl;


//30th Tick
	demo.read((char*)& Type, sizeof(Type));
	demo.read((char*)& Tick, sizeof(Tick));
	demo.read((char*)& Slot, sizeof(Slot));

	//30th Tick Output
	cout << endl;
	cout << "30th Tick" << endl;
	cout << "Type: " << static_cast<unsigned int>(Type) << endl;
	cout << "Tick: " << Tick << endl;
	cout << "Slot: " << Slot << endl;


	// Outputting Header Information
/*

	cout << Hl2demo << endl;
	cout << demoprotocol << endl;
	cout << networkprotocol << endl;
	cout << servername << endl;
	cout << clientname << endl;
	cout << mapname << endl;
	cout << gamedirectory << endl;
	cout << playbacktime << endl;
	cout << ticks << endl;
	cout << frames << endl;
	cout << signonlength << endl;
*/
	// Outputting Useful Demo Message Information




	return 0;
}
