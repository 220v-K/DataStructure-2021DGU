

#include <iostream>
#include <list>
#include <string>
#include <hash_map>
#include <algorithm>

using namespace std;
using namespace stdext;

//--------------------------------------------------------------------
//                       Class Definition
//--------------------------------------------------------------------

class Person
{
public:

    // Constructor
    Person(const string& newName)
    {
        this->name = newName;
    }

    string name;		//the name of person.

    list<Person> friendList;		//friend list

    friend class Facebook;
};

class Facebook
{
private:
    hash_map<string, Person> FB_hash_map;

public:
    
    // Constructor
    Facebook();

    // Destructor
    ~Facebook();

    // Operator
    void create(const string& newName);							//command 'P'
    void makefriend(const string& name1, const string& name2);	//command 'F'
    void break_up(const string& name1, const string& name2);	//command 'U'
    void print_friends(const string& name1);					//command 'L'
    void isFriend(const string& name1, const string& name2);	//command 'Q'

    // For Test
    void showAll();
};

bool operator==(const Person& p1, const Person& p2)         // Person class에 대한 연산자 Overloading (Line 178)
{
    if (p1.name == p2.name)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------
//                       Function Definition
//--------------------------------------------------------------------

Facebook::Facebook()
{
    
}

//--------------------------------------------------------------------

Facebook::~Facebook()
{
    FB_hash_map.clear();
}

//--------------------------------------------------------------------

void Facebook::create(const string& newName)							//command 'P'
{
    Person* newPerson = new Person(newName);    //새로운 Person 객체 생성
    FB_hash_map.insert(hash_map<string, Person>::value_type(newName, *newPerson));     //hash_map에 삽입.
}

//--------------------------------------------------------------------

void Facebook::makefriend(const string& name1, const string& name2)		//command 'F'
{
    hash_map<string, Person>::iterator iter_person1;    //iterator 선언부
    hash_map<string, Person>::iterator iter_person2;

    iter_person1 = FB_hash_map.find(name1);     //각 key(name)에 맞는 iterator 반환 후 저장.
    iter_person2 = FB_hash_map.find(name2);

    if (name1 == name2)
        cout << "Same names are entered." << endl;
    else if (iter_person1 == FB_hash_map.end() || iter_person2 == FB_hash_map.end())     //P로 생성(저장)되지 않은 이름 입력 시 예외처리.
        cout << "An unsaved name has been entered." << endl;
    else
    {
        iter_person1->second.friendList.push_back(iter_person2->second);    //person1의 friendlist에 person2 넣기
        iter_person2->second.friendList.push_back(iter_person1->second);    //person2의 friendlist에 person1 넣기
    }
}

//--------------------------------------------------------------------

void Facebook::break_up(const string& name1, const string& name2)		//command 'U'
{
    hash_map<string, Person>::iterator iter_person1;    //iterator 선언부
    hash_map<string, Person>::iterator iter_person2;
    list<Person>::iterator iter_f1;     //friendlist에서 지울 친구의 iterator
    list<Person>::iterator iter_f2;

    iter_person1 = FB_hash_map.find(name1);     //각 key(name)에 맞는 iterator 반환 후 저장.
    iter_person2 = FB_hash_map.find(name2);

    if (name1 == name2)
        cout << "Same names are entered." << endl;
    else
    {
        if (iter_person1 == FB_hash_map.end() || iter_person2 == FB_hash_map.end())  //P로 생성(저장)되지 않은 이름 입력 시 예외처리.
            cout << "An unsaved name has been entered." << endl;
        else
        {
            //person1의 friendlist에서 지울 친구의 iterator를 저장. iter_f2의 경우에도 반대로 동일.
            for (iter_f1 = iter_person1->second.friendList.begin(); iter_f1 != iter_person1->second.friendList.end(); iter_f1++)
            {
                if (iter_f1->name == name2)
                    break;
            }
            for (iter_f2 = iter_person2->second.friendList.begin(); iter_f2 != iter_person2->second.friendList.end(); iter_f2++)
            {
                if (iter_f2->name == name1)
                    break;
            }
            iter_person1->second.friendList.erase(iter_f1);  //person1의 friendlist에서 person2 제거
            iter_person2->second.friendList.erase(iter_f2);  //person2의 friendlist에서 person1 제거
        }
    } 
}

//--------------------------------------------------------------------

void Facebook::print_friends(const string& fname)						//command 'L'
{
    hash_map<string, Person>::iterator iter;    //iterator 선언부
    list<Person>::iterator iter_f;  

    iter = FB_hash_map.find(fname);     //매개변수 fname을 key로 하는 노드의 iterator 반환 후 저장.

    if (iter == FB_hash_map.end())  //P로 생성(저장)되지 않은 이름 입력 시 예외처리.
        cout << "An unsaved name has been entered." << endl;
    else
    {
        for (iter_f = iter->second.friendList.begin(); iter_f != iter->second.friendList.end(); iter_f++)     //그 노드의 friendList를 iterator 이용하여 출력.
        {
            cout << iter_f->name << " ";
        }
    }
}

//--------------------------------------------------------------------

void Facebook::isFriend(const string& name1, const string& name2)		//command 'Q'
{
    hash_map<string, Person>::iterator iter;    //iterator 선언부
    hash_map<string, Person>::iterator iter2;
    list<Person>::iterator iter_f;

    iter = FB_hash_map.find(name1);     //name1을 key로 하는 노드의 iterator 반환 후 저장.
    iter2 = FB_hash_map.find(name2);

    if (name1 == name2)
        cout << "Same names are entered." << endl;
    else
    {
        if (iter == FB_hash_map.end() || iter2 == FB_hash_map.end())  //P로 생성(저장)되지 않은 이름 입력 시 예외처리.
            cout << "An unsaved name has been entered." << endl;
        else
        {
            iter_f = find(iter->second.friendList.begin(), iter->second.friendList.end(), iter2->second);   //name1이 key인 노드의 friendlist에 name2가 존재한다면 name2가 있는 곳의 iterator 반환 후 저장.

            if (iter_f == iter->second.friendList.end())     // key인 노드의 friendlist에 name2가 존재하지 않으면 NO 출력
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
    }
 
}

//--------------------------------------------------------------------
// For Test

//void Facebook::showAll()    //테스트용 출력
//{
//    hash_map<string, Person>::iterator iter_hash;
//
//    if (FB_hash_map.size() == 0)
//        cout << "List is Empty" << endl;
//    else
//    {
//        for (iter_hash = FB_hash_map.begin(); iter_hash != FB_hash_map.end(); iter_hash++)
//        {
//            cout << iter_hash->second.name << endl;
//        }
//    }
//}

//--------------------------------------------------------------------
//                       execute part
//--------------------------------------------------------------------


    void print_help()   //Print Commands
    {
        cout << endl << "Commands:" << endl;
        cout << "   H - Print this commands message" << endl;
        cout << "   P <name> - Create a person record of the specified name. You may assume that no two people have the same name." << endl;
        cout << "   F <name1> <name2> - Record that the two specified people are friends." << endl;
        cout << "   U <name1> <name2> - Record that the two specified people are no longer friends." << endl;
        cout << "   L <name> - Print out the friends of the specified person." << endl;
        cout << "   Q <name1> <name2> - Check whether the two people are friends. If so, print \"Yes\"; if not, print \"No:\"" << endl;
        cout << "   X - terminate the program." << endl;
        cout << endl;
    }

    void main()
    {
        Facebook test;                         // Test 
        string inputName1, inputName2;         // input name
        char cmd;                              // Input command

        print_help();

        do
        {
            cout << endl;
            //test.showAll();                     // Output list

            cout << endl << "Command: ";                  // Read command
            cin >> cmd;
            if (cmd == 'P' || cmd == 'p' || cmd == 'L' || cmd == 'l')
                cin >> inputName1;
            else if (cmd == 'F' || cmd == 'f' || cmd == 'U' || cmd == 'u' || cmd == 'Q' || cmd == 'q')
                cin >> inputName1 >> inputName2;

            switch (cmd)
            {
            case 'H': case 'h':
                print_help();
                break;

            case 'P': case 'p':
                test.create(inputName1);
                break;

            case 'F': case 'f':
                test.makefriend(inputName1, inputName2);
                break;

            case 'U': case 'u':
                test.break_up(inputName1, inputName2);
                break;

            case 'L': case 'l':
                test.print_friends(inputName1);
                break;

            case 'Q': case 'q':
                test.isFriend(inputName1, inputName2);
                break;

            default:                               // Invalid command
                cout << "Inactive or invalid command" << endl;
            }
        } while (cmd != 'X' && cmd != 'x');
    }