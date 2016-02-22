//Daniel Clark
//Last Updated: 03/20/15
//Purpose: The Employee program used to experiment with malloc.
//Version: 1.0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 20
#define STREQUALS(str1, str2) (strcmp(str1, str2) == 0)


struct Employees {
	char* name;
	char ssn[9];
	int yearBorn;
	int salary;
};

struct Employees *emps[MAX_EMPLOYEES];

void display(struct Employees* emps) {
  char temp[16], temp1[16];
  int i, j, k;

  printf("Employee Name:%s ", emps->name);
  printf("SSN:%3.3s-%2.2s-%s\n", &(emps->ssn[0]),&(emps->ssn[3]),&(emps->ssn[5]));

  //convert int to char[]
  sprintf( temp, "%d", emps->salary);

  //add ',' to salary
  for( i=0,k=0, j=strlen(temp); j > 0; i++, k++, j--) {
    temp1[i]=temp[j-1];
    if( (k+1) % 3 == 0 && j != 1 ) {
      i++;
      temp1[i]=',';
    }
  }
  temp1[i]=0; //add zero ending to it

  //reverse the order
  for( i=0, j=strlen(temp1)-1; j >= 0; i++, j--) {
    temp[i]=temp1[j];
  }
  temp[i]=0; //add zero ending to it

  printf("Salary:$%s\n", temp );
}

void readEmployee(struct Employees* emps) {
	char buffer[20];
	printf("Please Enter Employee's Name: ");
	scanf("%s",buffer);
	emps->name = strdup(buffer);
	printf("Please Enter Employee's SSN: ");
	scanf("%s",emps->ssn);
	printf("Please Enter Employee's Year of Birth: ");
	scanf("%d",&emps->yearBorn);
	printf("Please Enter Employee's Salary: ");
	scanf("%d",&emps->salary);
}

void createEmployee() {
	int i = 0;
	struct Employees* tempEmp = (struct Employees*)malloc(sizeof(struct Employees));
	readEmployee(tempEmp);
	for(i = 0; i < MAX_EMPLOYEES; i++) {
		if(emps[i] == NULL)
		{
			emps[i] = tempEmp;
			break;
		}
	}
}

void releaseEmployee(struct Employees* emps) {
    //this method deallocates the memory holding an employee
	free(emps->name);
	free(emps);
}

struct Employees* findEmployee(char* _name) {
	int i;
	for(i = 0; i < MAX_EMPLOYEES; i++) {
		if(emps[i] != NULL && STREQUALS(emps[i]->name,_name))
		{
			display(emps[i]);
		}

	}
	return NULL;
}

void listEmployees() {
	int i;
	for(i = 0; i < MAX_EMPLOYEES; i++)
	{
		if(emps[i] != NULL)
			display(emps[i]);
	}
}

void fireEmployees(char* name) {
	int i;
	char confirm[4];
	for (i = 0; i < MAX_EMPLOYEES; i++) {
		if(emps[i] != NULL && STREQUALS(emps[i]->name,name)){
			printf("\nDo you wish to FIRE %s? (y/n) ",emps[i]->name);
			scanf("%s",confirm);
			if(STREQUALS(confirm,"y")) {
				printf("\n%s was fired... poor dude.\n",emps[i]->name);
				releaseEmployee(emps[i]);
				emps[i] = NULL;
				return;
			}else{
				printf("\n%s was not fired\n",emps[i]->name);
				return;
			}
		}
	}
	printf("\nEmployee does not exist.\n");
}


int main() {
	char choice[5];
	while(!STREQUALS(choice,"quit")) {
		printf("\nPlease choose a command:\n");
		printf("hire: Hire an Employee\n");
		printf("find: Find an Employee\n");
		printf("list: List all Employees\n");
		printf("fire: Fire an Employee\n");
		printf("quit: Quit the Application\n");
		printf("\nPlease Enter a Command: ");
		scanf("%s",choice);

		if(STREQUALS(choice,"hire")) {
			createEmployee();
		} else if (STREQUALS(choice,"list")) {
			listEmployees();
		}else if (STREQUALS(choice, "find")){
			char name[20];
			printf("\nPleae Enter the Employee to find: ");
			scanf("%s",name);
			findEmployee(name);
		} else if (STREQUALS(choice,"fire")){
			char name[20];
			printf("\nPleae Enter the Employee to fire: ");
			scanf("%s",name);
			fireEmployees(name);
		}
	}
	return 0;
}
