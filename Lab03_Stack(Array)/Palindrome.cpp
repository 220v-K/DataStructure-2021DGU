

#include <iostream>

using namespace std;

class Palindrome
{
public:
	char word[100];
	char* stack;
	char* reverse_stack;
	void push(char word[], int index);
	void reverse_push(char word[], int index);
	void Stack(int indexnum);
	void Palindromecheck(int index);
};

void Palindrome::Stack(int indexnum)
{
	stack = new char[indexnum];
	reverse_stack = new char[indexnum];
}

void Palindrome::push(char word[], int index)				//stack
{
	for (int i = 0; i < index; i++)
	{
		stack[i] = word[i];
	}
	stack[index] = '\0';
}

void Palindrome::reverse_push(char word[], int index)		//stackdwn
{
	for (int i = 0; i < index; i++)
	{
		reverse_stack[i] = stack[index - 1 - i];			//stack의 맨 위부터 reverse_stack에 넣어 문자열을 뒤집을 수 있음.
	}
	reverse_stack[index] = '\0';
}

void Palindrome::Palindromecheck(int index)							//Palindrome인지 확인
{
	int i;
	for (i = 0; i < index; i++)
	{
		if (stack[i] != reverse_stack[i])
		{
			break;
		}
	}

	if (i == index)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
}

void main(void)
{
	Palindrome c;

	for (int i = 0; i < 100; i++)	//문자열 초기화
	{
		c.word[i] = 0;
	}

	cout << "Enter word" << endl;

	cin >> c.word;		//문자 입력

	int index = 0;
	while (c.word[index] != 0)	//문자열 글자수 확인
	{
		index++;
	}

	c.Stack(index);					//글자수만큼의 크기 저장 가능한 stack 생성
	c.push(c.word, index);			//stack에 단어 한글자씩 삽입
	c.reverse_push(c.word, index);	//reverse_stack에 단어 한글자씩 뒤부터 삽입
	c.Palindromecheck(index);		//Palindrome인지 확인

	system("pause");
}