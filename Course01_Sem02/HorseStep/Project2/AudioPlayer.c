#include<stdio.h>
#include<SDL.h>// <-- #include<stdint.h>
uint64_t N = 0;

int HorseStep(int Position, int StepLevel) {
	int Result = 0;
	if (StepLevel >= N)
		return 1;
	switch (Position){
	case 0:    Result = HorseStep(4, StepLevel + 1) + HorseStep(6, StepLevel + 1); break;
	case 1:    Result = HorseStep(6, StepLevel + 1) + HorseStep(8, StepLevel + 1); break;
	case 2:    Result = HorseStep(7, StepLevel + 1) + HorseStep(9, StepLevel + 1); break;
	case 3:    Result = HorseStep(4, StepLevel + 1) + HorseStep(8, StepLevel + 1); break;
	case 4:    Result = HorseStep(0, StepLevel + 1) + HorseStep(3, StepLevel + 1) + HorseStep(9, StepLevel + 1); break;
	case 6:    Result = HorseStep(0, StepLevel + 1) + HorseStep(1, StepLevel + 1) + HorseStep(7, StepLevel + 1); break;
	case 7:    Result = HorseStep(2, StepLevel + 1) + HorseStep(6, StepLevel + 1); break;
	case 8:    Result = HorseStep(1, StepLevel + 1) + HorseStep(3, StepLevel + 1); break;
	case 9:    Result = HorseStep(4, StepLevel + 1) + HorseStep(2, StepLevel + 1); break;
	default:    exit(404);
	}
	return Result;
}

int main(void) {
	scanf_s("%lld", &N);
	uint32_t StepLevel = 0, Result = 0;
	for (uint32_t Position = 1; Position <= 9; Position++){
		StepLevel = 0;
		if (Position == 5 || Position == 8)
			continue;
		else 
			Result = Result + HorseStep(Position, StepLevel);
	}
	printf_s("%d\n", Result);
}