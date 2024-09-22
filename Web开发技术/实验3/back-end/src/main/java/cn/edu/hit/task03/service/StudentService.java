package cn.edu.hit.task03.service;

import cn.edu.hit.task03.entity.Student;

import java.sql.Date;
import java.util.List;

public interface StudentService {
    void create(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage);
    void remove(String sid);
    void modify(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage);
    List<Student> query(String name);
}
