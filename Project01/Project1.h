

using namespace std;

class ListNode                // Facilitator class for the List class
{
private:

    // Constructor
    ListNode();

    // Data members
    string name;
    string phone_number;
    string birthday, birth_month; 
    ListNode* next;         //pointing next Node of List

    friend class List;
};

//--------------------------------------------------------------------

class List
{
public:

    // Constructor
    List();

    // Destructor
    ~List();

    // List manipulation operations
    void read(const string& filename);
    void write(const string& filename);

    void insert();    // add one's information
    void remove();    // remove one's information

    //List condition
    bool isFull();
    bool isEmpty();

    // Output
    void showStructure();   //for test.
    void after_update();    //print after update.
    void select_month();

private:
    ListNode* head;
    ListNode* cursor;   //이곳저곳에 이용할 커서..
    // Data members
 
};
