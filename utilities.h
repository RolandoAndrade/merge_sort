
int indexOf(char a, char *s)
{
	for(int i=0;i<strlen(s);i++)
		if(toupper(a)==s[i])
			return i;
	return -1;
}

int compareChars(char a,char b, char *ABC)
{
	return indexOf(a,ABC)-indexOf(b,ABC);
}

int strCompare(char *a, char *b, char *ABC)
{
	for(int i=0,j=0;i<strlen(a)&&j<strlen(b);i++,j++)
	{
		int x=compareChars(a[i],b[j],ABC);
		if(x!=0)
			return x;
	}
	return 0;
}

void printError(const char *fileName)
{
	printf("El archivo %s no existe\n",fileName);
	exit(0);
}

int readStrings(const char *fileName, char **words)
{
	FILE * file = freopen(fileName, "r",stdin);
	if(!file)
		printError(fileName);

	int len=0;
	while(scanf("%s",words[len++])!=EOF);
	fclose(file);
	return len-1;
}

void readAlphabet(const char *fileName,char *ABC)
{
	FILE * file = freopen(fileName, "r",stdin);
	if(!file)
		printError(fileName);
	int i=0;
	while(scanf("%s",&(ABC[i++]))!=EOF);
	fclose(file);
}

void writeStrings(char **words, int len)
{
	for(int i=0;i<len;i++)
		printf("%s\n", words[i]);
}
