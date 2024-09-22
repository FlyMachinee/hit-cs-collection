#ifndef SCHOOL_HPP_INCLUDED
#define SCHOOL_HPP_INCLUDED

#define MAX_SCHOOL 100

class school
{
private:
	int len;
    	STUDENT students[MAX_SCHOOL];

	int find(const unsigned long ID);
	int find(const char* name);
public:
	school();
	void append(const STUDENT& stu);
	void append();
	void find_s(const unsigned long ID);
	void find_s(const char* name);
	static void show(const STUDENT& stu);
	void show();
	void change(const unsigned long ID);
	void destory(const unsigned long ID);
	void show_total_avg_by_stu();
	void show_avg_by_course();
	int sort_by(const char* course);
	void analyze();
	void save();
	void load();
};

#endif
