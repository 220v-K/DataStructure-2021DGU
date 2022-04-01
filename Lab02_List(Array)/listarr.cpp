//--------------------------------------------------------------------
//
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------

#include "listarr.h"

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

	: maxSize(maxNumber),
	size(0),
	cursor(-1)
{
	// pre-lab

	dataItems = new DataType[maxSize];	
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	delete[] dataItems;
}

//--------------------------------------------------------------------

void List::insert(const DataType& newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	// pre-lab
	try
	{
		if (isFull() == true)	//����Ʈ�� �� á�� ��� ���� ó��
		{
			throw logic_error("List is Full!");
		}

		if (cursor < size) //����Ʈ �߰��� ���� ��
		{
			size++; //�迭 ũ�� ����

			for (int i = size - 1; i > cursor; --i)
			{
				dataItems[i] = dataItems[i - 1]; //�迭 ���� �ϳ��� �ڷ� �и�
			}

			dataItems[++cursor] = newDataItem; //Ŀ�� ������ ���� �߰�

		}

		else //����Ʈ ���� ���� ��
		{
			size++; //�迭 ũ�� ����
			dataItems[++cursor] = newDataItem; //Ŀ�� ������ ���� �߰�
		}
	}


	catch (std::logic_error)
	{
		cout << "Insert: List is Full!" << endl;
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.
{
	// pre-lab
	try
	{
		if (isEmpty() == true)
		{
			throw logic_error("List is Empty!");
		}

		for (int i = cursor; i < size - 1; ++i) //Ŀ�� ��ġ�� ���Ҹ� �����ϱ� ���� Ŀ�� ���� ��ġ�� ���ҵ��� ������ ��ܿ�.
		{
			dataItems[i] = dataItems[i + 1];
			dataItems[i + 1] = 0;
		}
		size--;		//�迭 ũ�� 1 ����

		if (cursor >= size)		//���� Ŀ���� ������� ũ�ų� ���� ��� (Ŀ���� ���Ұ� ���� ��ġ�� ������ ���)
		{
			cursor = 0;			//Ŀ���� ����Ʈ �� ������ ����
		}
	}

	catch (std::logic_error)
	{
		cout << "Remove: List is Empty!" << endl;
	}
}

//--------------------------------------------------------------------

void List::replace(const DataType& newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.
{
	// Requires that the list is not empty
	// pre-lab
	try
	{
		if (isEmpty() == true)		//����Ʈ�� ����ִٸ�, ����ó��. Ŀ���� ���� ���� ��ġ�� ������ �� ���⿡, �������� ����.
		{
			throw logic_error("Empty!");	//������� ����.
		}

		dataItems[cursor] = newDataItem;	//���� �ִٸ�, �Է¹��� ������ �ٲ�. Ŀ�� ��ġ�� �״��
	}

	catch (std::logic_error)
	{
		cout << "Replace: value does not exist at cursor" << endl;
	}
}
//--------------------------------------------------------------------

void List::clear()
// Removes all the data items from a list.
{
	// pre-lab
	size = 0;
	cursor = -1;	//�迭 ũ��� Ŀ�� �ʱ�ȭ

	for (int i = 0; i < maxSize; ++i)		//�迭�� ��� ���Ҹ� 0���� �ʱ�ȭ
	{
		dataItems[i] = 0;
	}
}

//--------------------------------------------------------------------

bool List::isEmpty() const
// Returns 1 if a list is empty. Otherwise, returns 0.
{
	// pre-lab
	if (size == 0)		//�迭 ũ�� 0�϶� true(1) ��ȯ
	{
		return true;
	}

	else
	{
		return false;
	}
}

//--------------------------------------------------------------------

bool List::isFull() const
// Returns 1 if a list is full. Otherwise, returns 0.
{
	// pre-lab
	if (size == maxSize)		//�迭�� ũ�Ⱑ �ִ��϶� true(1) ��ȯ
	{
		return true;
	}

	else
	{
		return false;
	}
}

//--------------------------------------------------------------------

bool List::gotoBeginning() throw (logic_error)
// Moves the cursor to the beginning of the list.
{
	// pre-lab
	try
	{
		if (isEmpty() == 1)		//����Ʈ�� ����ִٸ�, ����ó�� (true�� 1�̴ϱ�..)
		{
			throw logic_error("List is Empty!");
		}

		cursor = 0;		//�ƴ϶��, Ŀ�� ��ġ�� ����Ʈ�� ���������� �ٲ�
	}

	catch (std::logic_error)
	{
		cout << "gotoBeginning: List is Empty!" << endl;
	}
}

//--------------------------------------------------------------------

bool List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	try
	{
		if (isEmpty() == 1)		//����Ʈ�� ����ִٸ�, ����ó�� (true�� 1�̴ϱ�..)
		{
			throw logic_error("List is Empty!");
		}

		cursor = size - 1;		//�ƴ϶��, Ŀ�� ��ġ�� ����Ʈ�� ������ �ٲ�
	}

	catch (std::logic_error)
	{
		cout << "gotoEnd: List is Empty!" << endl;
	}
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.
{
	// pre-lab

	if (isEmpty() == true || cursor == size - 1)		//����Ʈ�� ����ִٸ�, �Ǵ� Ŀ���� ����Ʈ�� �������� ��ġ�� �ִٸ�, ����ó��
	{
		cout << "gotoNext: List is Empty or Cursor is End of the List" << endl;
		return false;		//����ó�� �Ǿ��� ��, false ��ȯ
	}
	else
	{
		cursor = cursor + 1;		//�ƴ϶��, Ŀ�� ��ġ�� ���� ��ġ�� �ٲ�
		return true;		//�׸��� true ��ȯ
	}						//try-throw-catch�� ��� �ϴ� �� ���Ƽ� ã�Ƽ� ������.. �̰� �ξ� ���� �� ����.
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	try
	{
		if (isEmpty() == true || cursor == 0)		//����Ʈ�� ����ִٸ�, �Ǵ� Ŀ���� ����Ʈ�� ó���� ��ġ�� �ִٸ�, ����ó��
		{
			throw logic_error("Error");
		}

		cursor = cursor - 1;		//�ƴ϶��, Ŀ�� ��ġ�� ���� ��ġ�� �ٲ�
		return true;		//�׸��� true ��ȯ
	}

	catch (std::logic_error)
	{
		cout << "gotoPrior: List is Empty or Cursor is End of the List" << endl;
		return false;		//����ó�� �Ǿ��� ��, false ��ȯ
	}
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)
// Returns the item marked by the cursor.

{
	// pre-lab
	try
	{
		if (isEmpty() == true)		//����Ʈ�� ����ִٸ�, ����ó��
		{
			throw logic_error("Error");
		}

		return dataItems[cursor];	//dataItems[cursor]�� ��ȯ���ָ�, test4.cpp���� �̸� �ۼ��Ǿ��� �Լ� ȣ��� �¾ƶ������� �ڿ������� ��µ�.
	}

	catch (std::logic_error)
	{
		cout << "getCursor: List is Empty or Cursor is End of the List" << endl;
	}
}

//--------------------------------------------------------------------

void List::showStructure() const
// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
	// pre-lab

	cout << "size: " << size;
	cout << " cursor: " << cursor << endl;

	cout << "[0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]" << endl;

	for (int i = 0; i < size; ++i)
	{
		cout << " " << dataItems[i] << "   ";
	}
}

//--------------------------------------------------------------------

//in-lab
void List::moveToNth(int n) throw (logic_error)
{
	if (dataItems[1] == 0)		//����Ʈ�� ��� �ִٸ�, �Ǵ� ���� 1�����, ����ó��
	{
		cout << "List must has at least 2 value" << endl;
	}
	else
	{
		char temp = getCursor();
		int temp_cursor = cursor;

		if (n == cursor)		//�ű���� ��ġ�� Ŀ���� ��ġ�� ��
		{
			cout << "It's already in that position" << endl;
		}
		else if (n > cursor)	//�ű���� ��ġ�� Ŀ������ ���� ��
		{
			for (int i = 0; i < n-cursor; i++)
			{
				dataItems[temp_cursor] = dataItems[temp_cursor + 1];		//�ű� ��ġ�� �ִ� ���ұ����� ������ �а�
				temp_cursor++;
			}

			dataItems[n] = temp;						//�ű� ��ġ�� temp�� �����س��� ó�� Ŀ�� ��ġ�� �� ����
			cursor = n;									//Ŀ���� ���� �Ű� ��
		}
		else if (n < cursor)	//�ű���� ��ġ�� Ŀ������ ���� ��
		{
			for (int i = 0; i < cursor - n; i++)
			{
				dataItems[temp_cursor] = dataItems[temp_cursor - 1];		//�ű� ��ġ�� �ִ� ���ұ����� �ڷ� �а�
				temp_cursor--;
			}

			dataItems[n] = temp;						//�ű� ��ġ�� temp�� �����س��� ó�� Ŀ�� ��ġ �� ����
			cursor = n;									//Ŀ���� ���� �Ű� ��.
		}
	}
}


bool List::find(const DataType& searchDataItem) throw(logic_error)
{
	// in-lab 3
	bool Areyousearched = false;
	int temp_cursor = cursor;

	if (isEmpty() == true)
	{
		cout << "List is Empty!" << endl;
		return false;
	}
	else
	{
		for (int i = 1; i <= size-cursor; i++)		//Ŀ������ ã�� ����, �ִ� Ƚ�� : ����Ʈ�� (size - Ŀ��) ��ŭ
		{
			if (dataItems[temp_cursor] == searchDataItem)		//���� ã�Ҵٸ�,
			{
				cursor = temp_cursor;							//ã�� ������ Ŀ�� �̵�
				return true;
				break;								//ã�����Ƿ� ���̻� ã�� �ʰ� �ݺ��� Ż��
				Areyousearched = true;				//ã������ Areyousearched�� true��
			}
			temp_cursor++;
		}
		
		if (Areyousearched == false)				//���� ã�� ���ߴٸ�
		{
			cursor = size - 1;						//���������� ã�� ���� ���̹Ƿ� Ŀ���� ����������
			return false;
		}

		Areyousearched = false;						//�ٽ� ������ ���� ���� Areyousearched�� false�� �ʱ�ȭ
	}
}