package cn.edu.hit.test;

import cn.edu.hit.dao.UsersDao;
import cn.edu.hit.dao.impl.UsersDaoImpl;
import cn.edu.hit.entity.User;

public class Hello {

    public static void main(String[] args) {
//        StudentDao dao = new StudentDaoImpl();
//
//        List<Student> li = dao.selectBySname("");
//        for (Student stu: li) {
//            System.out.print("stu.getSid() = " + stu.getSid() + " ");
//            System.out.println("stu.getSname() = " + stu.getSname());
//        }
        UsersDao dao = new UsersDaoImpl();
        System.out.println("dao.isExist(\"admin\") = " + dao.isExist("admin"));
        System.out.println("dao.isMatch(\"2022113573\", \"123456789\") = " + dao.isMatch(new User("2022113573", "123456789")));
        dao.insert(new User("apple", "alpine"));
    }

}
