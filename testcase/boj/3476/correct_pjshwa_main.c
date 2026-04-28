/* ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem H - Hotline
   Michal Sevcenko
*/

#include <stdio.h>
#include <string.h>

#define MAX_WORD 102
#define MAX_STATEMENT 1000

#define bool int
#define true 1
#define false 0

struct Statement {
	char Subject[MAX_WORD];
	char Verb[MAX_WORD];
	char Object[MAX_WORD];
	bool Positive;
} Statements[MAX_STATEMENT];

int StatementCount;
bool Contradictory;

void IDontKnow()
{
	printf("I don't know.\n");
}

bool BeginsWith(const char *str, const char *token)
{
	return strncmp(str, token, strlen(token)) == 0;
}

void SkipWord(const char **str)
{
	while (**str && **str != ' ') (*str)++;
	if (**str) (*str)++;
}

void ReadWord(char *buffer, const char **str)
{
	while (**str && **str != ' ') *buffer++ = *(*str)++;
	*buffer = 0;
	if (**str) (*str)++;
}

int GetShape(const char *subject)
{
	if (strcmp(subject, "I") == 0)
		return 1;

	if (strcmp(subject, "you") == 0)
		return 2;

	return 3;
}

const char *GetNegativeDo(const char *subject)
{
	if (GetShape(subject) == 3)
		return "doesn't";
	return "don't";
}

void ConvertFromInfinitive(char *verb, const char *subject)
{
	char w[MAX_WORD];
	if (strcmp(subject, "I") != 0 && strcmp(subject, "you") != 0)
		sprintf(w, "%ss", verb);
	else
		sprintf(w, "%s", verb);
	strcpy(verb, w);
}

void ConvertToInfinitive(char *verb, const char *subject)
{
	if (strcmp(subject, "I") != 0 && strcmp(subject, "you") != 0)
		strchr(verb, 0)[-1] = 0;
}

void PrintPositive(const char *subject, const char *verb, const char
*object)
{
	char newverb[MAX_WORD];
	strcpy(newverb, verb);
	ConvertFromInfinitive(newverb, subject);
	printf("yes, %s %s%s%s.\n", subject, newverb, object[0] ? " ": "",
		object);
}

void PrintNegative(const char *subject, const char *verb, const char
*object)
{
	printf("no, %s %s %s%s%s.\n", subject, GetNegativeDo(subject), verb,
		object[0] ? " ": "", object);
}

/* who? */
void EnumerateSubjectsOfActivity(char *verb, const char *object)
{
	int c = 0, count = 0;
	int i;
	bool thirdshape = true;
	bool nobody = false;
	
	for (i=0; i<StatementCount; i++)
	{
		if (strcmp(Statements[i].Verb, verb) == 0 &&
			strcmp(Statements[i].Object, object) == 0)
		{
			if (Statements[i].Positive)
			{
				if (count || strcmp(Statements[i].Subject, "I") == 0 ||
					strcmp(Statements[i].Subject, "you") == 0) thirdshape = false;
				count++;
			}
			else
			if (strcmp(Statements[i].Subject, "everybody") == 0)
				nobody = true;
		}
	}
	
	if (count == 0)
	{
		if (nobody)
		{
			printf("nobody %ss", verb);
			if (object[0])
				printf(" %s", object);
			printf(".\n");
		}
		else
			IDontKnow();
		return;
	}

	for (i=0; i<StatementCount; i++)
	{
		if (strcmp(Statements[i].Verb, verb) != 0 ||
			strcmp(Statements[i].Object, object) != 0 ||
			!Statements[i].Positive) continue;

		if (c)
		{
			if (c == count-1)
				printf(" and ");
			else
				printf(", ");
		}
		if (strcmp(Statements[i].Subject, "you") == 0)
			printf("I");
		else
		if (strcmp(Statements[i].Subject, "I") == 0)
			printf("you");
		else
			printf("%s", Statements[i].Subject);
		c++;
	}
	printf(" %s%s", verb, thirdshape ? "s" : "");
	if (object[0]) printf(" %s", object);
	printf(".\n");
}

/* what? */
void EnumerateActivitiesOfSubject(const char *subject)
{
	int c = 0, count = 0;
	int i;
	char verb[MAX_WORD];
	char newsubject[MAX_WORD];

	if (strcmp(subject, "I") == 0)
		strcpy(newsubject, "you");
	else
	if (strcmp(subject, "you") == 0)
		strcpy(newsubject, "I");
	else
		strcpy(newsubject, subject);

	for (i=0; i<StatementCount; i++)
	{
		if (strcmp(Statements[i].Subject, subject) == 0 ||
			strcmp(Statements[i].Subject, "everybody") == 0)
			count++;
	}
	
	if (count == 0)
	{
		IDontKnow();
		return;
	}
	
	printf("%s ", newsubject);
	for (i=0; i<StatementCount; i++)
	{
		if (strcmp(Statements[i].Subject, subject) != 0 &&
			strcmp(Statements[i].Subject, "everybody") != 0)
			continue;

		if (c)
		{
			if (c == count-1)
				printf(", and ");
			else
				printf(", ");
		}
		strcpy(verb, Statements[i].Verb);
		if (Statements[i].Positive)
		{
			ConvertFromInfinitive(verb, newsubject);
			printf("%s", verb);
			if (Statements[i].Object[0])
				printf(" %s", Statements[i].Object);
		}
		else
		{
			printf("%s %s", GetNegativeDo(newsubject), verb);
			if (Statements[i].Object[0])
				printf(" %s", Statements[i].Object);
		}
		c++;
	}
	printf(".\n");
}

