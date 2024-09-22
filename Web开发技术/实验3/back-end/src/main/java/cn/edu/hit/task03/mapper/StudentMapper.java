package cn.edu.hit.task03.mapper;

import cn.edu.hit.task03.entity.Student;
import org.apache.ibatis.annotations.*;

import java.sql.Date;
import java.util.List;

@Mapper
public interface StudentMapper {
    @Insert("insert into student values (#{sid}, #{sname}, #{sgender}, #{sgrade}, #{sbirthdate}, #{sage})")
    void create(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage);
//
    @Delete("delete from student where sid=#{sid}")
    void remove(String sid);

    @Update("update student set sname = #{sname}, sgender = #{sgender}, sgrade = #{sgrade}, sbirthdate = #{sbirthdate}, sage = #{sage} where sid = #{sid}")
    void modify(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage);

    @Select("select * from student where sname like concat(concat('%',#{name},'%')) order by sid")
    List<Student> query(String name);
}
