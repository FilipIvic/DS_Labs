/*
5. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _StackElement;
typedef struct _StackElement* Position;

typedef struct _StackElement {
	double number;
	Position next;
} StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* destination, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFromFile(double* destination, char* fileName);

int main()
{
	double result = 0;

	CalculatePostfixFromFile(&result, "postfix.txt");

	printf("Rezultat: %lf", result);

	return EXIT_SUCCESS;
}

Position CreateStackElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(StackElement));
	if (!newElement) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateStackElement(number);
	if (!newElement) {
		return -1;
	}

	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp) {
		return EXIT_SUCCESS;
	}

	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* destination, Position head)
{
	Position first = head->next;

	if (!first)
	{
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}

	*destination = first->number;
	DeleteAfter(head);

	return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
		{	
			result = operand1 + operand2;
			break;
		}
	case '-':
		{
			result = operand1 - operand2;
			break;
		}
	case '*':
		{
			result = operand1 * operand2;
			break;
		}
	case '/':
		{
			if (operand2 == 0)
			{
				perror("Cannot divide with zero!\n");
				return -3;
			}
			result = operand1 / operand2;
			break;
	}
	default:
		{
			printf("This operation is not supported!\n");
			return -4;
		}
	}
	
	Push(head, result);

	return EXIT_SUCCESS;
}


int CalculatePostfixFromFile(double* destination, char* fileName)
{
	FILE* fp = NULL;
	int fileLength = 0, numBytes = 0, status = 0;
	double number = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	char operation = '0';
	StackElement head = { .number = 0, .next = NULL };

	fp = fopen(fileName, "rb");
	if (!fp)
	{
		perror("Can't open file!\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Can't allocate memory!\n");
		return -1;
	}

	rewind(fp);
	fread(buffer, sizeof(char), fileLength, fp);
	printf("|%s|\n", buffer);
	fclose(fp);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1)
		{
			Push(&head, number);
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				while (head.next != NULL)
				{
					DeleteAfter(&head);
				}
				return -2;
			}
			currentBuffer += numBytes;
		}
	}

	free(buffer);

	status = Pop(destination, &head);
	if (status != EXIT_SUCCESS)
	{
		while (head.next != NULL)
		{
			DeleteAfter(&head);
		}
		return -3;
	}

	if (head.next != NULL)
	{
		printf("Postfix not valid! Please check your file!\n");
		return -4;
	}

	return EXIT_SUCCESS;

}
