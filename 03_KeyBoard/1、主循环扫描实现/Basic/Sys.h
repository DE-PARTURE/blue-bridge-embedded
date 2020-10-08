#ifndef SYS_H_
#define SYS_H_

typedef struct{
	u8 StartFlag;
	u8 ExcuteFlag;
	u8 EndFlag;
}Task;

void TaskInit(Task *task);
void StartFlagScan(void);
void ExcuteFlagScan(void);
void EndFlagScan(void);

extern Task Action1;
extern Task Action2;
extern Task Action3;
extern Task Action4;

#endif
