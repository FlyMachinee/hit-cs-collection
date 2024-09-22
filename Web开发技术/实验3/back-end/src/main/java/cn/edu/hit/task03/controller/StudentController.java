package cn.edu.hit.task03.controller;

import cn.edu.hit.task03.entity.Student;
import cn.edu.hit.task03.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/student")
@CrossOrigin
public class StudentController {

    @Autowired
    private StudentService studentService;

    @PostMapping("/create")
    public void create(@RequestBody Student student) {
        studentService.create(student.getSid(), student.getSname(), student.getSgender(), student.getSgrade(), student.getSbirthdate(), student.getSage());
    }

    @DeleteMapping("/remove")
    public void remove(String sid) {
        studentService.remove(sid);
    }

    @PutMapping("/modify")
    public void modify(@RequestBody Student student) {
        studentService.modify(student.getSid(), student.getSname(), student.getSgender(), student.getSgrade(), student.getSbirthdate(), student.getSage());
    }

    @GetMapping("/query")
    public List<Student> query(String name) {
        return studentService.query(name);
    }

}