void PrintAnswer(const char *subject, const char *verb, const char
*object)
{
	int i;
	char newsubject[MAX_WORD];
	for (i=0; i<StatementCount; i++)
	{
		// the activity do not match
		if (strcmp(Statements[i].Verb, verb) != 0 ||
			strcmp(Statements[i].Object, object) != 0) continue;

		// subject do not match
		if (strcmp(Statements[i].Subject, "everybody") != 0 &&
			strcmp(Statements[i].Subject, subject) != 0) continue;

		if (strcmp(subject, "I") == 0)
			strcpy(newsubject, "you");
		else
		if (strcmp(subject, "you") == 0)
			strcpy(newsubject, "I");
		else
			strcpy(newsubject, subject);

		if (Statements[i].Positive)
			PrintPositive(newsubject, verb, object);
		else
			PrintNegative(newsubject, verb, object);
		return;

	}
	printf("maybe.\n");
}

void ProcessQuestion(const char *sentence)
{
	char subject[MAX_WORD];
	char verb[MAX_WORD];

	if (Contradictory)
	{
		printf("I am abroad.\n");
		return;
	}

	if (BeginsWith(sentence, "do ") ||
		BeginsWith(sentence, "does "))
	{
		SkipWord(&sentence);
		ReadWord(subject, &sentence);
		ReadWord(verb, &sentence);
		PrintAnswer(subject, verb, sentence);
	}
	else
	if (BeginsWith(sentence, "who "))
	{
		SkipWord(&sentence);
		ReadWord(verb, &sentence);
		ConvertToInfinitive(verb, "who");
		EnumerateSubjectsOfActivity(verb, sentence);
		return;
	}
	else
	{
		SkipWord(&sentence);
		SkipWord(&sentence);
		ReadWord(subject, &sentence);
		SkipWord(&sentence);
		EnumerateActivitiesOfSubject(subject);
	}
}

void AddStatement(const char *subject, const char *verb,
				  const char *object, bool positive)
{
	int i;

	for (i=0; i<StatementCount; i++)
	{
		// activity doesn't match
		if (strcmp(Statements[i].Verb, verb) != 0 ||
			strcmp(Statements[i].Object, object) != 0) continue;

		if (strcmp(subject, "everybody") == 0)
		{
			if (Statements[i].Positive != positive)
			{
				Contradictory = true;
				return;
			}
			strcpy(Statements[i].Subject, "everybody");
			// remove statements with same activity
			for (i++; i<StatementCount; i++)
			{
				if (strcmp(Statements[i].Verb, verb) != 0 ||
					strcmp(Statements[i].Object, object) != 0) continue;
				Statements[i].Verb[0] = 0;
				Statements[i].Subject[0] = 0;
				Statements[i].Object[0] = 0;
			}
			return;
		}
		if (strcmp(Statements[i].Subject, "everybody") == 0)
		{
			if (Statements[i].Positive != positive)
			{
				Contradictory = true;
				return;
			}
			return;
		}
		if (strcmp(subject, Statements[i].Subject) == 0)
		{
			if (Statements[i].Positive != positive)
			{
				Contradictory = true;
				return;
			}
			return;
		}
	}
	strcpy(Statements[i].Subject, subject);
	strcpy(Statements[i].Verb, verb);
	strcpy(Statements[i].Object, object);
	Statements[i].Positive = positive;
	StatementCount++;
}

void ProcessSentence(const char *sentence)
{
	char subject[MAX_WORD];
	char verb[MAX_WORD];
	bool positive = true;

	if (Contradictory) return;

	ReadWord(subject, &sentence);
	ReadWord(verb, &sentence);
	if (strcmp(verb, "don't") == 0 || strcmp(verb, "doesn't") == 0)
	{
		positive = false;
		ReadWord(verb, &sentence);
	}
	else
		ConvertToInfinitive(verb, subject);
	if (strcmp(subject, "nobody") == 0)
	{
		positive = false;
		strcpy(subject, "everybody");
	}
	AddStatement(subject, verb, sentence, positive);
}

void DoIt()
{
	char sentence[MAX_WORD];

	StatementCount = 0;
	Contradictory = false;
	while (true)
	{
		char *end;
		if (!gets(sentence)) break;
		end = strchr(sentence, 0)-1;
		if (*end == '?')
		{
			printf("%s\n", sentence);
			*end = 0;
			ProcessQuestion(sentence);
			printf("\n");
		}
		else
		if (*end == '.')
		{
			*end = 0;
			ProcessSentence(sentence);
		}
		else
		if (*end == '!')
		{
			printf("%s\n", sentence);
			break;
		}
	}
	printf("\n");
}

int main()
{
	int i, n;

	scanf("%i\n", &n);
	for (i=0; i<n; i++)
	{
		printf("Dialogue #%i:\n", i+1);
		DoIt();
	}

	return 0;
}

