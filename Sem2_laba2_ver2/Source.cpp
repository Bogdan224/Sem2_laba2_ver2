#include<iostream>
#include<ctime>
#include <Windows.h>
using namespace std;

struct StudyGroup {
    string name;
    string facult;
    int year;
    string level;
};

struct Item {
    StudyGroup* value;
    Item* right;
    Item* left;
};

StudyGroup* Init(string name, string facult, int year, string level) {
    StudyGroup* group = new StudyGroup();//(StudyGroup*)malloc(sizeof(StudyGroup)); 
    group->name = name;
    group->facult = facult;
    group->year = year;
    group->level = level;
    return group;
}

int GroupComparison(StudyGroup* g1, StudyGroup* g2) {
    if (g1->name == g2->name) return -1;
    else if (g1->name > g2->name) return 1;
    else if (g1->name < g2->name) return 0;
}
int GroupComparison(string g1, string g2) {
    if (g1 == g2) return -1;
    else if (g1 > g2) return 1;
    else if (g1 < g2) return 0;
}

void AddGroup(StudyGroup g1, StudyGroup g2) {
    g1.name = g2.name;
    g1.facult = g2.facult;
    g1.year = g2.year;
    g1.level = g2.level;
}

void Info(StudyGroup* group) {
    cout << "�������� ������: " << group->name << "\n����������� ��������: " << group->facult << "\n��� ������: " << group->year << "\n������� ����������: " << group->level << "\n\n";
}

void Insert(StudyGroup* val, Item** q)
{
    if (*q == NULL)
    {
        *q = (Item*)malloc(sizeof(Item));
        (*q)->left = (*q)->right = NULL;
        (*q)->value = (StudyGroup*)malloc(sizeof(StudyGroup));
        (*q)->value = val;
        return;
    }
    int i = GroupComparison((*q)->value, val);
    if (i == 1)
        Insert(val, &(*q)->left);
    if (i == 0)
        Insert(val, &(*q)->right);
    if (i == -1)
        return;

}

void PrintVos(Item* head) {
    if (head == NULL) {
        return;
    }

    PrintVos(head->left);
    Info(head->value);
    PrintVos(head->right);

}

void PrintUb(Item* head) {
    if (head == NULL) {
        return;
    }

    PrintUb(head->right);
    Info(head->value);
    PrintUb(head->left);
}

StudyGroup* Found(char* name, Item** q) {
    if (*q == NULL) return (*q)->value;

    int i = GroupComparison((*q)->value->name, name);
    if (i == 1)
        Found(name, &(*q)->left);
    if (i == 0)
        Found(name, &(*q)->right);
    if (i == -1)
        return (*q)->value;
}

int Delete(StudyGroup* key, Item** node) {
    Item* t, * up;
    system("cls");
    if (*node == NULL) return 0; // ��� ������ �������� � ������

    if (GroupComparison((*node)->value, key) == -1) {
        // ���� �������� ��������� � �����, �� ������� ����
        if (((*node)->left == NULL) && ((*node)->right == NULL)) {
            free(*node);
            *node = NULL;
            return 1;
        }
        if ((*node)->left == NULL) {
            t = *node;
            *node = (*node)->right;
            free(t);
            return 1;
        }
        if ((*node)->right == NULL) {
            t = *node;
            *node = (*node)->left;
            free(t);
            return 1;
        }
        up = *node;
        t = (*node)->left; // ���� � ����� ���������
        //���������� �� �������� ������� ����
        while (t->right != NULL) {
            up = t;
            t = t->right;
        }
        //�������� �������� �� ������� ���� ������ ���������� ��������
        (*node)->value = t->value;
        if (up != (*node)) {
            // ���� ������� ������ �� ����, �� ������������ ��� �� ������
            if (t->left != NULL) up->right = t->left;
            else up->right = NULL; // ������� ����
        }
        // ���� ���� ���������� ���� �������, ������� ����
        else (*node)->left = t->left;
        // ����������� ������ � ������� �������
        // ������ �������
        free(t);
        return 1;
    }
    if (GroupComparison((*node)->value, key) == 0)
        return Delete(key, &(*node)->right);
    return Delete(key, &(*node)->left);

}

void DeleteAll(Item*& root) {
    if (root == NULL) {
        return;
    }
    DeleteAll(root->left);
    DeleteAll(root->right);
    Delete(root->value, &root);
    root = NULL;
    
}

int Size(Item* head) {
    if (head == NULL) {
        return 1;
    }
    int N_r = 0, N_l = 0;
    if (head->left != NULL) {
        N_l = Size(head->left);
    }
    if (head->right != NULL) {
        N_r = Size(head->right);
    }
    return N_r + N_l + 1;
}



int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Item* it = NULL;

    StudyGroup* group= Init("���-214", "����", 2022, "��������");
    StudyGroup* group1=Init("���-213", "����", 2019, "��������");
    StudyGroup* group2=Init("���-25", "��", 2017, "�������");
    StudyGroup* group3=Init("��-124", "���", 2020, "��������");
    StudyGroup* group4=Init( "��-25", "����", 2018, "�������");

    Insert(group, &it);
    Insert(group1, &it);
    Insert(group2, &it);
    Insert(group3, &it);
    Insert(group4, &it);

    /*while (true) {
        char* name = (char*)malloc(sizeof(char));
        cout << "������� �������� ������: ";
        cin >> name;

        cout << "������� �������� ����������: ";
        char* facult = (char*)malloc(sizeof(char));
        cin >> facult;

        cout << "������� ��� �����������: ";
        int year;
        cin >> year;

        char* level = (char*)malloc(sizeof(char));
        cout << "������� �������(��������/�������): ";
        cin >> level;

        group = Init(name, facult, year, level);
        Insert(group, &it);
        cout << "����������?(1 - ��)" << endl;
        int a;
        cin >> a;
        if (a != 1) {
            break;
        }
    }*/

    PrintUb(it);
    cout << "\n" << "���-�� ���������: " << Size(it) << endl;

    char* name = (char*)malloc(sizeof(char));
    cout << "������� ������, ������� ������ ������� -> ";
    cin >> name;

    Delete(Found(name, &it), &it);
    PrintUb(it);
    system("pause");
    DeleteAll(it);
    PrintUb(it);

    return 0;
}