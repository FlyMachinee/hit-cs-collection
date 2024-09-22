#include "main.hpp"
#include "school.hpp"

int main()
{
    school hit = school();
    show_menu();
    bool exit_flag = false;
    char buf[128];
    unsigned long ID;
    cout << fixed << setprecision(1);
    while (! exit_flag)
    {
        int command = 0x3f3f3f3f;
        cout << "Please enter your choice: ";
        cin >> command;
	if (cin.fail())
	{
		cin.clear();
		cin.sync();
		command = 0x3f3f3f3f;
	}
        switch (command)
        {
        case -1://Show menu
            show_menu();
            break;
        
        case 0://Exit
            exit_flag = true;
            break;

        case 1://Append record
            hit.append();
            break;

        case 2://Search by name
            cout << "Input the goal name: ";
            cin >> buf;
            hit.find_s(buf);
            break;

        case 3://Search by ID
            ID = get_ID("Input the goal ID: ");
            hit.find_s(ID);
            break;

        case 4://Modify by ID
            ID = get_ID("Input the goal ID: ");
            hit.change(ID);
            break;

        case 5://Delete by ID
            ID = get_ID("Input the goal ID: ");
            hit.destory(ID);
            break;

        case 6://Caculate total and average score of every student
            hit.show_total_avg_by_stu();
            break;

        case 7://Caculate average score of every course
            hit.show_avg_by_course();
            break;

        case 8://Sort in descending order by course score
            cout << "Input the course name to sort: [ics/pdp/ds/dl]" << endl;
            cin >> buf;
            if (0 == hit.sort_by(buf))
                hit.show();
            break;

        case 9://Statistic analysis for every course
            hit.analyze();
            break;

        case 10://Save record
            hit.save();
            break;

        case 11://Load record
	    hit.load();
            break;

        case 12://Show all record
	    hit.show();
            break;

        default:
            cout << "Unknown command" << endl;
            break;
        }
    }
    return 0;
}


