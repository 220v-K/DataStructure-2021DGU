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
		if (isFull() == true)	//리스트가 꽉 찼을 경우 예외 처리
		{
			throw logic_error("List is Full!");
		}

		if (cursor < size) //리스트 중간에 넣을 때
		{
			size++; //배열 크기 증가

			for (int i = size - 1; i > cursor; --i)
			{
				dataItems[i] = dataItems[i - 1]; //배열 원소 하나씩 뒤로 밀림
			}

			dataItems[++cursor] = newDataItem; //커서 다음에 원소 추가

		}

		else //리스트 끝에 넣을 때
		{
			size++; //배열 크기 증가
			dataItems[++cursor] = newDataItem; //커서 다음에 원소 추가
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

		for (int i = cursor; i < size - 1; ++i) //커서 위치의 원소를 제거하기 위해 커서 다음 위치의 원소들을 앞으로 당겨옴.
		{
			dataItems[i] = dataItems[i + 1];
			dataItems[i + 1] = 0;
		}
		size--;		//배열 크기 1 감소

		if (cursor >= size)		//만약 커서가 사이즈보다 크거나 같을 경우 (커서가 원소가 없는 위치에 존재할 경우)
		{
			cursor = 0;			//커서를 리스트 맨 앞으로 보냄
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
		if (isEmpty() == true)		//리스트가 비어있다면, 예외처리. 커서가 값이 없는 위치에 존재할 수 없기에, 생각하지 않음.
		{
			throw logic_error("Empty!");	//실행되지 않음.
		}

		dataItems[cursor] = newDataItem;	//값이 있다면, 입력받은 값으로 바꿈. 커서 위치는 그대로
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
	cursor = -1;	//배열 크기와 커서 초기화

	for (int i = 0; i < maxSize; ++i)		//배열의 모든 원소를 0으로 초기화
	{
		dataItems[i] = 0;
	}
}

//--------------------------------------------------------------------

bool List::isEmpty() const
// Returns 1 if a list is empty. Otherwise, returns 0.
{
	// pre-lab
	if (size == 0)		//배열 크기 0일때 true(1) 반환
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
	if (size == maxSize)		//배열의 크기가 최대일때 true(1) 반환
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
		if (isEmpty() == 1)		//리스트가 비어있다면, 예외처리 (true는 1이니까..)
		{
			throw logic_error("List is Empty!");
		}

		cursor = 0;		//아니라면, 커서 위치를 리스트의 시작점으로 바꿈
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
		if (isEmpty() == 1)		//리스트가 비어있다면, 예외처리 (true는 1이니까..)
		{
			throw logic_error("List is Empty!");
		}

		cursor = size - 1;		//아니라면, 커서 위치를 리스트의 끝으로 바꿈
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

	if (isEmpty() == true || cursor == size - 1)		//리스트가 비어있다면, 또는 커서가 리스트의 마지막에 위치해 있다면, 예외처리
	{
		cout << "gotoNext: List is Empty or Cursor is End of the List" << endl;
		return false;		//예외처리 되었을 때, false 반환
	}
	else
	{
		cursor = cursor + 1;		//아니라면, 커서 위치를 다음 위치로 바꿈
		return true;		//그리고 true 반환
	}						//try-throw-catch를 써야 하는 것 같아서 찾아서 썼지만.. 이게 훨씬 편한 것 같다.
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
		if (isEmpty() == true || cursor == 0)		//리스트가 비어있다면, 또는 커서가 리스트의 처음에 위치해 있다면, 예외처리
		{
			throw logic_error("Error");
		}

		cursor = cursor - 1;		//아니라면, 커서 위치를 이전 위치로 바꿈
		return true;		//그리고 true 반환
	}

	catch (std::logic_error)
	{
		cout << "gotoPrior: List is Empty or Cursor is End of the List" << endl;
		return false;		//예외처리 되었을 때, false 반환
	}
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)
// Returns the item marked by the cursor.

{
	// pre-lab
	try
	{
		if (isEmpty() == true)		//리스트가 비어있다면, 예외처리
		{
			throw logic_error("Error");
		}

		return dataItems[cursor];	//dataItems[cursor]를 반환해주면, test4.cpp에서 미리 작성되어진 함수 호출과 맞아떨어져서 자연스럽게 출력됨.
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
	if (dataItems[1] == 0)		//리스트가 비어 있다면, 또는 값이 1개라면, 예외처리
	{
		cout << "List must has at least 2 value" << endl;
	}
	else
	{
		char temp = getCursor();
		int temp_cursor = cursor;

		if (n == cursor)		//옮기려는 위치가 커서의 위치일 때
		{
			cout << "It's already in that position" << endl;
		}
		else if (n > cursor)	//옮기려는 위치가 커서보다 뒤일 때
		{
			for (int i = 0; i < n-cursor; i++)
			{
				dataItems[temp_cursor] = dataItems[temp_cursor + 1];		//옮길 위치에 있는 원소까지는 앞으로 밀고
				temp_cursor++;
			}

			dataItems[n] = temp;						//옮길 위치에 temp로 저장해놓은 처음 커서 위치의 값 저장
			cursor = n;									//커서도 같이 옮겨 줌
		}
		else if (n < cursor)	//옮기려는 위치가 커서보다 앞일 때
		{
			for (int i = 0; i < cursor - n; i++)
			{
				dataItems[temp_cursor] = dataItems[temp_cursor - 1];		//옮길 위치에 있는 원소까지는 뒤로 밀고
				temp_cursor--;
			}

			dataItems[n] = temp;						//옮길 위치에 temp로 저장해놓은 처음 커서 위치 값 저장
			cursor = n;									//커서도 같이 옮겨 줌.
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
		for (int i = 1; i <= size-cursor; i++)		//커서부터 찾기 시작, 최대 횟수 : 리스트의 (size - 커서) 만큼
		{
			if (dataItems[temp_cursor] == searchDataItem)		//만약 찾았다면,
			{
				cursor = temp_cursor;							//찾은 곳으로 커서 이동
				return true;
				break;								//찾았으므로 더이상 찾지 않고 반복문 탈출
				Areyousearched = true;				//찾았으면 Areyousearched를 true로
			}
			temp_cursor++;
		}
		
		if (Areyousearched == false)				//만약 찾지 못했다면
		{
			cursor = size - 1;						//마지막까지 찾지 못한 것이므로 커서는 마지막으로
			return false;
		}

		Areyousearched = false;						//다시 실행할 때를 위해 Areyousearched를 false로 초기화
	}
}