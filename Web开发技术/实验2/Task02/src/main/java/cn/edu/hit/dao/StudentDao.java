package cn.edu.hit.dao;

import cn.edu.hit.entity.Student;

import java.util.List;

public interface StudentDao {
    void modify(String sql);
    void insert(Student student);
    void update(Student student);
    void delete(String sid);
    List<Student> selectAll();
    List<Student> selectAll(String sql);
    Student selectBySid(String sid);
    List<Student> selectBySname(String str);
}
