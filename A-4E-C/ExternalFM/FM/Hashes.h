#pragma once
    #include <Windows.h>

    static WCHAR* files[] = {L"entry.lua",L"A-4E-C.lua",L"Cockpit/Scripts/EFM_Data_Bus.lua",L"Entry/Suspension.lua"};

    static BYTE hashes[][32] = {
	{0xdb,0xe3,0x9b,0xc2,0x76,0xe2,0x47,0xbc,0x35,0x79,0x16,0x9e,0xae,0xf8,0xc1,0x6e,0x92,0x6b,0x4f,0x25},
	{0xe7,0x70,0x3f,0x84,0x67,0x7a,0x94,0x35,0x91,0xe9,0x05,0xb6,0xde,0x97,0x47,0xf3,0x92,0x23,0x50,0xa9},
	{0xb1,0x89,0x33,0x5a,0x6e,0xa9,0x38,0xc1,0x86,0x25,0x6e,0x34,0xec,0xc9,0xf1,0x2a,0x75,0x33,0xa6,0x0a},
	{0xed,0xcb,0xbd,0xaf,0xc5,0x81,0x09,0x41,0xca,0x24,0xf7,0x60,0x97,0x82,0x1c,0x4a,0x5c,0xd5,0xfd,0x29}
};
    