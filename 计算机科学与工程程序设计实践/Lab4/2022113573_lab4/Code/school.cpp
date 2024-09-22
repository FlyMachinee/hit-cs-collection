#ifndef SCHOOL_CPP_INCLUDED
#define SCHOOL_CPP_INCLUDED

#include "main.hpp"
#include "school.hpp"
#include "student.hpp"

school::school()
{
	len = 0;
}

void school::append(const STUDENT& stu)
{
	students[len++] = stu;
}

void school::append()
{
	if (len >= MAX_SCHOOL)
		cout << "School is full! unable to add new student" << endl;
	else
	{
		cout << "Format: [ID] [name] [ics] [pdp] [ds] [dl]" << endl;
		char buf[128];
		cin.sync();
		cin.getline(buf, 128);
		STUDENT temp;
		if (6 != sscanf(buf, "%lu %s %f %f %f %f", &temp.stu_id, temp.stu_name, &temp.score[0], &temp.score[1], &temp.score[2], &temp.score[3]))
			cout << "Input format error!" << endl;
		else
		{
			append(temp);
			cout << "Append complete" << endl;
		}
	}
}

int school::find(const unsigned long ID)
{
	for (int i = 0; i < len; i++)
	{
		if (ID == students[i].stu_id)
			return i;
	}
	return -1;
}

int school::find(const char* name)
{
	for (int i = 0; i < len; i++)
	{
		if (0 == strcmp(name, students[i].stu_name))
			return i;
	}
	return -1;
}

void school::find_s(const unsigned long ID)
{
	int index = find(ID);
	if (index == -1)
		cout << "No student with the ID: " << ID << endl;
	else
	{
		show_title();
		show(students[index]);
	}
}

void school::find_s(const char* name)
{
	int index = find(name);
	if (index == -1)
		cout << "No student with the name: " << name << endl;
	else
	{
		show_title();
		show(students[index]);
	}
}

void school::show(const STUDENT& stu)
{
	char buf[128];
	cout << STUDENT_to_string(stu, buf) << endl;
}

void school::show()
{
	if (len > 0)
	{
		show_title();
		for (int i = 0; i < len; i++)
			show(students[i]);
	}
	else
		cout << "No student in school!" << endl;
}

void school::change(const unsigned long ID)
{
	int index = find(ID);
	if (index == -1)
		cout << "No student with the ID: " << ID << endl;
	else
	{
		STUDENT& stu = students[index];
		while (1)
		{
			cout << "Current student data:" << endl;
			show_title();
			show(stu);
			cout << "Please input the course and the score you want to change: [format: <course> <score>]" << endl;
			cout << "Input \"quit\" to exit the change method" << endl;

			char buf[128];
			float score;

			cin >> buf;
			if (0 == strcmp(buf, "quit"))
				break;
			cin >> score;

			while (cin.fail())
			{
				cin.clear();
				cin.sync();
				cout << "Format error, try again. [format: <course> <score>]" << endl;
				cin >> buf;
				if (0 == strcmp(buf, "quit"))
					break;
				cin >> score;
			}

			if (0 == strcmp(buf, "quit"))
				break;
			else if (0 == strcmp(buf, "ics"))
				stu.score[0] = score;
			else if (0 == strcmp(buf, "pdp"))
				stu.score[1] = score;
			else if (0 == strcmp(buf, "ds"))
				stu.score[2] = score;
			else if (0 == strcmp(buf, "dl"))
				stu.score[3] = score;
			else
				cout << "No course named \"" << buf << '\"' << endl;
		}
	}
}

void school::destory(const unsigned long ID)
{
	int index = find(ID);
	if (index == -1)
		cout << "No student with the ID: " << ID << endl;
	else
	{
		if (index != len - 1)
			for (int i = index; i < len - 1; i++)
				students[i] = students[i + 1];
		len--;
		cout << "Destory complete" << endl;
	}
}

void school::show_total_avg_by_stu()
{
	if (len > 0)
	{
		cout << "ID         name\ttotal\tavg" << endl; 
		for (int i = 0; i < len; i++)
		{
			float total = 0;
			STUDENT& stu = students[i];
			for (int j = 0; j < 4; j++)
				total += stu.score[j];
			cout << stu.stu_id << ' ' << stu.stu_name << '\t' << total << '\t' << total/4 << endl;
		}
	}
	else
		cout << "No student in school!" << endl;
}

void school::show_avg_by_course()
{
	if (len > 0)
	{
		cout << "ics\tpdp\tds\tdl" << endl; 
		float ics = 0, pdp = 0, ds = 0, dl = 0;
		for (int i = 0; i < len; i++)
		{
			STUDENT& stu = students[i];
			dl += stu.score[3];
			ds += stu.score[2];
			ics += stu.score[0];
			pdp += stu.score[1];
		}
		cout << ics/len << '\t' << pdp/len << '\t' << ds/len << '\t' << dl/len << endl;
	}
	else
		cout << "No student in school!" << endl;
}

int school::sort_by(const char* course)
{
	if (0 == strcmp(course, "ics"))
	{
		bubble_sort(students, len, descend_by_ics);
		return 0;
	}
	else if (0 == strcmp(course, "pdp"))
	{
		bubble_sort(students, len, descend_by_pdp);
		return 0;
	}
	else if (0 == strcmp(course, "ds"))
	{	
		bubble_sort(students, len, descend_by_ds);
		return 0;
	}
	else if (0 == strcmp(course, "dl"))
	{	
		bubble_sort(students, len, descend_by_dl);
		return 0;
	}
	else
	{
		cout << "No course named \"" << course << '\"' << endl;
		return -1;
	}
}

void school::analyze()
{
	if (len <= 0)
	{
		cout << "No student in school!" << endl;
		return;
	}
	
	const char* courses[] = {"ics", "pdp", "ds", "dl"};
	int stat[4][5] = {0};
	/*
	excellent: 90-100
	good: 80-89.5
	moderate: 70-79.5
	pass: 60-69.5
	failed: 0-59.5
	*/
	for (int i = 0; i < len; i++)
	{
		STUDENT& stu = students[i];
		for (int j = 0; j < 4; j++)
		{
			if (90 <= stu.score[j] && stu.score[j] <= 100)
				stat[j][0]++;
			else if (80 <= stu.score[j] && stu.score[j] < 90)
				stat[j][1]++;
			else if (70 <= stu.score[j] && stu.score[j] < 80)
				stat[j][2]++;
			else if (60 <= stu.score[j] && stu.score[j] < 70)
				stat[j][3]++;
			else
				stat[j][4]++;
		}
	}
	cout << "course\tex\tgood\tmoder\tpass\tfail" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << courses[i];
		for (int j = 0; j < 5; j++)
			cout << '\t' << stat[i][j];
		cout << endl;
	}

	cout << "\ncourse\tex\tgood\tmoder\tpass\tfail" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << courses[i];
		for (int j = 0; j < 5; j++)
			cout << '\t' << (stat[i][j] / (float)len) * 100 << '%';
		cout << endl;
	}
}

void school::save()
{
	FILE* pf = fopen("data.dat", "wb");
	write_to_binary(pf, students, len);
	fclose(pf);
}

void school::load()
{
	FILE* pf = fopen("data.dat", "rb");
	len = 0;
	read_from_binary(pf, students, len);
	fclose(pf);
}

#endif
