

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

void Palindrome::Palindromecheck(int index)							
{
	int i;
	int indexnum_different;				//문자열을 뒤집었을 때 같지 않게 되는 부분의 index를 추출
										//(제거해야 하는 문자는 1개로 한정했으므로, 그 외의 경우는 생각지 않음.)

	for (i = 0; i < index; i++)
	{
		if (stack[i] != reverse_stack[i])
		{
			indexnum_different = i;
			break;
		}
	}

	if (i == index)
	{
		cout << "-1" << endl;
	}
	else
	{
		if(stack[indexnum_different+1] == stack[index-indexnum_different-1])
		{
			cout << "Index to remove: " << indexnum_different << endl;
		}
		else
		{
			cout << "Index to remove: " << index - indexnum_different - 1 << endl;
		}
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
	c.Palindromecheck(index);		

	system("pause");
}