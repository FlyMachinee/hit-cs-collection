#include "../Linear-list/src/MyList.hpp"
#include <iostream>
#include <string>
using namespace std;

class People
{
public:
    string name;
    string phone;
    string email;
    string address;

    People()
    {
        name = "No Name";
        phone = "No Phone";
        email = "No Email";
        address = "No Address";
    }

    People(string name, string phone, string email = "", string address = "")
    {
        this->name = name;
        this->phone = phone;
        this->email = email;
        this->address = address;
    }
    
    People operator=(const People &p)
    {
        name = p.name;
        phone = p.phone;
        email = p.email;
        address = p.address;
        return *this;
    }
};

ostream& operator<<(ostream &os, const People &p)
{
    os << "姓名: " << p.name << endl;
    os << "电话: " << p.phone << endl;
    os << "邮箱: " << p.email << endl;
    os << "地址: " << p.address << endl;
    return os;
}

class AddressBook
{
private:
    SeqList<People> data;

public:
    void add(string name, string phone, string email = "", string address = "")
    {
        data.push_back(People(name, phone, email, address));
    }

    void add(const People &p)
    {
        data.push_back(p);
    }

    void del_by_index(int index)
    {
        cout << "-------------------------------\n";
        cout << "已删除条目：\n";
        cout << data[index] << endl;
        data.remove(index);
        cout << "-------------------------------\n\n";
    }

    void del_by_name(string name)
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].name == name)
            {
                cout << "-------------------------------\n";
                cout << "已删除条目：\n";
                cout << data[i] << endl;
                data.remove(i);
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << name << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void del_by_phone(string phone)
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].phone == phone)
            {
                cout << "-------------------------------\n";
                cout << "已删除条目：\n";
                cout << data[i] << endl;
                cout << "-------------------------------\n\n";
                data.remove(i);
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << phone << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void alter_by_index(int index, string name, string phone, string email = "", string address = "")
    {
        cout << "-------------------------------\n";
        cout << "已修改条目：\n";
        cout << data[index] << endl;
        data[index].name = name;
        data[index].phone = phone;
        data[index].email = email;
        data[index].address = address;
        cout << "为：\n";
        cout << data[index] << endl;
        cout << "-------------------------------\n\n";
    }

    void alter_by_name(string goal_name, string name, string phone, string email = "", string address = "")
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].name == goal_name)
            {
                cout << "-------------------------------\n";
                cout << "已修改条目：\n";
                cout << data[i] << endl;
                data[i].name = name;
                data[i].phone = phone;
                data[i].email = email;
                data[i].address = address;
                cout << "为：\n";
                cout << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << goal_name << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void alter_by_phone(string goal_phone, string name, string phone, string email = "", string address = "")
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].phone == goal_phone)
            {
                cout << "-------------------------------\n";
                cout << "已修改条目：\n";
                cout << data[i] << endl;
                data[i].name = name;
                data[i].phone = phone;
                data[i].email = email;
                data[i].address = address;
                cout << "为：\n";
                cout << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << goal_phone << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void find_by_name(string name) const
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].name == name)
            {
                cout << "-------------------------------\n";
                cout << "已找到有关\"" << name << "\"的条目：\n";
                cout << "第" << i+1 << "个：\n" << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << name << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void find_by_phone(string phone) const
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].phone == phone)
            {
                cout << "-------------------------------\n";
                cout << "已找到有关\"" << phone << "\"的条目：\n";
                cout << "第" << i+1 << "个：\n" << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << phone << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void find_by_email(string email) const
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].email == email)
            {
                cout << "-------------------------------\n";
                cout << "已找到有关\"" << email << "\"的条目：\n";
                cout << "第" << i+1 << "个：\n" << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << email << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void find_by_address(string address) const
    {
        for (int i = 0; i < data.length(); i++)
        {
            if (data[i].address == address)
            {
                cout << "-------------------------------\n";
                cout << "已找到有关\"" << address << "\"的条目：\n";
                cout << "第" << i+1 << "个：\n" << data[i] << endl;
                cout << "-------------------------------\n\n";
                return;
            }
        }
        cout << "-------------------------------\n";
        cout << "未找到有关\"" << address << "\"的条目：\n";
        cout << "-------------------------------\n\n";
    }

    void print() const
    { 
        cout << "=====================================\n";
        cout << "通讯录成员：\n" << endl;
        for (int i = 0; i < data.length(); i++)
        {
            cout << "第" << i+1 << "个：\n" << data[i] << endl;
        }
        cout << "=====================================\n\n";
    }

    void sort_by_name()
    {
        for (int i = 0; i < data.length() - 1; i++)
        {
            for (int j = i + 1; j < data.length(); j++)
            {
                if (data[i].name > data[j].name)
                {
                    People temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

    void sort_by_phone()
    {
        for (int i = 0; i < data.length() - 1; i++)
        {
            for (int j = i + 1; j < data.length(); j++)
            {
                if (data[i].phone > data[j].phone)
                {
                    People temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }
};



int main()
{
    system("chcp 65001");
    People p1("张三", "13840072500", "zhangsan@pp.com", "上海");
    People p2("李四", "13901204800", "lisi@pp.com", "广州");
    People p3("王五", "13614853740", "wangwu@pp.com", "北京");

    AddressBook ab;

    ab.add(p1);
    ab.add(p2);
    ab.add(p3);
    ab.print();

    ab.del_by_name("李四");
    ab.print();

    ab.alter_by_name("王五", "李四", "13770742180", "lisi@qq.com", "上海");
    ab.print();

    ab.find_by_name("李四");
}