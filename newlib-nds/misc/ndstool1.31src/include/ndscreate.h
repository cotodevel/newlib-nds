#include "ndstree.h"

extern void AddFile(char *rootdir, char *prefix, char *entry_name, unsigned int file_id, unsigned int alignmask);
extern void AddDirectory(TreeNode *node, char *prefix, unsigned int this_dir_id, unsigned int _parent_id, unsigned int alignmask);
extern void Create();
extern unsigned short CalcSecureAreaCRC(bool encrypt);
extern void ShowInfo(char *ndsfilename);
extern void ShowHeaderInfo(Header &header, int romType, unsigned int length);
extern unsigned short CalcSecurityDataCRC();
extern unsigned short CalcSegment3CRC();
extern void ShowVerboseInfo(FILE *fNDS, Header &header, int romType);
extern int DetectRomType();