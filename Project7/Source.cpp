#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Elem
{
    int n;
    int cf_cos;
    int cf_sin;
};

struct Node
{
    Elem elem;
    Node* next;
};

// 1 \\ 
Node* create_list(ifstream& in, int& count_elem);

// 2 \\ 
void output_list(ofstream& out, Node* list);

// 3 \\ 
void check_input(int& n, int& cf_cos, int& cf_sin, int count_elem);
void add_elem(Node* list, int n, int cf_cos, int cf_sin, int& count_elem);

// 4 \\ 
void delete_elem(Node* list, int n);

// 5 \\ 
void finding_the_derivative_of_a_function(Node* list);

// 6 \\ 
void sum_of_polynomials(Node* list1, Node* list2, int count_elem, int count_elem_2);

// 7 \\ 
double calculating_the_value_at_a_point(Node* list, int x);

// 8 \\ 
Node* constructing_a_new_polynomial(Node* list);

int main() {
    ifstream in("input.txt");
    if (!in) cout << "error";
    ifstream in2("input2.txt");
    ofstream out("output.txt");
    int count_elem = 0;
    Node* list = create_list(in, count_elem);

    int count_elem_2 = 0;
    Node* list2 = create_list(in2, count_elem_2);


    int n, cf_cos, cf_sin;
    cout << "Enter the item to add(0 <= n <= " << count_elem + 1 << ", cf_cos != 0, cf_sin != 0): ";
    cin >> n >> cf_cos >> cf_sin;

    check_input(n, cf_cos, cf_sin, count_elem);

    add_elem(list, n, cf_cos, cf_sin, count_elem);



    cout << "Enter the serial number of the item to be deleted: ";
    cin >> n;
    delete_elem(list, n);



    finding_the_derivative_of_a_function(list);



    sum_of_polynomials(list, list2, count_elem, count_elem_2);



    int x;
    cout << "Enter dot: ";
    cin >> x;
    double value = calculating_the_value_at_a_point(list, x);
    cout << "Value at a point = " << value << endl;



    Node* new_polynomial = constructing_a_new_polynomial(list);



    output_list(out, new_polynomial);
    output_list(out, list);
    in.close();
    in2.close();
    out.close();
}

Node* create_list(ifstream& in, int& count_elem)
{

    Node* list = new Node;
    Node* top = list;
    list->next = NULL;

    while (!in.eof()) {
        list->next = new Node;
        list = list->next;
        list->next = NULL;
        in >> list->elem.n;
        in >> list->elem.cf_cos;
        in >> list->elem.cf_sin;
        count_elem++;
    }

    return top;
}

void output_list(ofstream& out, Node* list)
{
    list = list->next;
    while (list) {
        out << list->elem.n << " ";
        out << list->elem.cf_cos << " ";
        out << list->elem.cf_sin << " " << endl;
        Node* temp = list;
        list = list->next;
        delete temp;
    }
}

void check_input(int& n, int& cf_cos, int& cf_sin, int count_elem)
{
    while ((n < 0 || n > count_elem + 1) || cf_cos == 0 || cf_sin == 0) {
        cout << "Re-enter your details: ";
        cin >> n >> cf_cos >> cf_sin;
    }
}

void add_elem(Node* list, int n, int cf_cos, int cf_sin, int& count_elem)
{
    if (n == count_elem + 1) {
        while (list->next) list = list->next;
        list->next = new Node;
        list = list->next;
        list->next = NULL;
        list->elem.n = n;
        list->elem.cf_cos = cf_cos;
        list->elem.cf_sin = cf_sin;
        count_elem++;
    }
    else {
        for (int i = 0; i <= n; i++) {
            list = list->next;

        }
        list->elem.cf_cos = cf_cos;
        list->elem.cf_sin = cf_sin;
    }
}

void delete_elem(Node* list, int n)
{
    for (int i = 0; i < n; i++)
        list = list->next;

    Node* temp = list->next;
    list->next = list->next->next;
    delete temp;
}

void finding_the_derivative_of_a_function(Node* list)
{
    list = list->next; //перешли от болванчика к нулевому элементу
    list->elem.cf_cos = 0;//так как cos(0)=1, а sin(0)=0, то в многочлене первый элемент константа(к/ф перед cos) и ее производная равна 0

    list = list->next; // перешли к первому элементу
    while (list) {
        int temp = -list->elem.cf_cos * list->elem.n;
        list->elem.cf_cos = list->elem.cf_sin * list->elem.n;
        list->elem.cf_sin = temp;
        list = list->next;
    }
}

void sum_of_polynomials(Node* list1, Node* list2, int count_elem, int count_elem_2)
{
    list1 = list1->next;// перешли к нулевым элементам списка
    list2 = list2->next;


    if (count_elem != count_elem_2)
        cout << "Polynomials size are not equals!" << endl;
    else
        while (list1->next != NULL) {
            list1->elem.cf_cos += list2->elem.cf_cos;
            list1->elem.cf_sin += list2->elem.cf_sin;
            list1 = list1->next;
        }
}

double calculating_the_value_at_a_point(Node* list, int x)
{
    double value = 0;
    list = list->next;//переход к нулевому элементу многочлена

    while (list->next) {
        value += list->elem.cf_cos * cos(list->elem.n * x) + list->elem.cf_sin * sin(list->elem.n * x);
        /*cout << value << endl;*/
        list = list->next;
    }
    return value;
}

Node* constructing_a_new_polynomial(Node* list)
{
    Node* new_list = new Node;
    Node* top = new_list;

    list = list->next;

    while (list) {
        if (list->elem.cf_cos == 0 && list->elem.cf_sin == 0)
            list = list->next;
        else {
            new_list->next = new Node;
            new_list = new_list->next;
            new_list->next = NULL;
            new_list->elem.n = list->elem.n;
            new_list->elem.cf_cos = list->elem.cf_cos;
            new_list->elem.cf_sin = list->elem.cf_sin;
            list = list->next;
        }
    }

    return top;
}
