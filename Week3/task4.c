#include <stdio.h>
#include <string.h>

typedef struct
{
	char *FacID;		/* FIT, ENG, MTH, SCI, etc */
	int UnitID;			/* 1047, 2100, 3142, etc */
} UnitCode;

int main()
{
	/*
	UnitCode unit1;
	unit1.FacID = "FIT";
	unit1.UnitID = 2100;
	
	UnitCode unit2;
	unit2.FacID = "ENG";
	unit2.UnitID = 3142;
	*/
	
	/*
	UnitCode unit1;
	unit1.FacID = "FIT";
	unit1.UnitID = 2100;
	
	UnitCode unit2;
	unit2.FacID = "FIT";
	unit2.UnitID = 3142;
	*/
	
	
	UnitCode unit1;
	unit1.FacID = "FIT";
	unit1.UnitID = 2100;
	
	UnitCode unit2;
	unit2.FacID = "FIT";
	unit2.UnitID = 2100;
	
	
	//only true if both variables equal to each other
	//strcmp function from the <string.h> library
	if ((strcmp(unit1.FacID, unit2.FacID) == 0) && (unit1.UnitID == unit2.UnitID))
	{
		printf("The two UnitCodes are equal to each other. \n");
	}
	else
	{
		printf("The two UnitCodes are not equal to each other. \n");
	}
	
	return 0;
}
