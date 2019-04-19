#include <time.h>
#include <ndstool.h>
#include "default_arm7.h"
#include "logo.h"
#include "raster.h"
#include "banner.h"
#include "overlay.h"
//#include "loadme.h"
#include "ndstree.h"
#include "encryption.h"
#include "crc.h"

#define ROMTYPE_HOMEBREW	0
#define ROMTYPE_MULTIBOOT	1
#define ROMTYPE_NDSDUMPED	2	// decrypted secure area
#define ROMTYPE_ENCRSECURE	3
#define ROMTYPE_MASKROM		4	// unknown layout
#define ROMTYPE_INVALID		5	// rejected; can't be a supported rom


static const unsigned char default_arm7[] = { 0x0 };
static const int default_arm7_size = sizeof(default_arm7);

static const unsigned char loadme[] = {
	0xc8, 0x60, 0x4f, 0xe2, 0x01, 0x70, 0x8f, 0xe2, 0x17, 0xff, 0x2f, 0xe1, 0x12, 0x4f, 0x11, 0x48, 
	0x12, 0x4c, 0x20, 0x60, 0x64, 0x60, 0x7c, 0x62, 0x30, 0x1c, 0x39, 0x1c, 0x10, 0x4a, 0x00, 0xf0, 
	0x14, 0xf8, 0x30, 0x6a, 0x80, 0x19, 0xb1, 0x6a, 0xf2, 0x6a, 0x00, 0xf0, 0x0b, 0xf8, 0x30, 0x6b, 
	0x80, 0x19, 0xb1, 0x6b, 0xf2, 0x6b, 0x00, 0xf0, 0x08, 0xf8, 0x70, 0x6a, 0x77, 0x6b, 0x07, 0x4c, 
	0x60, 0x60, 0x38, 0x47, 0x07, 0x4b, 0xd2, 0x18, 0x9a, 0x43, 0x07, 0x4b, 0x92, 0x08, 0xd2, 0x18, 
	0x0c, 0xdf, 0xf7, 0x46, 0x04, 0xf0, 0x1f, 0xe5, 0x00, 0xfe, 0x7f, 0x02, 0xf0, 0xff, 0x7f, 0x02, 
	0xf0, 0x01, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const int loadme_size = sizeof(loadme);


unsigned int arm9_align = 0x1FF;
unsigned int arm7_align = 0x1FF;
unsigned int fnt_align = 0x1FF;		// 0x3 0x1FF
unsigned int fat_align = 0x1FF;		// 0x3 0x1FF
unsigned int banner_align = 0x1FF;
unsigned int file_align = 0x1FF;	// 0x3 0x1FF

unsigned int overlay_files = 0;

unsigned char romcontrol[] = { 0x00,0x60,0x58,0x00,0xF8,0x08,0x18,0x00 };

const unsigned char nintendo_logo[] =
{
	0x24,0xFF,0xAE,0x51,0x69,0x9A,0xA2,0x21,0x3D,0x84,0x82,0x0A,0x84,0xE4,0x09,0xAD,
	0x11,0x24,0x8B,0x98,0xC0,0x81,0x7F,0x21,0xA3,0x52,0xBE,0x19,0x93,0x09,0xCE,0x20,
	0x10,0x46,0x4A,0x4A,0xF8,0x27,0x31,0xEC,0x58,0xC7,0xE8,0x33,0x82,0xE3,0xCE,0xBF,
	0x85,0xF4,0xDF,0x94,0xCE,0x4B,0x09,0xC1,0x94,0x56,0x8A,0xC0,0x13,0x72,0xA7,0xFC,
	0x9F,0x84,0x4D,0x73,0xA3,0xCA,0x9A,0x61,0x58,0x97,0xA3,0x27,0xFC,0x03,0x98,0x76,
	0x23,0x1D,0xC7,0x61,0x03,0x04,0xAE,0x56,0xBF,0x38,0x84,0x00,0x40,0xA7,0x0E,0xFD,
	0xFF,0x52,0xFE,0x03,0x6F,0x95,0x30,0xF1,0x97,0xFB,0xC0,0x85,0x60,0xD6,0x80,0x25,
	0xA9,0x63,0xBE,0x03,0x01,0x4E,0x38,0xE2,0xF9,0xA2,0x34,0xFF,0xBB,0x3E,0x03,0x44,
	0x78,0x00,0x90,0xCB,0x88,0x11,0x3A,0x94,0x65,0xC0,0x7C,0x63,0x87,0xF0,0x3C,0xAF,
	0xD6,0x25,0xE4,0x8B,0x38,0x0A,0xAC,0x72,0x21,0xD4,0xF8,0x07,
};













void ShowVerboseInfo(FILE *fNDS, Header &header, int romType)
{
	
}

int DetectRomType()
{
	fseek(fNDS, 0x4000, SEEK_SET);
	unsigned int data[3];
	fread(data, 1, sizeof(data), fNDS);
	if (header.arm9_rom_offset < 0x4000) return ROMTYPE_HOMEBREW;
	if (data[0] == 0x00000000 && data[1] == 0x00000000) return ROMTYPE_MULTIBOOT;
	if (data[0] == 0xE7FFDEFF && data[1] == 0xE7FFDEFF) return ROMTYPE_NDSDUMPED;
	fseek(fNDS, 0x200, SEEK_SET);
	for (int i=0x200; i<0x4000; i++)
		if (fgetc(fNDS)) return ROMTYPE_MASKROM;	// found something odd ;)
	return ROMTYPE_ENCRSECURE;
}


unsigned short CalcSecurityDataCRC()
{
	fseek(fNDS, 0x1000, SEEK_SET);
	unsigned char data[0x2000];
	fread(data, 1, 0x2000, fNDS);
	return CalcCrc16(data, 0x2000);
}

unsigned short CalcSegment3CRC()
{
	fseek(fNDS, 0x3000, SEEK_SET);
	unsigned char data[0x1000];
	fread(data, 1, 0x1000, fNDS);
	for (int i=0; i<0x1000; i+=2)	// swap bytes
	{
		unsigned char t = data[i+1]; data[i+1] = data[i]; data[i] = t;
	}
	return CalcCcitt16(data, 0x1000);	// why would they use CRC16-CCITT ?
}
	
void ShowHeaderInfo(Header &header, int romType, unsigned int length = 0x200)
{
	printf("0x00\t%-25s\t", "Game title");

	for (unsigned int i=0; i<sizeof(header.title); i++)
		if (header.title[i]) putchar(header.title[i]); printf("\n");

	printf("0x0C\t%-25s\t", "Game code");
	for (unsigned int i=0; i<sizeof(header.gamecode); i++)
		if (header.gamecode[i]) putchar(header.gamecode[i]);
	for (int i=0; i<NumCountries; i++)
	{
		if (countries[i].countrycode == header.gamecode[3])
		{
			printf(" (NTR-");
			for (unsigned int j=0; j<sizeof(header.gamecode); j++)
				if (header.gamecode[j]) putchar(header.gamecode[j]);
			printf("-%s)", countries[i].name);
			break;
		}
	}
	printf("\n");
	
	printf("0x10\t%-25s\t", "Maker code"); for (unsigned int i=0; i<sizeof(header.makercode); i++)
		if (header.makercode[i]) putchar(header.makercode[i]);
	for (int j=0; j<NumMakers; j++)
	{
		if ((makers[j].makercode[0] == header.makercode[0]) && (makers[j].makercode[1] == header.makercode[1]))
		{
			printf(" (%s)", makers[j].name);
			break;
		}
	}
	printf("\n");

	printf("0x12\t%-25s\t0x%02X\n", "Unit code", header.unitcode);
	printf("0x13\t%-25s\t0x%02X\n", "Device type", header.devicetype);
	printf("0x14\t%-25s\t0x%02X (%d Mbit)\n", "Device capacity", header.devicecap, 1<<header.devicecap);
	printf("0x15\t%-25s\t", "reserved 1"); for (unsigned int i=0; i<sizeof(header.reserved1); i++) printf("%02X", header.reserved1[i]); printf("\n");
	printf("0x1E\t%-25s\t0x%02X\n", "ROM version", header.romversion);
	printf("0x1F\t%-25s\t0x%02X\n", "reserved 2", header.reserved2);
	printf("0x20\t%-25s\t0x%X\n", "ARM9 ROM offset", (int)header.arm9_rom_offset);
	printf("0x24\t%-25s\t0x%X\n", "ARM9 entry address", (int)header.arm9_entry_address);
	printf("0x28\t%-25s\t0x%X\n", "ARM9 RAM address", (int)header.arm9_ram_address);
	printf("0x2C\t%-25s\t0x%X\n", "ARM9 code size", (int)header.arm9_size);
	printf("0x30\t%-25s\t0x%X\n", "ARM7 ROM offset", (int)header.arm7_rom_offset);
	printf("0x34\t%-25s\t0x%X\n", "ARM7 entry address", (int)header.arm7_entry_address);
	printf("0x38\t%-25s\t0x%X\n", "ARM7 RAM address", (int)header.arm7_ram_address);
	printf("0x3C\t%-25s\t0x%X\n", "ARM7 code size", (int)header.arm7_size);
	printf("0x40\t%-25s\t0x%X\n", "File name table offset", (int)header.fnt_offset);
	printf("0x44\t%-25s\t0x%X\n", "File name table size", (int)header.fnt_size);
	printf("0x48\t%-25s\t0x%X\n", "FAT offset", (int)header.fat_offset);
	printf("0x4C\t%-25s\t0x%X\n", "FAT size", (int)header.fat_size);
	printf("0x50\t%-25s\t0x%X\n", "ARM9 overlay offset", (int)header.arm9_overlay_offset);
	printf("0x54\t%-25s\t0x%X\n", "ARM9 overlay size", (int)header.arm9_overlay_size);
	printf("0x58\t%-25s\t0x%X\n", "ARM7 overlay offset", (int)header.arm7_overlay_offset);
	printf("0x5C\t%-25s\t0x%X\n", "ARM7 overlay size", (int)header.arm7_overlay_size);
	printf("0x60\t%-25s\t0x%08X\n", "ROM control info 1", (int)header.rom_control_info1);
	printf("0x64\t%-25s\t0x%08X\n", "ROM control info 2", (int)header.rom_control_info2);
	printf("0x68\t%-25s\t0x%X\n", "Icon/title offset", (int)header.banner_offset);
	unsigned short secure_area_crc = CalcSecureAreaCRC((romType == ROMTYPE_NDSDUMPED));
	const char *s1, *s2 = "";
	if (romType == ROMTYPE_HOMEBREW) s1 = "-";
	else if (secure_area_crc == header.secure_area_crc) s1 = "OK";
	else
	{
		s1 = "INVALID";
	}
	switch (romType)
	{
		case ROMTYPE_HOMEBREW: s2 = "homebrew"; break;
		case ROMTYPE_MULTIBOOT: s2 = "multiboot"; break;
		case ROMTYPE_NDSDUMPED: s2 = "decrypted"; break;
		case ROMTYPE_ENCRSECURE: s2 = "encrypted"; break;
		case ROMTYPE_MASKROM: s2 = "mask ROM"; break;
	}
	printf("0x6C\t%-25s\t0x%04X (%s, %s)\n", "Secure area CRC", (int)header.secure_area_crc, s1, s2);
	printf("0x6E\t%-25s\t0x%04X\n", "ROM control info 3", (int)header.rom_control_info3);
	printf("0x70\t%-25s\t0x%X\n", "ARM9 ?", (int)header.offset_0x70);
	printf("0x74\t%-25s\t0x%X\n", "ARM7 ?", (int)header.offset_0x74);
	printf("0x78\t%-25s\t0x%08X\n", "Magic 1", (int)header.offset_0x78);
	printf("0x7C\t%-25s\t0x%08X\n", "Magic 2", (int)header.offset_0x7C);
	printf("0x80\t%-25s\t0x%08X\n", "Application end offset", (int)header.application_end_offset);
	printf("0x84\t%-25s\t0x%08X\n", "ROM header size", (int)header.rom_header_size);
	for (unsigned int i=0x88; i<0xC0; i+=4)
	{
		unsigned_int &x = ((unsigned_int *)&header)[i/4];
		if (x != 0) printf("0x%02X\t%-25s\t0x%08X\n", i, "?", (int)x);
	}
	unsigned short logo_crc = CalcLogoCRC(header);
	printf("0x15C\t%-25s\t0x%04X (%s)\n", "Logo CRC", (int)header.logo_crc, (logo_crc == header.logo_crc) ? "OK" : "INVALID");
	unsigned short header_crc = CalcHeaderCRC(header);
	printf("0x15E\t%-25s\t0x%04X (%s)\n", "Header CRC", (int)header.header_crc, (header_crc == header.header_crc) ? "OK" : "INVALID");
	for (unsigned int i=0x160; i<length; i+=4)
	{
		unsigned_int &x = ((unsigned_int *)&header)[i/4];
		if (x != 0) printf("0x%02X\t%-25s\t0x%08X\n", i, "?", (int)x);
	}
}

void ShowInfo(char *ndsfilename)
{
	fNDS = fopen(ndsfilename, "rb");
	if (!fNDS) { fprintf(stderr, "Cannot open file '%s'.\n", ndsfilename); exit(1); }
	fread(&header, 512, 1, fNDS);

	int romType = DetectRomType();

	printf("Header information:\n");
	ShowHeaderInfo(header, romType);

	// banner info
	if (header.banner_offset)
	{
		Banner banner;
		fseek(fNDS, header.banner_offset, SEEK_SET);
		if (fread(&banner, 1, sizeof(banner), fNDS))
		{
			unsigned short banner_crc = CalcBannerCRC(banner);
			printf("\n");
			printf("Banner CRC:                     \t0x%04X (%s)\n", (int)banner.crc, (banner_crc == banner.crc) ? "OK" : "INVALID");
	
			for (int language=1; language<=1; language++)
			{
				int line = 1;
				bool nextline = true;
				for (int i=0; i<128; i++)
				{
					unsigned short c = banner.title[language][i];
					if (c >= 128) c = '_';
					if (c == 0x00) { printf("\n"); break; }
					if (c == 0x0A)
					{
						nextline = true;
					}
					else
					{
						if (nextline)
						{
							if (line != 1) printf("\n");
							printf("%s banner text, line %d:", bannerLanguages[language], line);
							for (unsigned int i=0; i<11 - strlen(bannerLanguages[language]); i++) putchar(' ');
							printf("\t");
							nextline = false;
							line++;
						}
						putchar(c);
					}
				}
			}
		}
	}

	// ARM9 footer
	fseek(fNDS, header.arm9_rom_offset + header.arm9_size, SEEK_SET);
	unsigned_int nitrocode;
	if (fread(&nitrocode, sizeof(nitrocode), 1, fNDS) && (nitrocode == 0xDEC00621))
	{
		printf("\n");
		printf("ARM9 footer found.\n");
		unsigned_int x;
		fread(&x, sizeof(x), 1, fNDS);
		fread(&x, sizeof(x), 1, fNDS);
	}

	// show security CRCs
	if (romType >= ROMTYPE_NDSDUMPED)
	{
		printf("\n");
		unsigned short securitydata_crc = CalcSecurityDataCRC();
		printf("Security data CRC (0x1000-0x2FFF)  0x%04X\n", (int)securitydata_crc);
		unsigned short segment3_crc = CalcSegment3CRC();
		printf("Segment3 CRC (0x3000-0x3FFF)       0x%04X (%s)\n", (int)segment3_crc, (segment3_crc == 0x0254) ? "OK" : "INVALID");
	}

	// more information
	if (verbose >= 1)
	{
		ShowVerboseInfo(fNDS, header, romType);
	}

	fclose(fNDS);
}

/*
 * HasElfExtension
 */
bool HasElfExtension(char *filename)
{
	char *p = strrchr(filename, '.');
	if (!p) return false;
	return (strcmp(p, ".elf") == 0);
}

/*
 * CopyFromBin
 */
int CopyFromBin(char *binFilename, unsigned int *size = 0, unsigned int *size_without_footer = 0)
{
	FILE *fi = fopen(binFilename, "rb");
	if (!fi) { fprintf(stderr, "Cannot open file '%s'.\n", binFilename); exit(1); }
	unsigned int _size = 0;
	while (1)
	{
		unsigned char buffer[1024];
		int bytesread = fread(buffer, 1, sizeof(buffer), fi);
		if (bytesread <= 0) break;
		fwrite(buffer, 1, bytesread, fNDS);
		_size += bytesread;
	}
	if (size) *size = _size;

	// check footer
	if (size_without_footer)
	{
		fseek(fi, _size - 3*4, SEEK_SET);
		unsigned_int nitrocode;
		fread(&nitrocode, sizeof(nitrocode), 1, fi);
		if (nitrocode == 0xDEC00621)
			*size_without_footer = _size - 3*4;
		else
			*size_without_footer = _size;
	}

	fclose(fi);
	return 0;
}

/*
 * CopyFromElf
 */
#if 0
int CopyFromElf(char *elfFilename, unsigned int *entry, unsigned int *ram_address, unsigned int *size)
{
	int fd = open(elfFilename, O_RDONLY);
	if (fd < 0) { fprintf(stderr, "Cannot open file '%s'.\n", elfFilename); exit(1); }
	if (elf_version(EV_CURRENT) == EV_NONE) { fprintf(stderr, "libelf out of date!\n"); exit(1); }
	Elf *elf;
	if ((elf = elf_begin(fd, ELF_C_READ, 0)) == 0) { fprintf(stderr, "Cannot open ELF file!\n"); exit(1); }
	Elf32_Ehdr *ehdr;
	if ((ehdr = elf32_getehdr(elf)) == 0) { fprintf(stderr, "Cannot read ELF header!\n"); exit(1); }
	if (ehdr->e_machine != EM_ARM) { fprintf(stderr, "Not an ARM ELF file!\n"); exit(1); }

	*entry = ehdr->e_entry;
	*size = 0;
	*ram_address = 0;
//	printf("entry = 0x%X\n", ehdr->e_entry);

    Elf_Scn *scn = elf_getscn(elf, 0);
	Elf32_Shdr *shdr = elf32_getshdr(scn);
    while (shdr)
    {
		if (shdr->sh_flags & SHF_ALLOC)
		{
/*			char *name;
			if (!(name = elf_strptr(elf, ehdr->e_shstrndx, shdr->sh_name))) name = "???";
	    	printf("%s\n", name);*/

			if (!*ram_address) *ram_address = shdr->sh_addr;		// use first address (assume it's .text)

// don't mind the garbage here

//			printf("sh_addr=0x%X sh_offset=0x%X sh_size=0x%X sh_link=%u sh_entsize=%u sh_addralign=%u\n", shdr->sh_addr, shdr->sh_offset, shdr->sh_size, shdr->sh_link, shdr->sh_entsize, shdr->sh_addralign);
			//    Elf32_Word		sh_name;
			//    Elf32_Word		sh_type;
			//    Elf32_Word		sh_flags;
			//    Elf32_Addr		sh_addr;
			//    Elf32_Off		sh_offset;
			//    Elf32_Word		sh_size;
			//    Elf32_Word		sh_link;
			//    Elf32_Word		sh_info;
			//    Elf32_Word		sh_addralign;
			//    Elf32_Word		sh_entsize;

			Elf_Data *data;
			if ((data = elf_getdata(scn, NULL)))
			{
		    	/*for (int i=0; i<data->d_size; i++)
		    	{
					printf("%02X ", ((unsigned char *)data->d_buf)[i]);
		    	}
		    	printf("\n");*/
		    	fwrite(data->d_buf, 1, data->d_size, fNDS);
				*size += data->d_size;
			}
		}

		scn = elf_nextscn(elf, scn);
		shdr = elf32_getshdr(scn);
    }

	elf_end(elf);

	return 0;
}
#endif

/*
 * AddFile
 */
void AddFile(char *rootdir, char *prefix, char *entry_name, unsigned int file_id)
{
	// make filename
	char strbuf[MAXPATHLEN];
	strcpy(strbuf, rootdir);
	strcat(strbuf, prefix);
	strcat(strbuf, entry_name);

	//unsigned int file_end = ftell(fNDS);

	file_top = (file_top + file_align) &~ file_align;
	fseek(fNDS, file_top, SEEK_SET);

	FILE *fi = fopen(strbuf, "rb");
	if (!fi) { fprintf(stderr, "Cannot open file '%s'.\n", strbuf); exit(1); }
	fseek(fi, 0, SEEK_END);
	unsigned int size = ftell(fi);
	unsigned int file_bottom = file_top + size;
	fseek(fi, 0, SEEK_SET);

	// print
	if (verbose)
	{
		printf("%5u 0x%08X 0x%08X %9u %s%s\n", file_id, file_top, file_bottom, size, prefix, entry_name);
	}

	// write data
	unsigned int sizeof_copybuf = 256*1024;
	unsigned char *copybuf = new unsigned char [sizeof_copybuf];
	while (size > 0)
	{
		unsigned int size2 = (size >= sizeof_copybuf) ? sizeof_copybuf : size;
		fread(copybuf, 1, size2, fi);
		fwrite(copybuf, 1, size2, fNDS);
		size -= size2;
	}
	delete [] copybuf;
	fclose(fi);
	if ((unsigned int)ftell(fNDS) > file_end) file_end = ftell(fNDS);

	// write fat
	fseek(fNDS, header.fat_offset + 8*file_id, SEEK_SET);
	unsigned_int top = file_top;
	fwrite(&top, 1, sizeof(top), fNDS);
	unsigned_int bottom = file_bottom;
	fwrite(&bottom, 1, sizeof(bottom), fNDS);

	file_top = file_bottom;
}

/*
 * AddDirectory
 * Walks the tree and adds files to NDS
 */
void AddDirectory(TreeNode *node, char *prefix, unsigned int this_dir_id, unsigned int _parent_id)
{
	// skip dummy node
	node = node->next;

	if (verbose) printf("%s\n", prefix);

	// write directory info
	fseek(fNDS, header.fnt_offset + 8*(this_dir_id & 0xFFF), SEEK_SET);
	unsigned_int entry_start = _entry_start;	// reference location of entry name
	fwrite(&entry_start, 1, sizeof(entry_start), fNDS);
	unsigned int _top_file_id = free_file_id;
	unsigned_short top_file_id = _top_file_id;	// file ID of top entry
	fwrite(&top_file_id, 1, sizeof(top_file_id), fNDS);
	unsigned_short parent_id = _parent_id;	// ID of parent directory or directory count (root)
	fwrite(&parent_id, 1, sizeof(parent_id), fNDS);

	//printf("dir %X file_id %u +\n", this_dir_id, (int)top_file_id);

	// directory entrynames
	{
		// start of directory entrynames
		fseek(fNDS, header.fnt_offset + _entry_start, SEEK_SET);

		// write filenames
		for (TreeNode *t=node; t; t=t->next)
		{
			if (!t->directory)
			{
				int namelen = strlen(t->name);
				fputc(t->directory ? namelen | 128 : namelen, fNDS); _entry_start += 1;
				fwrite(t->name, 1, namelen, fNDS); _entry_start += namelen;

				//printf("[ %s -> %u ]\n", t->name, free_file_id);

				free_file_id++;
			}
		}

		// write directorynames
		for (TreeNode *t=node; t; t=t->next)
		{
			if (t->directory)
			{
				//printf("*entry %s\n", t->name);

				int namelen = strlen(t->name);
				fputc(t->directory ? namelen | 128 : namelen, fNDS); _entry_start += 1;
				fwrite(t->name, 1, namelen, fNDS); _entry_start += namelen;

				//printf("[ %s -> %X ]\n", t->name, t->dir_id);

				unsigned_short _dir_id_tmp = t->dir_id;
				fwrite(&_dir_id_tmp, 1, sizeof(_dir_id_tmp), fNDS);
				_entry_start += sizeof(_dir_id_tmp);
			}
		}

		fputc(0, fNDS); _entry_start += 1;	// end of directory entrynames
	}

	// add files
	unsigned int local_file_id = _top_file_id;
	for (TreeNode *t=node; t; t=t->next)
	{
		//printf("*2* %s\n", t->name);

		if (!t->directory)
		{
			AddFile(filerootdir, prefix, t->name, local_file_id++);
		}
	}

	// add subdirectories
	for (TreeNode *t=node; t; t=t->next)
	{
		//printf("*2* %s\n", t->name);

		if (t->directory)
		{
			char strbuf[MAXPATHLEN];
			strcpy(strbuf, prefix);
			strcat(strbuf, t->name);
			strcat(strbuf, "/");
			AddDirectory(t->directory, strbuf, t->dir_id, this_dir_id);
		}
	}
}


unsigned short CalcSecureAreaCRC(bool encrypt)
{
	fseek(fNDS, 0x4000, SEEK_SET);
	unsigned char data[0x4000];
	fread(data, 1, 0x4000, fNDS);
	if (encrypt) encrypt_arm9(*(u32 *)header.gamecode, data);
	return CalcCrc16(data, 0x4000);
}

/*
 * Create
 */
void Create()
{
	fNDS = fopen(ndsfilename, "wb");
	if (!fNDS) { fprintf(stderr, "Cannot open file '%s'.\n", ndsfilename); exit(1); }

	bool bSecureSyscalls = false;
	char *headerfilename = (headerfilename_or_size && (strtoul(headerfilename_or_size,0,0) == 0)) ? headerfilename_or_size : 0;
	u32 headersize = headerfilename_or_size ? strtoul(headerfilename_or_size,0,0) : 0x200;

	// initial header data
	if (headerfilename)
	{
		// header template
		FILE *fi = fopen(headerfilename, "rb");
		if (!fi) { fprintf(stderr, "Cannot open file '%s'.\n", headerfilename); exit(1); }
		fread(&header, 1, 0x200, fi);
		fclose(fi);
		
		if ((header.arm9_ram_address + 0x800 == header.arm9_entry_address) || (header.rom_header_size > 0x200))
		{
			bSecureSyscalls = true;
		}
	}
	else	// set header default values
	{
		// clear header
		memset(&header, 0, 0x200);
		memcpy(header.gamecode, "####", 4);

		if ((arm9RamAddress + 0x800 == arm9Entry) || (headersize > 0x200))
		{
			bSecureSyscalls = true;
		}
		else
		{
			header.reserved2 = 0x04;		// autostart
			*(unsigned_int *)(((unsigned char *)&header) + 0x0) = 0xEA00002E;		// for PassMe's that start @ 0x08000000
		}
		*(unsigned_int *)(((unsigned char *)&header) + 0x60) = 1<<22 | latency2<<16 | 1<<14 | 1<<13 | latency1;	// ROM control info 1
		*(unsigned_int *)(((unsigned char *)&header) + 0x64) = 1<<29 | latency2<<16 | latency1;	// ROM control info 2
		*(unsigned_short *)(((unsigned char *)&header) + 0x6E) = 0x051E;	// ROM control info 3
	}
	if (headersize) header.rom_header_size = headersize;
	if (header.rom_header_size == 0) header.rom_header_size = bSecureSyscalls ? 0x4000 : 0x200;

	// load a logo
	if (logofilename)
	{
		char *p = strrchr(logofilename, '.');
		if (!strcmp(p, ".bmp"))
		{
			CRaster raster;
			if (raster.LoadBMP(logofilename) < 0) exit(1);
			unsigned char white = (raster.palette[0].rgbGreen >= 128) ? 0 : 1;
			if (LogoConvert(raster.raster, header.logo, white) < 0) exit(1);
		}
		else
		{
			FILE *fi = fopen(logofilename, "rb");
			if (!fi) { fprintf(stderr, "Cannot open file '%s'.\n", logofilename); exit(1); }
			fread(&header.logo, 1, 156, fi);
			fclose(fi);
		}
	}
	else if (bSecureSyscalls)	// use Nintendo logo
	{
		memcpy(((unsigned char *)&header) + 0xC0, nintendo_logo, sizeof(nintendo_logo));
	}
	else	// add small NDS loader
	{
		if (loadme_size != 156) { fprintf(stderr, "loadme size error\n"); exit(1); }
		memcpy(header.logo, loadme, loadme_size);		// self-contained NDS loader for *Me GBA cartridge boot
		memcpy(&header.offset_0xA0, "SRAM_V110", 9);		// allow GBA cartridge SRAM backup
		memcpy(&header.offset_0xAC, "PASS01\x96", 7);		// automatically start with FlashMe, make it look more like a GBA rom
	}

	// override default title/game/maker codes
	if (title) strncpy(header.title, title, 12);
	if (gamecode) strncpy(header.gamecode, gamecode, 4);
	if (makercode) strncpy((char *)header.makercode, makercode, 2);

	// --------------------------

	fseek(fNDS, header.rom_header_size, SEEK_SET);

	// ARM9 binary
	if (arm9filename)
	{
		header.arm9_rom_offset = (ftell(fNDS) + arm9_align) &~ arm9_align;
		fseek(fNDS, header.arm9_rom_offset, SEEK_SET);

		unsigned int entry_address = arm9Entry ? arm9Entry : (unsigned int)header.arm9_entry_address;		// template
		unsigned int ram_address = arm9RamAddress ? arm9RamAddress : (unsigned int)header.arm9_ram_address;		// template
		if (!ram_address && entry_address) ram_address = entry_address;
		if (!entry_address && ram_address) entry_address = ram_address;
		if (!ram_address) { ram_address = entry_address = 0x02000000; }

		// add dummy area for secure syscalls
		header.arm9_size = 0;
		if (bSecureSyscalls)
		{
			unsigned_int x;
			FILE *fARM9 = fopen(arm9filename, "rb");
			if (fARM9)
			{
				fread(&x, sizeof(x), 1, fARM9);
				fclose(fARM9);
				if (x != 0xE7FFDEFF)	// not already exist?
				{
					x = 0xE7FFDEFF;
					for (int i=0; i<0x800/4; i++) fwrite(&x, sizeof(x), 1, fNDS);
					header.arm9_size = 0x800;
				}
			}
		}

		unsigned int size = 0;
#if 0
		if (HasElfExtension(arm9filename))
			CopyFromElf(arm9filename, &entry_address, &ram_address, &size);
		else
#endif
			CopyFromBin(arm9filename, 0, &size);
		header.arm9_entry_address = entry_address;
		header.arm9_ram_address = ram_address;
		header.arm9_size = header.arm9_size + ((size + 3) &~ 3);
	}
	else
	{
		fprintf(stderr, "ARM9 binary file required.\n");
		exit(1);
	}

	// ARM9 overlay table
	if (arm9ovltablefilename)
	{
		unsigned_int x1 = 0xDEC00621; fwrite(&x1, sizeof(x1), 1, fNDS);		// 0x2106c0de magic
		unsigned_int x2 = 0x00000AD8; fwrite(&x2, sizeof(x2), 1, fNDS);		// ???
		unsigned_int x3 = 0x00000000; fwrite(&x3, sizeof(x3), 1, fNDS);		// ???

		header.arm9_overlay_offset = ftell(fNDS);		// do not align
		fseek(fNDS, header.arm9_overlay_offset, SEEK_SET);
		unsigned int size = 0;
		CopyFromBin(arm9ovltablefilename, &size);
		header.arm9_overlay_size = size;
		overlay_files += size / sizeof(OverlayEntry);
		if (!size) header.arm9_overlay_offset = 0;
	}

	// COULD BE HERE: ARM9 overlay files, no padding before or between. end is padded with 0xFF's and then followed by ARM7 binary
	// fseek(fNDS, 1388772, SEEK_CUR);		// test for ASME

	// ARM7 binary
	header.arm7_rom_offset = (ftell(fNDS) + arm7_align) &~ arm7_align;
	fseek(fNDS, header.arm7_rom_offset, SEEK_SET);
	if (arm7filename)
	{
		unsigned int entry_address = arm7Entry ? arm7Entry : (unsigned int)header.arm7_entry_address;		// template
		unsigned int ram_address = arm7RamAddress ? arm7RamAddress : (unsigned int)header.arm7_ram_address;		// template
		if (!ram_address && entry_address) ram_address = entry_address;
		if (!entry_address && ram_address) entry_address = ram_address;
		if (!ram_address) { ram_address = entry_address = 0x03800000; }

		unsigned int size = 0;
#if 0
		if (HasElfExtension(arm7filename))
			CopyFromElf(arm7filename, &entry_address, &ram_address, &size);
		else
#endif
			CopyFromBin(arm7filename, &size);

		header.arm7_entry_address = entry_address;
		header.arm7_ram_address = ram_address;
		header.arm7_size = ((size + 3) &~ 3);
	}
	else	// default ARM7 binary
	{
		fwrite(default_arm7, 1, default_arm7_size, fNDS);
		header.arm7_entry_address = 0x03800000;
		header.arm7_ram_address = 0x03800000;
		header.arm7_size = ((default_arm7_size + 3) & ~3);
	}

	// ARM7 overlay table
	if (arm7ovltablefilename)
	{
		header.arm7_overlay_offset = ftell(fNDS);		// do not align
		fseek(fNDS, header.arm7_overlay_offset, SEEK_SET);
		unsigned int size = 0;
		CopyFromBin(arm7ovltablefilename, &size);
		header.arm7_overlay_size = size;
		overlay_files += size / sizeof(OverlayEntry);
		if (!size) header.arm7_overlay_offset = 0;
	}

	// COULD BE HERE: probably ARM7 overlay files, just like for ARM9
	//

	if (overlay_files && !overlaydir)
	{
		fprintf(stderr, "Overlay directory required!.\n");
		exit(1);
	}

	// filesystem
	//if (filerootdir || overlaydir)
	{
		// read directory structure
		free_file_id = overlay_files;
		free_dir_id++;
		directory_count++;
		TreeNode *filetree;
		if (filerootdir)
			filetree = ReadDirectory(new TreeNode(), filerootdir);
		else
			filetree = new TreeNode();		// dummy root node 0xF000

		// calculate offsets required for FNT and FAT
		_entry_start = 8*directory_count;		// names come after directory structs
		header.fnt_offset = (ftell(fNDS) + fnt_align) &~ fnt_align;
		header.fnt_size =
			_entry_start +		// directory structs
			total_name_size +	// total number of name characters for dirs and files
			directory_count*4 +	// directory: name length (1), dir id (2), end-character (1)
			file_count*1 +		// files: name length (1)
			- 3;				// root directory only has an end-character
		file_count += overlay_files;		// didn't take overlay files into FNT size, but have to be calculated into FAT size
		header.fat_offset = (header.fnt_offset + header.fnt_size + fat_align) &~ fat_align;
		header.fat_size = file_count * 8;		// each entry contains top & bottom offset

		// banner after FNT/FAT
		if (bannerfilename)
		{
			header.banner_offset = (header.fat_offset + header.fat_size + banner_align) &~ banner_align;
			file_top = header.banner_offset + 0x840;
			fseek(fNDS, header.banner_offset, SEEK_SET);
			if (bannertype == BANNER_IMAGE)
			{
				IconFromBMP();
			}
			else
			{
				CopyFromBin(bannerfilename, 0);
			}
		}
		else
		{
			file_top = header.fat_offset + header.fat_size;
			header.banner_offset = 0;
		}

		file_end = file_top;	// no file data as yet

		// add (hidden) overlay files
		for (unsigned int i=0; i<overlay_files; i++)
		{
			char s[32]; sprintf(s, OVERLAY_FMT, i/*free_file_id*/);
			AddFile(overlaydir, "/", s, i/*free_file_id*/);
			//free_file_id++;		// incremented up to overlay_files
		}

		// add all other (visible) files
		AddDirectory(filetree, "/", 0xF000, directory_count);
		fseek(fNDS, file_end, SEEK_SET);

		if (verbose)
		{
			printf("%u directories.\n", directory_count);
			printf("%u normal files.\n", file_count - overlay_files);
			printf("%u overlay files.\n", overlay_files);
		}
	}

	// --------------------------

	// align file size
	unsigned int newfilesize = file_end;	//ftell(fNDS);
	newfilesize = (newfilesize + 3) &~ 3;	// align to 4 bytes
	header.application_end_offset = newfilesize;
	fseek(fNDS, newfilesize-1, SEEK_SET); int c = fgetc(fNDS);
	fseek(fNDS, newfilesize-1, SEEK_SET); fputc((c >= 0) ? c : 0, fNDS);

	// calculate device capacity
	newfilesize |= newfilesize >> 16; newfilesize |= newfilesize >> 8;
	newfilesize |= newfilesize >> 4; newfilesize |= newfilesize >> 2;
	newfilesize |= newfilesize >> 1; newfilesize++;
	if (newfilesize <= 128*1024) newfilesize = 128*1024;
	int devcap = -18;
	unsigned int x = newfilesize;
	while (x != 0) { x >>= 1; devcap++; }
	header.devicecap = (devcap < 0) ? 0 : devcap;

	// fix up header CRCs and write header
	header.logo_crc = CalcLogoCRC(header);
	header.header_crc = CalcHeaderCRC(header);
	fseek(fNDS, 0, SEEK_SET);
	fwrite(&header, 0x200, 1, fNDS);

	fclose(fNDS);
}
