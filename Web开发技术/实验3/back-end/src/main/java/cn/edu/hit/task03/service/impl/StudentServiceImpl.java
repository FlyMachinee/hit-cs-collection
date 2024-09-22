package cn.edu.hit.task03.service.impl;

import cn.edu.hit.task03.entity.Student;
import cn.edu.hit.task03.mapper.StudentMapper;
import cn.edu.hit.task03.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.Date;
import java.util.List;

@Service
public class StudentServiceImpl implements StudentService {

    @Autowired
    private StudentMapper studentMapper;

    @Override
    public void create(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage) {
        studentMapper.create(sid, sname, sgender, sgrade, sbirthdate, sage);
    }

    @Override
    public void remove(String sid) {
        studentMapper.remove(sid);
    }

    @Override
    public void modify(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage) {
        studentMapper.modify(sid, sname, sgender, sgrade, sbirthdate, sage);
    }

    @Override
    public List<Student> query(String name) {
        return studentMapper.query(name);
    }
}
