

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
		reverse_stack[i] = stack[index - 1 - i];			//stack�� �� ������ reverse_stack�� �־� ���ڿ��� ������ �� ����.
	}
	reverse_stack[index] = '\0';
}

void Palindrome::Palindromecheck(int index)							//Palindrome���� Ȯ��
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

	for (int i = 0; i < 100; i++)	//���ڿ� �ʱ�ȭ
	{
		c.word[i] = 0;
	}

	cout << "Enter word" << endl;

	cin >> c.word;		//���� �Է�

	int index = 0;
	while (c.word[index] != 0)	//���ڿ� ���ڼ� Ȯ��
	{
		index++;
	}

	c.Stack(index);					//���ڼ���ŭ�� ũ�� ���� ������ stack ����
	c.push(c.word, index);			//stack�� �ܾ� �ѱ��ھ� ����
	c.reverse_push(c.word, index);	//reverse_stack�� �ܾ� �ѱ��ھ� �ں��� ����
	c.Palindromecheck(index);		//Palindrome���� Ȯ��

	system("pause");
}