void setup_DEBUG();
void DEBUG_Title(void);
void DEBUG_Ready();
void DEBUG_Separator();
void DEBUG_SectionTitle(const char *Title);
void DEBUG_LineOut(const char *Line);

void DEBUG_BlockOut(const char *Block);

void DEBUG_Success(const char *Line);
void DEBUG_Trouble(const char *Line);
void DEBUG_ProgressBar0();
void DEBUG_ProgressBar1();
void DEBUG_ProgressBar2(int dotcount);
void DEBUG_Reset();
void DEBUG_Init(const char* InitPart);
